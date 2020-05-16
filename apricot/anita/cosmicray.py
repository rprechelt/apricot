"""
Simulate the geometric acceptance of ANITA to UHECRs.

The basic runflow for this Monte Carlo simulation is as follows:

  1. Generate random origin points on the surface of a spherical cap.
  2. Propagate these events until shower max.
  3. Check if ANITA is visible wihin a maximum view angle of shower max.
  4. If visible, save the event to disk.

We choose events from the full 4pi steradians - events that propagate
away from the Earth are automatically cut. We then use the number
of detected events to estimate the geometric acceptance.

"""
from typing import Optional, Union

import numpy as np
import pandas as pd

import apricot
import apricot.root
import apricot.geometry
import apricot.utils.parsing as parsing


def propagate(
    ntrials: int,
    filename: str,
    earth_model: str,
    earth_radius: Union[str, float],
    particle: str,
    min_energy: Optional[float],
    max_energy: Optional[float],
    fixed_energy: Optional[float],
    altitude: float,
    maxview: float,
    mode: str,
    **kwargs,
) -> None:
    """
    Simulate the geometric acceptance of ANITA to UHECR.

    Parameters
    ----------
    ntrials: int
        The number of particles (trials) to throw.
    filename: str
        The filename to save detections into.
    earth_model: str
        A string describing the Earth model to use.
    particle: str
        A string describing the particle to throw.
    min_energy: Optional[float]
        The optional minimum particle energy in log10(eV).
    max_energy: Optional[float]
        The optional maximum particle energy in log10(eV).
    fixed_energy: Optional[float]
        The optional fixed energy in log10(eV)
    altitude: float
        The detector altitude in kilometers.
    maxview: float
        The maximum detectable view angle in degrees.
    mode: str
        Whether to simulate 'direct', 'reflected', or 'both' event types.

    Returns
    -------
    events, parameters: Tuple[pd.DataFrame, pd.DataFrame]

    """

    # create an Earth model
    earth = parsing.create_earth(earth_model, earth_radius)

    # and add an ExponentialAtmosphere
    earth.add(apricot.ExponentialAtmosphere())

    # get the radius of the current Earth model at the pole
    Re = earth.radius(np.asarray([0, 0, -1.0]))

    # the location of the payload
    payload = np.asarray([0, 0, -(Re + altitude)])

    # the maximum geocentric Earth angle for a particle
    # to view ANITA with an Earth skimming view vector
    # is the sum of the respective horizon angles
    # this is 16.25 degrees for 100 km
    # or 20.33 degrees for 200 km
    theta = np.pi / 8.

    # we use a surface 150 km above the surface
    source_altitude = 150.0

    # we pick particles on a cap 100km above the surface
    source = apricot.SphericalCapSource(
        radius=Re + source_altitude, theta=theta, center=np.pi
    )

    # create a flux model that just creates (10^19) cosmic ray protons.
    flux = parsing.create_flux(particle, min_energy, max_energy, fixed_energy)

    # create a simple detector
    detector = apricot.OrbitalDetector(earth, payload, maxview, mode=mode)

    # make sure that the maximum altitude of the detector
    # is at least as high as the source altitude
    detector.maxalt = source_altitude + 1e-3

    # create a simple propagator
    propagator = apricot.SimplePropagator(earth)

    # and propagate a single particle
    interactions = propagator.propagate(source, flux, detector, ntrials)

    # the number of events we got
    Nevents = sum([len(I) for I in interactions])

    # if we didn't detect any events
    if Nevents == 0:
        print(f"Simulation did not detect any events...")
        return

    # get the area of the cap that we draw particle origins on
    area = earth.surface_area(center=np.pi, theta=theta, altitude=source_altitude)

    # we now start constructing the parameters that we save into the output file
    parameters = {
        "ntrials": ntrials,
        "nevents": Nevents,
        "particle": getattr(apricot, particle.capitalize())(0.0).id,
        "fixed_energy": fixed_energy,
        "min_energy": min_energy,
        "max_energy": max_energy,
        "altitude": altitude,
        "maxview": maxview,
        "Re": Re,
        "area": area,
        "maxtheta": theta,
        "source_altitude": source_altitude,
    }

    # and save the file to disk
    apricot.root.to_file(filename, interactions, parameters)

    # load the events and the parameters back from the file
    # so we have nice DataFrame's to work with
    events, parameters = apricot.root.from_file(filename)

    # and use these to calculate the geometric acceptance
    _ = geometric_acceptance(events, parameters)


def geometric_acceptance( events: pd.DataFrame, parameters: pd.DataFrame, delev:
                          float = 0.25, reflected: bool = False) -> Optional[pd.DataFrame]:
    """
    Compute the geometric acceptance in payload elevation bins
    given events stored in a DataFrame.

    `events` must have an `ntrials` instance member, and an `area`
    instance member.

    Parameters
    ----------
    events: pd.DataFrame
        A Panda's DataFrame containing the loaded events.
    parameters: pd.DataFrame
        The DataFrame containing the simulation parameters.
    delev: float
        The size of each payload elevation bin.

    Returns
    -------
    geometric_acceptance: pd.DataFrame
        A Panda's DataFrame containing the geometric acceptance.
    """

    # the area that we drew the particles from.
    A = np.mean(parameters.area)

    # the solid angle we drew the particles from
    Omega = 4 * np.pi

    # and the total number of particles that we flew
    ntrials = parameters.ntrials

    # the sum of dot(n, r) - we take the absolute value since
    # the particle normal in apricot is defined radially. However,
    # in the geometric acceptance integral, the normal is defined as
    # pointing in the direction of the detector (which is *opposite* our
    # direction of normal). Since any particles that point above the local
    # horizontal are cut by apricot, they will never be detected.
    weights = events.weight.abs()

    # now compute the total geometric acceptance
    acceptance = Omega * A * weights.sum() / ntrials.sum()

    # and print!
    print(f"Total Detected Events: {weights.shape[0]}")
    print(f"Total Geometric Acceptance: {acceptance:.02f} [km^2 sr]")

    # we also want to bin the acceptance into payload elevation bins

    # if we only have one event, then we can't produce a payload spectrum
    if events.shape[0] == 1:
        return None

    # construct a location for the payload
    payload = np.asarray([[0, 0, -(parameters.Re[0] + parameters.altitude[0])]])

    # so first calculate the payload elevation angles
    apricot.geometry.payload_elevation(events, payload, inplace=True, reflected=reflected)

    # the range of elevations we detector
    elevrange = np.abs(events.elevation.max() - events.elevation.min())

    # calculate the number of bins that we want
    nbins = int(round(elevrange / delev))

    # bin up the payload elevation angles - weight by the dot product
    count, edges = np.histogram(events.elevation, weights=weights, bins=nbins)

    # calculate the center of each histogram bin
    centers = (edges[:-1] + edges[1:]) / 2.0

    # and apply the acceptance scaling
    count *= Omega * A / ntrials.sum()

    # and create a Panda's data frame for the binned acceptance
    return pd.DataFrame({"elevation": centers, "acceptance": count})

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

    # use a smaller than default angle to choose source origins from
    # this is beyond the horizon for ANITA (37.5) viewing a spot
    # on a spherical cap at 100 km ASL
    theta = np.pi / 10.0

    # we use a surface 100 km above the surface
    source_altitude = 100.0

    # we pick particles on a cap 100km above the surface
    source = apricot.SphericalCapSource(
        radius=Re + source_altitude, theta=theta, center=np.pi
    )

    # create a flux model that just creates (10^19) cosmic ray protons.
    flux = parsing.create_flux(particle, min_energy, max_energy, fixed_energy)

    # create a simple detector
    detector = apricot.OrbitalDetector(earth, payload, maxview, mode=mode)

    # create a simple propagator
    propagator = apricot.SimplePropagator(earth)

    # and propagate a single particle
    interactions = propagator.propagate(source, flux, detector, ntrials)

    # the number of events we got
    Nevents = sum([len(I) for I in interactions])

    # we now start constructing the parameters that we save into the output file
    parameters = {
        "ntrials": ntrials,
        "nevents": Nevents,
        "particle": getattr(apricot, particle.capitalize())(0.).id,
        "fixed_energy": fixed_energy,
        "min_energy": min_energy,
        "max_energy": max_energy,
        "altitude": altitude,
        "maxview": maxview,
        "Re": Re,
        "maxtheta": theta,
        "source_altitude": source_altitude,
    }

    # and save the file to disk
    apricot.root.to_file(filename, interactions, parameters)

    # load the events and the parameters back from the file
    # so we have nice DataFrame's to work with
    events, parameters = apricot.root.from_file(filename)

    # and print a status message
    print(f"Detected {Nevents} events in {ntrials} trials.")



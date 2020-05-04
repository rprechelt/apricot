"""
Simulate the geometric acceptance of ANITA to UHECRs.
"""
from typing import Optional, Union

import numpy as np

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
    """

    # create an Earth model
    earth = parsing.create_earth(earth_model, earth_radius)

    # and add an ExponentialAtmosphere
    earth.add(apricot.ExponentialAtmosphere())

    # get the radius of the current Earth model at the pole
    Re = earth.radius(np.asarray([0, 0, -1.0]))

    # the location of the payload
    payload = np.asarray([0, 0, -(Re + altitude)])

    # we pick particles on a cap 100km above the surface
    source = apricot.SphericalCapSource(radius=Re + 100.0)

    # create a flux model that just creates (10^19) cosmic ray protons.
    flux = parsing.create_flux(particle, min_energy, max_energy, fixed_energy)

    # create a simple detector
    detector = apricot.OrbitalDetector(earth, payload, maxview, mode=mode)
    # detector = apricot.PerfectDetector()

    # create a simple propagator
    propagator = apricot.SimplePropagator(earth)

    # and propagate a single particle
    interactions = propagator.propagate(source, flux, detector, ntrials)

    # and save the file
    apricot.root.to_file(filename, interactions)

    # the number of events we got
    Nevents = sum([len(I) for I in interactions])

    # and print a status message
    print(f"Detected {Nevents} events in {ntrials} trials.")

"""
This module attempts a low-statistics run
for calculating the geometrical acceptance of
a balloon payload (like ANITA).
"""
import apricot
import numpy as np

def test_basic_geometric_acceptance():
    """
    Perform a basic test of the geometric
    cosmic ray acceptance of an ANITA-like mission to direct
    cosmic ray air showers.
    """

    # the radius that we use for the Earth model
    Re = apricot.SphericalEarth.polar_radius

    # use a simple spherical Earth model
    earth = apricot.SphericalEarth(Re)

    # we pick particles on a cap 100km above the surface
    source = apricot.SphericalCapSource(radius=Re + 100.)

    # create a flux model that just creates (10^19) cosmic ray protons.
    flux = apricot.FixedProtonFlux(19.)

    # place ANITA 37 km above the exact south pole
    location = np.asarray([0, 0, Re+35.])

    # we consider anything with 1.5 degrees of the shower axis detectable
    maxview = 1.5

    # create a simple detector
    detector = apricot.OrbitalDetector(earth, location, maxview, mode="direct")

    # create a simple propagator
    propagator = apricot.SimplePropagator(earth)

    # and propagate a single particle
    # interactions = propagator.propagate(source, flux, detector)

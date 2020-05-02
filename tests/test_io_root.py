"""
Test the ROOT I/O for apricot interactions.
"""

import apricot
import apricot.root
import numpy as np


def test_basic_io_root():
    """
    Propagate a couple of cosmic ray events
    and write them to a ROOT file.
    """

    # the number of events we propagate
    N = 10

    # and the energy that we propagate
    E = 19.0

    # the radius that we use for the Earth model
    Re = apricot.SphericalEarth.polar_radius

    # use a simple spherical Earth model
    earth = apricot.SphericalEarth(Re)

    # we pick particles on a cap 100km above the surface
    source = apricot.SphericalCapSource(radius=Re + 100.0)

    # create a flux model that just creates (10^19) cosmic ray protons.
    flux = apricot.FixedProtonFlux(E)

    # place ANITA 37 km above the exact south pole
    location = np.asarray([0, 0, Re + 35.0])

    # we consider anything with 1.5 degrees of the shower axis detectable
    maxview = 1.5

    # create a simple detector
    detector = apricot.OrbitalDetector(earth, location, maxview, mode="direct")

    # create a simple propagator
    propagator = apricot.SimplePropagator(earth)

    # and propagate a single particle
    interactions = propagator.propagate(source, flux, detector, N)

    # and write them to a file
    apricot.root.to_file("/tmp/interactions.root", interactions)

    # now creck that we can load the file as a dataframe
    df = apricot.root.as_pandas("/tmp/interactions.root")

    # a quick check on the number of events we got
    assert df.index.shape[0] <= N

    # and that the energy is correct
    np.testing.assert_allclose(df.energy, E)

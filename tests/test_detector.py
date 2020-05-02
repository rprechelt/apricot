"""
Perform some sanity tests on the various detector models.
"""
import apricot
import numpy as np


def test_create_perfect_detector():
    """
    Test that I can create PerfectDetectors
    """
    _ = apricot.PerfectDetector()


def test_create_orbital_detector():
    """
    Test that I can create OrbitalDetector's
    """

    # create a spherical Earth
    earth = apricot.SphericalEarth()

    # and a location
    location = np.asarray([0, 0, 7000.0])

    # and maxview angle
    maxview = 1.5

    # and create the orbital detector
    _ = apricot.OrbitalDetector(earth, location, maxview)


def test_energy_cut_detector():
    """
    Test that I can create EnergyCutDetector's
    """

    # and create the orbital detector
    _ = apricot.EnergyCutDetector(18.0, 21.0)

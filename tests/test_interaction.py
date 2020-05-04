"""
Various tests on the Interaction classes.
"""
import apricot
import numpy as np


def test_create_access():
    """
    Test that we can create and access interactions.
    """

    # the parameters of the event
    pdgid = 2212
    itype = 100
    energy = 18.5
    location = np.asarray([0, 0, 6000.0])
    direction = np.asarray([0, 1.0, 0.0])
    weight = 0.5
    altitude = 2.

    # create an interaction
    interaction = apricot.Interaction(pdgid, energy, itype, location, direction, weight, altitude)

    # and check that everything matches
    np.testing.assert_allclose(pdgid, interaction.pdgid)
    np.testing.assert_allclose(itype, interaction.type)
    np.testing.assert_allclose(energy, interaction.energy)
    np.testing.assert_allclose(location, interaction.location)
    np.testing.assert_allclose(direction, interaction.direction)
    np.testing.assert_allclose(weight, interaction.weight)
    np.testing.assert_allclose(altitude, interaction.altitude)

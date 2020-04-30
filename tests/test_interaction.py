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
    ntrials = 1
    pdgid = 2212
    itype = 100
    energy = 18.5
    location = np.asarray([0, 0, 6000.0])
    direction = np.asarray([0, 1.0, 0.0])

    # create an interaction
    interaction = apricot.Interaction(
        ntrials, pdgid, energy, itype, location, direction
    )

    # and check that everything matches
    np.testing.assert_allclose(ntrials, interaction.ntrials)
    np.testing.assert_allclose(pdgid, interaction.pdgid)
    np.testing.assert_allclose(itype, interaction.type)
    np.testing.assert_allclose(energy, interaction.energy)
    np.testing.assert_allclose(location, interaction.location)
    np.testing.assert_allclose(direction, interaction.direction)

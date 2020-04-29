"""
Perform basic tests on the charged lepton classes.
"""
import apricot
import numpy as np


def test_create_particles():
    """
    Test that we can create all the particles.
    """

    # choose a range of energies
    for E in np.linspace(18.0, 21.0, 10):

        # and create the three particles
        _ = apricot.Electron(E)
        _ = apricot.Muon(E)
        _ = apricot.Tau(E)

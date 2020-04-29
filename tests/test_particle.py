"""
Perform some basic tests on the Paricle class and infrastructure.
"""
import apricot
import numpy as np


def test_pdg():
    """
    Check that I can access all the PDG ID's
    """

    # electronic
    _ = apricot.pdg.Electron
    _ = apricot.pdg.ElectronNeutrino
    _ = apricot.pdg.Positron
    _ = apricot.pdg.AntiElectronNeutrino

    # muonic
    _ = apricot.pdg.Muon
    _ = apricot.pdg.MuonNeutrino
    _ = apricot.pdg.AntiMuon
    _ = apricot.pdg.AntiMuonNeutrino

    # tauonic
    _ = apricot.pdg.Tau
    _ = apricot.pdg.TauNeutrino
    _ = apricot.pdg.AntiTau
    _ = apricot.pdg.AntiTauNeutrino

    # pi's
    _ = apricot.pdg.PiZero
    _ = apricot.pdg.PiPlus
    _ = apricot.pdg.PiMinus

    # others
    _ = apricot.pdg.Proton
    _ = apricot.pdg.Neutron
    _ = apricot.pdg.Photon
    _ = apricot.pdg.Apricotino


def test_generations():
    """
    Check that I can access all the particle generations.
    """
    _ = apricot.Generation.Electron
    _ = apricot.Generation.Muon
    _ = apricot.Generation.Tau


def test_proton():
    """
    Perform various tests on the Proton class.
    """

    # check that I can create perotons
    for E in np.linspace(18.0, 21.0, 10):
        _ = apricot.Proton(E)

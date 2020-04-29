#include "apricot/Particle.hpp"
#include "apricot/particles/Neutrino.hpp"
#include "apricot/particles/Proton.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Particle(py::module& m) {

  // create a submodule to wrap PDG values
  auto pdg = m.def_submodule("pdg");
  pdg.attr("Electron") = pybind11::int_(PDG::Electron);
  pdg.attr("ElectronNeutrino") = pybind11::int_(PDG::ElectronNeutrino);
  pdg.attr("Positron") = pybind11::int_(PDG::Positron);
  pdg.attr("AntiElectronNeutrino") = pybind11::int_(PDG::AntiElectronNeutrino);
  pdg.attr("Muon") = pybind11::int_(PDG::Muon);
  pdg.attr("MuonNeutrino") = pybind11::int_(PDG::MuonNeutrino);
  pdg.attr("AntiMuon") = pybind11::int_(PDG::AntiMuon);
  pdg.attr("AntiMuonNeutrino") = pybind11::int_(PDG::AntiMuonNeutrino);
  pdg.attr("Tau") = pybind11::int_(PDG::Tau);
  pdg.attr("TauNeutrino") = pybind11::int_(PDG::TauNeutrino);
  pdg.attr("AntiTau") = pybind11::int_(PDG::AntiTau);
  pdg.attr("AntiTauNeutrino") = pybind11::int_(PDG::AntiTauNeutrino);
  pdg.attr("Proton") = pybind11::int_(PDG::Proton);
  pdg.attr("Neutron") = pybind11::int_(PDG::Neutron);
  pdg.attr("Photon") = pybind11::int_(PDG::Photon);
  pdg.attr("PiZero") = pybind11::int_(PDG::PiZero);
  pdg.attr("PiPlus") = pybind11::int_(PDG::PiPlus);
  pdg.attr("PiMinus") = pybind11::int_(PDG::PiMinus);
  pdg.attr("Apricotino") = pybind11::int_(PDG::Apricotino);


  // particle Generation
  py::enum_<Generation>(m, "Generation")
    .value("Electron", Generation::Electron)
    .value("Muon", Generation::Muon)
    .value("Tau", Generation::Tau);

  // Particle
  py::class_<Particle>(m, "Particle")
      .def_property("energy", &Particle::get_energy, &Particle::set_energy)
      .def("__repr__", [](const Particle& p) {
        return "Particle(" + std::to_string(p.get_energy()) + ")";
      });

  // Proton
  py::class_<Proton, Particle>(m, "Proton")
      .def(py::init<const double>())
      .def("__repr__", [](const Proton& p) {
        return "Proton(" + std::to_string(p.get_energy()) + ")";
      });

}

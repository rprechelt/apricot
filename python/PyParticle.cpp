#include "apricot/Particle.hpp"
#include "apricot/particles/Neutrino.hpp"
#include "apricot/particles/UHECR.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Particle(py::module& m) {

  // create a submodule to wrap PDG values
  auto pdg                         = m.def_submodule("pdg");
  pdg.attr("Electron")             = pybind11::int_(PDG::Electron);
  pdg.attr("ElectronNeutrino")     = pybind11::int_(PDG::ElectronNeutrino);
  pdg.attr("Positron")             = pybind11::int_(PDG::Positron);
  pdg.attr("AntiElectronNeutrino") = pybind11::int_(PDG::AntiElectronNeutrino);
  pdg.attr("Muon")                 = pybind11::int_(PDG::Muon);
  pdg.attr("MuonNeutrino")         = pybind11::int_(PDG::MuonNeutrino);
  pdg.attr("AntiMuon")             = pybind11::int_(PDG::AntiMuon);
  pdg.attr("AntiMuonNeutrino")     = pybind11::int_(PDG::AntiMuonNeutrino);
  pdg.attr("Tau")                  = pybind11::int_(PDG::Tau);
  pdg.attr("TauNeutrino")          = pybind11::int_(PDG::TauNeutrino);
  pdg.attr("AntiTau")              = pybind11::int_(PDG::AntiTau);
  pdg.attr("AntiTauNeutrino")      = pybind11::int_(PDG::AntiTauNeutrino);
  pdg.attr("Proton")               = pybind11::int_(PDG::Proton);
  pdg.attr("Neutron")              = pybind11::int_(PDG::Neutron);
  pdg.attr("Photon")               = pybind11::int_(PDG::Photon);
  pdg.attr("PiZero")               = pybind11::int_(PDG::PiZero);
  pdg.attr("PiPlus")               = pybind11::int_(PDG::PiPlus);
  pdg.attr("PiMinus")              = pybind11::int_(PDG::PiMinus);
  pdg.attr("Helium")               = pybind11::int_(PDG::Helium);
  pdg.attr("Nitrogen")             = pybind11::int_(PDG::Nitrogen);
  pdg.attr("Iron")                 = pybind11::int_(PDG::Iron);
  pdg.attr("Apricotino")           = pybind11::int_(PDG::Apricotino);

  // particle Generation
  py::enum_<Generation>(m, "Generation")
      .value("Electron", Generation::Electron)
      .value("Muon", Generation::Muon)
      .value("Tau", Generation::Tau);

  // Particle
  py::class_<Particle>(m, "Particle")
      .def_property("energy", &Particle::get_energy, &Particle::set_energy)
      .def_property_readonly("id", &Particle::get_id, "Get the particle PDG id.")
      .def("__repr__", [](const Particle& p) {
        return "Particle(" + std::to_string(p.get_energy()) + ")";
      });

  // Proton
  py::class_<Proton, Particle>(m, "Proton")
      .def(py::init<const double>())
      .def_static("get_Xmax", &Proton::get_Xmax, "Get the grammage at shower max [g/cm^2].")
      .def_static("get_Xmax",
                  py::vectorize(&Proton::get_Xmax),
                  "Get the grammage at shower max [g/cm^2].")
      .def("__repr__", [](const Proton& p) {
        return "Proton(" + std::to_string(p.get_energy()) + ")";
      });

  // Helium
  py::class_<Helium, Particle>(m, "Helium")
      .def(py::init<const double>())
      .def_static("get_Xmax", &Helium::get_Xmax, "Get the grammage at shower max [g/cm^2].")
      .def_static("get_Xmax",
                  py::vectorize(&Helium::get_Xmax),
                  "Get the grammage at shower max [g/cm^2].")
      .def("__repr__", [](const Helium& p) {
        return "Helium(" + std::to_string(p.get_energy()) + ")";
      });

  // Nitrogen
  py::class_<Nitrogen, Particle>(m, "Nitrogen")
      .def(py::init<const double>())
      .def_static("get_Xmax",
                  &Nitrogen::get_Xmax,
                  "Get the grammage at shower max [g/cm^2].")
      .def_static("get_Xmax",
                  py::vectorize(&Nitrogen::get_Xmax),
                  "Get the grammage at shower max [g/cm^2].")
      .def("__repr__", [](const Nitrogen& p) {
        return "Nitrogen(" + std::to_string(p.get_energy()) + ")";
      });

  // Iron
  py::class_<Iron, Particle>(m, "Iron")
      .def(py::init<const double>())
      .def_static("get_Xmax", &Iron::get_Xmax, "Get the grammage at shower max [g/cm^2].")
      .def_static("get_Xmax",
                  py::vectorize(&Iron::get_Xmax),
                  "Get the grammage at shower max [g/cm^2].")
      .def("__repr__",
           [](const Iron& p) { return "Iron(" + std::to_string(p.get_energy()) + ")"; });

  // MixedUHECR
  py::class_<MixedUHECR, Particle>(m, "MixedUHECR")
      .def(py::init<const double>())
      .def_static("get_Xmax",
                  &MixedUHECR::get_Xmax,
                  "Get the grammage at shower max [g/cm^2].")
      .def_static("get_Xmax",
                  py::vectorize(&MixedUHECR::get_Xmax),
                  "Get the grammage at shower max [g/cm^2].")
      .def("__repr__", [](const MixedUHECR& p) {
        return "MixedUHECR(" + std::to_string(p.get_energy()) + ")";
      });
}

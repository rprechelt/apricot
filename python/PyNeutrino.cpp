#include "apricot/Particle.hpp"
#include "apricot/particles/Neutrino.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Neutrino(py::module& m) {

    // Neutrino
  py::class_<Neutrino, Particle>(m, "Neutrino");

  // ElectronNeutrino
  py::class_<ElectronNeutrino, Neutrino>(m, "ElectronNeutrino")
    .def(py::init<const double>())
    .def_property_readonly("id", &ElectronNeutrino::get_id,
                           "Return the particle's PDG ID.")
    .def("__repr__",
        [](const ElectronNeutrino& p) {
            return "ElectronNeutrino(" + std::to_string(p.get_energy()) + ")";
        }
    );

  // MuonNeutrino
  py::class_<MuonNeutrino, Neutrino>(m, "MuonNeutrino")
    .def(py::init<const double>())
    .def_property_readonly("id", &MuonNeutrino::get_id,
                           "Return the particle's PDG ID.")
    .def("__repr__",
        [](const MuonNeutrino& p) {
            return "MuonNeutrino(" + std::to_string(p.get_energy()) + ")";
        }
    );

  // TauNeutrino
  py::class_<TauNeutrino, Neutrino>(m, "TauNeutrino")
    .def(py::init<const double>())
    .def_property_readonly("id", &TauNeutrino::get_id,
                           "Return the particle's PDG ID.")
    .def("__repr__",
        [](const TauNeutrino& p) {
            return "TauNeutrino(" + std::to_string(p.get_energy()) + ")";
        }
    );

}

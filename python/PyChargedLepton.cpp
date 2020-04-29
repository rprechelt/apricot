#include "apricot/Particle.hpp"
#include "apricot/particles/ChargedLepton.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_ChargedLepton(py::module& m) {

  // Charged leptons
  py::class_<ChargedLepton, Particle>(m, "ChargedLepton");

  // Electron
  py::class_<Electron, ChargedLepton>(m, "Electron")
    .def(py::init<const double>())
    .def_property_readonly("id", &Electron::get_id,
                           "Return the particle's PDG ID.")
    .def("__repr__",
        [](const Electron& p) {
            return "Electron(" + std::to_string(p.get_energy()) + ")";
        }
    );

  // Muon
  py::class_<Muon, ChargedLepton>(m, "Muon")
    .def(py::init<const double>())
    .def_property_readonly("id", &Muon::get_id,
                           "Return the particle's PDG ID.")
    .def("__repr__",
        [](const Muon& p) {
            return "Muon(" + std::to_string(p.get_energy()) + ")";
        }
    );

  // Tau
  py::class_<Tau, ChargedLepton>(m, "Tau")
    .def(py::init<const double>())
    .def_property_readonly("id", &Tau::get_id,
                           "Return the particle's PDG ID.")
    .def("__repr__",
        [](const Tau& p) {
            return "Tau(" + std::to_string(p.get_energy()) + ")";
        }
    );

}

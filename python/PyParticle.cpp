#include "apricot/Particle.hpp"
#include "apricot/particles/Proton.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Particle(py::module& m) {

  // Particle
  py::class_<Particle>(m, "Particle")
      .def_property("energy", &Particle::get_energy, &Particle::set_energy)
      .def("__repr__",
           [](const Particle& p) { return "Particle(" + std::to_string(p.get_energy()) + ")"; });

  // Particle
  py::class_<Proton, Particle>(m, "Proton")
      .def("__repr__",
           [](const Proton& p) { return "Proton(" + std::to_string(p.get_energy()) + ")"; });
}

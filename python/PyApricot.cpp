#include <pybind11/pybind11.h>

namespace py = pybind11;

// all of our module functions
void Py_Flux(py::module&);
void Py_PREM(py::module&);
void Py_Earth(py::module&);
void Py_Source(py::module&);
void Py_Particle(py::module&);
void Py_Detector(py::module &m);
void Py_Propagator(py::module&);
void Py_Interaction(py::module&);
void Py_Atmosphere(py::module&);

// create our Python module
PYBIND11_MODULE(_apricot, m) {

  // register the doc string
  m.doc() = ("Apricot is a library for propagating\n"
             "ultra-high-energy particles through the Earth into\n"
             "the Antarctic ice (and beyond!)");

  // the various modules
  Py_Earth(m); // Earth.hpp
  Py_Flux(m); // Flux.hpp
  Py_PREM(m); // PREM.hpp
  Py_Source(m); // Source.hpp
  Py_Particle(m); // Particle.hpp
  Py_Detector(m); // Detector.hpp
  Py_Propagator(m); // Propagator.hpp
  Py_Interaction(m); // Interaction.hpp
  Py_Atmosphere(m); // Atmosphere.hpp

}

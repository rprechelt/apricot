#include <pybind11/pybind11.h>
#include "apricot/Random.hpp"

namespace py = pybind11;

// all of our module functions
void Py_Flux(py::module&);
void Py_PREM(py::module&);
void Py_Earth(py::module&);
void Py_Source(py::module&);
void Py_Particle(py::module&);
void Py_Neutrino(py::module&);
void Py_Detector(py::module&);
void Py_Atmosphere(py::module&);
void Py_Propagator(py::module&);
void Py_Interaction(py::module&);
void Py_ChargedLepton(py::module&);
void Py_NeutrinoYFactor(py::module&);
void Py_NeutrinoCrossSection(py::module&);

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
  Py_Neutrino(m); // Neutrino.hpp
  Py_Detector(m); // Detector.hpp
  Py_Propagator(m); // Propagator.hpp
  Py_Interaction(m); // Interaction.hpp
  Py_Atmosphere(m); // Atmosphere.hpp
  Py_ChargedLepton(m); // ChargedLepton.hpp
  Py_NeutrinoYFactor(m); // NeutrinoYFactor.hpp
  Py_NeutrinoCrossSection(m); // NeutrinoCrossSection.hpp

  // and expose a function for changing the random number seed
  m.def("seed", &apricot::random::set_seed,
        py::arg("seed"),
        "Set the RNG seed.");

}

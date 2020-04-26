#include <pybind11/pybind11.h>

namespace py = pybind11;

// all of our module functions
void Py_Earth(py::module&);
void Py_PREM(py::module&);
void Py_Atmosphere(py::module&);

// create our Python module
PYBIND11_MODULE(_apricot, m) {

  // register the doc string
  m.doc() = ("Apricot is a library for propagating\n"
             "ultra-high-energy particles through the Earth into\n"
             "the Antarctic ice (and beyond!)");

  // the various modules
  Py_Earth(m); // Earth.hpp
  Py_PREM(m); // PREM.hpp
  Py_Atmosphere(m); // Atmosphere.hpp

}

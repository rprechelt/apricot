#include <pybind11/pybind11.h>
#include <pybind11/numpy.h> // add support for numpy
#include "apricot/earth/PREM.hpp"

namespace py = pybind11;
using namespace apricot;

///
/// \brief Initialize the Python bindings for PREM
///
void Py_PREM(py::module& m) {

  // create a submodule for PREM
  auto prem = m.def_submodule("PREM");

  // create a submodule for BREM
  prem.doc() = ("Calculate Earth densities (g/cm^3) using the "
                "Preliminary Earth Reference Model (PREM).");

  // method definitions
  prem.def("density", &PREM::density,
           py::arg("radius"), py::arg("r_earth") = 6356.755,
           "Return the density of the Earth at a radius (km).");
  prem.def("density", py::vectorize(&PREM::density),
           py::arg("radius"), py::arg("r_earth") = 6356.755,
           "Return the density of the Earth at many radii (km).");

}

#include "apricot/atmospheres/ExponentialAtmosphere.hpp"
#include <memory>
#include <pybind11/numpy.h> // add support for numpy
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Atmosphere(py::module& m) {

  // Earth
  py::class_<Atmosphere, std::shared_ptr<Atmosphere>>(m, "Atmosphere");

  // SphericalEarth
  py::class_<ExponentialAtmosphere, Atmosphere,
             std::shared_ptr<ExponentialAtmosphere>>(m, "ExponentialAtmosphere")
      .def(py::init<const double, const double>(),
           py::arg("rho0") = 1.225e-3,
           py::arg("T")    = 273,
           "Create an exponential atmosphere model.")
      .def("density",
           &ExponentialAtmosphere::density,
           py::arg("altitude"),
           "The density of the atmosphere at a given altitude [km].")
      .def("density",
           py::vectorize(&ExponentialAtmosphere::density),
           py::arg("altitudes"),
           "The density of the atmosphere at several altitudes [km].");
}

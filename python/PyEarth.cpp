#include "apricot/Coordinates.hpp"
#include "apricot/Earth.hpp"
#include "apricot/earth/SphericalEarth.hpp"
#include <pybind11/eigen.h> // add support for Eigen
#include <pybind11/numpy.h> // add support for numpy
#include <pybind11/pybind11.h>

#include <iostream>

namespace py = pybind11;
using namespace apricot;

void
Py_Earth(py::module& m) {

  // Earth
  py::class_<Earth>(m, "Earth")
      .def("density", &Earth::density, "The density of the Earth at a location [km].")
      .def(
          "density",
          [](const Earth& earth, const CartesianCoordinates& locations) -> Array {
            // create the output
            Array out(locations.rows());

            // loop over the dynamic number of rows
            for (int i = 0; i < locations.rows(); ++i) {
              out(i) = earth.density(locations.row(i));
            }

            // and return thee output vector
            return out;
          },
          "The density of the Earth at several locations [km].");

  // SphericalEarth
  py::class_<SphericalEarth, Earth>(m, "SphericalEarth")
    .def(py::init<const double>(), py::arg("radius") = SphericalEarth::POLAR,
         "Create a spherical Earth model.")
    .def("radius", &SphericalEarth::radius,
         "The radius of the Earth at a given location [km].")
    .def("cap_area", &SphericalEarth::cap_area,
         "The area of a cap centered at a location with a half-opening angle [km^2].")
      .def(
          "radius",
          [](const SphericalEarth& earth, const CartesianCoordinates& locations) -> Array {
            // create the output
            Array out(locations.rows());

            // loop over the dynamic number of rows
            for (int i = 0; i < locations.rows(); ++i) {
              out(i) = earth.radius(locations.row(i));
            }

            // and return thee output vector
            return out;
          },
          "The radius of the Earth at several locations [km].");

}

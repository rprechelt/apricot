#include "apricot/Atmosphere.hpp"
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
      .def("density",
           &Earth::density,
           py::arg("location"),
           "The density of the Earth at a location [km].")
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
          "The density of the Earth at several locations [km].")
      .def("add",
           py::overload_cast<const std::shared_ptr<Atmosphere>&>(&Earth::add),
           py::arg("atmosphere"),
           "Add an atmosphere model to this Earth model.");

  // SphericalEarth
  py::class_<SphericalEarth, Earth>(m, "SphericalEarth")
      .def(py::init<const double>(),
           py::arg("radius") = SphericalEarth::POLAR,
           "Create a spherical Earth model.")
      .def("radius",
           &SphericalEarth::radius,
           py::arg("location"),
           "The radius of the Earth at a given location [km].")
      .def("find_surface",
           &SphericalEarth::find_surface,
           py::arg("location"),
           py::arg("direction"),
           "Find the intersection of a ray with the Earth.")
      .def_readonly_static("polar_radius", &SphericalEarth::POLAR)
      .def_readonly_static("polar_curvature", &SphericalEarth::POLAR_CURVATURE)
      .def_readonly_static("equatorial_radius", &SphericalEarth::EQUATORIAL)
      .def_readonly_static("volumetric_radius", &SphericalEarth::VOLUMETRIC)
      .def("surface_area",
           &SphericalEarth::surface_area,
           py::arg("center"),
           py::arg("theta"),
           py::arg("altitude"),
           "Calculate the sssurface area of a spherical cap. [km^2].")
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

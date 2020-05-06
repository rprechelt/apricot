#include "apricot/Geometry.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h> // add support for Eigen
#include <pybind11/numpy.h> // add support for numpy
#include <pybind11/stl.h> // add support for C++ STL


namespace py = pybind11;
using namespace apricot;

void
Py_Geometry(py::module& m) {

  auto geometry = m.def_submodule("geometry");

  // add a docstring
  geometry.doc() = "Apricot-related geometry routines.";

  geometry.def("random_spherical_point",
               &random_spherical_point,
               "Return a random vector on the unit sphere.");
  geometry.def("spherical_cap_area",
               &spherical_cap_area,
               py::arg("theta"), py::arg("radius"),
               "Return the area of a spherical cap.");
  geometry.def("random_cap_point",
               &random_cap_point,
               py::arg("mintheta"),
               py::arg("maxtheta"),
               py::arg("minphi"),
               py::arg("maxphi"),
               "Return a random location on the surface of a spherical cap.");
  geometry.def("propagate_to_sphere",
               &propagate_to_sphere,
               py::arg("start"),
               py::arg("direction"),
               py::arg("radius"),
               "Propagate a vector to the surface of a sphere.");
  geometry.def("propagate_to_sphere",
               [](const Eigen::Matrix<double, Eigen::Dynamic, 3> start,
                  const Eigen::Matrix<double, Eigen::Dynamic, 3> direction,
                  const double radius) -> Eigen::Matrix<double, Eigen::Dynamic, 3> {

                 // get the number of rows in the input
                 const auto N{start.rows()};

                 // check that directions has the same number of rows
                 if (N != direction.rows()) {
                   throw std::invalid_argument("`start` and `direction` are different sizes!");
                 }

                 // create the output array
                 Eigen::Matrix<double, Eigen::Dynamic, 3> out(N, 3);

                 // get a reference to a quiet NaN
                 const auto nan{std::numeric_limits<double>::quiet_NaN()};

                 // loop over the number of input rows
                 for (int i = 0; i < N; ++i) {

                   // propagate this row to the surface
                   const auto surface{propagate_to_sphere(start.row(i), direction.row(i), radius)};

                   // if we got a surface hit, save it
                   // otherwise make sure it is zero
                   if (surface) {
                     out.row(i) = *surface;
                   }
                   else {
                     out.row(i) << nan, nan, nan;
                   }
                 }

                 // and return the surface points
                 return out;

               },
               py::arg("start"),
               py::arg("direction"),
               py::arg("radius"),
               "Propagate a vector to the surface of a sphere.");
  geometry.def("reflect_below",
               &reflect_below,
               py::arg("location"),
               py::arg("normal"));
}

#include "apricot/Source.hpp"
#include "apricot/sources/SphericalCapSource.hpp"
#include <pybind11/eigen.h> // add support for Eigen
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Source(py::module& m) {

  // the base FluxModel class
  py::class_<Source>(m, "Source");

  // sample points on the spherical cap
  py::class_<SphericalCapSource, Source>(m, "SphericalCapSource")
      .def(py::init<const double, const double, const double>(), py::arg("radius") = 6356.755,
           py::arg("theta") = M_PI / 16., py::arg("center") = (15. / 16.) * M_PI,
           "Sample origin points on a spherical cap.")
      .def("get_origin", &SphericalCapSource::get_origin,
           "Return a random origin and direction from the cap.")
      .def(
          "get_origins",
          [](const SphericalCapSource& source,
             const int N) -> std::pair<Eigen::Matrix<double, Eigen::Dynamic, 3>,
                                       Eigen::Matrix<double, Eigen::Dynamic, 3>> {
            // create the output arrays
            Eigen::Matrix<double, Eigen::Dynamic, 3> origins(N, 3);
            Eigen::Matrix<double, Eigen::Dynamic, 3> directions(N, 3);

            // loop over the number of requested random points
            for (int i = 0; i < N; ++i) {
              
              // get the origin and direction point
              auto [origin, direction]{source.get_origin()};

              // fill in the origin and direction
              origins.row(i)    = origin;
              directions.row(i) = direction;
              
            }

            // and return the output vector
            return std::make_pair(origins, directions);
          },
          "Return many random origins and directions from the cap.");
}

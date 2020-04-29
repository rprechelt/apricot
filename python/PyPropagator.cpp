#include "apricot/Propagator.hpp"
#include "apricot/propagators/SimplePropagator.hpp"
#include "apricot/Earth.hpp"
#include "apricot/Source.hpp"
#include "apricot/Flux.hpp"
#include "apricot/Detector.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Propagator(py::module& m) {

  // the base FluxModel class
  py::class_<Propagator>(m, "Propagator")
    .def("__repr__",
         [](const Propagator& self) -> std::string {
           return "Propagator()";
         });
      // .def("propagate",
      //      py::overload_cast<const Earth&,
      //      Source&,
      //      Flux&,
      //      const Detector&,
      //      const int>(&Propagator::propagate),
      //      "Propagate several particles to a detector.");

  py::class_<SimplePropagator>(m, "SimplePropagator")
    .def(py::init<const Earth&>())
    .def("propagate", &SimplePropagator::propagate,
         "Propagate a single particle to the detector.")
    .def("__repr__",
         [](const Propagator& self) -> std::string {
           return "SimplePropagator()";
         });
           // py::overload_cast<const Earth&,
           // Source&,
           // Flux&,
           // const Detector&,
           // const int>(&SimplePropagator::propagate),
           // "Propagate several particles to a detector.");
  //          [](const Propagator& propagator,
  //             const Earth& earth,
  //             Source& source,
  //             Flux& flux,
  //             const Detector& detector,
  //             const int N) -> Eigen::Array<double, Eigen::Dynamic, 10> {
  //            // the storage for the events
  //            Eigen::Array<double, Eigen::Dynamic, 10> events(N, 10);

  //            // propagate the events using the propagator
  //            const auto interactions{
  //                propagator.propagate(earth, source, flux, detector, N)};

  //            // loop over the events and add them to our array
  //            for
  //          });

  // sample points on the spherical cap
  // py::class_<SphericalCapSource, Source>(m, "SphericalCapSource")
  //     .def(py::init<const double, const double, const double>(), py::arg("radius") =
  //     6356.755,
  //          py::arg("theta") = M_PI / 16., py::arg("center") = (15. / 16.) * M_PI,
  //          "Sample origin points on a spherical cap.")
  //     .def("get_origin", &SphericalCapSource::get_origin,
  //          "Return a random origin and direction from the cap.")
  //     .def(
  //         "get_origins",
  //         [](const SphericalCapSource& source,
  //            const int N) -> std::pair<Eigen::Matrix<double, Eigen::Dynamic, 3>,
  //                                      Eigen::Matrix<double, Eigen::Dynamic, 3>> {
  //           // create the output arrays
  //           Eigen::Matrix<double, Eigen::Dynamic, 3> origins(N, 3);
  //           Eigen::Matrix<double, Eigen::Dynamic, 3> directions(N, 3);

  //           // loop over the number of requested random points
  //           for (int i = 0; i < N; ++i) {

  //             // get the origin and direction point
  //             auto [origin, direction]{source.get_origin()};

  //             // fill in the origin and direction
  //             origins.row(i)    = origin;
  //             directions.row(i) = direction;

  //           }

  //           // and return the output vector
  //           return std::make_pair(origins, directions);
  //         },
  //         "Return many random origins and directions from the cap.");
}

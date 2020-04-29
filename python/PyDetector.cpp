#include "apricot/Detector.hpp"
#include "apricot/detectors/OrbitalDetector.hpp"
#include "apricot/detectors/EnergyCutDetector.hpp"
#include "apricot/detectors/AntarcticDetector.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>

namespace py = pybind11;
using namespace apricot;


void Py_Detector(py::module &m) {

  // the base detector class.
  py::class_<Detector>(m, "Detector")
    .def("__repr__",
         [](const Detector& self) -> std::string {
           return "Detector()";
         });

  // EnergyCutDetector
  py::class_<EnergyCutDetector, Detector>(m, "EnergyCutDetector")
    .def(py::init<const double, const double>())
    .def("__repr__",
         [](const EnergyCutDetector& self) -> std::string {
           return "EnergyCutDetector()";
         });

  // OrbitalDetector
  py::class_<OrbitalDetector, Detector>(m, "OrbitalDetector")
    .def(py::init<const Earth&, const CartesianCoordinate&, const double, const std::string>(),
         py::arg("earth"), py::arg("location"), py::arg("maxview"), py::arg("mode") = "both")
    .def("__repr__",
         [](const OrbitalDetector& self) -> std::string {
           return "OrbitalDetector()";
         });

  // AntarcticDetector
  // py::class_<AntarcticDetector, EnergyCutDetector>(m, "AntarcticDetector")
  //   .def(py::init<const Earth&,
  //        const double, const double, const double, const double>(),
  //        py::arg("earth"),
  //        py::arg("max_depth") = 3., py::arg("max_altitude") = 37.,
  //        py::arg("min_energy") = 16., py::arg("max_energy") = 21.);

}

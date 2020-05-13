#include "apricot/Detector.hpp"
#include "apricot/detectors/EnergyCutDetector.hpp"
#include "apricot/detectors/OrbitalDetector.hpp"
#include "apricot/detectors/PerfectDetector.hpp"

#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Detector(py::module& m) {

  // the base detector class.
  py::class_<Detector>(m, "Detector")
      .def("__repr__", [](const Detector& self) -> std::string { return "Detector()"; });

  // EnergyCutDetector
  py::class_<EnergyCutDetector, Detector>(m, "EnergyCutDetector")
      .def(py::init<const double, const double>())
      .def("__repr__", [](const EnergyCutDetector& self) -> std::string {
        return "EnergyCutDetector()";
      });

  // OrbitalDetector
  py::class_<OrbitalDetector, Detector>(m, "OrbitalDetector")
      .def(py::init<const Earth&,
                    const CartesianCoordinate&,
                    const double,
                    const std::string>(),
           py::arg("earth"),
           py::arg("location"),
           py::arg("maxview"),
           py::arg("mode") = "both")
      .def("view_angle",
           &OrbitalDetector::view_angle,
           "Calculate the view angle from the event [radians].")
      .def("payload_angle",
           &OrbitalDetector::payload_angle,
           "Calculate the payload elevation angle of the event [radians].")
      .def_property("maxalt", &OrbitalDetector::get_maxalt, &OrbitalDetector::set_maxalt)
      .def_property("maxview", &OrbitalDetector::get_maxview, &OrbitalDetector::set_maxview)
      .def_property("cutangle",
                    &OrbitalDetector::get_cutangle,
                    &OrbitalDetector::set_cutangle)
      .def_property("backwards",
                    &OrbitalDetector::get_backwards,
                    &OrbitalDetector::set_backwards)
      .def("__repr__",
           [](const OrbitalDetector& self) -> std::string { return "OrbitalDetector()"; });

  // PerfectDetector
  py::class_<PerfectDetector, Detector>(m, "PerfectDetector")
      .def(py::init<>())
      .def("__repr__",
           [](const PerfectDetector& self) -> std::string { return "PerfectDetector()"; });
}

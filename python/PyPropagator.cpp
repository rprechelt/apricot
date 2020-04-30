#include "apricot/Detector.hpp"
#include "apricot/Earth.hpp"
#include "apricot/Flux.hpp"
#include "apricot/Propagator.hpp"
#include "apricot/Source.hpp"
#include "apricot/propagators/SimplePropagator.hpp"

#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Propagator(py::module& m) {

  // the base FluxModel class
  py::class_<Propagator>(m, "Propagator")
      .def("__repr__",
           [](const Propagator& self) -> std::string { return "Propagator()"; });

  py::class_<SimplePropagator, Propagator>(m, "SimplePropagator")
      .def(py::init<const Earth&>())
      .def("propagate",
           py::overload_cast<Source&, Flux&, const Detector&>(&SimplePropagator::propagate,
                                                              py::const_),
           "Propagate a single particle to the detector.")
      .def("propagate",
           py::overload_cast<Source&, Flux&, const Detector&, const int>(
               &Propagator::propagate, py::const_),
           "Propagate several particles to a detector.")
      .def("__repr__", [](const SimplePropagator& self) -> std::string {
        return "SimplePropagator()";
      });
}

#include "apricot/Interaction.hpp"
#include "apricot/Particle.hpp"
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Interaction(py::module& m) {

  // Interaction
  py::class_<Interaction>(m, "Interaction")
      .def(py::init<const ParticleID,
                    const LogEnergy,
                    const InteractionType,
                    const CartesianCoordinate&,
                    const Vector&,
                    const double,
                    const double>())
      .def_readonly("pdgid", &Interaction::pdgid_)
      .def_readonly("energy", &Interaction::energy_)
      .def_readonly("type", &Interaction::type_)
      .def_readonly("location", &Interaction::location_)
      .def_readonly("direction", &Interaction::direction_)
      .def_readonly("weight", &Interaction::weight_)
      .def_readonly("altitude", &Interaction::altitude_);
}

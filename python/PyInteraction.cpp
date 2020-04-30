#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>
#include "apricot/Interaction.hpp"
#include "apricot/Particle.hpp"

namespace py = pybind11;
using namespace apricot;

void Py_Interaction(py::module& m) {

  // Interaction
  py::class_<Interaction>(m, "Interaction")
    .def(py::init<const int,
         const ParticleID,
         const LogEnergy,
         const InteractionType,
         const CartesianCoordinate&,
         const Vector&>())
    .def_readonly("ntrials", &Interaction::ntrials_)
    .def_readonly("pdgid", &Interaction::pdgid_)
    .def_readonly("energy", &Interaction::energy_)
    .def_readonly("type", &Interaction::type_)
    .def_readonly("location", &Interaction::location_)
    .def_readonly("direction", &Interaction::direction_);

}

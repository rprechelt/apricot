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
         const LogEnergy,
         const ParticleID,
         const InteractionType,
         const CartesianCoordinate&,
         const Vector&>());

}

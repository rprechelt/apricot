#include "apricot/Flux.hpp"
#include "apricot/particles/Proton.hpp"
#include "apricot/fluxes/FixedParticleFlux.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Flux(py::module& m) {

  // the base Flux class
  py::class_<Flux>(m, "Flux");

  // // a fixed particle and energy for
  py::class_<FixedParticleFlux<Proton>>(m, "FixedProtonFlux")
    .def(py::init<const double>(),
         "Create a FixedProtonFlux at an energy in log10(eV).")
    .def("get_particle", &FixedParticleFlux<Proton>::get_particle,
         "Return a randomly sampled particle from this flux model.");

}

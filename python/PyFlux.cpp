#include "apricot/Flux.hpp"
#include "apricot/particles/UHECR.hpp"
#include "apricot/fluxes/FixedParticleFlux.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace apricot;

void
Py_Flux(py::module& m) {

  // the base Flux class
  py::class_<Flux>(m, "Flux");

  // a fixed particle and energy for proton
  py::class_<FixedParticleFlux<Proton>, Flux>(m, "FixedProtonFlux")
    .def(py::init<const double>(),
         "Create a FixedProtonFlux at an energy in log10(eV).")
    .def("get_particle", &FixedParticleFlux<Proton>::get_particle,
         "Return a randomly sampled particle from this flux model.");

  // a fixed particle and energy for helium
  py::class_<FixedParticleFlux<Helium>, Flux>(m, "FixedHeliumFlux")
    .def(py::init<const double>(),
         "Create a FixedHeliumFlux at an energy in log10(eV).")
    .def("get_particle", &FixedParticleFlux<Helium>::get_particle,
         "Return a randomly sampled particle from this flux model.");

  // a fixed particle and energy for nitrogen
  py::class_<FixedParticleFlux<Nitrogen>, Flux>(m, "FixedNitrogenFlux")
    .def(py::init<const double>(),
         "Create a FixedNitrogenFlux at an energy in log10(eV).")
    .def("get_particle", &FixedParticleFlux<Nitrogen>::get_particle,
         "Return a randomly sampled particle from this flux model.");

  // a fixed particle and energy for iron
  py::class_<FixedParticleFlux<Iron>, Flux>(m, "FixedIronFlux")
    .def(py::init<const double>(),
         "Create a FixedIronFlux at an energy in log10(eV).")
    .def("get_particle", &FixedParticleFlux<Iron>::get_particle,
         "Return a randomly sampled particle from this flux model.");

}

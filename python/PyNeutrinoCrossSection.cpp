#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "apricot/particles/NeutrinoCrossSection.hpp"

namespace py = pybind11;
using namespace apricot;

void Py_NeutrinoCrossSection(py::module& m) {

  // create a submodule for cross sections
  auto CS = m.def_submodule("neutrino_cross_section");
  CS.doc() = "Calculate UHE neutrino cross sections.";

  // NeutrinoCrossSectionModel
  py::enum_<NeutrinoCrossSectionModel>(CS, "NeutrinoCrossSectionModel")
    .value("ConnollyLower", NeutrinoCrossSectionModel::ConnollyLower)
    .value("ConnollyMiddle", NeutrinoCrossSectionModel::ConnollyMiddle)
    .value("ConnollyUpper", NeutrinoCrossSectionModel::ConnollyUpper)
    .value("Gorham", NeutrinoCrossSectionModel::Gorham);

  // charged current
  CS.def("charged_current", &charged_current,
         "Calculate the charged current neutrino cross section "
         " [log10(g/cm^2)] at an energy in [log10(eV)]");
  CS.def("charged_current", py::vectorize(&charged_current),
         "Calculate the charged current neutrino cross section "
         " [log10(g/cm^2)] at energies in [log10(eV)]");

  // neutral current
  CS.def("neutral_current", &neutral_current,
         "Calculate the neutral current neutrino cross section "
         " [log10(g/cm^2)] at an energy in [log10(eV)]");
  CS.def("neutral_current", py::vectorize(&neutral_current),
         "Calculate the neutral current neutrino cross section "
         " [log10(g/cm^2)] at energies in [log10(eV)]");


}

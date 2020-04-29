#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "apricot/particles/NeutrinoYFactor.hpp"

namespace py = pybind11;
using namespace apricot;

void Py_NeutrinoYFactor(py::module& m) {

  // create a namespace yfactor to store this in
  auto yfactor = m.def_submodule("neutrino_yfactor");

  // YFactorModel
  py::enum_<NeutrinoYFactorModel>(m, "NeutrinoYFactorModel")
    .value("BDHM", NeutrinoYFactorModel::BDHM)
    .value("Soyez", NeutrinoYFactorModel::Soyez)
    .value("ALLM", NeutrinoYFactorModel::ALLM);

  // and the evaluation function
  yfactor.def("y_factor", &y_factor,
              "Calculate the average neutrino y-factor at an energy in log10(eV).");
  yfactor.def("y_factor", // vectorize over energy
    [](py::array_t<double> energy, NeutrinoYFactorModel& model) {
      return py::vectorize([model](const double E) { return y_factor(E, model); })(energy);
    }, "Calculate the average neutrino y-factor several energies in log10(eV).");

}

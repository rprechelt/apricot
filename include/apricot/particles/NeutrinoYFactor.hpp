#pragma once

#include "apricot/Apricot.hpp"

namespace apricot {

  ///
  /// \brief The various y-factor models.
  ///
  enum class NeutrinoYFactorModel { BDHM, Soyez, ALLM };

  ///
  /// \brief Evaluate the y-factor for a neutrino.
  ///
  /// Using the energy, and a specific y-factor model,
  /// this evaluates a parametrization of the neutrino y-factor.
  /// These are taken from arXiv::1704.00050.
  ///
  /// @param energy    The energy in log10(eV).
  /// @param model     The neutrino y-factor model to use.
  ///
  auto
  y_factor(const LogEnergy energy, const NeutrinoYFactorModel &model) -> double;

} // namespace apricot

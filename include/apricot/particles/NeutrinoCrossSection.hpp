#pragma once

#include "apricot/Apricot.hpp"
#include "apricot/Particle.hpp"

namespace apricot {

  /**
   * An alias for log10(g/cm^2)
   */
  using LogGrammage = double;

  ///
  /// \brief Neutrino Cross Section Models
  ///
  /// Connoly{Lower, Middle, Upper} are from arXiv:1707.00334v4
  /// Gorham is a straight lift from PG's original UHMC
  ///
  enum class NeutrinoCrossSectionModel {
    ConnollyLower,
    ConnollyMiddle,
    ConnollyUpper,
    Gorham
  };

  ///
  /// \brief Get the charged current cross section at an energy in log10(eV).
  ///
  /// NOTE: This returns the cross-section in log10(g/cm^2).
  ///
  auto __attribute__((hot)) charged_current(const NeutrinoCrossSectionModel model,
                                            const LogEnergy energy) -> LogGrammage;

  ///
  /// \brief Calculate the neutral current cross section at an energy in
  /// log10(eV).
  ///
  /// NOTE: This returns the cross-section in log10(g/cm^2).
  ///
  auto __attribute__((hot)) neutral_current(const NeutrinoCrossSectionModel model,
                                            const LogEnergy energy) -> LogGrammage;

} // namespace apricot

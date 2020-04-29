#pragma once

#include "apricot/Coordinates.hpp"
#include "apricot/Detector.hpp"
#include "apricot/Earth.hpp"
#include "apricot/Interaction.hpp"

namespace apricot {

  /* Forward declarations */
  class InteractionInfo;
  class Particle;

  /**
   * A detector that only accepts a range of energies.
   *
   */
  class EnergyCutDetector : public Detector {

    public:
    /**
     * Construct a detector to accept energies between min_energy and max_energy.
     */
    EnergyCutDetector(const double min_energy, const double max_energy)
        : min_energy_(min_energy), max_energy_(max_energy){};

    /**
     * Return True if a particle should be saved.
     */
    virtual auto
    detectable(const InteractionInfo& info,
               const std::unique_ptr<Particle>& particle,
               const CartesianCoordinate& location,
               const CartesianCoordinate& direction) const -> bool override;

    /**
     * True if an interaction should be cut during propagation.
     */
    virtual auto
    cut(const std::unique_ptr<Particle>& particle,
        const CartesianCoordinate& location,
        const CartesianCoordinate& direction) const -> bool override;

    protected:
    /**
     * Check if an energy [log10(eV)] is within range.
     */
    auto
    has_valid_energy(const std::unique_ptr<Particle>& particle) const -> bool;

    /**
     * The minimum energy we accept in log10(eV).
     */
    const double min_energy_;

    /**
     * The maximum energy we accept in log10(eV).
     */
    const double max_energy_;

  }; // END: class EnergyCutDetector

} // namespace apricot

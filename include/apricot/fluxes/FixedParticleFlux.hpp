#pragma once

#include "apricot/Flux.hpp"
#include <memory>

namespace apricot {

  /* Forward declarations */
  class Particle;

  /* An alias for energies in log10(eV) */
  using LogEnergy = double;

  /**
   * Produce a pure flux of one particle type at fixed energy.
   *
   * The template argument specifies the particle type
   * that is generated at each trial.
   *
   */
  template <typename ParticleType> class FixedParticleFlux final : public Flux {

    public:
    /**
     * The fixed particle energy in log10(eV).
     */
    const LogEnergy energy_;

    /**
     * Sample a fixed particle species at fixed energy.
     */
    FixedParticleFlux(const LogEnergy energy) : energy_(energy){};

    /**
     * Return the next particle from this flux model.
     */
    auto
    get_particle() const -> std::unique_ptr<Particle> final override {
      return std::make_unique<ParticleType>(this->energy_);
    }

    /**
     * A virtual destructor.
     */
    virtual ~FixedParticleFlux() = default;

  }; // END: class Flux

} // namespace apricot

#pragma once

#include "apricot/Flux.hpp"
#include "apricot/Random.hpp"
#include <memory>

namespace apricot {

  /* Forward declarations */
  class Particle;

  /* An alias for energies in log10(eV) */
  using LogEnergy = double;

  /**
   * Produce a flux of one particle type uniformly in log-space energy
   *
   * The template argument specifies the particle type
   * that is generated at each trial.
   *
   */
  template <typename ParticleType> class UniformParticleFlux final : public Flux {

    public:
    /**
     * The minimum particle energy in log10(eV).
     */
    const LogEnergy min_energy_;

    /**
     * The maximum particle energy in log10(eV).
     */
    const LogEnergy max_energy_;

    /**
     * Sample a fixed particle species at fixed energy.
     */
    UniformParticleFlux(const LogEnergy min_energy, const LogEnergy max_energy) :
        min_energy_(min_energy),
        max_energy_(max_energy){};

    /**
     * Return the next particle from this flux model.
     */
    auto
    get_particle() const -> std::unique_ptr<Particle> final override {

      // choose a random energy
      const LogEnergy energy{random::uniform(min_energy_, max_energy_)};

      // and create the particle
      return std::make_unique<ParticleType>(energy);
    }

    /**
     * A virtual destructor.
     */
    virtual ~UniformParticleFlux() = default;

  }; // END: class Flux

} // namespace apricot

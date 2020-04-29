#pragma once

#include "apricot/Particle.hpp"
#include <memory>

namespace apricot {

  /*
   * A cosmic ray proton.
   */
  class Proton final : public Particle {

    public:
    /**
     * Construct a particle from an energy in log10(eV).
     */
    Proton(const double energy) : Particle(energy){};

    /**
     * Get the proton PDG ID.
     */
    auto
    get_id() const -> ParticleID {
      return PDG::Proton;
    }

    /**
     * Return a new pointer to a concrete instance.
     */
    auto
    clone() const -> std::unique_ptr<Particle> {
      return std::make_unique<Proton>(energy_);
    }

  }; // END: class Proton

} // namespace apricot

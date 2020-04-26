#pragma once

#include <memory>

namespace apricot {

  /**
   * An abstract class representing all particles.
   */
  class Particle {

    public:
    
    /**
     * Construct a particle from an energy in log10(eV).
     */
    Particle(const double energy) : energy_(energy) {};

    /**
     * Get the particle energy in log10(eV).
     **/
    auto
    get_energy() const -> double {
      return energy_;
    };

    /**
     *  Set the particle energy in log10(eV).
     */
    auto
    set_energy(const double energy) -> void {
      energy_ = energy;
    };

    /**
     * Return a new pointer to a concrete instance.
     */
    virtual auto
    clone() const -> std::unique_ptr<Particle> = 0;

    /*
     * The energy of the particle [log10(eV)].
     */
    double energy_;

    /**
     *  A virtual destructor so this class is abstract.
     */
    virtual ~Particle() = default;

  }; // END: class Particle

} // namespace apricot

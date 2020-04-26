#pragma once

#include <memory>

namespace apricot {

  /* Forward declarations */
  class Particle;

  /**
   * The pure base for all Flux models.
   *
   * Flux models are responsible for choosing particles
   * to simulate (both in energy and in particle species).
   *
   */
  class Flux {

    public:
    /**
     * Return the next particle from this flux model.
     */
    virtual auto
    get_particle() const -> std::unique_ptr<Particle> = 0;

    /**
     * A virtual destructor.
     */
    virtual ~Flux() = default;

  }; // END: class Flux

} // namespace apricot

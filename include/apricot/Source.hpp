#pragma once

#include "apricot/Coordinates.hpp"

namespace apricot {

  /**
   * A pure base class for all particle sources.
   *
   */
  class Source {

    public:
    /**
     * Return a random particle origin and direction.
     *
     * @returns The starting location of the particle.
     * @returns The unit momentum vector of the particle.
     *
     */
    virtual auto
    get_origin() const -> std::pair<CartesianCoordinate, Vector> = 0;

    /**
     * A virtual destructor.
     *
     */
    virtual ~Source() = default;

  }; // END: class Source

} // namespace apricot

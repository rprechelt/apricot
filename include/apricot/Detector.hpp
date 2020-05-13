#pragma once

#include "apricot/Coordinates.hpp"
#include <memory>

namespace apricot {

  /* Forward declarations */
  class InteractionInfo;
  class Particle;

  /**
   * A pure base class for particle detectors.
   */
  class Detector {

    public:
    /**
     * True if an interaction is detectable and should be saved.
     */
    virtual auto
    detectable(const InteractionInfo& info,
               const std::unique_ptr<Particle>& particle,
               const CartesianCoordinate& location,
               const CartesianCoordinate& direction) const -> bool = 0;

    /**
     * True if an interaction should be cut during propagation.
     */
    virtual auto
    cut(const std::unique_ptr<Particle>& particle,
        const CartesianCoordinate& location,
        const CartesianCoordinate& direction) const -> bool {
      return false;
    }

    /**
     * Check if a source particle and direction is valid.
     *
     * This is called *once* when the source particle and direction
     * is sampled from the source+flux. This allows for cutting particles
     * before they are propagated at all.
     */
    virtual auto
    is_good(const std::unique_ptr<Particle>& particle,
            const CartesianCoordinate& location,
            const CartesianCoordinate& direction) const -> bool {
      return true;
    }

    /**
     * A virtual destructor.
     */
    virtual ~Detector() = default;

  }; // END: Detector

} // namespace apricot

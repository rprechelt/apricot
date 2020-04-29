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
        const CartesianCoordinate& direction) const -> bool { return false; }

    ///
    /// \brief A virtual destructor.
    ///
    virtual ~Detector() = default;

  }; // END: Detector

} // namespace apricot

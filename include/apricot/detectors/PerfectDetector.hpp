#pragma once

#include "apricot/Detector.hpp"
#include <memory>

namespace apricot {

  /**
   * This class acts as a perfect detector that can detect
   * all interactions that occur anywhere in simulation.
   *
   * This is primarily intended to be used as a tool to
   * aid in debugging other simulation components.
   */
  class PerfectDetector final : public Detector {

    public:
    /**
     * True if an interaction is detectable and should be saved.
     */
    auto
    detectable(const InteractionInfo& info,
               const std::unique_ptr<Particle>& particle,
               const CartesianCoordinate& location,
               const CartesianCoordinate& direction) const -> bool final override {
      return true;
    };

    /**
     * True if an interaction should be cut during propagation.
     */
    auto
    cut(const std::unique_ptr<Particle>& particle,
        const CartesianCoordinate& location,
        const CartesianCoordinate& direction) const -> bool final override {
      return false;
    }

    /**
     * A no-op destructor.
     */
    ~PerfectDetector(){};

  }; // END: Detector

} // namespace apricot

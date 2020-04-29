#pragma once

#include "apricot/detectors/EnergyCutDetector.hpp"
#include <memory>
#include <string>

namespace apricot {

  /* Forward Declaration */
  class Particle;

  /**
   * A pure base class for particle detectors.
   */
  class OrbitalDetector final : public Detector {

    const Earth& earth_;                 ///< The earth model that we use for reflection.
    const CartesianCoordinate& payload_; ///< The current location of the detector [km].
    double maxview_;                     ///< The maximum view angle [radians].
    double maxalt_{100. + 1e-3};         ///< The maximum altitude before we cut.
    const std::string mode_;             ///< The detection mode (direct, reflected, or both)

    public:
    /**
     * Create a new orbital detector.
     *
     * @param earth      The Earth model to use.
     * @param location   The geocentric location of the detector in this earth model [km].
     * @param maxview    The maximum view angle [degrees].
     * @param mode       Whether to detect "direct" or "reflected" events or "both"
     *
     */
    OrbitalDetector(const Earth& earth,
                    const CartesianCoordinate& location,
                    const double maxview,
                    const std::string mode = "both")
        : earth_(earth), payload_(location), maxview_(maxview), mode_(mode){};

    /**
     * True if an interaction is detectable and should be saved.
     */
    auto
    detectable(const InteractionInfo& info,
               const std::unique_ptr<Particle>& particle,
               const CartesianCoordinate& location,
               const CartesianCoordinate& direction) const -> bool final override;

    /**
     * True if an interaction should be cut during propagation.
     */
    auto
    cut(const std::unique_ptr<Particle>& particle,
        const CartesianCoordinate& location,
        const CartesianCoordinate& direction) const -> bool final override;

    /*
     * Return the maximum view angle [degrees].
     */
    auto
    get_maxview() const -> double {
      return deg_to_rad(this->maxview_);
    }

    /*
     * Set the maximum view angle [degrees].
     *
     * @param maxview   The new maximum view angle [degrees].
     */
    auto
    set_maxview(const double maxview) -> void {
      this->maxview_ = maxview;
    }

    ///
    /// \brief A virtual destructor.
    ///
    ~OrbitalDetector(){};

  }; // END: Detector

} // namespace apricot

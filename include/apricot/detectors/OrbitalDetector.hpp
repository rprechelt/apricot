#pragma once

#include "apricot/detectors/EnergyCutDetector.hpp"
#include <memory>
#include <string>

namespace apricot {

  /* Forward Declaration */
  class Particle;

  /* An alias for an angle in RADIANS. */
  using Angle = double;

  /**
   * A radio or optical detector at altitude above the Earth.
   *
   * This class models a balloon-borne or space detector above. Given the
   * payload location, this detector triggers on interactions that are visible
   * within a cone of emission centered at the interaction location and aligned
   * with the particle propagation axis.
   */
  class OrbitalDetector final : public Detector {

    const Earth& earth_;                 ///< The earth model that we use.
    const CartesianCoordinate payload_;  ///< The current location of the detector [km].
    double maxview_;                     ///< The maximum view angle [radians].
    double maxalt_{100. + 1e-3};         ///< The maximum altitude before we cut.
    const std::string mode_; ///< The detection mode (direct, reflected, or both)

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
                    const std::string mode = "both") :
        earth_(earth),
        payload_(location),
        maxview_(deg_to_rad(maxview)),
        mode_(mode){};

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

    /**
     * Return the view angle [radians] from a particle axis to the detector.
     *
     *  @param location    The geocentric location of the interaction [km].
     *  @param direction   The unit-length direction vector.
     *
     *  @returns view      The off-axis view angle from the interaction
     *                     to the detector.
     */
    auto
    view_angle(const CartesianCoordinate& location,
               const CartesianCoordinate& direction) const -> Angle;

    /**
     * Return the payload angle [radians] of an event.
     *
     * This is the angle (theta, phi) that an event is seen
     * from the detector where `theta` is the elevation angle.
     * theta==0 is the detector horizontal.
     *
     *  @param location       The geocentric location of the interaction [km].
     *  @param direction      The unit-length direction vector.
     *
     *  @returns theta,   The payload view angles [radians].
     *
     */
    auto
    payload_angle(const CartesianCoordinate& location,
                  const CartesianCoordinate& direction) const -> Angle;

    /*
     * Return the maximum view angle [degrees].
     */
    auto
    get_maxview() const -> Angle {
      return this->maxview_;
    }

    /*
     * Set the maximum view angle [degrees].
     *
     * @param maxview   The new maximum view angle [degrees].
     */
    auto
    set_maxview(const Angle maxview) -> void {
      this->maxview_ = maxview;
    }

    ///
    /// \brief A virtual destructor.
    ///
    ~OrbitalDetector(){};

  }; // END: Detector

} // namespace apricot

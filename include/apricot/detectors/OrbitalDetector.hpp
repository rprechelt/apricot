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
   * An enum for the detection mode.
   */
  enum class DetectionMode { Direct = 0, Reflected = 1, Both = 2 };

  /**
   * Convert a string to a detection mode.
   */
  auto
  mode_from_string(const std::string& mode) -> DetectionMode;

  /**
   * A radio or optical detector at altitude above the Earth.
   *
   * This class models a balloon-borne or space detector above. Given the
   * payload location, this detector triggers on interactions that are visible
   * within a cone of emission centered at the interaction location and aligned
   * with the particle propagation axis.
   */
  class OrbitalDetector final : public Detector {

    const Earth& earth_;                ///< The earth model that we use.
    const CartesianCoordinate payload_; ///< The current location of the detector [km].
    double maxview_;                    ///< The maximum view angle [radians].
    double maxalt_{100. + 1e-3};        ///< The maximum altitude before we cut.
    const DetectionMode mode_;          ///< The detection mode (direct, reflected, or both)

    /**
     * Check if this particle is directly visible.
     *
     * @param location    The location of the interaction.
     * @param direction   The unit-length direction vector.
     */
    auto
    visible_direct(const CartesianCoordinate& location,
                   const CartesianCoordinate& direction) const -> bool;

      /**
     * Check if this particle is visible undere reflection.
     *
     * @param location    The location of the interaction.
     * @param direction   The unit-length direction vector.
     */
    auto
    visible_reflected(const CartesianCoordinate& location,
                      const CartesianCoordinate& direction) const -> bool;

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
                    const std::string& mode = "direct");

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

    /*
     * Return the maximum altitude [km]
     */
    auto
    get_maxalt() const -> double {
      return this->maxalt_;
    }

    /*
     * Set the maximum altitude [km].
     *
     * @param maxalt   The new maximum alt angle [degrees].
     */
    auto
    set_maxalt(const double maxalt) -> void {
      this->maxalt_ = maxalt;
    }

    ///
    /// \brief A virtual destructor.
    ///
    ~OrbitalDetector(){};

  }; // END: Detector

} // namespace apricot

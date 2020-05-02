#pragma once

#include "apricot/Coordinates.hpp"
#include "apricot/Earth.hpp"
#include "apricot/Interaction.hpp"
#include "apricot/detectors/EnergyCutDetector.hpp"

namespace apricot {

  ///
  /// \brief Detect UHE particles that occur in shallow ice in Antarctica.
  ///
  class AntarcticDetector final : public EnergyCutDetector {

    public:
    ///
    /// \brief Create a new AntarcticDetector.
    ///
    AntarcticDetector(const Earth& earth,
                      const double max_depth    = 3.,
                      const double max_altitude = 37.,
                      const double min_energy   = 16.,
                      const double max_energy   = 21.) :
        EnergyCutDetector(min_energy, max_energy),
        earth_(earth),
        max_depth_(max_depth),
        max_altitude_(max_altitude){};

    ///
    /// \brief Return True if a particle should be saved.
    ///
    /// This checks that the particle is within the valid range of
    /// energies and that it is within the max depth and max altitude
    /// restrictions.
    ///
    virtual auto
    detectable(const InteractionInfo& info,
               const std::unique_ptr<Particle>& particle,
               const CartesianCoordinate& location,
               const CartesianCoordinate& direction) const -> bool final override;

    protected:
    ///
    /// \brief A reference to an initialized Earth
    ///
    const Earth& earth_;

    ///
    /// \brief The maximum depth we consider detectable (km).
    ///
    const double max_depth_;

    ///
    /// \brief The maximum altitude we consider detectable (km).
    ///
    const double max_altitude_;

  }; // END: class AntarcticDetector

} // namespace apricot

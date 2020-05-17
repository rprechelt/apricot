#include "apricot/detectors/AntarcticDetector.hpp"

using namespace apricot;

// check if we are on the continent
auto
AntarcticDetector::detectable(const InteractionInfo& info,
                              const std::unique_ptr<Particle>& particle,
                              const CartesianCoordinate& location,
                              const CartesianCoordinate& direction) const -> bool {

  // if this is not a valid energy, then return false immediately.
  if (!has_valid_energy(particle))
    return false;

  // get the radius of the Earth at this location
  const double R{earth_.radius(location)};

  // check if z is not negative-enough to be in the polar cap
  if (location(2) > -R * cos((30. / 180.) * M_PI))
    return false;


  // and get the length of our interaction location
  const double intr{location.norm()};

  // check if we are too deep
  if (intr < (R - max_depth_))
    return false;

  // check if we are too deep
  if (intr > (R + max_altitude_))
    return false;

  // if we reach here, we are good!
  return true;
}

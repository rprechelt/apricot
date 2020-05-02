#include "apricot/detectors/PerfectDetector.hpp"
#include "apricot/earth/SphericalEarth.hpp"

using namespace apricot;

auto
PerfectDetector::detectable(const InteractionInfo& info,
                            const std::unique_ptr<Particle>& particle,
                            const CartesianCoordinate& location,
                            const CartesianCoordinate& direction) const -> bool {
  return true;
}

auto
PerfectDetector::cut(const std::unique_ptr<Particle>& particle,
                     const CartesianCoordinate& location,
                     const CartesianCoordinate& direction) const -> bool {

  // cut any events are leave our detection volume
  if (location.norm() > (SphericalEarth::VOLUMETRIC + 100.))
    return true;

  // otherwise, continue propagating.
  return false;
}

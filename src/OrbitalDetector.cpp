#include "apricot/detectors/OrbitalDetector.hpp"

using namespace apricot;

auto
OrbitalDetector::detectable(const InteractionInfo& info,
                            const std::unique_ptr<Particle>& particle,
                            const CartesianCoordinate& location,
                            const CartesianCoordinate& direction) const -> bool {

  // the vector to ANITA from the location
  const auto view{this->payload_ - location};

  // and the dot product between this view angle and the axis
  if (acos(direction.normalized().dot(view.normalized())) < this->maxview_) {
    // we are within maxview of ANITA
    return true;
  }

  // otherwise don't save the event.
  return false;

}

auto
OrbitalDetector::cut(const std::unique_ptr<Particle>& particle,
                     const CartesianCoordinate& location,
                     const CartesianCoordinate& direction) const -> bool {

  // if the particle started greater than our max altitude, then cut
  if (location.norm() > (earth_.radius(location) + this->maxalt_)) return true;

  // the vector to ANITA from the location
  const auto view{this->payload_ - location};

  // calculate the cos(view angle) from the direction to ANITA.
  const auto viewangle{direction.normalized().dot(view.normalized())};

  // if cos(view angle) is less than zero, it's pointing away from ANITA
  if (viewangle < 0) return true; // then cut
  
  // otherwise, don't cut
  return false;

}

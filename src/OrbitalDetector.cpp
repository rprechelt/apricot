#include "apricot/detectors/OrbitalDetector.hpp"


using namespace apricot;

auto
OrbitalDetector::view_angle(const CartesianCoordinate& location,
                            const CartesianCoordinate& direction) const -> Angle {

  // the vector to the payload from the location
  const auto view{this->payload_ - location};

  // and take the inverse cosine of the dot product
  return acos(direction.dot(view.normalized()));
}

auto
OrbitalDetector::payload_angle(const CartesianCoordinate& location,
                               const CartesianCoordinate& direction) const -> Angle {

  // the vector to the location from the payload
  const auto view{location - this->payload_};

  // the angle between the payload nadir and the view angle
  const auto nadir{acos(this->payload_.normalized().dot(view.normalized()))};

  // and convert this to being referenced from the payload horizontal
  return M_PI/2. - nadir;


}

auto
OrbitalDetector::detectable(const InteractionInfo& info,
                            const std::unique_ptr<Particle>& particle,
                            const CartesianCoordinate& location,
                            const CartesianCoordinate& direction) const -> bool {


  // and the dot product between this view angle and the axis
  if (view_angle(location, direction) < this->maxview_) {
    // we are within maxview of the payload
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

  // get the view angle from the interaction to the payload
  const auto viewangle{view_angle(location, direction)};

  // if cos(view angle) is less than zero, it's pointing away from ANITA
  if (cos(viewangle) < 0) return true; // then cut
  
  // otherwise, don't cut
  return false;

}

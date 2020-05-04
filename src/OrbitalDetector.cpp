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

  // we check for events whose view angles *along* the particle
  // axis are less than maxview and events whose view angle
  // *back along* the axis is less than view angle. This accounts
  // for events that reach shower max after the payload but whose
  // RF emission may be pass very close by the payload.
  if ( (view_angle(location, direction) < this->maxview_) ||
       (view_angle(location, -direction) < this->maxview_) ) {

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

  // get the current radius of the particle
  const auto radius{location.norm()};

  // and the radius of the surface of the Earth
  const auto surface{earth_.radius(location)};

  // if the particle started greater than our max altitude, then cut
  if (radius > (surface + this->maxalt_)) return true;

  // if the particle reaches 10m's below ground, then cut it.
  if (radius < (surface - 1e-2)) return true;

  // get the view angle from the interaction to the payload
  // const auto viewangle{view_angle(location, direction)};

  // if cos(view angle) is less than zero, it's pointing away from ANITA
  // if (cos(viewangle) < 0) return true; // then cut
  
  // otherwise, don't cut
  return false;

}

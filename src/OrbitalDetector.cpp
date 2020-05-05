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
  return M_PI / 2. - nadir;
}

auto
OrbitalDetector::detectable(const InteractionInfo& info,
                            const std::unique_ptr<Particle>& particle,
                            const CartesianCoordinate& location,
                            const CartesianCoordinate& direction) const -> bool {

  // we check for events whose view angle *back along* the axis is less than max
  // angle. This accounts for events that reach shower max after the payload
  // but whose RF emission may be pass very close by the payload.
  if (view_angle(location, -direction) < this->maxview_) {
    // this is backwardly visible
    return true;
  }

  // otherwise, we check for events whose view angles *along* the particle axis
  // are less than maxview. This has some additional complexity as paths
  // can be naively visible but actually intersect the Earth

  if (view_angle(location, direction) < this->maxview_) {

    // if we got here, the interaction is potentially visible
    // but we have to check that the view vector does not
    // intersect the Earth somewhere along the ray

    // compute the view vector
    const auto view{this->payload_ - location};

    // calculate the location of a potential surface intersection
    const auto surface{earth_.find_surface(location, view)};

    // now check for an intersection - if this evaluates
    // to True, an interaction was found.
    if (surface) {

      // if the surface intersection is further away
      // than ANITA, then we are still good. This should only
      // occur when the shower develops past or close-by the
      // payload.

      // calculate the distance to the surface
      const auto Dsurf{(*surface - location).norm()};

      // and the distance from the interaction to ANITA
      const auto Danita{(location - payload_).norm()};

      // if the distance to the surface is less than ANITA then
      // the ray is stopped by the Earth so it's not detectable
      return (Dsurf < Danita) ? false : true;
    }

    // if we get here, the ray never intersects the Earth.
    // and we are within maxview of the payload
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
  if (radius > (surface + this->maxalt_))
    return true;

  // if the particle reaches 10m's below ground, then cut it.
  if (radius < (surface - 1e-2))
    return true;

  // get the view angle from the interaction to the payload
  // const auto viewangle{view_angle(location, direction)};

  // if cos(view angle) is less than zero, it's pointing away from ANITA
  // if (cos(viewangle) < 0) return true; // then cut

  // otherwise, don't cut
  return false;
}


auto
apricot::mode_from_string(const std::string& mode) -> DetectionMode {

  if (mode.compare("direct") == 0) {
    return DetectionMode::Direct;
  }
  else if (mode.compare("reflected") == 0) {
    return DetectionMode::Reflected;
  }
  else if (mode.compare("both") == 0) {
    return DetectionMode::Both;
  }
  else {
    throw std::invalid_argument("Unknown detection `mode` [direct, reflected, both].");
  }

}

#include "apricot/detectors/OrbitalDetector.hpp"
#include "apricot/Geometry.hpp"

using namespace apricot;

OrbitalDetector::OrbitalDetector(const Earth& earth,
                    const CartesianCoordinate& location,
                    const double maxview,
                    const std::string& mode) :
        earth_(earth),
        payload_(location),
        maxview_(deg_to_rad(maxview)),
        mode_(mode_from_string(mode)){}

auto
OrbitalDetector::view_angle(const CartesianCoordinate& location,
                            const CartesianCoordinate& direction) const -> Angle {

  // the vector to the payload from the location
  const auto view{this->payload_ - location};

  // and take the inverse cosine of the dot product
  return acos(direction.dot(view.normalized()));
}

auto
OrbitalDetector::visible_reflected(const CartesianCoordinate& location,
                                   const CartesianCoordinate& direction) const -> bool {

  // calculate the location of a potential surface hit
  // along the shower axis
  const auto surface{earth_.find_surface(location, direction)};

  // if we don't hit the surface, then it can't be visible under reflection
  if (!surface) return false;

  // if we get here, the shower axis *does* intersect the surface.

  // get the vector *to* the payload from the surface intersection
  const auto surface_view{payload_ - *surface};

  // reflect this view vector below the surface to find the proxy payload
  const auto reflected_payload{reflect_below(surface_view, (*surface).normalized())};

  // now compute the view vector from the interaction to the reflected payload
  const auto view{(reflected_payload - location).normalized()};

  // the offaxis angle
  const auto offaxis{acos(view.dot(direction))};

  // if we are within maxview, then we are detectable
  if (offaxis < maxview_) return true;

  // otherwise, we are not visible under reflection
  return false;


}

auto
OrbitalDetector::visible_direct(const CartesianCoordinate& location,
                                const CartesianCoordinate& direction) const -> bool {

  // we can check for events whose view angle *back along* the axis is less than
  // max angle. This accounts for events that reach shower max after the payload
  // but whose RF emission may be pass very close by the payload.
    if (view_angle(location, -direction) < this->maxview_) {
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
    const auto view{(this->payload_ - location).normalized()};

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

  // if we only look for direct events
  if (mode_ == DetectionMode::Direct) {
    return visible_direct(location, direction);
  }
  else if (mode_ == DetectionMode::Reflected) {
    return visible_reflected(location, direction);
  }
  else if (mode_ == DetectionMode::Both) {
    return visible_direct(location, direction) || visible_reflected(location, direction);
  }

  // we should never get here
  throw std::runtime_error("Invalid state in OrbitalDetector::detectable");

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

  if (mode == "direct") {
    return DetectionMode::Direct;
  }
  else if (mode == "reflected") {
    return DetectionMode::Reflected;
  }
  else if (mode == "both") {
    return DetectionMode::Both;
  }
  else {
    throw std::invalid_argument("Unknown detection `mode` [direct, reflected, both].");
  }

}

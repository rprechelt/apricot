#include "apricot/earth/SphericalEarth.hpp"
#include "apricot/Geometry.hpp"
#include <cmath>

using namespace apricot;

auto
SphericalEarth::radius(const CartesianCoordinate&) const -> double {
  return radius_;
}

auto
SphericalEarth::surface_area(const double center,
                             const double theta,
                             const double altitude) const -> double {
  return spherical_cap_area(theta, radius_ + altitude);
}

auto
SphericalEarth::find_surface(const CartesianCoordinate& location,
                             const Vector& direction) const
    -> std::optional<CartesianCoordinate> {
  return propagate_to_sphere(location, direction, this->radius(location));
}

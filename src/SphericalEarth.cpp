#include "apricot/earth/SphericalEarth.hpp"
#include "apricot/Geometry.hpp"
#include <cmath>

using namespace apricot;

auto
SphericalEarth::radius(const CartesianCoordinate&) const -> double {
  return radius_;
}

auto
SphericalEarth::cap_area(const CartesianCoordinate& center, const double theta) -> double {
  return 2*M_PI*radius_*radius_*(1 - cos(theta));
}

auto
SphericalEarth::find_surface(const CartesianCoordinate& location, const Vector& direction) const
  -> std::optional<CartesianCoordinate> {
  return propagate_to_sphere(location, direction, this->radius(location));
}

#include "apricot/earth/SphericalEarth.hpp"
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

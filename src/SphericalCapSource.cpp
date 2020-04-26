#include "apricot/sources/SphericalCapSource.hpp"
#include "Geometry.hpp"
#include <cmath>

using namespace apricot;

auto
SphericalCapSource::get_origin() const -> std::pair<CartesianCoordinate, Vector> {

  // the minimum theta we want to pick ( or zero )
  const auto mintheta{std::max(center_ - theta_, 0.)};

  // the maximum theta we want to pick ( or zero )
  const auto maxtheta{std::min(center_ + theta_, M_PI)};

  // choose a random point on the unit sphere
  auto origin{random_cap_point(mintheta, maxtheta, 0., 2*M_PI)};

  // and scale it by the desired radius
  origin *= this->radius_;

  // and pick a vector uniformly in 4\pi steradians
  const auto direction{random_spherical_point()};

  // and return the pair
  return std::make_pair(origin, direction);
  
}

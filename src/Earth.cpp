#include "apricot/Earth.hpp"
#include "apricot/earth/PREM.hpp"

using namespace apricot;

auto
Earth::density(const CartesianCoordinate& location) const -> double {

  // the radius of the Earth at this location
  auto Rearth{this->radius(location)};

  // the radius of the current point
  auto radius{location.norm()};

  // if the location is less than the Earth radius
  if ( radius < Rearth ) {
    return PREM::density(radius, Rearth);
  }
  else { // we are not in the bulk of the Earth
    return 0.;
  }

}

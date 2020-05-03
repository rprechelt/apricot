#include "apricot/Earth.hpp"
#include "apricot/earth/PREM.hpp"

using namespace apricot;

auto
Earth::density(const CartesianCoordinate& location) const -> double {

  // the radius of the Earth at this location
  const auto Rearth{this->radius(location)};

  // the radius of the current point
  const auto radius{location.norm()};

  // if the location is less than the Earth radius
  if ( radius < Rearth ) {
    return PREM::density(radius, Rearth);
  }
  else { // we are not in the bulk of the Earth

    // check if we have an atmosphere model
    if (atmosphere_ != nullptr) {

      // compute the altitude of this point
      const auto altitude{radius - Rearth};

      // return the density of the atmosphere
      return atmosphere_->density(altitude);
    }

    // with no atmosphere model, assume zero density.
    return 0.;
    
  } // END: else

}

auto
Earth::add(const std::shared_ptr<Atmosphere>& atmosphere) -> void {
  this->atmosphere_ = std::static_pointer_cast<Atmosphere>(atmosphere);
}

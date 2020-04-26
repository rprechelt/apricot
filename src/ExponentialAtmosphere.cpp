#include "apricot/atmospheres/ExponentialAtmosphere.hpp"
#include <cmath>

using namespace apricot;

auto
ExponentialAtmosphere::density(const double altitude) const -> double {
  return rho0_ * exp ( (- g * M * altitude) / (R * T_) );
}

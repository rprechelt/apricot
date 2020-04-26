#include "apricot/earth/PREM.hpp"
#include <cmath>

// using namespace Eigen;
using namespace apricot;

// Get the density (in g/cm^3) at a given radius.
auto PREM::density(const double radius, const double Rearth) -> double {
  // both arguments in kilometers

  // get dimensionless constant as a function of Earth radius
  const auto x{radius / Rearth};

  // this is straight from PG's MC
  if (x < 0.19216) // 1221.5 km
    return 13.0885 - 8.8381 * x * x;

  if (x < 0.54745) // 3480 km
    return 12.5815 - 1.2638 * x - 3.6426 * x * x - 5.5281 * x * x * x;

  if (x < 0.89684) // 5701 km
    return 7.9565 - 6.4761 * x + 5.5283 * x * x - 3.0807 * x * x * x;

  if (x < 0.90628) // 5761 km
    return 5.3197 - 1.4836 * x;

  if (x < 0.93759) // 5960 km
    return 11.2494 - 8.0298 * x;

  if (x < 0.96590) // 6140 km
    return 7.1089 - 3.8045 * x;

  if (x < 0.99658) // 6335 km
    return 2.691 + 0.6924 * x;

  if (x < 0.99752) // 6341 km
    return 2.9;

  if (x < 0.99941) // 6353 km
    return 2.6;

  if (x < 0.999984) // 6356.655 km
    return 1.02;

  // otherwise we are not in the Earth
  return 0.;
}

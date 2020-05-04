#include "apricot/Geometry.hpp"
#include "apricot/earth/SphericalEarth.hpp"
#include "apricot/Random.hpp"
#include <stdexcept>

using namespace apricot;

auto
apricot::random_spherical_point() -> CartesianCoordinate {

  // create uniform number generators to use - note static.
  static std::uniform_real_distribution<double> randtheta(-1., 1.);
  static std::uniform_real_distribution<double> randphi(0., 1.);

  // and get the R, theta, phi
  const double theta{acos(randtheta(random::generator))};
  const double phi{M_PI * (2 * randphi(random::generator) - 1)};
  const double r{1.};

  // and convert from spherical to cartesian coordinates
  return to_cartesian(SphericalCoordinate(r, theta, phi));
}

auto
apricot::random_cap_point(const double mintheta, const double maxtheta, const double minphi,
                          const double maxphi) -> Vector {

  // choose a random point on the unit-sphere between mintheta and
  // maxtheta [radians] where theta is measured from (0, 0, 1).
  // we do this with true spherical point picking.
  const double theta{acos(random::uniform(cos(mintheta), cos(maxtheta)))};

  // and choose theta randomly
  const double phi{random::uniform(0., 2 * M_PI)};

  // create the spherical coordinate (r, theta, phi)
  SphericalCoordinate spherical(1., theta, phi);

  // but return it in Cartesian
  return to_cartesian(spherical);
}

auto
apricot::propagate_to_sphere(const CartesianCoordinate& start, const CartesianCoordinate& direction,
                             const double radius) -> CartesianCoordinate {
  // we assume that the surface intersection point can be parametrized as
  // surface = start + t*direction

  // this computes how far start is from the middle of the chord formed by
  // start and direction
  const auto D{direction};
  const auto LD(start.dot(direction));
  const double L{start.norm()};

  // and compute how much further we must travel along the chord.
  const auto t{sqrt(LD * LD - L * L + radius * radius)};

  // and finally compute the intersection
  const auto surface{start + (t - LD) * D};

  // get the magnitude of the surface vector
  const auto magnitude{surface.norm()};

  // and check that we are indeed at the surface.
  if ((magnitude < (radius - 1e-3)) || (magnitude > (radius + 1e-3))) {
    throw std::runtime_error("propagate_to_sphere FAILED");
  }

  // and return the surface point
  return surface;
}

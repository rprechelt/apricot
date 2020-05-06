#include "apricot/Geometry.hpp"
#include "Utils.hpp"
#include "apricot/Random.hpp"
#include "apricot/earth/SphericalEarth.hpp"
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
apricot::random_cap_point(const double mintheta,
                          const double maxtheta,
                          const double minphi,
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
apricot::spherical_cap_area(const double theta, const double radius) -> double {
  return 2*M_PI*radius*radius*(1. - cos(theta));
}

auto
apricot::propagate_to_sphere(const CartesianCoordinate& start,
                             const CartesianCoordinate& direction,
                             const double radius) -> std::optional<CartesianCoordinate> {
  // we assume that the surface intersection point can be parametrized as
  // surface = start + t*direction

  // this computes how far start is from the middle of the chord formed by
  // start and direction
  // const auto D{direction};
  // const auto LD(start.dot(direction));
  // const double L{start.norm()};

  // // and compute how much further we must travel along the chord.
  // const auto t{sqrt(LD * LD - L * L + radius * radius)};

  // // and finally compute the intersection
  // const auto surface{start + (t - LD) * D};

  // // get the magnitude of the surface vector
  // const auto magnitude{surface.norm()};
  //
  // # compute the distance from the origin to the perpendicular
  // radial line at the location of closest approach
  const auto LD{start.dot(direction)};

  // now compute the squared distance of closest approach
  const auto D2{start.dot(start) - LD * LD};

  // if this is greater than the squared radius, then we don't
  // intersect the sphere. So, return a none value
  if (D2 > radius * radius)
    return std::nullopt;

  // now compute the offset from this central intersect point
  const auto thc{sqrt(radius * radius - D2)};

  // due to numerical precision, we generally always have
  // two solutions to the intersection: -LD +/- thc

  // when we are INSIDE the sphere, we want the far/second solution
  // as this is the solution *along* the ray path
  // if we are OUTSIDE the sphere, we want the closest/first solution
  // as that is the location of the first intersection with the sphere

  // compute the parameter for the appropriate intersection
  // using the starting radius to check for the sign
  const auto t{-LD - sgn(start.norm() - radius) * thc};

  // now compute the intersection with the surface
  const auto surface{start + t * direction};

  // and check that we are indeed at the surface.
  // if ((magnitude < (radius - 1e-3)) || (magnitude > (radius + 1e-3))) {
  //   throw std::runtime_error("propagate_to_sphere FAILED");
  // }

  // and return the surface point
  return surface;
}

auto
apricot::reflect_below(const CartesianCoordinate& location,
                       const CartesianCoordinate& normal) -> CartesianCoordinate {

  // given a vector v, and a normal n, the mirror image of v below
  // the surface defined by n is:
  // R = v - 2(v . n)n

  // find the projection vector of `location` onto the `normal`.
  const auto P{location.dot(normal) * normal};

  // and construct the mirrored vector
  return location - 2 * P;
}

#pragma once

#include "apricot/Coordinates.hpp"
#include <optional>

namespace apricot {

  /**
   * Return a random vector on the unit sphere.
   *
   * This uses true spherical point picking to choose a random
   * vector uniformly distributed (in area) on the unit sphere.
   *
   * @returns vector    A unit-length vector on the unit-sphere.
   */
  auto
  random_spherical_point() -> Vector;

  /**
   * Return the area of a spherical cap.
   *
   * Given the angular half-opening angle (i.e. longitude) of a
   * spherical cap, and the radius, return the area in units of radius**2.
   *
   * @param theta    The half-opening angle of the cap.
   * @param radius   The radius of the sphere.
   *
   * @returns        The area of the spherical cap.
   */
  auto
  spherical_cap_area(const double theta, const double radius) -> double;

  /**
   * Return a random point on the surface of a spherical cap.
   *
   * This returns a random point (picked using true spherical point
   * picking) on the surface of a spherical cap (or surface segment)
   * between `mintheta` and `maxtheta` and `minphi` and `maxphi` all
   * in radians.
   *
   * This returns the unit-vector in (x, y, z) coordinates.
   *
   * @returns point    A point on the spherical cap.
   */
  auto
  random_cap_point(const double mintheta,
                   const double maxtheta,
                   const double minphi,
                   const double maxphi) -> Vector;

  /**
   * Propagate a ray to a sphere with known radius.
   *
   * Given a ray *inside* or *outside* a sphere located at `start`, and a
   * normalized direction vector `direction`, return the intersection of that
   * ray with the sphere of radius `radius` assuming that the coordinate system
   * of `start` shares the same origin as the sphere.
   *
   * This returns the first intersection that is *along* the forward direction
   * of the ray's path given `direction`.
   *
   * @param start        The starting location of the ray.
   * @param direction    The normalized unit vector direction of the ray.
   * @param radius       The radius of the sphere to intersect with.
   *
   * @returns intersect  The intersection of the ray with the spher.
   */
  auto
  propagate_to_sphere(const CartesianCoordinate& start,
                      const Vector& direction,
                      const double radius) -> std::optional<CartesianCoordinate>;

  /**
   * Reflect `location` *below* the surface defined by `normal`.
   *
   * Given a vector `location` measured from the location of `normal`
   * (a unit-length) normal vector the surface, calculate the
   * mirror image of `location` *BELOW* the surface.
   *
   * @param location    The vector to reflect/mirror.
   * @param normal      The normal vector of the surface (unit-length).
   *
   * @returns reflected `location` reflected below the surface.
   *
   */
  auto
  reflect_below(const CartesianCoordinate& location,
                const CartesianCoordinate& normal) -> CartesianCoordinate;
  
} // namespace apricot

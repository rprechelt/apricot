#pragma once

#include <Eigen/Core>
#include <cfloat>
#include <cmath>

namespace apricot {

  /**
   * An alias for a geocentric cartesian coordinate [km]
   */
  using CartesianCoordinate = Eigen::Vector3d;

  /**
   * An alias for a geocentric spherical coordinate [km]
   */
  using SphericalCoordinate = Eigen::Vector3d;

  /**
   * An alias for many cartesian coordinates
   */
  using CartesianCoordinates = Eigen::Matrix<double, Eigen::Dynamic, 3>;

  /**
   * An alias for many spherical coordinates
   */
  using SphericalCoordinates = Eigen::Matrix<double, Eigen::Dynamic, 3>;

  /**
   * An alias for a 3D vectors.
   */
  using Vector = Eigen::Vector3d;

  /**
   * An alias for many 3D vectors.
   */
  using Vectors = Eigen::Matrix<double, Eigen::Dynamic, 3>;

  /**
   * An alias for an array of scalar values.
   */
  using Array = Eigen::ArrayXd;

  /**
   * Convert degrees to radians.
   *
   * @param degree    An angle in degrees.
   */
  inline auto
  deg_to_rad(const double degree) noexcept -> double {
    return (degree / 180.) * M_PI;
  }

  /**
   * Convert radians to degrees.
   *
   * @param radian    An angle in radians.
   */
  inline auto
  rad_to_deg(const double radian) noexcept -> double {
    return (radian / M_PI) * 180.;
  }

  /**
   * Convert a CartesianCoordinate to a SphericalCoordinate
   *
   * @param location   A CartesianCoordinate (x, y, z).
   *
   */
  static auto
  to_spherical(const CartesianCoordinate& location) -> SphericalCoordinate {

    // extract out the components
    const auto x{location(0)};
    const auto y{location(1)};
    const auto z{location(2)};

    // get R and theta
    const double r{location.norm()};
    const double theta{acos(z / r)};

    // we need to check for the case when x AND y are EXACTLY zero
    // i.e. when specifying explicit constants in test programs or
    // during command line arguments. In that case, phi is undefined.
    // in that case, we assume that phi == 0
    const double phi{(abs(x) < DBL_MIN) ? 0. : atan(y / x)};

    // assign the elements of the vector
    return SphericalCoordinate(r, theta, phi);
  }

  /**
   * Convert a SphericalCoordinate to a CartesianCoordinate.
   *
   * @param location   A SphericalCoordinate (r, theta, phi).
   *
   */
  static auto
  to_cartesian(const SphericalCoordinate& location) noexcept -> CartesianCoordinate {

    // get a named reference to each component to be safe
    const auto radius{location(0)};
    const auto theta{location(1)};
    const auto phi{location(2)};

    // convert to (x, y, z)
    const auto x{radius * sin(theta) * cos(phi)};
    const auto y{radius * sin(theta) * sin(phi)};
    const auto z{radius * cos(theta)};

    // and create the cartesian coordinate
    return CartesianCoordinate(x, y, z);
  }

} // namespace apricot

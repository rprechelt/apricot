#pragma once

#include <Eigen/Core>

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

} // namespace apricot

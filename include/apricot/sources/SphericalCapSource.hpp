#pragma once

#include "apricot/Coordinates.hpp"
#include "apricot/Source.hpp"
#include <cmath>

namespace apricot {

  /**
   * Generate particles on the surface of a spherical cap.
   *
   * This class generates particle origin points on the surface of
   * a spherical cap with a specific angular opening angle.
   *
   * By default, this picks points on the surface of a spherical cap
   * 100 km above Antarctic. Direction vectors are picked uniformly
   * from 4\pi steradians.
   *
   */
  class SphericalCapSource final : public Source {

    public:
    /**
     * The radius of the spherical cap.
     */
    const double radius_;

    /**
     * The polar half-opening angle of the cap [radians].
     */
    const double theta_;

    /**
     * The center of the spherical cap [radians].
     *
     */
    const double center_;

    /**
     * Create a SphericalCapSource.
     *
     * @param radius    The radius of the spherical cap [km].
     * @param theta     The half-opening angle of the cap [radians].
     * @param center    The central angle of the spherical cap.
     *
     */
    SphericalCapSource(const double radius = 6356.755,
                       const double theta  = M_PI / 16.,
                       const double center = (15 / 16.) * M_PI) :
        radius_(radius),
        theta_(theta),
        center_(center) {}

    /**
     * Choose a random point on the surface of the cap.
     */

    /**
     * Sample points uniformly on the surface of the cap.
     *
     * Direct
     */
    auto
    get_origin() const -> std::pair<CartesianCoordinate, Vector> final override;

  }; // END: class SphericalCapSource

} // namespace apricot

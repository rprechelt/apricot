#pragma once

#include "apricot/Earth.hpp"

namespace apricot {

  /**
   * A spherical Earth model.
   *
   * This classes models a spherical Earth at a user-selectable
   * radius (i.e. polar radius, volumetric radius) that attempt
   * to approximate the true Earth ellipsoid.
   *
   * This is the fastest and simplest Earth model.
   */
  class SphericalEarth final : public Earth {

    /**
     * The Earth radius we use for simulations [km].
     */
    const double radius_;

    public:
    /**
     * The polar radius [km].
     */
    static constexpr double POLAR{6356.752};

    /**
     * The polar radius of curvature [km].
     */
    static constexpr double POLAR_CURVATURE{6399.594};

    /**
     * The equatorial radius [km].
     */
    static constexpr double EQUATORIAL{6378.137};

    /**
     * The volumetric radius [km].
     */
    static constexpr double VOLUMETRIC{6371.000};

    /**
     * Construct an spherical Earth with a given radius.
     */
    SphericalEarth(const double radius = SphericalEarth::POLAR) : radius_(radius){};

    /**
     * Get the radius of the Earth (km) along a given vector.
     *
     * @param radius    The 3D geocentric location (in km).
     */
    auto
    radius(const CartesianCoordinate&) const -> double final override;

    /**
     * Get the area of a spherical cap.
     *
     * @param center    The center of the spherical cap.
     * @param theta     The HALF-opening angle of the cap [radians]
     *
     */
    auto
    cap_area(const CartesianCoordinate& center, const double theta) -> double;

  }; // END: class SphericalEarth

} // namespace apricot

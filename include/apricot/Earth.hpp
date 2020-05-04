#pragma once

#include "apricot/Coordinates.hpp"
#include "apricot/Atmosphere.hpp"
#include <memory>
#include <optional>

namespace apricot {

  /* Forward Declarations */
  class Atmosphere;

  /**
   * The base class that handles all Earth models.
   *
   * This is a CRTP base class that uses the different
   * derived classes to modify the overall model at compile
   * time.
   *
   */
  class Earth {

    std::shared_ptr<Atmosphere> atmosphere_{nullptr}; ///< The atmosphere model to use.

    public:
    /**
     * The radius of the Earth at a given location.
     *
     * This returns the radius in kilometers.
     *
     * @param location    A geocentric coordinate [km].
     */
    virtual auto
    radius(const CartesianCoordinate& location) const -> double = 0;

    /**
     * The density of the Earth at a given location.
     *
     * This returns the density in g/cm^3.
     *
     * @param location    A geocentric coordinate [km].
     */
    auto
    density(const CartesianCoordinate& location) const -> double;

    /**
     * Find the intersection of a ray with the surface.
     *
     * Given a starting location, and a *unit-length* direction
     * vector, find the intersection of this ray with the surface.
     * If no intersection is found, this returns std::nullopt.
     *
     * @param location    The starting location of the ray.
     * @param direction   The unit-length ray direction vector.
     *
     * @returns surface   The location of the surface intersiction or nullopt.
     *
     */
    virtual auto
    find_surface(const CartesianCoordinate& location,
                 const Vector& direction) const -> std::optional<CartesianCoordinate> = 0;

    /**
     * Add an atmosphere model to this Earth model.
     *
     * This replaces any existing atmosphere model.
     *
     * @param atmosphere    The atmosphere model to add.
     */
    auto
    add(const std::shared_ptr<Atmosphere>& atmosphere) -> void;

    /**
     * Virtual destructor.
     */
    virtual ~Earth() = default;

  }; // END: class Earth

} // namespace apricot

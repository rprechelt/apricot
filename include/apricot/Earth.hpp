#pragma once

#include "apricot/Coordinates.hpp"
#include "apricot/Atmosphere.hpp"
#include <memory>

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

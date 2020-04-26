#pragma once


namespace apricot {

  /**
   * A pure base class for atmospheric models.
   *
   */
  class Atmosphere {

    public:

    /**
     * The density of the atmosphere at a given altitude.
     *
     * This returns density in g/cm^3.
     *
     * @param altitude   Altitude in kilometers [km].
     *
     */
    virtual auto
    density(const double altitude) const -> double = 0;

  };

}

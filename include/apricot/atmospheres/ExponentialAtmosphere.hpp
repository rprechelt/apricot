#pragma once

#include "apricot/Atmosphere.hpp"

namespace apricot {

  /**
   * A simple exponential atmosphere model.
   *
   * This models the atmosphere as:
   *
   *     \rho = \rho_0 \exp { -g M h / RT }
   *
   */
  class ExponentialAtmosphere final : public Atmosphere {

    /*
     * The unit-less scaling relation, M.
     */
    static constexpr double M{28.966};

    /*
     * The gas-constant [J mol^-1 K^-1]
     */
    static constexpr double R{8.3145};

    /*
     * The acceleration due to gravity [m/s^2]
     */
    static constexpr double g{9.81};

    public:
    /*
     * The sea-level density (g/cm^3).
     */
    double rho0_;

    /*
     * The reference temperature (K).
     */
    double T_;

    /**
     * Create an ExponentialAtmosphere from parameters.
     *
     * The default temperature (273 K) is a little lower than the standard
     * atmospheric model (T = 288 K) to better approximate the South Pole.
     *
     * @param rho0    The sea level density in [g/cm^3].
     * @param T       The reference temperature [K]
     */
    ExponentialAtmosphere(const double rho0 = 1.225e-3, const double T = 273) :
        rho0_(rho0),
        T_(T){};

    /**
     * The density of the atmosphere at a given altitude.
     *
     *
     * This returns density in g/cm^3.
     *
     * @param altitude   Altitude in kilometers [km].
     *
     */
    auto
    density(const double altitude) const -> double final override;

  }; // END: ExponentialAtmosphere

} // namespace apricot

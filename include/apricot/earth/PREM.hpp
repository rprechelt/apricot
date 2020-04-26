#pragma once

namespace apricot::PREM {

  ///
  /// \brief Compute the density (in g/cm^3) at a given radius in km.
  ///
  /// This function normalizes a parametrization of the PREM density
  /// model to the radius of the Earth along the geocentric vector
  /// to the sample location.
  ///
  /// @param radius    The radius within the Earth [km].
  /// @param r_earth   The radius *of* the Earth at this location [km]
  ///
  auto __attribute__((hot))
  density(const double radius, const double Rearth = 6356.799) -> double;

} // namespace apricot::PREM

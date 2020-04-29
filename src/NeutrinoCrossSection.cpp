#include <apricot/particles/NeutrinoCrossSection.hpp>
#include <array>
#include <cmath>

using namespace apricot;

// a function to evalute the cross section polynomial
auto
evaluate(const double energy, const std::array<double, 4>& coeff) -> double {
  // this stores the final cross section value
  double xsection{0.};

  // iterate over the polynomial powers
  for (int i = 0; i < 4; i += 1) {
    xsection += coeff[i] * pow(energy, float(i));
  }
  // and take a final power
  return xsection;
}

// get the charged current cross section
auto
apricot::charged_current(const NeutrinoCrossSectionModel model, const LogEnergy energy)
    -> LogGrammage {

  // the following cross section parametrizations are copied directly from
  // https://github.com/harmscho/NuTauSim/
  // starting L708:simu_elost.cxx
  // these are taken from arXiV:1102.0691

  switch (model) {

  case NeutrinoCrossSectionModel::ConnollyMiddle: {
    // Connolly et al. 2011 middle model (ARW's parametrization)
    const std::array<double, 4> p{
        {-5.35400180e+01, 2.65901551e+00, -1.14017685e-01, 1.82495442e-03}};
    return evaluate(energy, p);
  }

  case NeutrinoCrossSectionModel::ConnollyLower: {
    // Connolly et al. 2011 lower model (ARW's parametrization)
    const std::array<double, 4> p{
        {-4.26355014e+01, 4.89151126e-01, 2.94975025e-02, -1.32969832e-03}};
    return evaluate(energy, p);
  }

  case NeutrinoCrossSectionModel::ConnollyUpper: {
    // Connolly et al. 2011 upper model (ARW's parametrization){
    const std::array<double, 4> p{
        {-5.31078363e+01, 2.72995742e+00, -1.28808188e-01, 2.36800261e-03}};
    return evaluate(energy, p);
  }

  case NeutrinoCrossSectionModel::Gorham:
  default: // this is also the fall-through model
  {
    // this model is lifted straight from Peter Gorham's original MC
    return log10(1.e-36 * exp(82.893 - 98.8 * (pow((energy - 9.) / log10(M_E), -0.0964))));
  }

  } // end: switch
}

// get cross-section at a given energy for a given cross-section model
auto
apricot::neutral_current(const NeutrinoCrossSectionModel model, const LogEnergy energy)
    -> LogGrammage {

  // the following cross section parametrizations are copied directly from
  // https://github.com/harmscho/NuTauSim/
  // starting L708:simu_elost.cxx

  switch (model) {

  case NeutrinoCrossSectionModel::ConnollyMiddle: {
    // Connolly et al. 2011 middle model (ARW's parametrization)
    const std::array<double, 4> p{
        {-5.41463399e+01, 2.65465169e+00, -1.11848922e-01, 1.75469643e-03}};
    return evaluate(energy, p);
  }

  case NeutrinoCrossSectionModel::ConnollyLower: {
    // Connolly et al. 2011 lower model (ARW's parametrization)
    const std::array<double, 4> p{
        {-4.42377028e+01, 7.07758518e-01, 1.55925146e-02, -1.02484763e-03}};
    return evaluate(energy, p);
  }

  case NeutrinoCrossSectionModel::ConnollyUpper: {
    // Connolly et al. 2011 upper model (ARW's parametrization)
    const std::array<double, 4> p{
        {-5.36713302e+01, 2.72528813e+00, -1.27067769e-01, 2.31235293e-03}};
    return evaluate(energy, p);
  }

  case NeutrinoCrossSectionModel::Gorham:
  default: // this is also the fall-through model
  {
    // this model is lifted straight from Peter Gorham's original MC
    // this had NC as CC/2.39 but `getChargedCurrentCrossSection` returns
    // log-space Xsection
    return charged_current(NeutrinoCrossSectionModel::Gorham, energy) - log10(2.39);
  }

  } // end switch
    //
}

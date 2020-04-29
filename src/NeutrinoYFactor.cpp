#include "apricot/particles/NeutrinoYFactor.hpp"
#include <array>
#include <cmath>

using namespace apricot;

// we create a lambda expression and wrap E in a closure
// so that we only need to provide the coefficients
// double E = this->getEnergy();
static auto evaluate(const double E, const std::array<double, 3> &coeff)
    -> double {

  // convert base 10 energies to natural logarithm in GeV
  const double En{log(10) * (E - 9)};

  // and return
  return coeff[0] + coeff[1] * En + coeff[2] * En * En;
}

// use the Y-factor parametrization to estimate <y> at a given energy
auto apricot::y_factor(const LogEnergy energy, const NeutrinoYFactorModel &model)
    -> double {

  // we provide the three 3-parameter parametrizations on
  // Pg. 9 of  arXiv::1704.00050
  // the following arrays are {y0, y1, y2}
  // <y>(E) = y0 + y1*ln(E) + y2*(ln(E)^2
  // E is in GeV
  //
  // according to authors, this has <1% error between 10^6 and 10^13 GeV

  // these parametrizations are split into two parts
  if (energy <= 17) {

    switch (model) {

    case NeutrinoYFactorModel::BDHM: {
      const std::array<double, 3> coeff{{0.909, -5.95e-2, 1.17e-3}};
      return evaluate(energy, coeff);
    }

    case NeutrinoYFactorModel::Soyez: {
      const std::array<double, 3> coeff{{1.08, -8.55e-2, 2.07e-3}};
      return evaluate(energy, coeff);
    }

    case NeutrinoYFactorModel::ALLM:
    default: {
      const std::array<double, 3> coeff{{1.17, -9.99e-2, 2.59e-3}};
      return evaluate(energy, coeff);
    }

    }    // END: switch(model)
  }      // if (energy <= 17)
  else { // for energies greater than 17

    switch (model) {

    case NeutrinoYFactorModel::BDHM: {
      const std::array<double, 3> coeff{{0.654, -3.35e-2, 5.01e-4}};
      return evaluate(energy, coeff);
    }

    case NeutrinoYFactorModel::Soyez: {
      const std::array<double, 3> coeff{{0.478, -2.05e-2, 2.98e-4}};
      return evaluate(energy, coeff);
    }

    case NeutrinoYFactorModel::ALLM:
    default: {
      const std::array<double, 3> coeff{{0.356, -1.25e-2, 2.27e-4}};
      return evaluate(energy, coeff);
    }

    } // END: switch (model)
  }   // END: else
}

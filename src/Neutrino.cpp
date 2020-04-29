#include "apricot/particles/Neutrino.hpp"
#include "Random.hpp"
#include <cmath>
#include <stdexcept>

using namespace apricot;

// decide on a charged current or neutral current interaction for a neutrino
auto
Neutrino::get_interaction() const -> InteractionInfo {

  // get cross sections for NC and CC at the current energy
  // these are in log10(g/cm^2)
  const LogGrammage CC_cross{cross_section(interactions::ChargedCurrent)};
  const LogGrammage NC_cross{cross_section(interactions::NeutralCurrent)};

  // create a uniform number generator to use next.
  static std::uniform_real_distribution<double> uniform(0., 1.);

  // exponential(lambda) has mean=1/lambda so the following have mean 1/{CC,NC}
  // the result of exponential is in g/cm^2
  constexpr double N_A{6.0221415e23}; // mol^-1
  const double CC{-log(uniform(random::generator)) * (1. / (N_A * pow(10, CC_cross)))};
  const double NC{-log(uniform(random::generator)) * (1. / (N_A * pow(10, NC_cross)))};

  // decide which interaction happens first based on the cross section
  const auto current{CC < NC ? interactions::ChargedCurrent : interactions::NeutralCurrent};

  // and return the InteractionInfo object
  return InteractionInfo(current, fmin(CC, NC));
}

// evaluate the neutrino cross section
auto
Neutrino::cross_section(const InteractionType& interaction) const -> LogGrammage {

  // swich on the interaction type
  switch (interaction) {

    // charged current interaction
  case interactions::ChargedCurrent:
    return charged_current(Neutrino::cross_section_model, energy_);

    // charged current interaction
  case interactions::NeutralCurrent:
    return neutral_current(Neutrino::cross_section_model, energy_);

  default:
    // there is no amonut of grammage that the propagator to give
    // that will give
    return -1;

  } // END: switch(interaction)
}

// return a particle from a flavor and energy.
auto
Neutrino::from_generation(const Generation gen, const double energy)
    -> std::unique_ptr<Particle> {

  // switch on the desired generation
  switch (gen) {

    // electron neutrinos
  case Generation::Electron:
    return std::make_unique<ElectronNeutrino>(energy);
    break;

    // muon neutrino
  case Generation::Muon:
    return std::make_unique<MuonNeutrino>(energy);
    break;

    // tau neutrino
  case Generation::Tau:
    return std::make_unique<TauNeutrino>(energy);
    break;

    // when all else fails, throw an exception
  default:
    throw std::invalid_argument("Unknown particle generation!");

  } // END: switch (gen)
}

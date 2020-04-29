#include "apricot/particles/ChargedLepton.hpp"
#include "apricot/particles/Neutrino.hpp"
#include "apricot/Random.hpp"

using namespace apricot;

auto
Tau::get_interaction() const -> InteractionInfo {
  // we currently only support tau decays

  // get a randomly distributed lifetime
  const auto time{this->decay_time()};

  // return an InteractionInfo struct with this information
  // InteractionInfo uses nanoseconds in lab frame.
  return InteractionInfo(interactions::Decay, -1., time);
}

auto
Tau::get_decay_product() const -> std::unique_ptr<Particle> {

  // get a random decay from the decay table
  const auto decay{decaytable_.random_final_state()};

  // we currently only generate neutrinos from the decay
  // interactions and we currently only generate the
  // neutrino with the highest neutrino.
  if (decay.nu_tau >= decay.nu_e && decay.nu_tau >= decay.nu_muon) {
    return std::make_unique<TauNeutrino>(decay.nu_tau);
  } else if (decay.nu_muon >= decay.nu_e && decay.nu_muon >= decay.nu_tau) {
    return std::make_unique<MuonNeutrino>(decay.nu_muon);
  } else {
    return std::make_unique<ElectronNeutrino>(decay.nu_e);
  }

  // and we should never get here.
}

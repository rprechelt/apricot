#include "apricot/particles/ChargedLepton.hpp"
#include "apricot/Random.hpp"

using namespace apricot;

auto Muon::get_interaction() const -> InteractionInfo {

  // we currently only support muon decays

  // get a randomly distributed lifetime
  const auto time{this->decay_time()};

  // return an InteractionInfo struct with this information
  // InteractionInfo uses nanoseconds in lab frame.
  return InteractionInfo(interactions::Decay, -1., time);
}

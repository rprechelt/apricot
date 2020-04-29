#include <fstream>
#include <string>

#include "apricot/particles/TauDecayTable.hpp"
#include "apricot/Random.hpp"

#include <filesystem>
#include <iostream>

using namespace apricot;

auto TauDecayTable::load_decay_table() const -> decltype(finalstates_) {

  // try and open the file
  // std::ifstream
  // table{std::string(DATA_DIR)+std::string("/particles/")+filename_};
  std::ifstream table{std::string("data/particles/tau/") + filename_};

  // check that it is good to read
  if (!table.good()) {
    std::cout << std::filesystem::current_path()
              << std::string("/data/particles/tau/") + filename_ << "\n";
    throw std::runtime_error("Unable to open tau decay file.");
  }

  // create a file to load the data into
  std::decay_t<decltype(finalstates_)> states;

  // walk through the file adding data
  for (size_t state = 0; state < nstates_; ++state) {
    for (size_t pid = 0; pid < nparticles_; ++pid) {
      table >> states[state * nparticles_ + pid];
    }
  }

  // and return the array
  return states;
}

auto TauDecayTable::random_state() const
    -> std::array<double, TauDecayTable::nparticles_> {

  // generate a random index into a state
  const size_t start{size_t(random::uniform_int(0, nstates_) * nparticles_)};

  // create a new smaller array to fill in the values
  std::array<double, TauDecayTable::nparticles_> states;

  // and fill in the values
  for (size_t idx = 0; idx < nparticles_; ++idx) {
    states[idx] = finalstates_[start + idx];
  }

  // and return the corresponding FinalState
  return states;
}

auto TauDecayTable::random_final_state() const -> TauDecayProducts {
  return TauDecayProducts(random_state());
}

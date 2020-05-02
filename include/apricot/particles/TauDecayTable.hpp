#pragma once

#include <array>

namespace apricot {

  /**
   * The fractional energy transferred to each component in a tau decay.
   *
   * Every entry in our tau decay table contains one final simulation
   * state showing the energy transferred to each component of the
   * decay.
   */
  class TauDecayProducts final {

    public:
    /*
     * The fractional energy transferred to the electron neutrino.
     */
    double nu_e;

    /*
     * The fractional energy transferred to the muon neutrino.
     */
    double nu_muon;

    /*
     * The fractional energy transferred to the tau neutrino.
     */
    double nu_tau;

    /*
     * The fractional energy transferred to the hadronic shower.
     */
    double hadronic;

    /*
     * The fractional energy transferred to the electron.
     */
    double electron;

    /*
     * The fractional energy transferred to the muon.
     */
    double muon;

    /**
     * Construct a final decay state from an initializer state.
     *
     * @param state   The energy transferred to each decay component.
     */
    TauDecayProducts(const std::array<double, 6>& state) :
        nu_e(state[2]),
        nu_muon(state[1]),
        nu_tau(state[0]),
        hadronic(state[3]),
        electron(state[5]),
        muon(state[4]){};

    /**
     *  Return a Python-format string representation.
     *
     *  @returns A string representation of this TauDecayProducts.
     */
    auto
    to_string() const -> std::string {
      return "TauDecayProducts(nu_e=" + std::to_string(nu_e) +
             ", nu_mu=" + std::to_string(nu_muon) + ", nu_tau=" + std::to_string(nu_tau) +
             ", hadronic=" + std::to_string(hadronic) +
             ", electron=" + std::to_string(electron) + ", muon=" + std::to_string(muon) +
             ")";
    }
  };

  /**
   * Read and sample from a file of sampled tau decays.
   *
   * This class reads tau decays stored in NuTauSim-format and provides
   * methods to randomly sample simulations from this format.
   * See /data/particle/tauola for more information on the format
   * or see https://github.com/harmscho/NuTauSim for the original code.
   *
   * Each row of the datafile corresponds to a different decay simulation
   * showing the fractional energy transferred to the neutrino, leptonic,
   * and hadronic components.
   */
  class TauDecayTable final {

    private:
    static constexpr size_t nstates_{
        1000}; ///< The number of final states in the decay table
    static constexpr size_t nparticles_{
        6}; ///< The number of particles in each energy state
    const std::string filename_{"tau_decay_tauola.dat"};
    const std::array<double, nstates_ * nparticles_>
        finalstates_; ///< The array containing all the finalstates

    /**
     * Load the tau decay table from the file.
     *
     * The filename is given by this->filename_. This is currently
     * fixed at compile time but could easily be modified to load
     * arbitrary files.
     *
     * @returns The final state array loaded from the file.
     */
    auto
    load_decay_table() const -> decltype(finalstates_);

    /**
     * Return a random row-entry from the decay file.
     *
     * @returns A raw array of fraction energies.
     */
    auto
    random_state() const -> std::array<double, nparticles_>;

    public:
    /**
     * Load a decay table from a file.
     *
     * Currently, this loads from the file this->filename_.
     *
     */
    TauDecayTable() : finalstates_(load_decay_table()){};

    /**
     * Return a random decay state from the file.
     *
     * @returns A random entry from the tau decay file.
     */
    auto
    random_final_state() const -> TauDecayProducts;

  }; // END: class DecayTable final

} // namespace apricot

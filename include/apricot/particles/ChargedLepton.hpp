#pragma once

#include "apricot/Apricot.hpp"
#include "apricot/InteractionInfo.hpp"
#include "apricot/Particle.hpp"
#include "apricot/particles/Decayable.hpp"
#include "apricot/particles/TauDecayTable.hpp"
#include <cmath>

namespace apricot {

  /**
   * The supported energy loss models for charged leptons.
   */
  enum class LeptonEnergyLossModel { BDHM, Soyez, ALLM, BS };

  /**
   * An abstract base class for all charged leptons.
   *
   * This module provides methods common to Electron,
   * Muon, and Tau classes (currently). It cannot be
   * instantiated directly.
   *
   */
  class ChargedLepton : public Particle {

    public:
    /**
     * Create a charged lepton from its energy.
     *
     * @param energy    The energy in log10(eV).
     */
    ChargedLepton(const LogEnergy energy, const double mass) :
        Particle(energy),
        mass_(log10(mass)){};

    /**
     * Calculate the Lorentz (gamam) factor of this particle.
     */
    auto
    gamma() const -> double {
      return pow(10., energy_ - mass_);
    };

    /**
     * Get the next interacrtion this particle will undergo.
     *
     * This gives the type and grammage of the next interaction
     * as well as the lifetime before the next particle decay.
     *
     * @returns The parameters of the next interaction and decay.
     */
    virtual auto
    get_interaction() const -> InteractionInfo = 0;

    /**
     * Return a charged lepton from a generation.
     *
     * This returns either an Electron, Muon, or Tau with
     * the corresponding energy.
     *
     * @param generation  The generation of particle to create.
     * @param energy      The energy in log10(eV).
     *
     * @returns The created particle.
     */
    static auto
    from_generation(const Generation generation, const LogEnergy energy)
        -> std::unique_ptr<Particle>;

    /**
     * A virtual destructor.
     */
    virtual ~ChargedLepton() = default;

    /**
     * The mass of the lepton in log10(eV/c^2).
     */
    const double mass_;

    /**
     * The model to use for leptonic energy loss.
     *
     * This is set for all instances of the ChargedLepton classes.
     */
    inline static auto energy_loss_model{LeptonEnergyLossModel::ALLM};

  }; // END: class ChargedLepton

  /**
   * An electron.
   *
   */
  class Electron final : public ChargedLepton {

    public:
    /**
     * Create an electron with a given energy.
     *
     * @param energy  The particle energy in log10(eV).
     */
    Electron(const LogEnergy energy) : ChargedLepton(energy, 0.510998e6){};

    /**
     * Return the PDG ID of the electron.
     *
     * @returns the electron's PDG ID.
     */
    auto
    get_id() const -> ParticleID final {
      return PDG::Electron;
    };

    /**
     * Return a terminating interaction for all electrons.
     *
     * apricot does not support propagating UHE electrons so we
     * return a terminating InteractionInfo to end propagation.
     *
     * @returns A default InteractionInfo instance (no interaction).
     */
    auto
    get_interaction() const -> InteractionInfo final override {
      return InteractionInfo();
    }

    /**
     * Create a copy of this electron.
     *
     * @returns A unique_ptr to a copy of this electron.
     */
    auto
    clone() const -> std::unique_ptr<Particle> final override {
      return std::make_unique<Electron>(this->energy_);
    };

    /**
     * An empty destructor.
     */
    ~Electron(){};

  }; // END: class Electron

  /**
   * A muon.
   *
   */
  class Muon final : public ChargedLepton, public Decayable<Muon> {

    public:
    /**
     * Create a muon with a given energy.
     *
     * @param energy  The particle energy in log10(eV).
     */
    Muon(const LogEnergy energy) : ChargedLepton(energy, 105.66e6){};

    /**
     * Return the PDG ID of the muon.
     *
     * @returns the muon's PDG ID.
     */
    auto
    get_id() const -> ParticleID final {
      return PDG::Muon;
    };

    /**
     * Return the next interaction that this muon will experience.
     *
     * Since we use a continuous energy loss model for the muon-matter
     * interactions, our only 'discrete' Muon interaction is a decay.
     * This currently always returns a Muon decay with a randomly
     * sampled lifetime.
     *
     * @returns A default InteractionInfo instance (no interaction).
     */
    auto
    get_interaction() const -> InteractionInfo final override;

    /**
     * Create a copy of this muon.
     *
     * @returns A unique_ptr to a copy of this muon.
     */
    auto
    clone() const -> std::unique_ptr<Particle> final override {
      return std::make_unique<Muon>(this->energy_);
    };

    /**
     * An empty destructor.
     */
    ~Muon(){};

    /**
     * The mean muon lifetime (ns).
     */
    static constexpr double lifetime_{2.1969811e3};

  }; // END: class Muon

  /**
   * An tau lepton.
   *
   */
  class Tau final : public ChargedLepton, public Decayable<Tau> {

    public:
    /**
     * Create a tau with a given energy.
     *
     * @param energy  The particle energy in log10(eV).
     */
    Tau(const LogEnergy energy) : ChargedLepton(energy, 1776.86e6){};

    /**
     * Return the PDG ID of the tau.
     *
     * @returns the tau's PDG ID.
     */
    auto
    get_id() const -> ParticleID final {
      return PDG::Tau;
    };

    /**
     * Return the next interaction that this tau will experience.
     *
     * Since we use a continuous energy loss model for the tau-matter
     * interactions, our only 'discrete' Tau interaction is a decay.
     * This currently always returns a Tau decay with a randomly
     * sampled lifetime.
     *
     * @returns A default InteractionInfo instance (no interaction).
     */
    auto
    get_interaction() const -> InteractionInfo final override;

    /**
     * Get the decay products of a Tau decay.
     *
     * This uses a TauDecayTable to sample random tau decay's
     * produced using TAUOLA.
     *
     * @returns   A randomly chosen particle from a tau decay.
     */
    auto
    get_decay_product() const -> std::unique_ptr<Particle>;

    /**
     * Create a copy of this tau.
     *
     * @returns A unique_ptr to a copy of this tau.
     */
    auto
    clone() const -> std::unique_ptr<Particle> final override {
      return std::make_unique<Tau>(this->energy_);
    };

    /**
     * An empty destructor.
     */
    ~Tau(){};

    /**
     * The mean tau lifetime (ns)
     */
    static constexpr double lifetime_{2.903e-4};

    private:
    /**
     * A TauDecayTable to produce random tau decays.
     */
    inline static const TauDecayTable decaytable_;

  }; // END: class Tau

} // namespace apricot

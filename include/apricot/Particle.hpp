#pragma once

#include "apricot/Apricot.hpp"
#include "apricot/InteractionInfo.hpp"
#include <memory>

namespace apricot {

  /**
   * An alias for an abstract particle type.
   */
  class Particle;
  using ParticlePtr = std::unique_ptr<Particle>;

  /**
   * A list of PDG ID's (Particle ID) for various particles.
   */
  namespace PDG {
    static constexpr ParticleID Electron             = 11;
    static constexpr ParticleID Positron             = -11;
    static constexpr ParticleID ElectronNeutrino     = 12;
    static constexpr ParticleID AntiElectronNeutrino = -12;
    static constexpr ParticleID Muon                 = 13;
    static constexpr ParticleID AntiMuon             = -13;
    static constexpr ParticleID MuonNeutrino         = 14;
    static constexpr ParticleID AntiMuonNeutrino     = -14;
    static constexpr ParticleID Tau                  = 15;
    static constexpr ParticleID AntiTau              = -15;
    static constexpr ParticleID TauNeutrino          = 16;
    static constexpr ParticleID AntiTauNeutrino      = -16;
    static constexpr ParticleID Proton               = 2212;
    static constexpr ParticleID Neutron              = 2112;
    static constexpr ParticleID Photon               = 22;
    static constexpr ParticleID PiPlus               = 211;
    static constexpr ParticleID PiZero               = 111;
    static constexpr ParticleID PiMinus              = -211;
  } // namespace PDG

  /**
   * An abstract class representing all particles.
   */
  class Particle {

    public:
    /**
     * Construct a particle from an energy in log10(eV).
     */
    Particle(const double energy) : energy_(energy){};

    /**
     * Get the next interaction this particle should undergo.
     *
     * By default, this returns a "no interaction" struct.
     *
     */
    virtual auto
    get_interaction() const -> InteractionInfo {
      return InteractionInfo();
    }

    /**
     * Get the PDG ID of this particle.
     */
    virtual auto
    get_id() const -> ParticleID = 0;

    /**
     * Return a new pointer to a concrete instance.
     */
    virtual auto
    clone() const -> ParticlePtr = 0;

    /**
     * Get the particle energy in log10(eV).
     **/
    auto
    get_energy() const -> double {
      return energy_;
    };

    /**
     *  Set the particle energy in log10(eV).
     */
    auto
    set_energy(const double energy) -> void {
      energy_ = energy;
    };

    /*
     * The energy of the particle [log10(eV)].
     */
    double energy_;

    /**
     *  A virtual destructor so this class is abstract.
     */
    virtual ~Particle() = default;

  }; // END: class Particle

} // namespace apricot

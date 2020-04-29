#pragma once

#include "apricot/Particle.hpp"
#include "apricot/particles/NeutrinoCrossSection.hpp"
#include <memory>

namespace apricot {

  ///
  /// \brief An abstract class representing all neutrinos.
  ///
  class Neutrino : public Particle {

    public:
    ///
    /// \brief Construct an ElectronNeutrino from an energy in log10(eV).
    ///
    Neutrino(const double energy) : Particle(energy){};

    ///
    /// \brief Evaluate the UHE neutrino cross-section (g/cm^2).
    ///
    auto
    cross_section(const InteractionType& interaction) const -> double;

    ///
    /// \brief Get the next interaction for this particle.
    ///
    auto
    get_interaction() const -> InteractionInfo final override;

    ///
    /// \brief Return a random neutrino from an energy and flavor.
    ///
    /// Energy must be in log10(eV).
    ///
    static auto
    from_generation(const Generation flavor, const double energy)
        -> std::unique_ptr<Particle>;

    ///
    /// \brief A virtual destructor so this class is abstract.
    ///
    virtual ~Neutrino() = default;

    ///
    /// \brief The neutrino cross section model to use.
    ///
    inline static auto cross_section_model{NeutrinoCrossSectionModel::ConnollyMiddle};

  }; // END: class Neutrino

  ///
  /// \brief A concrete class for an ElectronNeutrino
  ///
  class ElectronNeutrino final : public Neutrino {

    public:
    ///
    /// \brief Construct an ElectronNeutrino from an energy in log10(eV).
    ///
    ElectronNeutrino(const LogEnergy energy) : Neutrino(energy){};

    ///
    /// \brief Return the particle's PDG ID.
    ///
    auto
    get_id() const -> ParticleID {
      return PDG::ElectronNeutrino;
    };

    ///
    /// \brief Return a new pointer to a concrete instance.
    ///
    auto
    clone() const -> std::unique_ptr<Particle> override {
      return std::make_unique<ElectronNeutrino>(this->energy_);
    };

    ///
    /// \brief A non-virtual destructor.
    ///
    ~ElectronNeutrino(){};

  }; // END: class ElectronNeutrino

  ///
  /// \brief A concrete class for an MuonNeutrino
  ///
  class MuonNeutrino final : public Neutrino {

    public:
    ///
    /// \brief Construct an MuonNeutrino from an energy in log10(eV).
    ///
    MuonNeutrino(const LogEnergy energy) : Neutrino(energy){};

    ///
    /// \brief Return the particle's PDG ID.
    ///
    auto
    get_id() const -> ParticleID {
      return PDG::MuonNeutrino;
    };

    ///
    /// \brief Return a new pointer to a concrete instance.
    ///
    auto
    clone() const -> std::unique_ptr<Particle> override {
      return std::make_unique<MuonNeutrino>(this->energy_);
    };

    ///
    /// \brief A non-virtual destructor.
    ///
    ~MuonNeutrino(){};

  }; // END: class MuonNeutrino

  ///
  /// \brief A concrete class for an TauNeutrino
  ///
  class TauNeutrino final : public Neutrino {

    public:
    ///
    /// \brief Construct an TauNeutrino from an energy in log10(eV).
    ///
    TauNeutrino(const LogEnergy energy) : Neutrino(energy){};

    ///
    /// \brief Return the particle's PDG ID.
    ///
    auto
    get_id() const -> ParticleID {
      return PDG::TauNeutrino;
    };

    ///
    /// \brief Return a new pointer to a concrete instance.
    ///
    auto
    clone() const -> std::unique_ptr<Particle> override {
      return std::make_unique<TauNeutrino>(this->energy_);
    };

    ///
    /// \brief A non-virtual destructor.
    ///
    ~TauNeutrino(){};

  }; // END: class TauNeutrino

} // namespace apricot

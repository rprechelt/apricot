#pragma once

#include "apricot/InteractionInfo.hpp"
#include "apricot/Particle.hpp"
#include <memory>

namespace apricot {

  /**
   * A constexpr function to UHECR's to PDG ID's
   */
  template <typename T> auto constexpr id() -> ParticleID { return PDG::Apricotino; }

  /**
   * An base class for all UHECR's.
   */
  template <typename T> class UHECR : public Particle {

    public:
    /**
     *  Construct a UHECR from an energy in log10(eV).
     */
    UHECR(const LogEnergy energy) : Particle(energy){};

    /**
     * Get the next interaction for this particle.
     *
     * This uses a quadratic fit to telescope array data.
     * See data/calibrations/Xmax.
     */
    auto
    get_interaction() const -> InteractionInfo final override {

      // return an interaction at shower max
      return InteractionInfo(interactions::ShowerMax, get_Xmax(energy_));
    }

    /**
     * Calculate the grammage at showe max
     */
    static auto
    get_Xmax(const LogEnergy energy) -> double {
      return T::a_ * energy * energy + T::b_ * energy + T::c_;
    }

    /**
     * Return the particle's PDG ID.
     */
    auto
    get_id() const -> ParticleID final override {
      return apricot::id<T>();
    };

    /**
     * A virtual destructor.
     */
    virtual ~UHECR() = default;

    /**
     * Return a new pointer to a concrete instance.
     */
    auto
    clone() const -> std::unique_ptr<Particle> override {
      return std::make_unique<T>(this->energy_);
    };

    /**
     * Get a const reference to the underlying type.
     */
    T const&
    underlying() const {
      return static_cast<T const&>(*this);
    }

  }; // END: class UHECR

  // we create supported UHECR's below

  /*
   * An UHECR proton.
   */
  class Proton final : public UHECR<Proton> {

    public:
    // the parameters for a fit to average shower max
    // from 8.5 years of Telescope Array data.
    static constexpr double a_{-5.21640};
    static constexpr double b_{244.91536};
    static constexpr double c_{-1989.9836};

    /**
     * Construct an UHECR proton from an energy [log10(eV)].
     */
    Proton(const LogEnergy energy) : UHECR(energy){};
  }; // END: Proton

  /*
   * An UHECR helium
   */
  class Helium final : public UHECR<Helium> {

    public:
    // the parameters for a fit to average shower max
    // from 8.5 years of Telescope Array data.
    static constexpr double a_{-8.554321};
    static constexpr double b_{374.29550};
    static constexpr double c_{-3269.18886};

    /**
     * Construct an UHECR helium from an energy [log10(eV)].
     */
    Helium(const LogEnergy energy) : UHECR(energy){};
  }; // END: Helium

  /*
   * An UHECR nitrogen
   */
  class Nitrogen final : public UHECR<Nitrogen> {

    public:
    // the parameters for a fit to average shower max
    // from 8.5 years of Telescope Array data.
    static constexpr double a_{3.16165};
    static constexpr double b_{-66.0359};
    static constexpr double c_{836.2584};

    /**
     * Construct an UHECR nitrogen from an energy [log10(eV)].
     */
    Nitrogen(const LogEnergy energy) : UHECR(energy){};
  }; // END: Nitrogen

  /*
   * An UHECR iron
   */
  class Iron final : public UHECR<Iron> {

    public:
    // the parameters for a fit to average shower max
    // from 8.5 years of Telescope Array data.
    // Xmax = a*log(energy)**2. + b*log(energy) + c
    static constexpr double a_{4.99839};
    static constexpr double b_{-136.00973};
    static constexpr double c_{1471.62867};

    /**
     * Construct an UHECR iron from an energy [log10(eV)].
     */
    Iron(const LogEnergy energy) : UHECR(energy){};
  }; // END: Iron

  /*
   * This class represents an *average* over the cosmic ray spectrum.
   *
   * This uses a fit to telescope array data for the measured
   * cosmic ray spectrum which is not a pure single-species flux.
   */
  class MixedUHECR final : public UHECR<MixedUHECR> {

    public:
    // the parameters for a fit to average shower max
    // from 8.5 years of Telescope Array data.
    // Xmax = a*log(energy)**2. + b*log(energy) + c
    static constexpr double a_{-26.20137};
    static constexpr double b_{1034.4526};
    static constexpr double c_{-9435.8754};

    /**
     * Construct a mixed UHECR from an energy [log10(eV)].
     */
    MixedUHECR(const LogEnergy energy) : UHECR(energy){};
  }; // END: MixedUHECR

  // we now override the ID function for all of our created
  // cosmic rays
  template <>
  constexpr auto
  id<Proton>() -> ParticleID {
    return PDG::Proton;
  }
  template <>
  constexpr auto
  id<Helium>() -> ParticleID {
    return PDG::Helium;
  }
  template <>
  constexpr auto
  id<Nitrogen>() -> ParticleID {
    return PDG::Nitrogen;
  }
  template <>
  constexpr auto
  id<Iron>() -> ParticleID {
    return PDG::Iron;
  }

} // namespace apricot

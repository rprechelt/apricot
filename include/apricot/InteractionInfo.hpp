#pragma once

namespace apricot {

  /**
   * An alias for an interaction type.
   */
  using InteractionType = int;

  /*
   * Various standard particle interactions.
   */
  namespace interactions {

    /**
     * A no-op interaction.
     */
    static constexpr InteractionType No = 0;

    /**
     * A neutrino charged current interaction.
     */
    static constexpr InteractionType ChargedCurrent = 1;

    /**
     * A neutrino neutral current interaction.
     */
    static constexpr InteractionType NeutralCurrent = 2;

    /**
     * A lepton decay interactions.
     */
    static constexpr InteractionType Decay = 3;

    /**
     * A cosmic ray has reached shower max.
     */
    static constexpr InteractionType ShowerMax = 100;

    /*
     * An unknown or unspecified interaction.
     */
    static constexpr InteractionType Other = -1;

  } // namespace interactions

  /**
   * A possible interaction.
   */
  struct InteractionInfo final {

    InteractionType type_; ///< The type of this interaction.
    double grammage_;      ///< The grammage (g/cm^2) for a particle-medium interaction
    double lifetime_;      ///< The lab decay time (ns) at which a decay should occur.

    ///
    /// \brief Construct a new InteractionInfo.
    ///
    InteractionInfo(const InteractionType& type,
                    const double grammage,
                    const double lifetime = -1.)
        : type_(type), grammage_(grammage), lifetime_(lifetime){};

    /**
     * An instance indicating *no* future interaction.
     *
     * This has no interaction grammage and no lifetime so
     * will never interact in our propagators. This should
     * effectively terminate this particle.
     */
    InteractionInfo() : type_(interactions::No), grammage_(-1.), lifetime_(-1.){};

  }; // END: struct InteractionInfo

} // namespace apricot

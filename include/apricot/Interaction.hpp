#pragma once

#include "apricot/Apricot.hpp"
#include "apricot/Coordinates.hpp"
#include "apricot/InteractionInfo.hpp"
#include <forward_list>
#include <memory>
#include <vector>

namespace apricot {

  /* Forward declarations */
  class Particle;

  /**
   * A base class for all particle interactions.
   *
   * These are stored as POD's (no Eigen allowed) so that
   * it is directly convertible to NumPy arrays and to ROOT
   * data files.
   *
   * Typically, I make all of these entries const-members
   * however that breaks the PyBind11 wrapping (a bug in
   * the current version of PyBind11). These will be made
   * const as PyBind11 is fixed.
   */
  struct Interaction {

    /**
     * Construct a new Interaction.
     *
     * @param ntrials     The number of prior trials.
     * @param particle    The particle that interacted.
     * @param type        The type of the interaction.
     * @param location    The geocentric location of the interaction.
     * @param direction   The direction of the particle momentum.
     *
     */
    Interaction(const int ntrials,
                const std::unique_ptr<Particle>& particle,
                const InteractionType type,
                const CartesianCoordinate& location,
                const Vector& direction);

    /**
     * Construct a new Interaction.
     *
     * @param ntrials     The number of prior trials.
     * @param energy      The energy of the particle [log10(eV)].
     * @param pid         The ID of the interacting particle.
     * @param type        The type of the interaction.
     * @param location    The geocentric location of the interaction.
     * @param direction   The direction of the particle momentum.
     *
     */
    Interaction(const int ntrials,
                const ParticleID pid,
                const LogEnergy energy,
                const InteractionType type,
                const CartesianCoordinate& location,
                const Vector& direction);

    int ntrials_;                  ///< The number of trials before this interaction.
    ParticleID pdgid_;             ///< The PDG ID of the interacting particle.
    LogEnergy energy_;             ///< The energy of the interacting particle [log10(eV)].
    InteractionType type_;         ///< The type of the interaction that occured.
    CartesianCoordinate location_; ///< The location of the interaction [km].
    Vector direction_;             ///< The unit-length direction vector.

    /**
     * A virtual default destructor.
     */
    virtual ~Interaction() = default;

  }; // END: struct Interaction

  /*
   * An alias for a tree of interactions.
   */
  using InteractionTree = std::vector<std::unique_ptr<Interaction>>;

  /*
   * An alias for a collection of many interaction trees.
   */
  using Events = std::vector<InteractionTree>;

} // namespace apricot

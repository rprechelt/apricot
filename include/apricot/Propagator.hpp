#pragma once

#include "apricot/Coordinates.hpp"
#include "apricot/Interaction.hpp"
#include "apricot/Particle.hpp"

#include <tuple>

namespace apricot {

  /* Forward Declarations */
  class Flux;
  class Earth;
  class Source;
  class Particle;
  class Detector;

  /**
   * A base class for all apricot propagators.
   *
   * Propagators are responsible for taking particles
   * from Source and Flux models and propagating them
   * through the Earth to a Detector.
   *
   * This propagator propagates a single particle at a
   * time from the source+flux to the detector.
   *
   */
  class Propagator {

    public:
    const Earth& earth_; ///< The Earth model we use for propagation.
    int maxtrials_{
        1'000'000}; ///< The maximum number of trials without success before halting.

    /**
     * Create a new Propagator for a given Earth model.
     */
    Propagator(const Earth& earth) : earth_(earth){};

    /**
     * Propagate several particles from a Source to a Detector.
     *
     * @param source     The Source model to generate particle tracks.
     * @param flux       The Flux model to generate particles
     * @param detector   The Detector model used to detect particles.
     * @param N          The number of interactions to generate.
     *
     */
    auto
    propagate(Source& source, Flux& flux, const Detector& detector, const int N) const
        -> Events;

    /**
     * Propagate a single particle from a Source to a Detector.
     *
     * @param earth      The Earth model to use for propagation.
     * @param source     The Source model to generate particle tracks.
     * @param flux       The Flux model to generate particles
     * @param detector   The Detector model used to detect particles.
     *
     */
    virtual auto
    propagate(Source& source, Flux& flux, const Detector& detector) const
        -> InteractionTree = 0;

    /**
     * A default virtual destructor.
     */
    virtual ~Propagator() = default;

    protected:
    /**
     * Calculate the step size for propagation.
     *
     * @param particle   The particle that is being processed.
     * @param location   The location of the particle.
     *
     */
    virtual auto
    step_size(const ParticlePtr& particle, const CartesianCoordinate& location) const
        -> double;

    protected:
    /**
     * Return the starting parameters of a new trials.
     *
     */
    auto
    new_trial(Source& source, Flux& flux) const
        -> std::tuple<ParticlePtr, CartesianCoordinate, Vector, InteractionInfo>;

    /**
     * Step a location vector to the next step and return the grammage.
     *
     * This returns the total grammage (g/cm^2) of the step.
     *
     * @param earth      The earth model to propagate through.
     * @param location   The current location of the particle.
     * @param direction  The unit-length momentum direction.
     *
     */
    auto
    step(const ParticlePtr& particle,
         CartesianCoordinate& location,
         Vector& direction) const -> double;

  }; // END: class Propagator

} // namespace apricot

#pragma once

#include "apricot/Propagator.hpp"

namespace apricot {

  /* Forward Declarations */
  class Flux;
  class Earth;
  class Source;
  class Particle;
  class Detector;

  /**
   * Propagate a particle through to a single interaction.
   *
   * This propagator samples particles from the source+flux
   * and propagates them until they have interacted. They are
   * then passed to the detector and saved if they are
   * detectable. This propagator does not continue propagating
   * particles after their first propagation.
   *
   */
  class SimplePropagator final : public Propagator {

    public:

    /**
     * Construct a SimplePropagator.
     */
    SimplePropagator(const Earth& earth) : Propagator(earth) {}

    /**
     * Propagate a single particle from a Source to a Detector.
     *
     * @param earth      The Earth model to use for propagation.
     * @param source     The Source model to generate particle tracks.
     * @param flux       The Flux model to generate particles
     * @param detector   The Detector model used to detect particles.
     *
     */
    auto
    propagate(Source& source,
              Flux& flux,
              const Detector& detector) const -> InteractionTree final override;

    /**
     * A default virtual destructor.
     */
    ~SimplePropagator(){};

  }; // END: class Propagator

} // namespace apricot

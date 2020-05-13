#include "apricot/propagators/SimplePropagator.hpp"
#include "apricot/Detector.hpp"
#include "apricot/Earth.hpp"
#include "apricot/Flux.hpp"
#include "apricot/Interaction.hpp"
#include "apricot/Source.hpp"

using namespace apricot;

auto
SimplePropagator::propagate(Source& source, Flux& flux, const Detector& detector) const
    -> InteractionTree {

  // create the tree to store the particles
  InteractionTree tree;

  // get a new trial particle to propagate
  auto [particle, location, direction, info]{new_trial(source, flux)};

  // check if this is a good particle
  if (!detector.is_good(particle, location, direction)) return tree;

  // this is the grammage that we accumulate over this trial
  double grammage{0.};

  // compute the dot product weight for this trial
  const double weight{location.normalized().dot(direction)};

  // now loop through the Earth until we reach our propagation limits
  while (!detector.cut(particle, location, direction)) {

    // step the particle along the direction and accumulate the grammage
    grammage += this->step(particle, location, direction);

    // if we have reached our interaction grammage
    if (grammage >= info.grammage_) {

      // if the particle is detectable, return the interaction
      if (detector.detectable(info, particle, location, direction)) {

        // compute the altitude of the interaction
        const auto altitude{location.norm() - earth_.radius(location)};

        // return the interaction that occured
        tree.emplace_back(std::make_unique<Interaction>(
            particle, info.type_, location, direction, weight, altitude));

        return tree;

      } // END: if (detector.detectable...

      // we have interacted but it was not detected
      // so break from our loop to try again
      break; // this breaks from while (!detector...

    } // END: if (grammage >= info.grammage)

  } // END: while (!detector.cut..

  // if we have reached here, the particle has interacted
  // but wasn't 'detected' or was cut by the detector before it
  // interacted.

  // so return the (empty) tree
  return tree;

} // END: propagate

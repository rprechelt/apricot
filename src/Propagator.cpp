#include "apricot/Propagator.hpp"
#include "apricot/Flux.hpp"
#include "apricot/Earth.hpp"
#include "apricot/Interaction.hpp"
#include "apricot/Particle.hpp"
#include "apricot/Source.hpp"

using namespace apricot;

// propagate many interactions
auto
Propagator::propagate(Source& source,
                      Flux& flux,
                      const Detector& detector,
                      const int N) const -> Events {

  // create a new InteractionTree
  Events interactions;

  // resize it to store the number of events that were requested
  interactions.reserve(N);

  // loop over the number of interactions
  for (int i = 0; i < N; ++i) {
    // propagate one particle
    interactions.push_back(propagate(source, flux, detector));
  }

  // and we are done
  return interactions;
}

auto
Propagator::new_trial(Source& source, Flux& flux) const
    -> std::tuple<ParticlePtr, CartesianCoordinate, Vector, InteractionInfo> {

  // random pick a new particle from this source
  auto particle{flux.get_particle()};

  // randomly pick a new start location and direction
  auto [location, direction]{source.get_origin()};

  // get the next interaction by this particle
  const auto info{particle->get_interaction()};

  // and return it all
  return std::make_tuple(std::move(particle), location, direction, info);
}

auto
Propagator::step(const ParticlePtr& particle,
                 CartesianCoordinate& location,
                 Vector& direction) const -> double {


  // get the step size at the current location
  const auto step_length{this->step_size(particle, location)};

  // compute one-half of the step-length
  const auto half_step{0.5 * step_length * direction};

  // step the particle to the midpoint
  location += half_step;

  // get the density at the midpoint
  const double density{earth_.density(location)};

  // and step the particle the rest of the way
  location += half_step;

  // increment the grammage we have travelled through
  return density * 1e5 * step_length; // grammage in cm, step_size in km
}

auto
Propagator::step_size(const std::unique_ptr<Particle>& particle,
                      const CartesianCoordinate& location) const -> double {


    // get the radius of this point normalized to an average Earth radius.
  const double x{location.norm() / earth_.radius(location)};

  // and do a four-piece step function returning step size in km
  if (x < 0.85)
    return 10; // 10km
  if (x < 0.9)
    return 5; // 5km
  if (x < 0.99)
    return 1; // 1km
  if (x < 0.999)
    return 50e-3;     // 50m
  if (x < (1 + 8e-4)) // in ice up to surface of Antarctica at 4km
    return 10e-3;      // in firn/ice

  // we are in air
  return 10e-3;
}

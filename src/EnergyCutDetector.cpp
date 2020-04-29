#include "apricot/detectors/EnergyCutDetector.hpp"
#include "apricot/Particle.hpp"

using namespace apricot;

//  Return True if a particle should be saved / considered a success.
auto
EnergyCutDetector::detectable(const InteractionInfo& info,
                              const std::unique_ptr<Particle>& particle,
                              const CartesianCoordinate& location,
                              const CartesianCoordinate& direction) const -> bool {
  return has_valid_energy(particle);
}

// do we have a valid energy for our cut.
auto
EnergyCutDetector::has_valid_energy(const std::unique_ptr<Particle>& particle) const
    -> bool {
  return (particle->get_energy() < max_energy_) && (particle->get_energy() > min_energy_);
}

auto
EnergyCutDetector::cut(const std::unique_ptr<Particle>& particle,
                       const CartesianCoordinate& location,
                       const CartesianCoordinate& direction) const -> bool {

  // if it's less than the minimum energy, cut it
  if (particle->get_energy() < this->min_energy_) return true;

  // otherwise, keep propagating
  return false;

}

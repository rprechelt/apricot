#include "apricot/Interaction.hpp"
#include "apricot/Particle.hpp"

using namespace apricot;

Interaction::Interaction(const int ntrials,
                         const std::unique_ptr<Particle>& particle,
                         const InteractionType type,
                         const CartesianCoordinate& location,
                         const Vector& direction)
    : ntrials_(ntrials), pdgid_(particle->get_id()), energy_(particle->get_energy()),
      type_(type), location_(location), direction_(direction) {}

Interaction::Interaction(const int ntrials,
                         const ParticleID pid,
                         const LogEnergy energy,
                         const InteractionType type,
                         const CartesianCoordinate& location,
                         const Vector& direction)
    : ntrials_(ntrials), pdgid_(pid), energy_(energy), type_(type), location_(location),
      direction_(direction) {}

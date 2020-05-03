#include "apricot/Interaction.hpp"
#include "apricot/Particle.hpp"

using namespace apricot;

Interaction::Interaction(const std::unique_ptr<Particle>& particle,
                         const InteractionType type,
                         const CartesianCoordinate& location,
                         const Vector& direction,
                         const double weight,
                         const double altitude)
    : pdgid_(particle->get_id()), energy_(particle->get_energy()), type_(type),
      location_(location), direction_(direction), weight_(weight), altitude_(altitude) {}

Interaction::Interaction(const ParticleID pid,
                         const LogEnergy energy,
                         const InteractionType type,
                         const CartesianCoordinate& location,
                         const Vector& direction,
                         const double weight,
                         const double altitude)

    : pdgid_(pid), energy_(energy), type_(type), location_(location), direction_(direction),
      weight_(weight), altitude_(altitude) {}

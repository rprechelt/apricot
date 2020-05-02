
#pragma once

#include "apricot/Constants.hpp"
#include "apricot/Random.hpp"

namespace apricot {

  /*
   * This is a CRTP class for adding particle decays to sub-classes.
   *
   * Any classes that inherit from this class using CRTP
   * gain decay_time() and decay_length() methods. The particle
   * sub-class must have a `lifetime_` member variable and provide
   * a gamma() function that returns the Lorentz factor.
   *
   */
  template <typename T> struct Decayable {

    /*
     * Randomly sample a particle lifetime in ns.
     *
     * @returns A random particle lifetime in nanosecond.
     */
    auto
    decay_time() const -> double {

      // get a reference to the underlying particle
      const auto particle{this->get_particle()};

      // compute the exponential parameter
      const double lambda{1. / particle.lifetime_};

      // return a randomly sampled lifetime (in ns)
      // in the rest frame of the muon
      auto time{random::exponential<double>(lambda)};

      // boost this lifetime into the lab frame
      time *= particle.gamma();

      // and return the boosted time
      return time;
    };

    /*
     * Return a random decay length in km.
     *
     * This assumes the particle is travelling at *c*.
     *
     * @returns A random decay length in kilometer.
     */
    auto
    decay_length() const -> double {

      // get a random decay_time
      const auto time{decay_time()};

      // and convert this to a decay-length
      const auto length{C_km_ns * time};

      // and we are done.
      return length;
    }

    private:
    /*
     * Get a reference to the underlying particle instance.
     *
     * @returns A mutable reference to the underlying  particle.
     */
    auto
    get_particle() -> T& {
      return static_cast<T&>(*this);
    }

    /*
     * Get a const reference to the underlying particle instance.
     *
     * @returns A const reference to the underlying particle.
     */
    auto
    get_particle() const -> T const& {
      return static_cast<T const&>(*this);
    }

  }; // END: struct Decayable

} // namespace apricot

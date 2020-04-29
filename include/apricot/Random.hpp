/**
 * This file provides some easy routines to generate a variety
 * of random numbers. This should be used for all random
 * number generation in apricot to ensure reproducibility.
 *
 * While each new random number generation creates a new
 * generator, the initialization of a generator is
 * very light and adds only a few instructions.
 *
 * If you wish to generate other random numbers, please
 * ensure that you use this `generator` instance to ensure
 * reproducibility.
 */
#pragma once

#include <random>

namespace apricot::random {

  /**
   * A 64-bit Mersenne twister RNG.
   *
   * Note: this is *significantly* faster than the standard
   * mt19937 generator with random performance that is almost
   * as good (there's still plenty of entropy for our application).
   */
  inline static std::mt19937_64 generator(999983);

  /**
   * A templated uniform random number generator.
   *
   * The default range is [0, 1).
   * For accuracy, we recommend using always using this
   * with `double`, not `float.*
   *
   * @param min   The minimum value generated.
   * @param max   The maximum value generated (exclusive).
   */
  template <typename T>
  inline auto
  uniform(const T min = 0., const T max = 1.) -> T {

    // a uniform dist generator
    std::uniform_real_distribution<T> dist(min, max);

    // and convert it to the desired distribution
    return dist(generator);
  }

  /**
   * A templated uniform integer random number generator.
   *
   * @param min  The minimum value generated.
   * @param max  The maximum value generated (inclusive).
   */
  inline auto
  uniform_int(const int min, const int max) -> int {

    // a uniform dist generator
    std::uniform_int_distribution<int> dist(min, max);

    // and convert it to the desired distribution
    return dist(generator);
  }

  /**
   * A templated exponential random generator.
   *
   * For accuracy, we recommend using always using this
   * with `double`, not `float.`
   *
   * @param lambda  The exponential parameter.
   */
  template <typename T>
  inline auto
  exponential(const T lambda) -> T {

    // a uniform dist generator
    std::exponential_distribution<T> dist(lambda);

    // and convert it to the desired distribution
    return dist(generator);
  }

  /**
   * A templated Poisson random generator.
   *
   * For accuracy, we recommend using always using this
   * with `double`, not `float.`
   *
   * @param mu  The Poisson parameter.
   */
  template <typename T>
  inline auto
  poisson(const T mu) -> T {

    // a uniform dist generator
    std::poisson_distribution<int> dist(mu);

    // and convert it to the desired distribution
    return dist(generator);
  }

  /**
   * A templated Gaussian generator.
   *
   * By default this has mean 0 and stdev 1.
   * For accuracy, we recommend using always using this
   * with `double`, not `float.`  *
   *
   * @param mean    The Gaussian mean.
   * @param stdev   The Gaussian standard deviation.
   */
  template <typename T>
  inline auto
  gaussian(const T mean = 0., const T stdev = 1.) -> T {

    // a uniform dist generator
    std::normal_distribution<T> dist(mean, stdev);

    // and convert it to the desired distribution
    return dist(generator);
  }

} // namespace apricot::random

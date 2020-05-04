#pragma once


namespace apricot {

  /**
   * Return the sign of the value.
   *
   * This returns >1 if the value is positive,
   * <1 if the value is negative, and zero if the
   * argument is zero.
   *
   * @param val    The value to check
   *
   * @returns sgn  The sign of the argument
   */
  template <typename T> auto
  sgn(const T val) -> int {
    return (T(0) < val) - (val < T(0));
  }


}

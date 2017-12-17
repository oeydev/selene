// This file is part of the `Selene` library.
// Copyright 2017 Michael Hofmann (https://github.com/kmhofmann).
// Distributed under MIT license. See accompanying LICENSE file in the top-level directory.

#ifndef SELENE_BASE_ROUND_HPP
#define SELENE_BASE_ROUND_HPP

/// @file

#include <cstdint>
#include <type_traits>

namespace sln {

/** \brief Rounds the given floating point value to the nearest integer value.
 *
 * The rounding is biased, such that values with fraction 0.5 will always be rounded up.
 *
 * @tparam Result The result value type. Has to be an integral type.
 * @tparam Value The input value type. Has to be a floating point type.
 * @param val The input value.
 * @return The rounded output value.
 */
template <typename Result, typename Value>
inline constexpr Result round_half_up(Value val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  static_assert(std::is_floating_point<Value>::value, "Argument to round not floating point");
  return static_cast<Result>(val + Value{0.5});
}

/** \brief Rounds the given floating point value to the nearest integer value.
 *
 * The rounding is biased, such that values with fraction 0.5 will always be rounded down.
 *
 * @tparam Result The result value type. Has to be an integral type.
 * @tparam Value The input value type. Has to be a floating point type.
 * @param val The input value.
 * @return The rounded output value.
 */
template <typename Result, typename Value>
inline constexpr Result round_half_down(Value val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  static_assert(std::is_floating_point<Value>::value, "Argument to round not floating point");
  return static_cast<Result>(val - Value{0.5});
}

/** \brief Rounds the given floating point value to the nearest integer value.
 *
 * The rounding may be biased in an unspecified way when rounding values with fraction 0.5.
 *
 * @tparam Result The result value type.
 * @tparam Value The input value type.
 * @param val The input value.
 * @return The rounded output value.
 */
template <typename Result, typename Value>
inline constexpr Result round(Value val)
{
  return round_half_up<Result>(val);
}

/// \cond INTERNAL

template <typename Result>
inline constexpr Result round(char val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(signed char val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(unsigned char val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(short val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(unsigned short val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(int val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(unsigned int val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(long val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(unsigned long val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(long long val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

template <typename Result>
inline constexpr Result round(unsigned long long val)
{
  static_assert(std::is_integral<Result>::value, "Cannot round to non-integral type");
  return static_cast<Result>(val);
}

/// \endcond

}  // namespace sln

#endif  // SELENE_BASE_ROUND_HPP

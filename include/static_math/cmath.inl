/*
 * Copyright (C) 2011-2012 Morwenn
 *
 * static_math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * static_math is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

namespace
{
    template<typename T, typename U>
    constexpr T _pow_helper(T acc, T value, U times)
    {
        return (times > 1) ?
            _pow_helper(acc*value, value, times-1) :
                acc;
    }
}

template<typename T>
constexpr
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
abs(T x)
{
    return (x >= 0) ? x : -x;
}

template<typename Numeric, typename... Rest>
constexpr
Numeric min(Numeric first, Numeric second, Rest... rest)
{
    return (first < second) ? min(first, rest...) : min(second, rest...);
}

template<typename Numeric>
constexpr
Numeric min(Numeric first, Numeric second)
{
    return (first < second) ? first : second;
}

template<typename Numeric, typename... Rest>
constexpr
Numeric max(Numeric first, Numeric second, Rest... rest)
{
    return (first > second) ? max(first, rest...) : max(second, rest...);
}

template<typename Numeric>
constexpr
Numeric max(Numeric first, Numeric second)
{
    return (first > second) ? first : second;
}

template<typename Float>
constexpr
typename std::enable_if<std::is_floating_point<Float>::value, int>::type
floor(Float value)
{
    return (int(value) == value) ? int(value) :
        (value >= 0.0) ? int(value) :
            int(value) - 1;
}

template<typename Float>
constexpr
typename std::enable_if<std::is_floating_point<Float>::value, int>::type
ceil(Float value)
{
    return (int(value) == value) ? int(value) :
        (value >= 0.0) ? int(value) + 1 :
            int(value);
}

template<typename Float>
constexpr
typename std::enable_if<std::is_floating_point<Float>::value, int>::type
round(Float value)
{
    return (value >= 0.0) ? int(value + 0.5) : int(value - 0.5);
}

template<typename Float>
constexpr
typename std::enable_if<std::is_floating_point<Float>::value, int>::type
trunc(Float value)
{
    return int(value);
}

template<typename T, typename U>
constexpr
typename std::enable_if<std::is_integral<U>::value && std::is_arithmetic<T>::value, T>::type
pow(T value, U exponent)
{
    return (exponent == 0) ? 1 :
        (exponent > 0) ? _pow_helper(value, value, exponent) :
            1 / _pow_helper(value, value, exponent);
}
// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Precomputed.h
//! @brief     Defines classes Precomputed, providing precomputed constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PRECOMPUTED_H
#define PRECOMPUTED_H

#include "WinDllMacros.h"
#include "ISingleton.h"
#include <array>
#include <utility>
#include <vector>

//! Compile-time generated std::arrays of factorials and their reciprocals
namespace Precomputed
{
template<size_t N>
struct Factorial
{
    static constexpr double value = N*Factorial<N - 1>::value;
};

template<>
struct Factorial<0>
{
    static constexpr double value = 1.0;
};

template<size_t N>
struct ReciprocalFactorial
{
    static constexpr double value = 1.0/Factorial<N>::value;
};

template<template<size_t> class F, size_t... I>
constexpr std::array<double, sizeof...(I)> GenerateArrayHelper(std::integer_sequence<size_t, I...>)
{
    return { F<I>::value... };
};

template<size_t N, typename Indices = std::make_index_sequence<N>>
constexpr std::array<double, N> GenerateFactorialArray()
{
    return GenerateArrayHelper<Factorial>(Indices{});
};

template<size_t N, typename Indices = std::make_index_sequence<N>>
constexpr std::array<double, N> GenerateReciprocalFactorialArray()
{
    return GenerateArrayHelper<ReciprocalFactorial>(Indices{});
};
}  // namespace Precomputed

#endif // PRECOMPUTED_H

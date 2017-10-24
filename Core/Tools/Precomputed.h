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

//! Compile-time generated std::array of reciprocal factorials
namespace Precomputed
{
template<size_t N>
struct ReciprocalFactorial
{
    static constexpr double value = ReciprocalFactorial<N-1>::value/N;
};

template<>
struct ReciprocalFactorial<0>
{
    static constexpr double value = 1.0;
};

template<template<size_t> class F, size_t... I>
constexpr std::array<double, sizeof...(I)> GenerateArrayHelper(std::index_sequence<I...>)
{
    return { F<I>::value... };
};

template<size_t N, typename Indices = std::make_index_sequence<N>>
constexpr std::array<double, N> GenerateReciprocalFactorialArray()
{
    return GenerateArrayHelper<ReciprocalFactorial>(Indices{});
};
}  // namespace Precomputed

#endif // PRECOMPUTED_H

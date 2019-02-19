// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/IPositionBuilder.h
//! @brief     Declares interface IPositionBuilder and subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IPOSITIONBUILDER_H
#define IPOSITIONBUILDER_H

#include <vector>

class IPositionBuilder
{
public:
    virtual ~IPositionBuilder();

    virtual std::vector<std::vector<double>> generatePositions(double layer_size,
                                                               double density = 0.0) const = 0;
};

class RandomPositionBuilder : public IPositionBuilder
{
public:
    RandomPositionBuilder();
    ~RandomPositionBuilder() override;

    std::vector<std::vector<double>> generatePositions(double layer_size,
                                                       double density = 0.0) const override;
};

#endif // IPOSITIONBUILDER_H

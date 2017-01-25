// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/Lattice2DItems.h
//! @brief     Defines classes Lattice2DItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef LATTICE2DITEMS_H
#define LATTICE2DITEMS_H

#include "SessionItem.h"
class Lattice2D;

class BA_CORE_API_ Lattice2DItem : public SessionItem
{
public:
    explicit Lattice2DItem(const QString& modelType);
};


class BA_CORE_API_ BasicLatticeItem : public Lattice2DItem
{
public:
    static const QString P_LATTICE_LENGTH1;
    static const QString P_LATTICE_LENGTH2;
    static const QString P_LATTICE_ANGLE;
    BasicLatticeItem();
};

class BA_CORE_API_ SquareLatticeItem : public Lattice2DItem
{
public:
    static const QString P_LATTICE_LENGTH;
    SquareLatticeItem();
};

class BA_CORE_API_ HexagonalLatticeItem : public Lattice2DItem
{
public:
    static const QString P_LATTICE_LENGTH;
    HexagonalLatticeItem();
};

#endif // LATTICE2DITEMS_H

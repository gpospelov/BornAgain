// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LatticeTypeItems.h
//! @brief     Declares classes LatticeTypeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef LATTICETYPEITEMS_H
#define LATTICETYPEITEMS_H

#include "SessionItem.h"

class BA_CORE_API_ BasicLatticeTypeItem : public SessionItem
{

public:
    static const QString P_LATTICE_LENGTH1;
    static const QString P_LATTICE_LENGTH2;
    static const QString P_LATTICE_ANGLE;
    explicit BasicLatticeTypeItem();
    virtual ~BasicLatticeTypeItem(){}
};

class BA_CORE_API_ SquareLatticeTypeItem : public SessionItem
{

public:
    static const QString P_LATTICE_LENGTH;
    explicit SquareLatticeTypeItem();
    virtual ~SquareLatticeTypeItem(){}
};

class BA_CORE_API_ HexagonalLatticeTypeItem : public SessionItem
{

public:
    static const QString P_LATTICE_LENGTH;
    explicit HexagonalLatticeTypeItem();
    virtual ~HexagonalLatticeTypeItem(){}
};

#endif // LATTICETYPEITEMS_H

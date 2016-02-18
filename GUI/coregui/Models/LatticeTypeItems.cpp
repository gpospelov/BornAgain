// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/LatticeTypeItems.cpp
//! @brief     Implements classes LatticeTypeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LatticeTypeItems.h"
#include "Units.h"

const QString BasicLatticeTypeItem::P_LATTICE_LENGTH1 = "Lattice_length_1";
const QString BasicLatticeTypeItem::P_LATTICE_LENGTH2 = "Lattice_length_2";
const QString BasicLatticeTypeItem::P_LATTICE_ANGLE = "Lattice_angle";
const QString SquareLatticeTypeItem::P_LATTICE_LENGTH = "Lattice_length";
const QString HexagonalLatticeTypeItem::P_LATTICE_LENGTH = "Lattice_length";


BasicLatticeTypeItem::BasicLatticeTypeItem()
    : ParameterizedItem(QString("BasicLatticeType"))
{
    registerProperty(P_LATTICE_LENGTH1, 20.0);
    registerProperty(P_LATTICE_LENGTH2, 20.0);
    registerProperty(P_LATTICE_ANGLE, 90.0);
}

SquareLatticeTypeItem::SquareLatticeTypeItem()
    : ParameterizedItem(QString("SquareLatticeType"))
{
    registerProperty(P_LATTICE_LENGTH, 20.0);
}

HexagonalLatticeTypeItem::HexagonalLatticeTypeItem()
    : ParameterizedItem(QString("HexagonalLatticeType"))
{
    registerProperty(P_LATTICE_LENGTH, 20.0);
}

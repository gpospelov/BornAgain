// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/Lattice2DItems.cpp
//! @brief     Implements classes Lattice2DItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "Lattice2DItems.h"
#include "BornAgainNamespace.h"

Lattice2DItem::Lattice2DItem(const QString& modelType)
    : SessionItem(modelType)
{

}


const QString BasicLatticeItem::P_LATTICE_LENGTH1
    = QString::fromStdString(BornAgain::LatticeLength1);
const QString BasicLatticeItem::P_LATTICE_LENGTH2
    = QString::fromStdString(BornAgain::LatticeLength2);
const QString BasicLatticeItem::P_LATTICE_ANGLE
    = QString::fromStdString(BornAgain::LatticeAngle);

BasicLatticeItem::BasicLatticeItem()
    : Lattice2DItem(Constants::BasicLatticeType)
{
    addProperty(P_LATTICE_LENGTH1, 20.0);
    addProperty(P_LATTICE_LENGTH2, 20.0);
    addProperty(P_LATTICE_ANGLE, 90.0);
}

// --------------------------------------------------------------------------------------------- //

const QString SquareLatticeItem::P_LATTICE_LENGTH
    = QString::fromStdString(BornAgain::LatticeLength);

SquareLatticeItem::SquareLatticeItem()
    : Lattice2DItem(Constants::SquareLatticeType)
{
    addProperty(P_LATTICE_LENGTH, 20.0);
}

// --------------------------------------------------------------------------------------------- //

const QString HexagonalLatticeItem::P_LATTICE_LENGTH
    = QString::fromStdString(BornAgain::LatticeLength);

HexagonalLatticeItem::HexagonalLatticeItem()
    : Lattice2DItem(Constants::HexagonalLatticeType)
{
    addProperty(P_LATTICE_LENGTH, 20.0);
}


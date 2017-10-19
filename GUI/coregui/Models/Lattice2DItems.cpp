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
#include "Lattice2D.h"
#include "Units.h"

namespace {
    const QString axis_rotation_tooltip
        = "Rotation of lattice with respect to x-axis of reference frame \n"
          "(beam direction) in degrees";
}

const QString Lattice2DItem::P_LATTICE_ROTATION_ANGLE
    = QString::fromStdString(BornAgain::Xi);

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
    setToolTip(QStringLiteral("Two dimensional lattice"));
    addProperty(P_LATTICE_LENGTH1, 20.0)
        ->setToolTip(QStringLiteral("Length of first lattice vector in nanometers"));
    addProperty(P_LATTICE_LENGTH2, 20.0)
        ->setToolTip(QStringLiteral("Length of second lattice vector in nanometers"));
    addProperty(P_LATTICE_ANGLE, 90.0)
        ->setToolTip(QStringLiteral("Angle between lattice vectors in degrees"));
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> BasicLatticeItem::createLattice() const
{
    return std::make_unique<BasicLattice>(
                getItemValue(P_LATTICE_LENGTH1).toDouble(),
                getItemValue(P_LATTICE_LENGTH2).toDouble(),
                Units::deg2rad(getItemValue(P_LATTICE_ANGLE).toDouble()),
                Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble())
                );
}

// --------------------------------------------------------------------------------------------- //

const QString SquareLatticeItem::P_LATTICE_LENGTH
    = QString::fromStdString(BornAgain::LatticeLength);

SquareLatticeItem::SquareLatticeItem()
    : Lattice2DItem(Constants::SquareLatticeType)
{
    addProperty(P_LATTICE_LENGTH, 20.0)
        ->setToolTip(QStringLiteral("Length of first and second lattice vectors in nanometers"));
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> SquareLatticeItem::createLattice() const
{
    return std::make_unique<SquareLattice>(
                getItemValue(P_LATTICE_LENGTH).toDouble(),
                Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble())
                );
}

// --------------------------------------------------------------------------------------------- //

const QString HexagonalLatticeItem::P_LATTICE_LENGTH
    = QString::fromStdString(BornAgain::LatticeLength);

HexagonalLatticeItem::HexagonalLatticeItem()
    : Lattice2DItem(Constants::HexagonalLatticeType)
{
    addProperty(P_LATTICE_LENGTH, 20.0)
        ->setToolTip(QStringLiteral("Length of first and second lattice vectors in nanometers"));
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> HexagonalLatticeItem::createLattice() const
{
    return std::make_unique<HexagonalLattice>(
                getItemValue(P_LATTICE_LENGTH).toDouble(),
                Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble())
                );
}


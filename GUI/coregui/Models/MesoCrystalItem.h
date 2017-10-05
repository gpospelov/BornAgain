// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MesoCrystalItem.h
//! @brief     Defines class MesoCrystalItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke, Dmitry Yurov
//
// ************************************************************************** //

#ifndef MESOCRYSTALITEM_H
#define MESOCRYSTALITEM_H

#include "Lattice.h"
#include "SessionGraphicsItem.h"

class IFormFactor;
class IParticle;
class MesoCrystal;

class BA_CORE_API_ MesoCrystalItem : public SessionGraphicsItem
{
public:
    static const QString P_FORM_FACTOR;
    static const QString T_BASIS_PARTICLE;
    static const QString LATTICE_VECTOR;
    static const QString P_VECTOR_A;
    static const QString P_VECTOR_B;
    static const QString P_VECTOR_C;

    MesoCrystalItem();

    std::unique_ptr<MesoCrystal> createMesoCrystal() const;

    QStringList translateList(const QStringList& list) const override;

private:
    Lattice getLattice() const;
    std::unique_ptr<IParticle> getBasis() const;
    std::unique_ptr<IFormFactor> getOuterShape() const;
};

#endif // MESOCRYSTALITEM_H

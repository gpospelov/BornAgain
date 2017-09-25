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

#include "SessionGraphicsItem.h"

class BA_CORE_API_ MesoCrystalItem : public SessionGraphicsItem
{
public:
    static const QString P_FORM_FACTOR;
    static const QString P_ABUNDANCE;
    static const QString T_BASIS_PARTICLE;
    static const QString P_LATTICE;
    static const QString P_POSITION;
    static const QString T_TRANSFORMATION;

    MesoCrystalItem();

private:
};

#endif // MESOCRYSTALITEM_H

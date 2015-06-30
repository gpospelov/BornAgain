// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleCoreShellItem.h
//! @brief     Defines class ParticleCoreShellItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECORESHELLITEM_H
#define PARTICLECORESHELLITEM_H

#include "ParameterizedGraphicsItem.h"
#include <QVector>

class BA_CORE_API_ ParticleCoreShellItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    enum ECoreShell { CORE, SHELL};
    explicit ParticleCoreShellItem(ParameterizedItem *parent=0);
    ~ParticleCoreShellItem(){}
    void insertChildItem(int row, ParameterizedItem *item);
private:
    PortInfo::EPorts getFirstAvailableParticlePort() const;
};


#endif


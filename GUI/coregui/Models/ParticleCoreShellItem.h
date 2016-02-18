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

#include "ParticleCoreShell.h"
#include "ParameterizedGraphicsItem.h"

#include <QVector>
#include <memory>

class BA_CORE_API_ ParticleCoreShellItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    enum ECoreShell { CORE, SHELL};
    explicit ParticleCoreShellItem();
    virtual ~ParticleCoreShellItem() {}
    virtual void insertChild(int row, ParameterizedItem *item);
    virtual void onPropertyChange(const QString &name);
    std::unique_ptr<ParticleCoreShell> createParticleCoreShell() const;

    void notifyChildParticlePortChanged();

private:
    PortInfo::EPorts getFirstAvailableParticlePort() const;
};

#endif

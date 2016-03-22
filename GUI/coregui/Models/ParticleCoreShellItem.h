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
#include "SessionGraphicsItem.h"

#include <QVector>
#include <memory>

class BA_CORE_API_ ParticleCoreShellItem : public SessionGraphicsItem
{

public:
    const static QString T_CORE;
    const static QString T_SHELL;
    enum ECoreShell { CORE, SHELL};
    explicit ParticleCoreShellItem();
    virtual ~ParticleCoreShellItem() {}
    std::unique_ptr<ParticleCoreShell> createParticleCoreShell() const;

};

#endif

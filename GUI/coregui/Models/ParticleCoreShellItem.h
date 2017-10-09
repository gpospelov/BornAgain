// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleCoreShellItem.h
//! @brief     Defines class ParticleCoreShellItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECORESHELLITEM_H
#define PARTICLECORESHELLITEM_H

#include "SessionGraphicsItem.h"

class ParticleCoreShell;

class BA_CORE_API_ ParticleCoreShellItem : public SessionGraphicsItem
{
public:
    const static QString T_CORE;
    const static QString T_SHELL;
    ParticleCoreShellItem();
    std::unique_ptr<ParticleCoreShell> createParticleCoreShell() const;
};

#endif // PARTICLECORESHELLITEM_H

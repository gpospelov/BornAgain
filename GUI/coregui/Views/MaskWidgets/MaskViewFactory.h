// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskViewFactory.h
//! @brief     Defines class MaskViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKVIEWFACTORY_H
#define MASKVIEWFACTORY_H

#include "WinDllMacros.h"
#include <QString>

class IMaskView;
class SessionItem;
class ISceneAdaptor;

//! Factory to construct views out of MaskItems for MaskGraphicsScene

class BA_CORE_API_ MaskViewFactory
{
public:
    static IMaskView *createMaskView(SessionItem *item,
                                     ISceneAdaptor *adaptor = 0);
};

#endif

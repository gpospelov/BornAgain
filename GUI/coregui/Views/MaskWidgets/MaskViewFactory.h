// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskViewFactory.h
//! @brief     Defines class MaskViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MASKVIEWFACTORY_H
#define MASKVIEWFACTORY_H

#include "Wrap/WinDllMacros.h"
#include <QString>

class IShape2DView;
class SessionItem;
class ISceneAdaptor;

//! Factory to construct views out of MaskItems for MaskGraphicsScene

class BA_CORE_API_ MaskViewFactory
{
public:
    static IShape2DView* createMaskView(SessionItem* item, ISceneAdaptor* adaptor = 0);
};

#endif // MASKVIEWFACTORY_H

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/SampleViewFactory.h
//! @brief     Defines class SampleViewFactory
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEVIEWFACTORY_H
#define SAMPLEVIEWFACTORY_H

#include "WinDllMacros.h"
#include <QStringList>
#include <QMap>

class IView;

class BA_CORE_API_ SampleViewFactory
{
public:
    static bool isValidItemName(const QString &name);
    static IView *createSampleView(const QString &name);

    static bool isValidExampleName();

private:
    static QStringList m_valid_item_names;
};


#endif

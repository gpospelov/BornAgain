// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/CustomEventFilters.h
//! @brief     Defines classes releted to event filtering
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CUSTOMEVENTFILTERS_H
#define CUSTOMEVENTFILTERS_H

#include "WinDllMacros.h"
#include <QObject>

class QEvent;

//! Filter out space bar key events, which is special case for dialog windows

class BA_CORE_API_ SpaceKeyEater : public QObject
{
    Q_OBJECT
public:

    SpaceKeyEater(QObject *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif

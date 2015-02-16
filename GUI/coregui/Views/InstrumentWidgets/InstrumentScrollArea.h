// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentScrollArea.h
//! @brief     Defines class InstrumentScrollArea
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTSCROLLAREA_H
#define INSTRUMENTSCROLLAREA_H

#include "WinDllMacros.h"
#include <QWidget>

class BA_CORE_API_ InstrumentScrollArea : public QWidget
{
    Q_OBJECT
public:
    InstrumentScrollArea(QWidget *parent = 0);

};

#endif

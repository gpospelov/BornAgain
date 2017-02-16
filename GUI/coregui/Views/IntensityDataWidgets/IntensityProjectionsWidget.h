// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityProjectionsWidget.h
//! @brief     Defines class IntensityProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYPROJECTIONSWIDGET_H
#define INTENSITYPROJECTIONSWIDGET_H

#include "SessionItemWidget.h"

class SessionItem;

//! A common widget to display color map (IntensityDataCanvas) and properties
//! (IntensityDataPropertyWidget) of intensity data item.

class BA_CORE_API_ IntensityProjectionsWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    IntensityProjectionsWidget(QWidget* parent = 0);

};

#endif // INTENSITYPROJECTIONSWIDGET_H

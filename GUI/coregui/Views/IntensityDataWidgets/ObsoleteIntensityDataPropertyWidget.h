// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ObsoleteIntensityDataPropertyWidget.h
//! @brief     Declares class ObsoleteIntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEINTENSITYDATAPROPERTYWIDGET_H
#define OBSOLETEINTENSITYDATAPROPERTYWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class JobModel;
class IntensityDataItem;
class ComponentEditor;

//! The IntensityDataPropertyWidget shows ComponentEditor for given IntensityDataItem.

class BA_CORE_API_ ObsoleteIntensityDataPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ObsoleteIntensityDataPropertyWidget(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(230, 256); }
    QSize minimumSizeHint() const { return QSize(230, 64); }

public slots:
    void setItem(IntensityDataItem *item);

private:
    IntensityDataItem *m_currentItem;
    ComponentEditor *m_componentEditor;
};

#endif

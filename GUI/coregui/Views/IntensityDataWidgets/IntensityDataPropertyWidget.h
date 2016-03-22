// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.h
//! @brief     Defines class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAPROPERTYWIDGET_H
#define INTENSITYDATAPROPERTYWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class JobModel;
class IntensityDataItem;
class ComponentEditor;

//! Widget to show and change properties of currently selected JobItem
//! Left buttom corner of JobQueueView
class BA_CORE_API_ IntensityDataPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntensityDataPropertyWidget(QWidget *parent = 0);

    void setModel(JobModel *model);

    QSize sizeHint() const { return QSize(230, 256); }
    QSize minimumSizeHint() const { return QSize(230, 64); }

public slots:
    void setItem(IntensityDataItem *item);

private:
    JobModel *m_jobModel;
    IntensityDataItem *m_currentItem;
    ComponentEditor *m_componentEditor;
};


#endif

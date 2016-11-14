// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataEditorWidget.h
//! @brief     Defines class RealDataEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATAEDITORWIDGET_H
#define REALDATAEDITORWIDGET_H

#include "SessionItemWidget.h"

class SessionItem;
class IntensityDataWidget;
class IntensityDataPropertyWidget;
class IntensityDataItem;
class QAction;

//! The RealDataEditorWidget class provides editing/presenation of RealDataItem in ImportDataView.

class BA_CORE_API_ RealDataEditorWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    RealDataEditorWidget(QWidget *parent = 0);

//    QSize sizeHint() const { return QSize(200, 400); }
//    QSize minimumSizeHint() const { return QSize(200, 200); }

    void setItem(class SessionItem *item);

    QList<QAction *> actionList();

private:
    IntensityDataWidget *m_intensityWidget;
    IntensityDataPropertyWidget *m_propertyWidget;
    IntensityDataItem *m_currentItem;
};

#endif // REALDATAEDITORWIDGET_H

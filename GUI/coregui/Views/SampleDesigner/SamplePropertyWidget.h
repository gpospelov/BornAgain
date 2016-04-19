// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SamplePropertyWidget.h
//! @brief     Declares class SamplePropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEPROPERTYWIDGET_H
#define SAMPLEPROPERTYWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QItemSelectionModel;
class QItemSelection;
class AwesomePropertyEditor;
class ComponentEditor;

//! Property editor to modify property of the objectcurrently selected on the
//! graphics scene, located in the bottom right corner of SampleView.
class BA_CORE_API_ SamplePropertyWidget : public QWidget
{
    Q_OBJECT
public:
    SamplePropertyWidget(QItemSelectionModel *selection_model,
                         QWidget *parent = 0);

    QSize sizeHint() const { return QSize(230, 256); }
    QSize minimumSizeHint() const { return QSize(230, 64); }

    void setSelectionModel(QItemSelectionModel *selection_model);

public slots:
    //! show property of currently selected object (triggered by graphics scene)
    void selectionChanged(const QItemSelection & selected,
                          const QItemSelection & deselected);

private:
    QItemSelectionModel *m_selection_model;
//    AwesomePropertyEditor *m_propertyEditor;
    ComponentEditor *m_propertyEditor;
};

#endif

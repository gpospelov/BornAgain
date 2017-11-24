// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SamplePropertyWidget.h
//! @brief     Defines class SamplePropertyWidget
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
class ComponentEditor;

//! Property editor to modify property of the object currently selected on the
//! graphics scene. Located in the bottom right corner of SampleView.

class BA_CORE_API_ SamplePropertyWidget : public QWidget
{
    Q_OBJECT
public:
    SamplePropertyWidget(QItemSelectionModel* selection_model, QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setSelectionModel(QItemSelectionModel* selection_model);

public slots:
    void selectionChanged(const QItemSelection& selected, const QItemSelection&);

private:
    QItemSelectionModel* m_selection_model;
    ComponentEditor* m_propertyEditor;
};

#endif // SAMPLEPROPERTYWIDGET_H

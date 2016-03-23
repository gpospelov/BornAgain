// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/DistributionEditor.h
//! @brief     Defines class DistributionEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONEDITOR_H
#define DISTRIBUTIONEDITOR_H

#include <QWidget>
#include "qcustomplot.h"

class QGroupBox;
class DistributionWidget;
class GroupItem;
class ComponentBoxEditor;

//! The DistributionEditor class, being a child of DistributionDialog, contains a widget
//! to show Distribution1D and awesome property editor to change distribution parameters
class DistributionEditor : public QWidget
{
    Q_OBJECT
public:
    DistributionEditor(QWidget *parent = 0);
    virtual ~DistributionEditor() {}
    void setItem(SessionItem *item);
    void plotItem(SessionItem *item);
    void setNameOfEditor(QString name);

private slots:
    void onPropertyChanged(const QString &property_name);

private:
    ComponentBoxEditor *m_propertyEditor;
    GroupItem *m_item;
    DistributionWidget *m_plotwidget;
    QString m_nameOfEditor;
    QGroupBox *m_box;
};

#endif

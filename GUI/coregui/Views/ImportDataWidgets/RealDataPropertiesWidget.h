// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/RealDataPropertiesWidget.h
//! @brief     Defines class RealDataPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATAPROPERTIESWIDGET_H
#define REALDATAPROPERTIESWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class ComponentEditor;
class SessionItem;
class QDataWidgetMapper;
class QLineEdit;

//! The RealDataPropertiesWidget class holds component editor for RealDataItem.
//! Part of RealDataSelectorWidget, resides at lower left corner of ImportDataView.

class BA_CORE_API_ RealDataPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RealDataPropertiesWidget(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(64, 256); }
    QSize minimumSizeHint() const { return QSize(64, 64); }

    void setItem(SessionItem *item);

    void setModels();

private:
    ComponentEditor *m_propertyEditor;
//    ComponentEditor *m_propertyEditor2;
    QDataWidgetMapper *m_dataNameMapper;
    QLineEdit *m_dataNameEdit;
};

#endif

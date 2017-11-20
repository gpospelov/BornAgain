// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyWidgetItem.h
//! @brief     Defines class PropertyWidgetItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROPERTYWIDGETITEM_H
#define PROPERTYWIDGETITEM_H

#include "WinDllMacros.h"
#include <QObject>

class QLabel;
class QWiget;
class QDataWidgetMapper;
class QGridLayout;
class SessionItem;

//! Container to hold label and editor for PropertyItem.
//! Contains also logic to map editor to SessionModel.

class BA_CORE_API_ PropertyWidgetItem : public QObject
{
    Q_OBJECT
public:
    explicit PropertyWidgetItem(QWidget* parent = nullptr);
    ~PropertyWidgetItem();

    void setItemEditor(SessionItem* item, QWidget* editor);
    void addToGrid(QGridLayout* gridLayout, int nrow);

private:
    QLabel* m_label;
    QWidget* m_editor;
    QDataWidgetMapper* m_dataMapper;
};

#endif

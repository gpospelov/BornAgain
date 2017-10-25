// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PropertyRepeater.h
//! @brief     Defines class PropertyRepeater
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROPERTYREPEATER_H
#define PROPERTYREPEATER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QVector>
#include <QMap>

class SessionItem;

//! Tracks property change (axes range, units etc) for the collection of IntensityDataItems
//! and sets same properties for all of them.

class BA_CORE_API_ PropertyRepeater : public QObject
{
    Q_OBJECT
public:
    explicit PropertyRepeater(QObject* parent = nullptr, bool repeat_child_properties = false);
    ~PropertyRepeater();

    void addItem(SessionItem* sessionItem, const QStringList& activeProperties = QStringList());

    void clear();

    void setActive(bool isActive);
private:
    void onPropertyChanged(SessionItem* item, const QString& propertyName);
    void setOnChildPropertyChange(SessionItem* item, const QString& propertyName);
    QVector<SessionItem*> targetItems(SessionItem* sourceItem);
    bool isPropertyBroadcastAllowed(SessionItem* item, const QString& propertyName);
    bool isPropertyReceiveAllowed(SessionItem* item, const QString& propertyName);

    QVector<SessionItem*> m_dataItems;
    //! List of properties which item is allowed to report to others and receive updates.
    QMap<SessionItem*, QStringList> m_itemProperties;
    bool m_block_repeater;
    bool m_repeat_child_properties;
};

#endif // PROPERTYREPEATER_H

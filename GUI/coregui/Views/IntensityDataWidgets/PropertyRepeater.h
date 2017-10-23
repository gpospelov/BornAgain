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

class SessionItem;
class IntensityDataItem;

//! Tracks property change (axes range, units etc) for the collection of IntensityDataItems
//! and sets same properties for all of them.

class BA_CORE_API_ PropertyRepeater : public QObject
{
    Q_OBJECT
public:
    explicit PropertyRepeater(QObject* parent = nullptr);

    void addItem(IntensityDataItem* item);

    void clear();
private:
    void onPropertyChanged(SessionItem* item, const QString& propertyName);
    void setOnChildPropertyChange(SessionItem* item, const QString& propertyName);
    QVector<SessionItem*> targetItems(SessionItem* sourceItem);

    QVector<SessionItem*> m_dataItems;
    bool m_block_repeater;
};

#endif // PROPERTYREPEATER_H

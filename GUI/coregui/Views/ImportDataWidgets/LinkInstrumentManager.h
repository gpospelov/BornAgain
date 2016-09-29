// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h
//! @brief     Defines class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef LINKINSTRUMENTMANAGER_H
#define LINKINSTRUMENTMANAGER_H

#include "WinDllMacros.h"
#include <QObject>

class InstrumentModel;
class RealDataModel;

//! The LinkInstrumentManager class provides communication between InstrumentModel and
//! RealDataModel. Particularly, it notifies RealDataItem about changes in linked instruments.

class BA_CORE_API_ LinkInstrumentManager : public QObject {
    Q_OBJECT

public:
    explicit LinkInstrumentManager(QObject *parent =  0);

    void setModels(InstrumentModel *instrumentModel, RealDataModel *realDataModel);

private slots:
    void updateInstrumentMap();

private:
    void setInstrumentModel(InstrumentModel *model);
    void setRealDataModel(RealDataModel *model);

    InstrumentModel *m_instrumentModel;
    RealDataModel *m_realDataModel;
    QStringList m_instrumentNames;
};

#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewActions.h
//! @brief     Defines class InstrumentViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTVIEWACTIONS_H
#define INSTRUMENTVIEWACTIONS_H

#include "WinDllMacros.h"
#include <QObject>
#include <QMap>

class QAction;
class SessionModel;
class QItemSelectionModel;
class QModelIndex;

//! Collection of actions to add/remove/clone instrument.

class BA_CORE_API_ InstrumentViewActions : public QObject
{
    Q_OBJECT

public:
    explicit InstrumentViewActions(QWidget* parent = 0);

    void setModel(SessionModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

public slots:
    void onAddInstrument();
    void onRemoveInstrument();
    void onCloneInstrument();
    void onContextMenuRequest(const QPoint &point, const QModelIndex &indexAtPoint);

private:
    void setAllActionsEnabled(bool value);
    void updateSelection();
    QString suggestInstrumentName(const QString& currentName);
    QMap<QString, int> mapOfNames();

    QAction* m_addInstrumentAction;
    QAction* m_removeInstrumentAction;
    QAction* m_cloneInstrumentAction;
    SessionModel* m_model;
    QItemSelectionModel* m_selectionModel;
};

#endif // INSTRUMENTVIEWACTIONS_H

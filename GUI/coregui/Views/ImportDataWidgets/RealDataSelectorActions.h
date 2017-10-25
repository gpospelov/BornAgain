// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.h
//! @brief     Defines class RealDataSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATASELECTORACTIONS_H
#define REALDATASELECTORACTIONS_H

#include "WinDllMacros.h"
#include <QObject>

class RealDataModel;
class QAction;
class QItemSelectionModel;

//! The RealDataSelectorActions class contains actions to run/remove real data.
//! Actions are used by the toolbar and context menu of selector list.

class BA_CORE_API_ RealDataSelectorActions : public QObject {
    Q_OBJECT
public:
    RealDataSelectorActions(QObject* parent = nullptr);

    void setRealDataModel(RealDataModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

public slots:
    void onImportDataAction();
    void onRemoveDataAction();
    void onContextMenuRequest(const QPoint &point, const QModelIndex &indexAtPoint);

private:
    void setAllActionsEnabled(bool value);
    void updateSelection();

    QAction* m_importDataAction;
    QAction* m_removeDataAction;
    RealDataModel* m_realDataModel;
    QItemSelectionModel* m_selectionModel;
};


#endif

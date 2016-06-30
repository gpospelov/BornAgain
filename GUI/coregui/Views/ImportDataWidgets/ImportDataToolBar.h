// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataToolBar.h
//! @brief     Declares class ImportDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef IMPORTDATATOOLBAR_H
#define IMPORTDATATOOLBAR_H

#include "StyledToolBar.h"

class QAction;
class RealDataModel;
class InstrumentModel;
class QItemSelectionModel;
class RealDataItem;

//! The ImportDataToolBar class represents a narrow toolbar on top of ImportDataView. Contains
//! all action's logic to import, clone and remove data set.

class BA_CORE_API_ ImportDataToolBar : public StyledToolBar
{
    Q_OBJECT
public:
    ImportDataToolBar(QWidget *parent = 0);

    void setRealDataModel(RealDataModel *model);
    void setInstrumentModel(InstrumentModel *model);
    void setSelectionModel(QItemSelectionModel *selectionModel);

    void setActionList(const QList<QAction *> &actionList);

private slots:
    void onImportDataAction();
    void onCloneDataAction();
    void onRemoveDataAction();

private:
    void matchAxesToInstrument(RealDataItem *realDataItem);

    QAction *m_importDataAction;
//    QAction *m_cloneDataAction;
    QAction *m_removeDataAction;

    RealDataModel *m_realDataModel;
    InstrumentModel *m_instrumentModel;
    QItemSelectionModel *m_selectionModel;
};

#endif

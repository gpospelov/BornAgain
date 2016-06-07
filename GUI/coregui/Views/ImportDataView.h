// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/ImportDataView.h
//! @brief     Declares class ImportDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef IMPORTDATAVIEW_H
#define IMPORTDATAVIEW_H

#include "WinDllMacros.h"
#include "ItemStackPresenter.h"
#include "RealDataEditorWidget.h"
#include <QWidget>

//! The ImportDataView class is a main view for importing experimental data.

class BA_CORE_API_ ImportDataView : public QWidget
{
    Q_OBJECT

public:
    ImportDataView(class MainWindow *mainWindow);

private:
    void setupConnections();

    class ImportDataToolBar *m_toolBar;
    class QSplitter *m_splitter;
    class ItemSelectorWidget *m_selectorWidget;
    ItemStackPresenter<RealDataEditorWidget> *m_stackedWidget;
    class RealDataModel *m_realDataModel;
};

#endif

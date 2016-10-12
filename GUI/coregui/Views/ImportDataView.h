// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataView.h
//! @brief     Defines class ImportDataView
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

#include "ItemStackPresenter.h"
#include "RealDataEditorWidget.h"
#include "RealDataMaskWidget.h"

class ImportDataToolBar;
class RealDataModel;
class RealDataSelectorWidget;
namespace Manhattan { class MiniSplitter; }

//! The ImportDataView class is a main view for importing experimental data.

class BA_CORE_API_ ImportDataView : public QWidget
{
    Q_OBJECT

public:
    ImportDataView(class MainWindow *mainWindow);

public slots:
    void onSelectionChanged(SessionItem *item);

private:
    void setupConnections();

    ImportDataToolBar *m_toolBar;
    Manhattan::MiniSplitter *m_splitter;
    RealDataSelectorWidget *m_selectorWidget;
    ItemStackPresenter<RealDataMaskWidget> *m_stackedWidget;
//    ItemStackPresenter<RealDataEditorWidget> *m_stackedWidget;
    RealDataModel *m_realDataModel;
};

#endif // IMPORTDATAVIEW_H

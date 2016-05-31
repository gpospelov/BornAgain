// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/ImportDataView.cpp
//! @brief     Implements class ImportDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ImportDataView.h"
#include "mainwindow.h"
#include "ImportDataToolBar.h"
#include "RealDataSelectorWidget.h"
#include <QVBoxLayout>
#include <QSplitter>
#include <QStackedWidget>

ImportDataView::ImportDataView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_toolBar(new ImportDataToolBar(this))
    , m_splitter(new QSplitter(this))
    , m_selectorWidget(new RealDataSelectorWidget(this))
    , m_stackedWidget(new QStackedWidget(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    m_splitter->addWidget(m_selectorWidget);
    m_splitter->addWidget(m_stackedWidget);
    m_splitter->setCollapsible(0, false);
    m_splitter->setCollapsible(1, false);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_splitter);

    setLayout(mainLayout);
}

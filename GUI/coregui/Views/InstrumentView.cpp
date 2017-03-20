// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentView.cpp
//! @brief     Implements class InstrumentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InstrumentView.h"
#include "ExtendedDetectorDialog.h"
#include "InstrumentEditorWidget.h"
#include "InstrumentModel.h"
#include "InstrumentSelectorWidget.h"
#include "StyledToolBar.h"
#include "mainwindow.h"
#include "DetectorItems.h"
#include <QAction>
#include <QLabel>
#include <QBoxLayout>
#include <QListView>
#include <QStackedWidget>
#include <QToolButton>

InstrumentView::InstrumentView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_instrumentModel(mainWindow->instrumentModel())
    , m_toolBar(new StyledToolBar(this))
    , m_instrumentSelector(new InstrumentSelectorWidget(m_instrumentModel, this))
    , m_instrumentEditor(new InstrumentEditorWidget)
    , m_addInstrumentAction(0)
    , m_removeInstrumentAction(0)
    , m_addInstrumentButton(0)
    , m_removeInstrumentButton(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(m_instrumentSelector);
    horizontalLayout->addWidget(m_instrumentEditor, 1);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(horizontalLayout);
    setLayout(mainLayout);

    setupActions();

    if(m_instrumentModel->rowCount(QModelIndex()) == 0)
        onAddInstrument();

    connect(m_instrumentSelector, SIGNAL(selectionChanged(SessionItem*)),
            this, SLOT(onItemSelectionChanged(SessionItem*)));
}


void InstrumentView::onAddInstrument()
{
    SessionItem *instrument = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument->setItemName(getNewInstrumentName("Default GISAS"));
    m_instrumentSelector->updateSelection();
}

void InstrumentView::onRemoveInstrument()
{
    QModelIndex currentIndex = m_instrumentSelector->selectionModel()->currentIndex();
    if(currentIndex.isValid())
        m_instrumentModel->removeRows(currentIndex.row(), 1, QModelIndex());

    m_instrumentSelector->updateSelection();
}

void InstrumentView::onExtendedDetectorEditorRequest(DetectorItem *detectorItem)
{
    ExtendedDetectorDialog *dialog = new ExtendedDetectorDialog(this);
    dialog->setDetectorContext(m_instrumentModel, detectorItem);
    dialog->show();
}

void InstrumentView::onItemSelectionChanged(SessionItem* instrumentItem)
{
    m_instrumentEditor->setInstrumentItem(instrumentItem);
}

void InstrumentView::showEvent(QShowEvent*)
{
    m_instrumentSelector->updateSelection();
}

void InstrumentView::setupActions()
{
    m_addInstrumentButton = new QToolButton;
    m_addInstrumentButton->setText("Add instrument");
    m_addInstrumentButton->setIcon(QIcon(":/images/toolbar_newitem.png"));
    m_addInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_addInstrumentButton->setToolTip("Add new instrument");
    connect(m_addInstrumentButton, SIGNAL(clicked()), this, SLOT(onAddInstrument()));
    m_toolBar->addWidget(m_addInstrumentButton);

    m_toolBar->addWidget(new QLabel(" "));
    m_toolBar->addSeparator();
    m_toolBar->addWidget(new QLabel(" "));

    m_removeInstrumentButton = new QToolButton;
    m_removeInstrumentButton->setText("Remove instrument");
    m_removeInstrumentButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_removeInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeInstrumentButton->setToolTip("Remove currently selected instrument");
    connect(m_removeInstrumentButton, SIGNAL(clicked()), this, SLOT(onRemoveInstrument()));
    m_toolBar->addWidget(m_removeInstrumentButton);

    m_toolBar->addWidget(new QLabel(" "));
    m_toolBar->addSeparator();
    m_toolBar->addWidget(new QLabel(" "));

    m_addInstrumentAction
        = new QAction(QIcon(":/images/toolbar_newitem_dark.png"), "Add new instrument", this);
    connect(m_addInstrumentAction, SIGNAL(triggered()), this, SLOT(onAddInstrument()));

    m_removeInstrumentAction
        = new QAction(QIcon(":/SampleDesigner/images/toolbar_recycle_dark.png"),
                      "Remove currently selected instrument", this);
    connect(m_removeInstrumentAction, SIGNAL(triggered()), this, SLOT(onRemoveInstrument()));

    m_instrumentSelector->listView()->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_instrumentSelector->listView()->addAction(m_addInstrumentAction);
    m_instrumentSelector->listView()->addAction(m_removeInstrumentAction);
}


//! returns name of instrument which is based on suggested name
//! If "Default GISAS" name already exists, then "Default GISAS (2)" will be proposed.
QString InstrumentView::getNewInstrumentName(const QString &name)
{
    updateMapOfNames();

    int ncopies = m_name_to_copy[name];
    if(ncopies == 0) {
        m_name_to_copy[name]=1;
        return name;
    }
    else {
        m_name_to_copy[name]++;
        return QString("%1 (%2)").arg(name).arg(m_name_to_copy[name]);
    }
}


//! construct map of instrument names defined in the model together with number
//! of copies
void InstrumentView::updateMapOfNames()
{

    m_name_to_copy.clear();
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < m_instrumentModel->rowCount( parentIndex ); ++i_row) {
        QModelIndex itemIndex = m_instrumentModel->index( i_row, 0, parentIndex );
        QString name =  m_instrumentModel->itemForIndex(itemIndex)->itemName();
        int ncopy(1);
        QRegExp regexp("\\((.*)\\)");
        if(regexp.indexIn(name) >= 0) {
            ncopy = regexp.cap(1).toInt();
        }
        name.replace(regexp.cap(0),"");
        name = name.trimmed();
        m_name_to_copy[name] = ncopy;
    }
}

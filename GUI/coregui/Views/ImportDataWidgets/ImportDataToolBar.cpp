// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataToolBar.cpp
//! @brief     Implements class ImportDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ImportDataToolBar.h"
#include "ImportDataToolBar.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "IDetector2D.h"
#include "IDetector2D.h"
#include "ImportDataAssistant.h"
#include "InstrumentItem.h"
#include "InstrumentModel.h"
#include "IntensityDataItem.h"
#include "JobItemUtils.h"
#include "RealDataItem.h"
#include "RealDataModel.h"
#include "RectangularDetectorItem.h"
#include "SessionItem.h"
#include "SphericalDetectorItem.h"
#include <QAction>
#include <QItemSelectionModel>

ImportDataToolBar::ImportDataToolBar(QWidget* parent)
    : StyledToolBar(parent), m_importDataAction(0), m_removeDataAction(0), m_realDataModel(0),
      m_instrumentModel(0), m_selectionModel(0)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    m_importDataAction = new QAction(QStringLiteral("Import"), parent);
    m_importDataAction->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_importDataAction->setToolTip(QStringLiteral("Import data"));
    connect(m_importDataAction, SIGNAL(triggered()), this, SLOT(onImportDataAction()));
    addAction(m_importDataAction);

    m_removeDataAction = new QAction(QStringLiteral("Remove"), parent);
    m_removeDataAction->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeDataAction->setToolTip(QStringLiteral("Remove selected data"));
    connect(m_removeDataAction, SIGNAL(triggered()), this, SLOT(onRemoveDataAction()));
    addAction(m_removeDataAction);
}

void ImportDataToolBar::setRealDataModel(RealDataModel* model) { m_realDataModel = model; }

void ImportDataToolBar::setInstrumentModel(InstrumentModel* model) { m_instrumentModel = model; }

void ImportDataToolBar::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;
}

//! Sets action to toolbar, preserving own toolbar's actions.

void ImportDataToolBar::setActionList(const QList<QAction*>& actionList)
{
    clear();

    addAction(m_importDataAction);
    addAction(m_removeDataAction);

    addStyledSeparator();

    foreach (QAction* action, actionList)
        addAction(action);
}

void ImportDataToolBar::onImportDataAction()
{
    Q_ASSERT(m_realDataModel);
    ImportDataAssistant assistant;
    QString baseNameOfImportedFile;

    std::unique_ptr<OutputData<double>> data(assistant.importData(baseNameOfImportedFile));
    if (data) {
        RealDataItem* realDataItem
            = dynamic_cast<RealDataItem*>(m_realDataModel->insertNewItem(Constants::RealDataType));
        realDataItem->setItemName(baseNameOfImportedFile);
        realDataItem->setOutputData(data.release());
        m_selectionModel->clearSelection();
        m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
    }
}

void ImportDataToolBar::onRemoveDataAction()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();
    if (currentIndex.isValid())
        m_realDataModel->removeRows(currentIndex.row(), 1, currentIndex.parent());
}

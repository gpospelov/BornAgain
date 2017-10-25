// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.cpp
//! @brief     Implements class RealDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataSelectorWidget.h"
#include "ItemSelectorWidget.h"
#include "RealDataPropertiesWidget.h"
#include "RealDataModel.h"
#include "minisplitter.h"
#include "RealDataSelectorActions.h"
#include "RealDataSelectorToolBar.h"
#include <QVBoxLayout>
#include <QItemSelectionModel>

RealDataSelectorWidget::RealDataSelectorWidget(QWidget* parent)
    : QWidget(parent)
    , m_selectorActions(new RealDataSelectorActions(this))
    , m_toolBar(new RealDataSelectorToolBar(this))
    , m_splitter(new Manhattan::MiniSplitter)
    , m_selectorWidget(new ItemSelectorWidget)
    , m_propertiesWidget(new RealDataPropertiesWidget)
{
    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setWindowTitle("RealDataSelectorWidget");

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_selectorWidget);
    m_splitter->addWidget(m_propertiesWidget);
    m_splitter->setChildrenCollapsible(true);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);

    m_selectorActions->setSelectionModel(m_selectorWidget->selectionModel());

    connect(m_selectorWidget, &ItemSelectorWidget::selectionChanged,
            this, &RealDataSelectorWidget::onSelectionChanged);
}

QSize RealDataSelectorWidget::sizeHint() const
{
    return QSize(200, 400);
}

QSize RealDataSelectorWidget::minimumSizeHint() const
{
    return QSize(128, 200);
}

void RealDataSelectorWidget::setModels(InstrumentModel* instrumentModel,
                                       RealDataModel* realDataModel)
{
    m_selectorWidget->setModel(realDataModel);
    m_propertiesWidget->setModels(instrumentModel, realDataModel);

    m_selectorActions->setRealDataModel(realDataModel);

    m_toolBar->setRealDataModel(realDataModel);
    m_toolBar->setInstrumentModel(instrumentModel);
    m_toolBar->setSelectionModel(m_selectorWidget->selectionModel());
}

void RealDataSelectorWidget::onSelectionChanged(SessionItem* item)
{
    m_propertiesWidget->setItem(item);
    emit selectionChanged(item);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SphericalDetectorWidget.cpp
//! @brief     Implements class SphericalDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SphericalDetectorWidget.h"
#include "ComponentBoxEditor.h"
#include "SphericalDetectorItem.h"
#include "ColumnResizer.h"
#include <QGroupBox>
#include <QVBoxLayout>

SphericalDetectorWidget::SphericalDetectorWidget(ColumnResizer* columnResizer,
                                                 SessionItem* detectorItem, QWidget* parent)
    : QWidget(parent)
    , m_columnResizer(columnResizer)
    , m_phiAxisEditor(new ComponentBoxEditor)
    , m_alphaAxisEditor(new ComponentBoxEditor)
    , m_resolutionFunctionEditor(new ComponentBoxEditor)
    , m_polarizationAnalysisEditor(new ComponentBoxEditor)
    , m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_phiAxisEditor, 1, 0);
    m_gridLayout->addWidget(m_alphaAxisEditor, 1, 1);
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);
    m_gridLayout->addWidget(m_polarizationAnalysisEditor, 1, 3);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);

    connect(m_columnResizer, SIGNAL(destroyed(QObject*)), this,
            SLOT(onColumnResizerDestroyed(QObject*)));

    // main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    setDetectorItem(detectorItem);
}

SphericalDetectorWidget::~SphericalDetectorWidget()
{
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();
    m_polarizationAnalysisEditor->clearEditor();
    if (m_columnResizer)
        m_columnResizer->dropWidgetsFromGridLayout(m_gridLayout);
}

void SphericalDetectorWidget::setDetectorItem(SessionItem* detectorItem)
{
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();
    m_polarizationAnalysisEditor->clearEditor();

    if (!detectorItem)
        return;

    Q_ASSERT(detectorItem->modelType() == Constants::SphericalDetectorType);

    SessionItem* phiAxisItem = detectorItem->getItem(SphericalDetectorItem::P_PHI_AXIS);
    m_phiAxisEditor->addPropertyItems(phiAxisItem, QStringLiteral("Phi axis"));

    SessionItem* alphaAxisItem = detectorItem->getItem(SphericalDetectorItem::P_ALPHA_AXIS);
    m_alphaAxisEditor->addPropertyItems(alphaAxisItem, QStringLiteral("Alpha axis"));

    SessionItem* resFuncGroup = detectorItem->getItem(SphericalDetectorItem::P_RESOLUTION_FUNCTION);
    m_resolutionFunctionEditor->addPropertyItems(resFuncGroup,
                                                 QStringLiteral("Resolution function"));

    SessionItem* analysisDirection = detectorItem->getItem(DetectorItem::P_ANALYZER_DIRECTION);
    m_polarizationAnalysisEditor->addPropertyItems(
        analysisDirection, QStringLiteral("Analyzer orientation"));
    m_polarizationAnalysisEditor->addItem(
        detectorItem->getItem(DetectorItem::P_ANALYZER_EFFICIENCY));
    m_polarizationAnalysisEditor->addItem(
        detectorItem->getItem(DetectorItem::P_ANALYZER_TOTAL_TRANSMISSION));
}

void SphericalDetectorWidget::onColumnResizerDestroyed(QObject* object)
{
    if (object == m_columnResizer)
        m_columnResizer = 0;
}

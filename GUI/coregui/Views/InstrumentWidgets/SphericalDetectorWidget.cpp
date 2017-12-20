// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SphericalDetectorWidget.cpp
//! @brief     Implements class SphericalDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SphericalDetectorWidget.h"
#include "ComponentEditor.h"
#include "SphericalDetectorItem.h"
#include "ColumnResizer.h"
#include <QGroupBox>
#include <QVBoxLayout>

namespace {
const QString phi_axis_title = "Phi axis";
const QString alpha_axis_title = "Alpha axis";
const QString resolution_title = "Resolution function";
const QString polarization_title = "Analyzer orientation";
}

SphericalDetectorWidget::SphericalDetectorWidget(ColumnResizer* columnResizer,
                                                 SessionItem* detectorItem, QWidget* parent)
    : QWidget(parent)
    , m_columnResizer(columnResizer)
    , m_phiAxisEditor(new ComponentEditor(ComponentEditor::GroupWidget, phi_axis_title))
    , m_alphaAxisEditor(new ComponentEditor(ComponentEditor::GroupWidget, alpha_axis_title))
    , m_resolutionFunctionEditor(new ComponentEditor(ComponentEditor::GroupWidget, resolution_title))
    , m_polarizationAnalysisEditor(new ComponentEditor(ComponentEditor::GroupWidget, polarization_title))
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
    m_phiAxisEditor->setItem(phiAxisItem);

    SessionItem* alphaAxisItem = detectorItem->getItem(SphericalDetectorItem::P_ALPHA_AXIS);
    m_alphaAxisEditor->setItem(alphaAxisItem);

    SessionItem* resFuncGroup = detectorItem->getItem(SphericalDetectorItem::P_RESOLUTION_FUNCTION);
    m_resolutionFunctionEditor->setItem(resFuncGroup);

    SessionItem* analysisDirection = detectorItem->getItem(DetectorItem::P_ANALYZER_DIRECTION);
    m_polarizationAnalysisEditor->setItem(analysisDirection);

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

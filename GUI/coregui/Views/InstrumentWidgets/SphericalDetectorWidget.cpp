// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/SphericalDetectorWidget.cpp
//! @brief     Implements class SphericalDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SphericalDetectorWidget.h"
#include "AwesomePropertyEditor.h"
#include "DetectorItems.h"
#include "GroupBox.h"
#include "ExtendedDetectorDialog.h"
#include "columnresizer.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDebug>

SphericalDetectorWidget::SphericalDetectorWidget(ColumnResizer *columnResizer,
                                                 DetectorItem *detectorItem, QWidget *parent)
    : QWidget(parent)
    , m_columnResizer(columnResizer)
    , m_detectorTypeEditor(0)
    , m_phiAxisEditor(0)
    , m_alphaAxisEditor(0)
    , m_resolutionFunctionEditor(0)
    , m_gridLayout(new QGridLayout)
{
//    m_detectorTypeEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
//    m_gridLayout->addWidget(m_detectorTypeEditor, 0, 0);

    m_phiAxisEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_phiAxisEditor, 1, 0);
    m_alphaAxisEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_alphaAxisEditor, 1, 1);

    m_resolutionFunctionEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);

    connect(m_columnResizer, SIGNAL(destroyed(QObject*)), this, SLOT(onColumnResizerDestroyed(QObject *)));

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    setDetectorItem(detectorItem);
}

SphericalDetectorWidget::~SphericalDetectorWidget()
{
    qDebug() << "SphericalDetectorWidget::~SphericalDetectorWidget()";
//    m_detectorTypeEditor->clearEditor();
//    m_phiAxisEditor->clearEditor();
//    m_alphaAxisEditor->clearEditor();
//    m_resolutionFunctionEditor->clearEditor();
    if(m_columnResizer) m_columnResizer->dropWidgetsFromGridLayout(m_gridLayout);

}

void SphericalDetectorWidget::setDetectorItem(DetectorItem *detectorItem)
{
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();

    if (!detectorItem)
        return;

//    m_detectorTypeEditor->addItemProperty(detectorItem, DetectorItem::P_DETECTOR, QString(),
//                                     AwesomePropertyEditor::SKIP);

    SphericalDetectorItem *sphericalDetector = dynamic_cast<SphericalDetectorItem *>(
                detectorItem->getGroupItem(DetectorItem::P_DETECTOR));
    Q_ASSERT(sphericalDetector);

    ParameterizedItem *phiAxisItem = sphericalDetector->getGroupItem(SphericalDetectorItem::P_PHI_AXIS);
    m_phiAxisEditor->addItemProperties(phiAxisItem, QString("Phi axis"),
                                       AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *alphaAxisItem
        = sphericalDetector->getGroupItem(SphericalDetectorItem::P_ALPHA_AXIS);
    m_alphaAxisEditor->addItemProperties(alphaAxisItem, QString("Alpha axis"),
                                         AwesomePropertyEditor::INSERT_AFTER);

    m_resolutionFunctionEditor->addItemProperty(
        sphericalDetector, SphericalDetectorItem::P_RESOLUTION_FUNCTION, "Resolution function",
                AwesomePropertyEditor::INSERT_AFTER);
}

void SphericalDetectorWidget::onColumnResizerDestroyed(QObject *object)
{
    if(object == m_columnResizer) m_columnResizer = 0;
}



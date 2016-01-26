// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/RectangularDetectorWidget.cpp
//! @brief     Implements class RectangularDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RectangularDetectorWidget.h"
#include "AwesomePropertyEditor.h"
#include "DetectorItems.h"
#include "GroupBox.h"
#include "ExtendedDetectorDialog.h"
#include "columnresizer.h"
#include <QGroupBox>
#include <QVBoxLayout>

RectangularDetectorWidget::RectangularDetectorWidget(ColumnResizer *columnResizer,
                                                     DetectorItem *detectorItem, QWidget *parent)
    : QWidget(parent)
    , m_detectorTypeEditor(0)
    , m_xAxisEditor(0)
    , m_yAxisEditor(0)
    , m_resolutionFunctionEditor(0)
    , m_gridLayout(new QGridLayout)
{
//    m_detectorTypeEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
//    m_gridLayout->addWidget(m_detectorTypeEditor, 0, 0);

    m_xAxisEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_xAxisEditor, 1, 0);
    m_yAxisEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_yAxisEditor, 1, 1);

    m_resolutionFunctionEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);

//    columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
//    columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
//    columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    setDetectorItem(detectorItem);
}

void RectangularDetectorWidget::setDetectorItem(DetectorItem *detectorItem)
{
    m_xAxisEditor->clearEditor();
    m_yAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();

    if (!detectorItem)
        return;

//    m_detectorTypeEditor->addItemProperty(detectorItem, DetectorItem::P_DETECTOR, QString(),
//                                     AwesomePropertyEditor::SKIP);

    RectangularDetectorItem *rectangularDetector = dynamic_cast<RectangularDetectorItem *>(
                detectorItem->getSubItems()[DetectorItem::P_DETECTOR]);
    Q_ASSERT(rectangularDetector);

    ParameterizedItem *xAxisItem = rectangularDetector->getSubItems()[RectangularDetectorItem::P_X_AXIS];
    m_xAxisEditor->addItemProperties(xAxisItem, QString("X axis"),
                                       AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *yAxisItem
        = rectangularDetector->getSubItems()[RectangularDetectorItem::P_Y_AXIS];
    m_yAxisEditor->addItemProperties(yAxisItem, QString("Y axis"),
                                         AwesomePropertyEditor::INSERT_AFTER);

    m_resolutionFunctionEditor->addItemProperty(
        rectangularDetector, RectangularDetectorItem::P_RESOLUTION_FUNCTION, "Resolution function",
                AwesomePropertyEditor::INSERT_AFTER);
}



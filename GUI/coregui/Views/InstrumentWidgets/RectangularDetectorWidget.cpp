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
#include "ComboProperty.h"
#include "columnresizer.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDebug>

RectangularDetectorWidget::RectangularDetectorWidget(ColumnResizer *columnResizer,
                                                     RectangularDetectorItem *detectorItem, QWidget *parent)
    : QWidget(parent)
    , m_columnResizer(columnResizer)
    , m_detectorTypeEditor(0)
    , m_xAxisEditor(0)
    , m_yAxisEditor(0)
    , m_resolutionFunctionEditor(0)
    , m_alignmentEditor(0)
    , m_positionsEditor(0)
    , m_normalEditor(0)
    , m_directionEditor(0)
    , m_gridLayout(new QGridLayout)
    , m_detectorItem(0)
{
//    m_detectorTypeEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
//    m_gridLayout->addWidget(m_detectorTypeEditor, 0, 0);

    create_editors();


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

RectangularDetectorWidget::~RectangularDetectorWidget()
{
    if(m_columnResizer) m_columnResizer->dropWidgetsFromGridLayout(m_gridLayout);
}

void RectangularDetectorWidget::setDetectorItem(RectangularDetectorItem *detectorItem)
{
    if(m_detectorItem) {
        disconnect(m_detectorItem,
                   SIGNAL(propertyChanged(const QString &)),
                   this,
                   SLOT(onPropertyChanged(const QString &)));
    }

    m_detectorItem = detectorItem;

    if(!m_detectorItem) return;

    connect(m_detectorItem,
               SIGNAL(propertyChanged(const QString &)),
               this,
               SLOT(onPropertyChanged(const QString &)));


//    m_xAxisEditor->clearEditor();
//    m_yAxisEditor->clearEditor();
//    m_resolutionFunctionEditor->clearEditor();

//    if (!detectorItem)
//        return;

////    m_detectorTypeEditor->addItemProperty(detectorItem, DetectorItem::P_DETECTOR, QString(),
////                                     AwesomePropertyEditor::SKIP);

//    m_detectorItem = dynamic_cast<RectangularDetectorItem *>(
//                detectorItem->getSubItems()[DetectorItem::P_DETECTOR]);
//    Q_ASSERT(m_detectorItem);

    init_editors();

}

void RectangularDetectorWidget::onPropertyChanged(const QString &propertyName)
{
    qDebug() << "RectangularDetectorWidget::onPropertyChanged()" << propertyName;
    if(propertyName == RectangularDetectorItem::P_ALIGNMENT) {
        init_alignment_editors();
    }

}

void RectangularDetectorWidget::onColumnResizerDestroyed(QObject *object)
{
    if(object == m_columnResizer) m_columnResizer = 0;
}

//! create various editors to hold RectangularDetector properties
void RectangularDetectorWidget::create_editors()
{
    // axes and resolution function editors
    m_xAxisEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_xAxisEditor, 1, 0);
    m_yAxisEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_yAxisEditor, 1, 1);
    m_resolutionFunctionEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);

    // alignment selector editors
    m_alignmentEditor
            = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_alignmentEditor, 2, 0);

    // editors for various positions
    m_positionsEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_positionsEditor, 3, 0);

    m_normalEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_normalEditor, 3, 1);

    m_directionEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_directionEditor, 3, 2);

}

void RectangularDetectorWidget::init_editors()
{
    m_xAxisEditor->clearEditor();
    ParameterizedItem *xAxisItem = m_detectorItem->getSubItems()[RectangularDetectorItem::P_X_AXIS];
    m_xAxisEditor->addItemProperties(xAxisItem, QString("X axis"),
                                       AwesomePropertyEditor::INSERT_AFTER);

    m_yAxisEditor->clearEditor();
    ParameterizedItem *yAxisItem
        = m_detectorItem->getSubItems()[RectangularDetectorItem::P_Y_AXIS];
    m_yAxisEditor->addItemProperties(yAxisItem, QString("Y axis"),
                                         AwesomePropertyEditor::INSERT_AFTER);

    m_resolutionFunctionEditor->clearEditor();
    m_resolutionFunctionEditor->addItemProperty(
        m_detectorItem, RectangularDetectorItem::P_RESOLUTION_FUNCTION, "Resolution function",
                AwesomePropertyEditor::INSERT_AFTER);

    m_alignmentEditor->clearEditor();
    m_alignmentEditor->addItemProperty(
        m_detectorItem, RectangularDetectorItem::P_ALIGNMENT, QString(),
                AwesomePropertyEditor::SKIP);

    init_alignment_editors();

}

void RectangularDetectorWidget::init_alignment_editors()
{
    m_positionsEditor->clearEditor();
    m_positionsEditor->hide();

    m_normalEditor->clearEditor();
    m_normalEditor->hide();

    m_directionEditor->clearEditor();
    m_directionEditor->hide();

    ComboProperty alignment
        = m_detectorItem->getRegisteredProperty(RectangularDetectorItem::P_ALIGNMENT)
              .value<ComboProperty>();


    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {
        m_positionsEditor->show();
        m_normalEditor->show();
        m_directionEditor->show();

        ParameterizedItem *uvItem
            = m_detectorItem->getSubItems()[RectangularDetectorItem::P_UV];

        m_positionsEditor->addItemProperties(uvItem, "Uv",AwesomePropertyEditor::INSERT_AFTER);

        ParameterizedItem *normalVectorItem
            = m_detectorItem->getSubItems()[RectangularDetectorItem::P_NORMAL];
        m_normalEditor->addItemProperties(normalVectorItem, "Normal vector",
                    AwesomePropertyEditor::INSERT_AFTER);

        ParameterizedItem *directionVectorItem
            = m_detectorItem->getSubItems()[RectangularDetectorItem::P_DIRECTION];
        m_directionEditor->addItemProperties(directionVectorItem, "Direction vector",
                    AwesomePropertyEditor::INSERT_AFTER);


    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM ||
               alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE ||
               alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
        m_positionsEditor->show();

        ParameterizedItem *uvItem
            = m_detectorItem->getSubItems()[RectangularDetectorItem::P_UV];
        m_positionsEditor->addItemProperties(uvItem, "Positions",
                    AwesomePropertyEditor::INSERT_AFTER);
        m_positionsEditor->addItemProperty(
            m_detectorItem, RectangularDetectorItem::P_DISTANCE, "Positions",
                    AwesomePropertyEditor::INSERT_AFTER);


//        setPropertyAppearance(P_DISTANCE, PropertyAttribute::VISIBLE);
//        setPropertyAppearance(P_UV, PropertyAttribute::VISIBLE);
    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE) {
//        setPropertyAppearance(P_DISTANCE, PropertyAttribute::VISIBLE);
//        setPropertyAppearance(P_UV, PropertyAttribute::VISIBLE);
    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
//        setPropertyAppearance(P_DISTANCE, PropertyAttribute::VISIBLE);
//        setPropertyAppearance(P_UV, PropertyAttribute::VISIBLE);
    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {
//        setPropertyAppearance(P_DISTANCE, PropertyAttribute::VISIBLE);
//        setPropertyAppearance(P_UV_DPOS, PropertyAttribute::VISIBLE);
    }

}



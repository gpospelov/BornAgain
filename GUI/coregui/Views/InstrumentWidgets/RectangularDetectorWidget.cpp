// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/RectangularDetectorWidget.cpp
//! @brief     Implements class RectangularDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RectangularDetectorWidget.h"
#include "ComboProperty.h"
#include "ComponentBoxEditor.h"
#include "ComponentEditor.h"
#include "DetectorItems.h"
#include "RectangularDetectorItem.h"
#include "ExtendedDetectorDialog.h"
#include "GroupInfoBox.h"
#include "ColumnResizer.h"
#include <QGroupBox>
#include <QVBoxLayout>

RectangularDetectorWidget::RectangularDetectorWidget(ColumnResizer* columnResizer,
                                                     RectangularDetectorItem* detectorItem,
                                                     QWidget* parent)
    : QWidget(parent)
    , m_columnResizer(nullptr)
    , m_xAxisEditor(nullptr)
    , m_yAxisEditor(nullptr)
    , m_resolutionFunctionEditor(nullptr)
    , m_alignmentEditor(nullptr)
    , m_positionsEditor(nullptr)
    , m_normalEditor(nullptr)
    , m_directionEditor(nullptr)
    , m_gridLayout(new QGridLayout)
    , m_detectorItem(nullptr)
{
    create_editors();
    setColumnResizer(columnResizer);

    // main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    setDetectorItem(detectorItem);
}

RectangularDetectorWidget::~RectangularDetectorWidget()
{
    if (m_columnResizer)
        m_columnResizer->dropWidgetsFromGridLayout(m_gridLayout);
}

void RectangularDetectorWidget::setDetectorItem(RectangularDetectorItem* detectorItem)
{
    if (m_detectorItem == detectorItem) {
        return;

    } else {
        if (m_detectorItem)
            m_detectorItem->mapper()->unsubscribe(this);

        m_detectorItem = detectorItem;

        if (!m_detectorItem)
            return;

        m_detectorItem->mapper()->setOnPropertyChange(
            [this](const QString& name) { onPropertyChanged(name); }, this);

        init_editors();
    }
}

void RectangularDetectorWidget::onPropertyChanged(const QString& propertyName)
{
    if (propertyName == RectangularDetectorItem::P_ALIGNMENT)
        init_alignment_editors();
}

void RectangularDetectorWidget::onColumnResizerDestroyed(QObject* object)
{
    if (object == m_columnResizer)
        m_columnResizer = 0;
}

//! set widget alignment to be under the control of external resizer
void RectangularDetectorWidget::setColumnResizer(ColumnResizer* columnResizer)
{
    if (m_columnResizer) {
        m_columnResizer->dropWidgetsFromGridLayout(m_gridLayout);
        disconnect(m_columnResizer, SIGNAL(destroyed(QObject*)), this,
                   SLOT(onColumnResizerDestroyed(QObject*)));
    }
    m_columnResizer = columnResizer;

    if (m_columnResizer) {
        connect(m_columnResizer, SIGNAL(destroyed(QObject*)), this,
                SLOT(onColumnResizerDestroyed(QObject*)));
        m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
        m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
        m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);
    }
}

//! create various editors to hold RectangularDetector properties
void RectangularDetectorWidget::create_editors()
{
    // axes and resolution function editors
    m_xAxisEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_xAxisEditor, 1, 0);

    m_yAxisEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_yAxisEditor, 1, 1);

    m_resolutionFunctionEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);

    // alignment selector editors
    m_alignmentEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_alignmentEditor, 2, 0);

    // editors for various positions
    m_positionsEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_positionsEditor, 3, 0);

    m_normalEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_normalEditor, 3, 1);

    m_directionEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_directionEditor, 3, 2);
}

void RectangularDetectorWidget::init_editors()
{
    m_xAxisEditor->clearEditor();
    SessionItem* xAxisItem = m_detectorItem->getItem(RectangularDetectorItem::P_X_AXIS);
    m_xAxisEditor->addPropertyItems(xAxisItem, QString("X axis"));

    m_yAxisEditor->clearEditor();
    SessionItem* yAxisItem = m_detectorItem->getItem(RectangularDetectorItem::P_Y_AXIS);
    m_yAxisEditor->addPropertyItems(yAxisItem, QString("Y axis"));

    m_resolutionFunctionEditor->clearEditor();
    SessionItem* resFuncGroup
        = m_detectorItem->getItem(RectangularDetectorItem::P_RESOLUTION_FUNCTION);
    m_resolutionFunctionEditor->addPropertyItems(resFuncGroup, QString("Resolution function"));

    m_alignmentEditor->clearEditor();
    m_alignmentEditor->addItem(m_detectorItem->getItem(RectangularDetectorItem::P_ALIGNMENT));

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
        = m_detectorItem->getItemValue(RectangularDetectorItem::P_ALIGNMENT).value<ComboProperty>();

    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {
        m_positionsEditor->show();
        m_normalEditor->show();
        m_directionEditor->show();

        m_positionsEditor->addPropertyItems(m_detectorItem->getItem(RectangularDetectorItem::P_U0),
                                            "Positions");
        m_positionsEditor->addPropertyItems(m_detectorItem->getItem(RectangularDetectorItem::P_V0),
                                            "Positions");

        SessionItem* normalVectorItem = m_detectorItem->getItem(RectangularDetectorItem::P_NORMAL);
        m_normalEditor->addPropertyItems(normalVectorItem, "Normal vector");

        SessionItem* directionVectorItem
            = m_detectorItem->getItem(RectangularDetectorItem::P_DIRECTION);
        m_directionEditor->addPropertyItems(directionVectorItem, "Direction vector");

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM
               || alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {
        m_positionsEditor->show();
        m_positionsEditor->addPropertyItems(
            m_detectorItem->getItem(RectangularDetectorItem::P_DBEAM_U0), "Positions");
        m_positionsEditor->addPropertyItems(
            m_detectorItem->getItem(RectangularDetectorItem::P_DBEAM_V0), "Positions");

        m_positionsEditor->addPropertyItems(
            m_detectorItem->getItem(RectangularDetectorItem::P_DISTANCE), "Positions");

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE
               || alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
        m_positionsEditor->show();

        m_positionsEditor->addPropertyItems(m_detectorItem->getItem(RectangularDetectorItem::P_U0),
                                            "Positions");
        m_positionsEditor->addPropertyItems(m_detectorItem->getItem(RectangularDetectorItem::P_V0),
                                            "Positions");

        m_positionsEditor->addPropertyItems(
            m_detectorItem->getItem(RectangularDetectorItem::P_DISTANCE), "Positions");
    }
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/DetectorEditorWidget.cpp
//! @brief     Implements class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DetectorEditorWidget.h"
#include "ComponentBoxEditor.h"
#include "DetectorItems.h"
#include "GroupInfoBox.h"
#include "ExtendedDetectorDialog.h"
#include "SphericalDetectorWidget.h"
#include "RectangularDetectorWidget.h"
#include "columnresizer.h"
#include "GUIHelpers.h"
#include "DetectorItems.h"
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

DetectorEditorWidget::DetectorEditorWidget(ColumnResizer *columnResizer, QWidget *parent)
    : QWidget(parent)
    , m_columnResizer(columnResizer)
    , m_groupBox(new GroupInfoBox("Detector Parameters"))
    , m_detectorItem(0)
    , m_subDetectorWidget(0)
{
    QVBoxLayout *groupLayout = new QVBoxLayout;
    m_groupBox->setButtonToolTip("Gives access to the detector mask editor");
    m_groupBox->setLayout(groupLayout);
    connect(m_groupBox, SIGNAL(clicked()), this, SLOT(onGroupBoxExtendedButton()));

    m_detectorTypeEditor = new ComponentBoxEditor;
    groupLayout->addWidget(m_detectorTypeEditor);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

DetectorEditorWidget::~DetectorEditorWidget()
{
    qDebug() << "DetectorEditorWidget::~DetectorEditorWidget()";
}

void DetectorEditorWidget::setDetectorItem(DetectorItem *detectorItem)
{
    qDebug() << "DetectorEditorWidget::setDetectorItem() -> XXX";

    m_detectorItem = detectorItem;
    if(!m_detectorItem) return;

    ModelMapper *mapper = new ModelMapper(this);
    mapper->setItem(m_detectorItem);
    mapper->setOnPropertyChange(
                [this](const QString &name)
    {
        onPropertyChanged(name);
    });

    m_detectorTypeEditor->clearEditor();
    m_detectorTypeEditor->addItem(m_detectorItem->getItem(DetectorItem::P_DETECTOR));

    init_SubDetector_Widget();
}

void DetectorEditorWidget::onPropertyChanged(const QString &propertyName)
{
    if(propertyName == DetectorItem::P_DETECTOR) {
        init_SubDetector_Widget();
    }
}

void DetectorEditorWidget::onGroupBoxExtendedButton()
{
    emit extendedDetectorEditorRequest(m_detectorItem);
}

void DetectorEditorWidget::init_SubDetector_Widget()
{
    if(m_subDetectorWidget) m_groupBox->layout()->removeWidget(m_subDetectorWidget);
    delete m_subDetectorWidget;
    m_subDetectorWidget = 0;


    SessionItem *subItem = m_detectorItem->getGroupItem(DetectorItem::P_DETECTOR);
//    if(SphericalDetectorItem *SphericalDetectorItem = dynamic_cast<)


    if(subItem->modelType() == Constants::SphericalDetectorType) {
        m_subDetectorWidget = new SphericalDetectorWidget(m_columnResizer, m_detectorItem);
    } else if(subItem->modelType() == Constants::RectangularDetectorType) {
        m_subDetectorWidget = new RectangularDetectorWidget(
            m_columnResizer, dynamic_cast<RectangularDetectorItem *>(subItem));
    } else {
        throw GUIHelpers::Error("DetectorEditorWidget::init_SubDetector_Widget() -> Error!"
                                "Unknown sybdetector type.");
    }

    m_groupBox->layout()->addWidget(m_subDetectorWidget);
}




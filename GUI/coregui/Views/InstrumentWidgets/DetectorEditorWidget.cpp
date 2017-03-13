// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorEditorWidget.cpp
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
#include "SphericalDetectorItem.h"
#include "RectangularDetectorItem.h"
#include "ExtendedDetectorDialog.h"
#include "GUIHelpers.h"
#include "GroupInfoBox.h"
#include "RectangularDetectorWidget.h"
#include "SphericalDetectorWidget.h"
#include "columnresizer.h"
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

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
}

void DetectorEditorWidget::setDetectorItem(DetectorContainerItem *detectorItem)
{
    if(m_detectorItem == detectorItem) {
        return;

    } else {
        if(m_detectorItem)
            m_detectorItem->mapper()->unsubscribe(this);

        m_detectorItem = detectorItem;
        if(!m_detectorItem) return;

        m_detectorItem->mapper()->setOnPropertyChange(
                    [this](const QString &name)
        {
            onPropertyChanged(name);
        }, this);

        m_detectorTypeEditor->clearEditor();
        m_detectorTypeEditor->addItem(m_detectorItem->getItem(DetectorContainerItem::P_DETECTOR));

        init_SubDetector_Widget();
    }

//    m_detectorItem = detectorItem;
//    if(!m_detectorItem) return;

//    m_mapper.reset(new ModelMapper);
//    m_mapper->setItem(m_detectorItem);
//    m_mapper->setOnPropertyChange(
//                [this](const QString &name)
//    {
//        onPropertyChanged(name);
//    });

//    m_detectorTypeEditor->clearEditor();
//    m_detectorTypeEditor->addItem(m_detectorItem->getItem(DetectorItem::P_DETECTOR));

//    init_SubDetector_Widget();
}

void DetectorEditorWidget::onPropertyChanged(const QString &propertyName)
{
    if(propertyName == DetectorContainerItem::P_DETECTOR) {
        init_SubDetector_Widget();
    }
}

void DetectorEditorWidget::onGroupBoxExtendedButton()
{
    emit extendedDetectorEditorRequest(m_detectorItem->detectorItem());
}

void DetectorEditorWidget::init_SubDetector_Widget()
{
    if(m_subDetectorWidget) m_groupBox->layout()->removeWidget(m_subDetectorWidget);
    delete m_subDetectorWidget;
    m_subDetectorWidget = 0;


    SessionItem *subItem = m_detectorItem->getGroupItem(DetectorContainerItem::P_DETECTOR);
//    if(SphericalDetectorItem *SphericalDetectorItem = dynamic_cast<)


    if(subItem->modelType() == Constants::SphericalDetectorType) {
        m_subDetectorWidget = new SphericalDetectorWidget(m_columnResizer, subItem);
    } else if(subItem->modelType() == Constants::RectangularDetectorType) {
        m_subDetectorWidget = new RectangularDetectorWidget(
            m_columnResizer, dynamic_cast<RectangularDetectorItem *>(subItem));
    } else {
        throw GUIHelpers::Error("DetectorEditorWidget::init_SubDetector_Widget() -> Error!"
                                "Unknown sybdetector type.");
    }

    m_groupBox->layout()->addWidget(m_subDetectorWidget);
}




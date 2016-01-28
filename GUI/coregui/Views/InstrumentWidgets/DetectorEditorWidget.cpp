// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/DetectorEditorWidget.cpp
//! @brief     Implements class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorEditorWidget.h"
#include "AwesomePropertyEditor.h"
#include "DetectorItems.h"
#include "GroupBox.h"
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
    , m_groupBox(new GroupBox("Detector Parameters"))
    , m_detectorItem(0)
    , m_subDetectorWidget(0)
{
    QVBoxLayout *groupLayout = new QVBoxLayout;
    m_groupBox->setButtonToolTip("Gives access to the detector mask editor");
    m_groupBox->setLayout(groupLayout);
    connect(m_groupBox, SIGNAL(clicked()), this, SLOT(onGroupBoxExtendedButton()));

    m_detectorTypeEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
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

    if(m_detectorItem) {
        disconnect(m_detectorItem,
                   SIGNAL(propertyChanged(const QString &)),
                   this,
                   SLOT(onPropertyChanged(const QString &)));
        disconnect(m_detectorItem,
                   SIGNAL(subItemChanged(const QString &)),
                   this,
                   SLOT(onSubItemChanged(const QString &)));
        disconnect(m_detectorItem,
                   SIGNAL(subItemPropertyChanged(const QString &, const QString &)),
                   this,
                   SLOT(onSubItemPropertyChanged(const QString &, const QString &)));
    }

    m_detectorItem = detectorItem;

    if(!m_detectorItem) return;

    connect(m_detectorItem,
               SIGNAL(propertyChanged(const QString &)),
               this,
               SLOT(onPropertyChanged(const QString &)));
    connect(m_detectorItem,
               SIGNAL(subItemChanged(const QString &)),
               this,
               SLOT(onSubItemChanged(const QString &)));
    connect(m_detectorItem,
               SIGNAL(subItemPropertyChanged(const QString &, const QString &)),
               this,
               SLOT(onSubItemPropertyChanged(const QString &, const QString &)));

    m_detectorTypeEditor->clearEditor();
    m_detectorTypeEditor->addItemProperty(m_detectorItem, DetectorItem::P_DETECTOR, QString(),
                                     AwesomePropertyEditor::SKIP);

    init_SubDetector_Widget();
}

void DetectorEditorWidget::onPropertyChanged(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}

void DetectorEditorWidget::onSubItemChanged(const QString &propertyName)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << "DetectorEditorWidget::onSubItemChanged" << propertyName;
    if(propertyName == DetectorItem::P_DETECTOR) {
        init_SubDetector_Widget();
    }
}

void DetectorEditorWidget::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "DetectorEditorWidget::onSubItemPropertyChanged" << property_group << property_name;

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


    ParameterizedItem *subItem = m_detectorItem->getSubItems()[DetectorItem::P_DETECTOR];
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




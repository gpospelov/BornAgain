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

#include <QDebug>
#include <QGroupBox>
#include <QVBoxLayout>
#include "ComponentBoxEditor.h"
#include "DetectorItems.h"
#include "ExtendedDetectorDialog.h"
#include "GroupInfoBox.h"
#include "columnresizer.h"
#include "SphericalDetectorWidget.h"

SphericalDetectorWidget::SphericalDetectorWidget(ColumnResizer *columnResizer,
                                                 DetectorItem *detectorItem, QWidget *parent)
    : QWidget(parent)
    , m_columnResizer(columnResizer)
    , m_phiAxisEditor(0)
    , m_alphaAxisEditor(0)
    , m_resolutionFunctionEditor(0)
    , m_gridLayout(new QGridLayout)
{
    m_phiAxisEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_phiAxisEditor, 1, 0);

    m_alphaAxisEditor = new ComponentBoxEditor;
    m_gridLayout->addWidget(m_alphaAxisEditor, 1, 1);

    m_resolutionFunctionEditor = new ComponentBoxEditor;
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
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();
    if(m_columnResizer) m_columnResizer->dropWidgetsFromGridLayout(m_gridLayout);

}

void SphericalDetectorWidget::setDetectorItem(DetectorItem *detectorItem)
{
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();

    if (!detectorItem)
        return;

    SphericalDetectorItem *sphericalDetector = dynamic_cast<SphericalDetectorItem *>(
                detectorItem->getGroupItem(DetectorItem::P_DETECTOR));
    Q_ASSERT(sphericalDetector);

    SessionItem *phiAxisItem = sphericalDetector->getItem(SphericalDetectorItem::P_PHI_AXIS);
    m_phiAxisEditor->addPropertyItems(phiAxisItem, QString("Phi axis"));

    SessionItem *alphaAxisItem
        = sphericalDetector->getItem(SphericalDetectorItem::P_ALPHA_AXIS);
    m_alphaAxisEditor->addPropertyItems(alphaAxisItem, QString("Alpha axis"));

    SessionItem *resFuncGroup = sphericalDetector->getItem(SphericalDetectorItem::P_RESOLUTION_FUNCTION);
    m_resolutionFunctionEditor->addPropertyItems(resFuncGroup, QString("Resolution function"));
}

void SphericalDetectorWidget::onColumnResizerDestroyed(QObject *object)
{
    if(object == m_columnResizer) m_columnResizer = 0;
}



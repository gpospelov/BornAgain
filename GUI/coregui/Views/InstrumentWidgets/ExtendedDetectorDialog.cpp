// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/ExtendedDetectorDialog.cpp
//! @brief     Implements class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ExtendedDetectorDialog.h"
#include "MaskEditor.h"
#include "MaskModel.h"
#include "DetectorMaskDelegate.h"
#include <QPushButton>
#include <QModelIndex>
#include <QVBoxLayout>

ExtendedDetectorDialog::ExtendedDetectorDialog(QWidget *parent)
    : QDialog(parent)
    , m_maskEditor(new MaskEditor)
    , m_detectorMaskDelegate(new DetectorMaskDelegate(this))
{
    setMinimumSize(256, 256);
    resize(800, 600);
    setWindowTitle("Mask Editor");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setModal(true);

    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button = new QPushButton("Close", this);
    button->setAutoDefault(false);
    connect(button, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->setContentsMargins(4, 4, 4, 4);
    buttonLayout->addWidget(button);

    layout->addWidget(m_maskEditor);
    layout->addLayout(buttonLayout);

    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

//    m_maskEditor->init_test_model();

}

void ExtendedDetectorDialog::setDetectorItem(DetectorItem *detectorItem)
{
    m_detectorMaskDelegate->setDetectorItem(detectorItem);
    m_maskEditor->setModel(m_detectorMaskDelegate->getMaskModel());
}

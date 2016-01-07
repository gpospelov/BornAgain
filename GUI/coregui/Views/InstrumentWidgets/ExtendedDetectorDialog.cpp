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
#include "CustomEventFilters.h"
#include <QPushButton>
#include <QModelIndex>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>
#include <QSettings>

ExtendedDetectorDialog::ExtendedDetectorDialog(QWidget *parent)
    : QDialog(parent)
    , m_maskEditor(new MaskEditor)
    , m_detectorMaskDelegate(new DetectorMaskDelegate(this))
{
    setMinimumSize(256, 256);

    QSettings settings;
    if (settings.childGroups().contains("MaskEditor")) {
        settings.beginGroup("MaskEditor");
        resize(settings.value("size", QSize(750, 650)).toSize());
        move(settings.value("pos", QPoint(200,200)).toPoint());
    }
    else {
        resize(750, 650);
    }

    setWindowTitle("Mask Editor");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setModal(true);

    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button = new QPushButton("Close", this);
    connect(button, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->setContentsMargins(4, 4, 4, 4);
    buttonLayout->addWidget(button);

    layout->addWidget(m_maskEditor);
    layout->addLayout(buttonLayout);

    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // hadling keyboar focus policies
    button->setDefault(false);
    button->setAutoDefault(false);
    setFocusProxy(m_maskEditor);

    SpaceKeyEater *filter = new SpaceKeyEater(this);
    installEventFilter(filter);
    button->installEventFilter(filter);

}

void ExtendedDetectorDialog::setDetectorContext(InstrumentModel *instrumentModel,
                                                DetectorItem *detectorItem)
{
    m_detectorMaskDelegate->setDetectorContext(instrumentModel, detectorItem);
    m_detectorMaskDelegate->initMaskEditor(m_maskEditor);
}

void ExtendedDetectorDialog::reject()
{
    QSettings settings;
    settings.beginGroup("MaskEditor");
    settings.setValue("size", this->size());
    settings.setValue("pos", this->pos());
    settings.endGroup();
    QDialog::reject();
}

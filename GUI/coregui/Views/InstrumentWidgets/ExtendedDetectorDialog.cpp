// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ExtendedDetectorDialog.cpp
//! @brief     Implements class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ExtendedDetectorDialog.h"
#include "CustomEventFilters.h"
#include "DetectorMaskDelegate.h"
#include "MaskEditor.h"
#include "mainwindow_constants.h"
#include <QKeyEvent>
#include <QModelIndex>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

ExtendedDetectorDialog::ExtendedDetectorDialog(QWidget *parent)
    : QDialog(parent)
    , m_maskEditor(new MaskEditor)
    , m_detectorMaskDelegate(new DetectorMaskDelegate(this))
{
    setMinimumSize(256, 256);

    readSettings();

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
    m_detectorMaskDelegate->initMaskEditorContext(m_maskEditor, instrumentModel,
                                                  detectorItem);
}

void ExtendedDetectorDialog::reject()
{
    writeSettings();
    QDialog::reject();
}

void ExtendedDetectorDialog::readSettings()
{
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_MASKEDITOR)) {
        settings.beginGroup(Constants::S_MASKEDITOR);
        resize(settings.value(Constants::S_WINDOWSIZE, QSize(750, 650)).toSize());
        move(settings.value(Constants::S_WINDOWPOSITION, QPoint(200,200)).toPoint());
    }
    else {
        resize(750, 650);
    }
}

void ExtendedDetectorDialog::writeSettings()
{
    QSettings settings;
    settings.beginGroup(Constants::S_MASKEDITOR);
    settings.setValue(Constants::S_WINDOWSIZE, this->size());
    settings.setValue(Constants::S_WINDOWPOSITION, this->pos());
    settings.endGroup();
}

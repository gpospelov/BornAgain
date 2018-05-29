// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceDialog.cpp
//! @brief     Implements class RealSpaceDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceDialog.h"
#include "RealSpaceWidget.h"
#include "StyleUtils.h"
#include <QAction>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include "mainwindow_constants.h"

namespace
{
    const QSize minimum_dialog_size(400, 250);
    const QSize default_dialog_size(500, 400);
}

RealSpaceDialog::RealSpaceDialog(SampleModel *sampleModel,
                                             QItemSelectionModel* selectionModel, QWidget *parent)
    : QWidget(parent)
    , m_sampleModel(sampleModel)
    , m_selectionModel(selectionModel)
{
    setWindowTitle("Real Space Viewer");
    setMinimumSize(minimum_dialog_size);
    resize(default_dialog_size);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowFlags(windowFlags() | Qt::Window | Qt::WindowStaysOnTopHint);

    // read the user's last persistent settings (size and position) of the dialog box
    readSettings();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    //layout->setContentsMargins(0, 0, 0, 0);

    #ifdef BORNAGAIN_OPENGL
    RealSpaceWidget* widget = new RealSpaceWidget(m_sampleModel, m_selectionModel);
    widget->setModel(m_sampleModel, m_selectionModel);
    layout->addWidget(widget);
    #endif

    setLayout(layout);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void RealSpaceDialog::closeEvent(QCloseEvent *)
{
    // on close event, remember the settings (size and position) of the dialog box as persistent
    writeSettings();
}

void RealSpaceDialog::readSettings()
{
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_REALSPACEDIALOG)) {
        settings.beginGroup(Constants::S_REALSPACEDIALOG);
        resize(settings.value(Constants::S_WINDOWSIZE, default_dialog_size).toSize());
        if (settings.contains(Constants::S_WINDOWPOSITION)) {
            move(settings.value(Constants::S_WINDOWPOSITION).toPoint());
        }
    } else {
        resize(default_dialog_size);
    }
}

void RealSpaceDialog::writeSettings()
{
    QSettings settings;
    settings.beginGroup(Constants::S_REALSPACEDIALOG);
    settings.setValue(Constants::S_WINDOWSIZE, this->size());
    settings.setValue(Constants::S_WINDOWPOSITION, this->pos());
    settings.endGroup();
}

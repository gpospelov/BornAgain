//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/sldeditor.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/sldeditor/sldeditor.h"
#include "gui2/mainwindow/styleutils.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/sldeditor/graphicsscene.h"
#include "gui2/sldeditor/sldeditoractions.h"
#include "gui2/sldeditor/sldeditortoolbar.h"
#include "gui2/sldeditor/sldviewwidget.h"
#include "mvvm/plotting/graphcanvas.h"
#include <QVBoxLayout>

namespace gui2 {

//! The constructor
SLDEditor::SLDEditor(QWidget* parent)
    : QWidget(parent)
    , m_editorActions(new SLDEditorActions(this))
    , m_viewWidget(new SLDViewWidget(this))
    , m_toolBar(new SLDEditorToolBar(m_editorActions)) {
    setWindowTitle("SLD editor");
    auto layout = new QVBoxLayout;
    layout->addWidget(m_toolBar);
    layout->addWidget(m_viewWidget);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    connect(dynamic_cast<SLDEditorToolBar*>(m_toolBar), &SLDEditorToolBar::resetViewport, [this]() {
        GraphicsScene* scene_item = dynamic_cast<GraphicsScene*>(m_viewWidget->scene());
        if (!scene_item)
            return;
        scene_item->graphCanvas()->setViewportToContent();
    });
}

//! The destructor
SLDEditor::~SLDEditor() = default;

void SLDEditor::setModels(ApplicationModels* models) {
    m_viewWidget->setModels(models);
    m_editorActions->setModel(models->sldViewModel());
}

QSize SLDEditor::sizeHint() const {
    return StyleUtils::DockSizeHint();
}

QSize SLDEditor::minimumSizeHint() const {
    return StyleUtils::DockMinimumSizeHint();
}

} // namespace gui2

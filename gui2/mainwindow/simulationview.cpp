//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/mainwindow/simulationview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/mainwindow/simulationview.h"
#include "gui2/layereditor/layereditor.h"
#include "gui2/materialeditor/materialeditor.h"
#include "gui2/quicksimeditor/instrumentpropertyeditor.h"
#include "gui2/quicksimeditor/quicksimeditor.h"
#include "gui2/sldeditor/sldeditor.h"
#include "mvvm/widgets/collapsiblelistwidget.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace ModelView;

namespace gui2 {

SimulationView::SimulationView(ApplicationModels* models, QWidget* parent)
    : QMainWindow(parent)
    , m_editorList(new CollapsibleListWidget)
    , m_simEditor(new QuickSimEditor)
    , m_models(models) {
    auto splitter = new QSplitter;

    initEditorList();

    splitter->addWidget(m_editorList);
    splitter->addWidget(m_simEditor);

    setCentralWidget(splitter);
}

void SimulationView::initEditorList() {
    m_editorList->layout()->setContentsMargins(4, 4, 4, 4);
    auto material_editor = new MaterialEditor(this);
    auto layer_editor = new LayerEditor(this);
    auto sld_editor = new SLDEditor(this);
    auto instrument_editor = new InstrumentPropertyEditor(this);

    m_editorList->addWidget(material_editor, "Material editor");
    m_editorList->addWidget(layer_editor, "Layer editor", /*set_collapsed*/ true);
    m_editorList->addWidget(instrument_editor, "Instrument editor", /*set_collapsed*/ true);
    m_editorList->addWidget(sld_editor, "SLD editor", /*set_collapsed*/ true);

    material_editor->setModels(m_models);
    layer_editor->setModels(m_models);
    sld_editor->setModels(m_models);
    m_simEditor->setModels(m_models);
    instrument_editor->setModels(m_models);
}

} // namespace gui2

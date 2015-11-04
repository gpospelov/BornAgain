// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditor.cpp
//! @brief     Implements class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditor.h"
#include "MaskEditorCanvas.h"
#include "MaskEditorToolPanel.h"
#include <QBoxLayout>
#include <QSplitter>

#include "SimulationRegistry.h"
#include <boost/scoped_ptr.hpp>
#include "SampleBuilderFactory.h"
#include "IntensityDataItem.h"


MaskEditor::MaskEditor(QWidget *parent)
    : QWidget(parent)
    , m_editorCanvas(new MaskEditorCanvas(this))
    , m_editorToolPanel(new MaskEditorToolPanel(this))
    , m_splitter(new QSplitter(this))
{
    setObjectName(QStringLiteral("IntensityDataPlotWidget"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_splitter->addWidget(m_editorCanvas);
    m_splitter->addWidget(m_editorToolPanel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);
}

IntensityDataItem *MaskEditor::create_test_item() const
{
    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    SampleBuilderFactory sampleFactory;
    boost::scoped_ptr<ISample> sample(sampleFactory.createSample("CylindersAndPrismsBuilder"));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    IntensityDataItem *result = new IntensityDataItem;
    result->setOutputData(simulation->getOutputData()->clone());

    return result;
}

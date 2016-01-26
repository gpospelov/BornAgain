// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestMesoCrystal1.cpp
//! @brief     Implements class TestMesoCrystal1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestMesoCrystal1.h"
#include "SimulationRegistry.h"
#include "Types.h"
#include "Utils.h"
#include "DrawHelper.h"
#include "IsGISAXSTools.h"
#include "IntensityDataIOFactory.h"
#include "FileSystem.h"

void TestMesoCrystal1::execute()
{
    SimulationRegistry sim_registry;
    GISASSimulation *simulation = sim_registry.createSimulation("mesocrystal01");
    simulation->setProgramOptions(mp_options);

    // loading reference data
    std::string filename = Utils::FileSystem::GetReferenceDataDir()
            + "mesocrystal01_reference.int.gz";

    OutputData<double> *reference =
            IntensityDataIOFactory::readOutputData(filename);

    simulation->runSimulation();
    //simulation->normalize();

    OutputData<double> *data = simulation->getDetectorIntensity();

    TCanvas *c1 = DrawHelper::createAndRegisterCanvas("sim_meso_crystal",
            "mesocrystal", 1024, 768);
    c1->cd(); gPad->SetLogz();

    TH2D *h2 = IsGISAXSTools::getOutputDataTH2D(*data, "mesocrystal");
    h2->SetTitle("");
    h2->GetXaxis()->SetTitle("#phi_{f}");
    h2->GetYaxis()->SetTitle("#alpha_{f}");
    h2->GetXaxis()->SetTitleOffset(0.9);
    h2->GetYaxis()->SetTitleOffset(1.0);
    h2->SetMinimum(100.);
    h2->SetMaximum(1e6);
    h2->Draw("COLZ");

    IsGISAXSTools::drawOutputDataComparisonResults(
            *data, *reference, "found", "found params", 100, 1e6);

    IntensityDataIOFactory::writeOutputData(*data,"test_mesocrystal1.int");
    delete data;

    delete simulation;
    delete reference;
}


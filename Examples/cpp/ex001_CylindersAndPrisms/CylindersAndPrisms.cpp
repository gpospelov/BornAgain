#include "OutputData.h"
#include "Simulation.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"

#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TStyle.h"
#include "TLine.h"
#include "TROOT.h"
#include "TApplication.h"

#include "CylindersAndPrisms.h"


void CylindersAndPrismsExample::setSample() 
{
    m_sample = new MultiLayer();

    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0., 0.);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    ParticleDecoration particle_decoration;
    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    particle_decoration.addParticle(
                new Particle(particle_material,
                             new FormFactorCylinder(5*Units::nanometer,
                                                    5*Units::nanometer)),
                0.0, 0.5);
    particle_decoration.addParticle(
                new Particle(particle_material,
                             new FormFactorPrism3(5*Units::nanometer,
                                                  5*Units::nanometer)),
                0.0, 0.5);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    m_sample->addLayer(air_layer);
    m_sample->addLayer(substrate_layer);

}

void CylindersAndPrismsExample::setSimulation()  
{
	m_simulation = new Simulation();

    m_simulation->setDetectorParameters(
        100,-1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    m_simulation->setSample(*m_sample);
}

CylindersAndPrismsExample::CylindersAndPrismsExample() : m_result(0)
{
	setSample();
	setSimulation();
}

void CylindersAndPrismsExample::runSimulation() 
{
	m_simulation->runSimulation();
	m_result = m_simulation->getIntensityData();
}

void CylindersAndPrismsExample::drawResult()
{
	const IAxis *axisPhi = m_result->getAxis(0);
	const IAxis *axisAlpha = m_result->getAxis(1);

	size_t nPhibins = axisPhi->getSize();
	size_t nAlphabins = axisAlpha->getSize();

    TH2D *hist = new TH2D("Layer Roughness", "Layer Roughness", 
		(int)nPhibins, axisPhi->getMin()*Units::degree, axisPhi->getMax()*Units::degree, 
		(int)nAlphabins, axisAlpha->getMin()*Units::degree, axisAlpha->getMax()*Units::degree);

	//hist->GetXaxis()->SetTitle( axisPhi->getName() );
    //hist->GetYaxis()->SetTitle( axisAplha->getName() );

	OutputData<double>::const_iterator it = m_result->begin();
    while (it != m_result->end())
    {
        double x = m_result->getValueOfAxis( axisPhi->getName(), it.getIndex() );
        double y = m_result->getValueOfAxis( axisAlpha->getName(), it.getIndex() );
        double value = *it++;
        hist->Fill(x*Units::degree, y*Units::degree, value);
    }
	
	hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);

	TCanvas *c1 = new TCanvas("Layer Roughness", "Layer Roughness", 800, 800);
	c1->cd();
	c1->SetLogz();
	hist->SetMinimum(1.0);
	hist->DrawCopy("colz");
	c1->Update();
	
	delete axisPhi;
	delete axisAlpha;
	delete hist;
}


int main(int argc, char **argv)
{
	CylindersAndPrismsExample* example = new CylindersAndPrismsExample();
	example->runSimulation();
	TApplication *theApp = new TApplication("theApp", &argc, argv);
	example->drawResult();
	theApp->Run();
    return 0;
}

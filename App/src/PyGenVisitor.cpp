#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include "Exceptions.h"
#include "FormFactors.h"
#include "InterferenceFunctions.h"
#include "IMaterial.h"
#include "ICompositeSample.h"
#include "Layer.h"
#include "LabelSample.h"
#include "LayerInterface.h"
#include "ParticleBuilder.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleInfo.h"
#include "ParticleLayout.h"
#include "PyGenVisitor.h"
#include "TestPyGenerator.h"

PyGenVisitor::PyGenVisitor()
    : m_label(new LabelSample())
{

}

LabelSample * PyGenVisitor::getLabelSample()
{
    return m_label;
}

void PyGenVisitor::genPyScript()
{
    std::ofstream myfile;
    myfile.open ("PythonScript.py");
    myfile << "import numpy \nimport matplotlib \nimport pylab \nfrom libBornAgainCore import *\n\n";
    myfile << "#NOTE: All the ANGLES are displayed in RADIANS\n\n";
    myfile << "def GetSample():\n\t# Defining Materials" << std::endl;
    std::map<const IMaterial *,std::string>::iterator it1 = m_label->getMaterialMap()->begin();
    while (it1 != m_label->getMaterialMap()->end())
    {
        if (visitedMaterials.find(it1->second) == visitedMaterials.end())
        {
            visitedMaterials.insert(it1->second);
            const IMaterial *material = it1->first;
            complex_t ri = material->getRefractiveIndex();
            double delta = 1-real(ri);
            double beta = imag(ri);
            myfile << "\t" << m_label->getLabel(material) << " = HomogenousMaterial(\"" << material->getName();
            myfile << "\"," << PrintDouble(delta) << "," << PrintDouble(beta) << ")" << std::endl;
        }
        it1++;
    }

    myfile << "\n\t# Defining Layers" << std::endl;
    std::map<const Layer *,std::string>::iterator it2 = m_label->getLayerMap()->begin();
    while (it2 != m_label->getLayerMap()->end())
    {
        const Layer *layer = it2->first;
        myfile << "\t" << it2->second << " = Layer(" << m_label->getLabel(layer->getMaterial());
        if (layer->getThickness() != 0)
        {
            myfile << "," << layer->getThickness();
        }
        myfile << ")" << std::endl;
        it2++;
    }

    if (m_label->getParticleMap()->size() != 0)
    {
        myfile << "\n\t# Defining Particles" << std::endl;
    }

    int formFactorNotFound =0;
    std::map<const IFormFactor *,std::string>::iterator it3 = m_label->getFormFactorMap()->begin();
    while (it3 != m_label->getFormFactorMap()->end())
    {
        myfile << "\t" << it3->second;
        const IFormFactor *iFormFactor = it3->first;

        if (const FormFactorAnisoPyramid *anisoPyramid = dynamic_cast<const FormFactorAnisoPyramid *>(iFormFactor))
        {
            myfile << " = FormFactorAnisoPyramid(" << anisoPyramid->getLength() << "*nanometer,"
            << anisoPyramid->getWidth() << "*nanometer," << anisoPyramid->getHeight() << "*nanometer,"
            << anisoPyramid->getAlpha() << ")" << std::endl;
        }

        else if (const FormFactorBox *box = dynamic_cast<const FormFactorBox *>(iFormFactor))
        {
            myfile << " = FormFactorBox(" << box->getLength() << "*nanometer,"
            << box->getWidth()<< "*nanometer," << box->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorCone *cone = dynamic_cast<const FormFactorCone *>(iFormFactor))
        {
            myfile << " = FormFactorCone(" << cone->getRadius() << "*nanometer," << cone->getHeight()
            << "*nanometer," << cone->getAlpha() << ")" << std::endl;
        }

        else if (const FormFactorCone6 *cone6 = dynamic_cast<const FormFactorCone6 *>(iFormFactor))
        {
            myfile << " = FormFactorCone6(" << cone6->getRadius() << "*nanometer," << cone6->getHeight()
            << "*nanometer," << cone6->getAlpha() << ")" << std::endl;
        }

        else if (const FormFactorCuboctahedron *cuboctahedron = dynamic_cast<const FormFactorCuboctahedron *>(iFormFactor))
        {
            myfile << " = FormFactorCuboctahedron(" << cuboctahedron->getLength() << "*nanometer,"
            << cuboctahedron->getHeight() << "*nanometer," << cuboctahedron->getHeightRatio() << "*nanometer"
            << cuboctahedron->getAlpha() << ")" << std::endl;
        }

        else if (const FormFactorCylinder *cylinder = dynamic_cast<const FormFactorCylinder *>(iFormFactor))
        {
            myfile << " = FormFactorCylinder(" << cylinder->getHeight() << "*nanometer,"
            << cylinder->getRadius() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorEllipsoidalCylinder *ellipsoidalCylinder = dynamic_cast<const FormFactorEllipsoidalCylinder *>(iFormFactor))
        {
            myfile << " = FormFactorEllipsoidalCylinder(" << ellipsoidalCylinder->getRadiusA()
            << "*nanometer," << ellipsoidalCylinder->getRadiusB() << "*nanometer,"
            << ellipsoidalCylinder->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorFullSphere *fullSphere = dynamic_cast<const FormFactorFullSphere *>(iFormFactor))
        {
            myfile << " = FormFactorFullSphere(" << fullSphere->getRadius() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorFullSpheroid *fullSpheroid = dynamic_cast<const FormFactorFullSpheroid *>(iFormFactor))
        {
            myfile << " = FormFactorFullSpheroid(" << fullSpheroid->getRadius() << "*nanometer,"
            << fullSpheroid->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorGauss *gauss = dynamic_cast<const FormFactorGauss *>(iFormFactor))
        {
            if(gauss->getRadius() == gauss->getHeight())
            {
                myfile << " = FormFactorGauss(" << gauss->getVolume() << "*(nanometer)**3)" << std::endl;
            }
            else
            {
                myfile << " = FormFactorGauss(" << gauss->getRadius() << "*nanometer,"
                << gauss->getHeight() << "*nanometer)" << std::endl;
            }
        }

        else if (const FormFactorHemiEllipsoid *hemiEllipsoid = dynamic_cast<const FormFactorHemiEllipsoid *>(iFormFactor))
        {
            myfile << " = FormFactorHemiEllipsoid(" << hemiEllipsoid->getRadiusA() << "*nanometer,"
            << hemiEllipsoid->getRadiusB() << "*nanometer," << hemiEllipsoid->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorInfLongBox *infLongBox = dynamic_cast<const FormFactorInfLongBox *>(iFormFactor))
        {
            myfile << " = FormFactorInfLongBox(" << infLongBox->getWidth() << "*nanometer,"
            << infLongBox->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorInfLongRipple1 *infLongRipple1 = dynamic_cast<const FormFactorInfLongRipple1 *>(iFormFactor))
        {
            myfile << " = FormFactorInfLongRipple1(" << infLongRipple1->getWidth() << "*nanometer,"
            << infLongRipple1->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorInfLongRipple2 *infLongRipple2 = dynamic_cast<const FormFactorInfLongRipple2 *>(iFormFactor))
        {
            myfile << " = FormFactorInfLongRipple2(" << infLongRipple2->getWidth() << "*nanometer,"
            << infLongRipple1->getHeight() << "*nanometer," << infLongRipple2->getAsymetry() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorLorentz *lorentz = dynamic_cast<const FormFactorLorentz *>(iFormFactor))
        {
            if(lorentz->getRadius() == lorentz->getHeight())
            {
                myfile << " = FormFactorLorentz(" << lorentz->getVolume() << "*(nanometer)**3)" << std::endl;
            }
            else
            {
                myfile << " = FormFactorLorentz(" << lorentz->getRadius() << "*nanometer,"
                << lorentz->getHeight() << "*nanometer)" << std::endl;
            }
        }

        else if (const FormFactorPrism3 *prism3 = dynamic_cast<const FormFactorPrism3 *>(iFormFactor))
        {
            myfile << " = FormFactorPrism3(" << prism3->getLength() << "*nanometer,"
            << prism3->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorPrism6 *prism6 = dynamic_cast<const FormFactorPrism6 *>(iFormFactor))
        {
            myfile << " = FormFactorPrism6(" << prism6->getRadius() << "*nanometer,"
            << prism6->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorPyramid *pyramid = dynamic_cast<const FormFactorPyramid *>(iFormFactor))
        {
            myfile << " = FormFactorPyramid(" << pyramid->getLength() << "*nanometer," <<
            pyramid->getHeight() << "*nanometer," << pyramid->getAlpha() << ")" << std::endl;
        }

        else if (const FormFactorRipple1 *ripple1 = dynamic_cast<const FormFactorRipple1 *>(iFormFactor))
        {
            myfile << " = FormFactorRipple1(" << ripple1->getLength() << "*nanometer," <<
            ripple1->getWidth() << "*nanometer," << ripple1->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorRipple2 *ripple2 = dynamic_cast<const FormFactorRipple2 *>(iFormFactor))
        {
            myfile << " = FormFactorRipple2(" << ripple2->getLength() << "*nanometer," <<
            ripple2->getWidth() << "*nanometer," << ripple2->getHeight() << "nanometer," <<
            ripple2->getAsymmetry() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorTetrahedron *tetrahedron = dynamic_cast<const FormFactorTetrahedron *>(iFormFactor))
        {
            myfile << " = FormFactorTetrahedron(" << tetrahedron->getLength() << "*nanometer," <<
            tetrahedron->getHeight() << "*nanometer," << tetrahedron->getAlpha() << ")" << std::endl;
        }

        else if (const FormFactorTruncatedSphere *truncatedSphere = dynamic_cast<const FormFactorTruncatedSphere *>(iFormFactor))
        {
            myfile << " = FormFactorTruncatedSphere(" << truncatedSphere->getRadius() << "*nanometer,"
            << truncatedSphere->getHeight() << "*nanometer)" << std::endl;
        }

        else if (const FormFactorTruncatedSpheroid *truncatedSpheroid = dynamic_cast<const FormFactorTruncatedSpheroid *>(iFormFactor))
        {
            myfile << " = FormFactorTruncatedSpheroid(" << truncatedSpheroid->getRadius() << "*nanometer,"
            << truncatedSpheroid->getHeight() << "*nanometer," << truncatedSpheroid->getHeightFlattening()
            << "*nanometer)" << std::endl;
        }

        else
        {
            myfile << std::endl << formFactorNotFound << ": " << iFormFactor->getName()
            << "Not Casted To Any FormFactor" << std::endl;
            formFactorNotFound++;
        }
        it3++;
    }

    std::map<const Particle *,std::string>::iterator it4 = m_label->getParticleMap()->begin();
    while (it4 != m_label->getParticleMap()->end())
    {
        const Particle *particle = it4->first;
        myfile << "\t" << it4->second << " = Particle(" << m_label->getLabel(particle->getMaterial())
        << "," << m_label->getLabel(particle->getSimpleFormFactor()) << ")" << std::endl;
        it4++;
    }

    if (m_label->getInterferenceFunctionMap()->size() != 0)
    {
        myfile << "\n\t# Defining Interference functions" << std::endl;
    }

    int interfernceFunctionNotFound =0;
    std::map<const IInterferenceFunction *,std::string>::iterator it = m_label->getInterferenceFunctionMap()->begin();
    while (it != m_label->getInterferenceFunctionMap()->end())
    {
        myfile << "\t" << it->second;
        const IInterferenceFunction *iInterferenceFunction = it->first;

        if (const InterferenceFunctionNone *none = dynamic_cast<const InterferenceFunctionNone *>(iInterferenceFunction))
        {
            myfile << " = InterFerenceFunctionNone()" << std::endl;
        }

        else if (const InterferenceFunction1DLattice *oneDLattice = dynamic_cast<const InterferenceFunction1DLattice *>(iInterferenceFunction))
        {
            myfile << " = InterFerenceFunction1DLattice()" << std::endl;
        }

        else if (const InterferenceFunction1DParaCrystal *oneDParaCrystal = dynamic_cast<const InterferenceFunction1DParaCrystal *>(iInterferenceFunction))
        {
            myfile << " = InterFerenceFunction1DParaCrystal(" << oneDParaCrystal->getPeakDistance()
            << "*nanometer," << oneDParaCrystal->getDampingLength() << "*nanometer)" << std::endl;
        }

        else if (const InterferenceFunction2DLattice *twoDLattice = dynamic_cast<const InterferenceFunction2DLattice *>(iInterferenceFunction))
        {
            myfile << " = InterFerenceFunction2DLattice)" << std::endl;
        }

        else if (const InterferenceFunction2DParaCrystal *twoDParaCrystal = dynamic_cast<const InterferenceFunction2DParaCrystal *>(iInterferenceFunction))
        {
            myfile << " = InterFerenceFunction2DParaCrystal(" <<twoDParaCrystal->getLatticeLengths()[0]
            << "*nanometer," << twoDParaCrystal->getLatticeLengths()[1] << "*nanometer," <<
            twoDParaCrystal->getAlphaLattice() << "*nanometer," << twoDParaCrystal->getLatticeOrientation()
            << "*nanometer," << twoDParaCrystal->getDampingLength() << "*nanometer)" << std::endl;
        }

        else
        {
            myfile << std::endl << interfernceFunctionNotFound << ": " << iInterferenceFunction->getName()
            << "Not Casted To Any Interference Function" << std::endl;
            formFactorNotFound++;
        }
        it++;
    }

    if (m_label->getParticleLayoutMap()->size() > 0)
    {
        myfile << "\n\t# Defining Particle layouts" << std::endl;
    }
    std::map<const ILayout *,std::string>::iterator it5 = m_label->getParticleLayoutMap()->begin();
    while (it5 != m_label->getParticleLayoutMap()->end())
    {
        const ILayout *iLayout = it5->first;
        if (const ParticleLayout *particleLayout = dynamic_cast<const ParticleLayout *>(iLayout))
        {
            myfile << "\t" << it5->second << " = ParticleLayout()" << std::endl;
            size_t numberOfParticles = particleLayout->getNumberOfParticles();
            size_t particleIndex = 0;
            while (particleIndex != numberOfParticles)
            {
                const ParticleInfo *particleInfo = particleLayout->getParticleInfo(particleIndex);
                myfile << "\t" << it5->second << ".addParticle(" << m_label->getLabel(particleInfo->getParticle()) << ","
                << PrintDouble(particleInfo->getDepth()) << "," << PrintDouble(particleInfo->getAbundance()) << ")" << std::endl;
                particleIndex++;
            }
            size_t numberOfInterferenceFunctions = particleLayout->getNumberOfInterferenceFunctions();
            size_t interferenceFunctionsIndex = 0;
            while (interferenceFunctionsIndex != numberOfInterferenceFunctions)
            {
                myfile << "\t" << it5->second << ".addInterferenceFunction("
                << m_label->getLabel(particleLayout->getInterferenceFunction(interferenceFunctionsIndex)) << ")" << std::endl;
                interferenceFunctionsIndex++;
            }
        }
        it5++;
    }

    it2 = m_label->getLayerMap()->begin();
    while (it2 != m_label->getLayerMap()->end())
    {
        const Layer *layer = it2->first;
        if (layer->hasDWBASimulation())
        {
            myfile << "\t" << it2->second << ".setLayout(" << m_label->getLabel(layer->getLayout())<< ")" << std::endl;
        }
        it2++;
    }

    if (m_label->getLayerRoughnessMap()->size() != 0)
    {
        myfile << "\n\t# Defining Roughness Parameters" << std::endl;
    }
    std::map<const LayerRoughness *,std::string>::iterator it6 = m_label->getLayerRoughnessMap()->begin();
    while (it6 != m_label->getLayerRoughnessMap()->end())
    {
        myfile << "\t" << it6->second << " = LayerRoughness(" << it6->first->getSigma()
        << "*nanometer," << it6->first->getHurstParameter() << "*nanometer,"
        << it6->first->getLatteralCorrLength() << "*nanometer)" << std::endl;
        it6++;
    }

    myfile << "\n\t# Defining Multilayers" << std::endl;
    std::map<const MultiLayer *,std::string>::iterator it7 = m_label->getMultiLayerMap()->begin();
    while (it7 != m_label->getMultiLayerMap()->end())
    {
        myfile << "\t" << it7->second << " = MultiLayer()" << std::endl;
        size_t numberOfLayers = it7->first->getNumberOfLayers();
        myfile << "\t" << it7->second << ".addLayer(" <<
        m_label->getLabel(it7->first->getLayer(0)) << ")" << std::endl;
        size_t layerIndex = 1;
        while (layerIndex != numberOfLayers)
        {
            const LayerInterface *layerInterface = it7->first->getLayerInterface(layerIndex-1);
            if (m_label->getLayerRoughnessMap()->find(layerInterface->getRoughness())
                == m_label->getLayerRoughnessMap()->end())
            {
                myfile << "\t" << it7->second << ".addLayer(" <<
                m_label->getLabel(it7->first->getLayer(layerIndex)) << ")" << std::endl;
            }
            else
            {
                myfile << "\t" << it7->second << ".addLayerWithTopRoughness(" <<
                m_label->getLabel(it7->first->getLayer(layerIndex)) << "," <<
                m_label->getLabel(layerInterface->getRoughness()) << ")" << std::endl;
            }
            layerIndex++;
        }
        myfile <<"\treturn " << it7->second <<  std::endl << std::endl;
        it7++;
    }

    myfile << "def GetSample():\n";
    myfile << "\t# Creating and returning GISAXS simulation\n";
    myfile << "\t# Defining Beam and Detector Parameters\n";
    myfile << "\tsimulation = Simulation()\n";
    myfile << "\tsimulation.setDetectorParameters(" ;
    const Simulation *simulation = makeSimulation();
    size_t numberOfDetectorDimensions = simulation->getInstrument().getDetectorDimension();
    size_t index = 0;
    while (index != numberOfDetectorDimensions)
    {
        if (index != 0) {myfile << ",";}
        myfile << simulation->getInstrument().getDetectorAxis(index).getSize() << "," <<
        simulation->getInstrument().getDetectorAxis(index).getMin() << "," <<
        simulation->getInstrument().getDetectorAxis(index).getMax();
        index++;
    }
    myfile << ") \n";
    myfile << "\tsimulation.setBeamParameters(" ;
    myfile << simulation->getInstrument().getBeam().getWavelength() << "*nanometer,"
    << simulation->getInstrument().getBeam().getAlpha() << "," <<
    simulation->getInstrument().getBeam().getPhi() << ")\n";
    myfile.close();

}

Simulation *PyGenVisitor::makeSimulation()
{
    m_simulation = new Simulation();
    m_simulation->setDetectorParameters(400,-1.0*Units::degree, 1.0*Units::degree, 400,0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation->setBeamParameters(2.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return m_simulation;

}

std::string PyGenVisitor::PrintDouble(double input)
{
    std::ostringstream inter;
    if((input-floor(input)) == 0.0)
    {
        inter << input << ".";
    }
    else
    {
        inter << input;
    }
    return inter.str();
}

void PyGenVisitor::visit(const FormFactorAnisoPyramid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorBox *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCone *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCone6 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCuboctahedron *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCylinder *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorEllipsoidalCylinder *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorFullSphere *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorFullSpheroid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorGauss *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorHemiEllipsoid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorInfLongBox *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorInfLongRipple1 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorInfLongRipple2 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorLorentz *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorPrism3 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorPrism6 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorPyramid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorRipple1 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorRipple2 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorTetrahedron *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorTruncatedSphere *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorTruncatedSpheroid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunctionNone *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction1DLattice *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction1DParaCrystal *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction2DLattice *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const Layer *sample)
{
    m_label->insertMaterial(sample->getMaterial());
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const LayerInterface *)
{
/*    myfile << sample->getLayerTop()->getMaterial()->getName() << std::endl;
    myfile << sample->getLayerBottom()->getMaterial()->getName() << std::endl;
*/
}

void PyGenVisitor::visit(const LayerRoughness *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const MultiLayer *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const Particle *sample)
{
    m_label->insertMaterial(sample->getMaterial());
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const ParticleLayout *sample)
{
    m_label->setLabel(sample);
//     myfile << sample->getName() << std::endl;
}

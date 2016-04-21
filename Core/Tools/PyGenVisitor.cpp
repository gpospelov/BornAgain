// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/PyGenVisitor.cpp
//! @brief     Implements standard mix-in PyGenVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <utility>
#include "Exceptions.h"
#include "FormFactors.h"
#include "InterferenceFunctions.h"
#include "IMaterial.h"
#include "ICompositeSample.h"
#include "Layer.h"
#include "SampleLabelHandler.h"
#include "LayerInterface.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "PyGenVisitor.h"
#include "PyGenTools.h"
#include "ParameterDistribution.h"
#include "Rotations.h"
#include "DetectorMask.h"
#include "ConvolutionDetectorResolution.h"
#include "ResolutionFunction2DGaussian.h"
#include "RectangularDetector.h"
#include "SphericalDetector.h"
#include "SimulationOptions.h"

PyGenVisitor::PyGenVisitor() : m_label(new SampleLabelHandler())
{
}

PyGenVisitor::~PyGenVisitor()
{
    delete m_label;
}

std::string PyGenVisitor::writePyScript(const GISASSimulation *simulation)
{
    std::ostringstream result;
    result << definePreamble();

    result << defineGetSample();
    result << defineGetSimulation(simulation);
    result << definePlotting(simulation);
    result << defineRunSimulation();

    result << "if __name__ == '__main__': \n";
    result << indent() << "runSimulation('output')";
    return result.str();
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

void PyGenVisitor::visit(const FormFactorDodecahedron *sample)
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

void PyGenVisitor::visit(const FormFactorIcosahedron *sample)
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

void PyGenVisitor::visit(const FormFactorTruncatedCube *sample)
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

void PyGenVisitor::visit(const InterferenceFunctionRadialParaCrystal *sample)
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

void PyGenVisitor::visit(const LayerRoughness *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const MultiLayer *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const ParticleComposition *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const MesoCrystal *sample)
{
    (void)sample;
    throw Exceptions::NotImplementedException("PyGenVisitor::visit(const MesoCrystal *sample): "
                                              "not implemented!");
}

void PyGenVisitor::visit(const Particle *sample)
{
    m_label->insertMaterial(sample->getMaterial());
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const ParticleDistribution *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const ParticleCoreShell *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const ParticleLayout *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const RotationX *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const RotationY *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const RotationZ *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const RotationEuler *sample)
{
    m_label->setLabel(sample);
}

std::string PyGenVisitor::definePreamble() const
{
    std::ostringstream result;
    result << "import numpy\n";
    result << "#NOTE: Uncomment the next import statements for plotting\n";
    result << "#import matplotlib\n";
    result << "#from matplotlib import pyplot as plt\n";
    result << "from bornagain import *\n\n\n";
    //    result << "#NOTE: All the ANGLES are displayed in RADIANS\n\n";
    //    result << "#NOTE: Running this Script by default will write output data"
    //           << "to \"output.int\" file\n";
    //    result << "#NOTE: To avoid writing data to a file, delete the argument('output')"
    //           << "given to runSimulation in __main__\n";
    //    result << "#NOTE: To read data from a file use the command:"
    //           << "IntensityDataIOFactory.readIntensityData(fileName))\n\n";
    return result.str();
}

std::string PyGenVisitor::defineGetSample() const
{
    std::ostringstream result;
    result << "def getSample():\n";
    result << defineMaterials();
    result << defineLayers();
    result << defineFormFactors();
    result << defineParticles();
    result << defineCoreShellParticles();
    result << defineParticleCompositions();
    result << defineParticleDistributions();
    result << defineInterferenceFunctions();
    result << defineParticleLayouts();
    result << defineRoughnesses();
    result << addLayoutsToLayers();
    result << defineMultiLayers();
    result << std::endl;
    result << std::endl;
    return result.str();
}

std::string PyGenVisitor::defineGetSimulation(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    result << "def getSimulation():\n";
    //    result << indent() << "# Creating and returning GISAXS simulation\n";
    result << indent() << "simulation = GISASSimulation()\n";
    result << defineDetector(simulation);
    result << defineDetectorResolutionFunction(simulation);
    result << defineBeam(simulation);
    result << defineParameterDistributions(simulation);
    result << defineMasks(simulation);
    result << defineSimulationOptions(simulation);
    result << indent() << "return simulation\n\n\n";
    return result.str();
}

std::string PyGenVisitor::defineMaterials() const
{
    if (m_label->getMaterialMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << indent() << "# Defining Materials\n";
    SampleLabelHandler::materials_t::iterator it = m_label->getMaterialMap()->begin();
    std::set<std::string> visitedMaterials;
    while (it != m_label->getMaterialMap()->end()) {
        if (visitedMaterials.find(it->second) == visitedMaterials.end()) {
            visitedMaterials.insert(it->second);
            const IMaterial *p_material = it->first;
            complex_t ri = p_material->getRefractiveIndex();
            double delta = 1.0 - std::real(ri);
            double beta = std::imag(ri);
            if (p_material->isScalarMaterial()) {
                result << indent() << m_label->getLabel(p_material) << " = HomogeneousMaterial(\""
                       << p_material->getName();
                result << "\", " << PyGenTools::printDouble(delta) << ", "
                       << PyGenTools::printDouble(beta) << ")\n";
            } else {
                const HomogeneousMagneticMaterial *p_mag_material
                    = dynamic_cast<const HomogeneousMagneticMaterial *>(p_material);
                if (p_mag_material == 0) {
                    throw Exceptions::RuntimeErrorException("PyGenVisitor::defineMaterials: "
                                                            "Non scalar material should be of type "
                                                            "HomogeneousMagneticMaterial");
                }
                kvector_t magnetic_field = p_mag_material->getMagneticField();
                result << indent() << "magnetic_field = kvector_t(" << magnetic_field.x() << ", "
                       << magnetic_field.y() << ", " << magnetic_field.z() << ", "
                       << ")\n";
                result << indent() << m_label->getLabel(p_material)
                       << " = HomogeneousMagneticMaterial(\"" << p_material->getName();
                result << "\", " << PyGenTools::printDouble(delta) << ", "
                       << PyGenTools::printDouble(beta) << ", "
                       << "magnetic_field)\n";
            }
        }
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineLayers() const
{
    if (m_label->getLayerMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Layers\n";
    SampleLabelHandler::layers_t::iterator it = m_label->getLayerMap()->begin();
    while (it != m_label->getLayerMap()->end()) {
        const Layer *layer = it->first;
        result << indent() << it->second << " = Layer(" << m_label->getLabel(layer->getMaterial());
        if (layer->getThickness() != 0) {
            result << ", " << layer->getThickness();
        }
        result << ")\n";
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineFormFactors() const
{
    if (m_label->getFormFactorMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Form Factors\n";
    SampleLabelHandler::formfactors_t::iterator it = m_label->getFormFactorMap()->begin();
    while (it != m_label->getFormFactorMap()->end()) {
        result << indent() << it->second;
        const IFormFactor *p_ff = it->first;

        if (const FormFactorAnisoPyramid *anisoPyramid
            = dynamic_cast<const FormFactorAnisoPyramid *>(p_ff)) {
            result << " = FormFactorAnisoPyramid("
                   << PyGenTools::printNm(anisoPyramid->getLength()) << ", "
                   << PyGenTools::printNm(anisoPyramid->getWidth()) << ", "
                   << PyGenTools::printNm(anisoPyramid->getHeight()) << ", "
                   << PyGenTools::printDegrees(anisoPyramid->getAlpha()) << ")\n";
        }

        else if (const FormFactorBox *box = dynamic_cast<const FormFactorBox *>(p_ff)) {
            result << " = FormFactorBox("
                   << PyGenTools::printNm(box->getLength()) << ", "
                   << PyGenTools::printNm(box->getWidth()) << ", "
                   << PyGenTools::printNm(box->getHeight()) << ")\n";
        }

        else if (const FormFactorCone *cone = dynamic_cast<const FormFactorCone *>(p_ff)) {
            result << " = FormFactorCone("
                   << PyGenTools::printNm(cone->getRadius()) << ", "
                   << PyGenTools::printNm(cone->getHeight()) << ", "
                   << PyGenTools::printDegrees(cone->getAlpha()) << ")\n";
        }

        else if (const FormFactorCone6 *cone6 = dynamic_cast<const FormFactorCone6 *>(p_ff)) {
            result << " = FormFactorCone6("
                   << PyGenTools::printNm(cone6->getRadius()) << ", "
                   << PyGenTools::printNm(cone6->getHeight()) << ", "
                   << PyGenTools::printDegrees(cone6->getAlpha()) << ")\n";
        }

        else if (const FormFactorCuboctahedron *cuboctahedron
                 = dynamic_cast<const FormFactorCuboctahedron *>(p_ff)) {
            result << " = FormFactorCuboctahedron("
                   << PyGenTools::printNm(cuboctahedron->getLength()) << ", "
                   << PyGenTools::printNm(cuboctahedron->getHeight()) << ", "
                   << PyGenTools::printNm(cuboctahedron->getHeightRatio()) << ", "
                   << PyGenTools::printDegrees(cuboctahedron->getAlpha()) << ")\n";
        }

        else if (const FormFactorCylinder *cylinder
                 = dynamic_cast<const FormFactorCylinder *>(p_ff)) {
            result << " = FormFactorCylinder("
                   << PyGenTools::printNm(cylinder->getRadius()) << ", "
                   << PyGenTools::printNm(cylinder->getHeight()) << ")\n";
        }

        else if (const FormFactorDodecahedron *dodecahedron
                 = dynamic_cast<const FormFactorDodecahedron *>(p_ff)) {
            result << " = FormFactorDodecahedron("
                   << PyGenTools::printNm(dodecahedron->getEdge()) << ")\n";
        }

        else if (const FormFactorEllipsoidalCylinder *ellipsoidalCylinder
                 = dynamic_cast<const FormFactorEllipsoidalCylinder *>(p_ff)) {
            result << " = FormFactorEllipsoidalCylinder("
                   << PyGenTools::printNm(ellipsoidalCylinder->getRadiusX()) << ", "
                   << PyGenTools::printNm(ellipsoidalCylinder->getRadiusY()) << ", "
                   << PyGenTools::printNm(ellipsoidalCylinder->getHeight()) << ")\n";
        }

        else if (const FormFactorFullSphere *fullSphere
                 = dynamic_cast<const FormFactorFullSphere *>(p_ff)) {
            result << " = FormFactorFullSphere("
                   << PyGenTools::printNm(fullSphere->getRadius()) << ")\n";
        }

        else if (const FormFactorFullSpheroid *fullSpheroid
                 = dynamic_cast<const FormFactorFullSpheroid *>(p_ff)) {
            result << " = FormFactorFullSpheroid("
                   << PyGenTools::printNm(fullSpheroid->getRadius()) << ", "
                   << PyGenTools::printNm(fullSpheroid->getHeight()) << ")\n";
        }

        else if (const FormFactorGauss *gauss = dynamic_cast<const FormFactorGauss *>(p_ff)) {
            if (gauss->getRadius() == gauss->getHeight()) {
                result << " = FormFactorGauss("
                       << PyGenTools::printDouble(gauss->getVolume()) << "*(nanometer)**3)\n";
            } else {
                result << " = FormFactorGauss("
                       << PyGenTools::printNm(gauss->getRadius()) << ", "
                       << PyGenTools::printNm(gauss->getHeight()) << ")\n";
            }
        }

        else if (const FormFactorHemiEllipsoid *hemiEllipsoid
                 = dynamic_cast<const FormFactorHemiEllipsoid *>(p_ff)) {
            result << " = FormFactorHemiEllipsoid("
                   << PyGenTools::printNm(hemiEllipsoid->getRadiusX()) << ", "
                   << PyGenTools::printNm(hemiEllipsoid->getRadiusY()) << ", "
                   << PyGenTools::printNm(hemiEllipsoid->getHeight()) << ")\n";
        }

        else if (const FormFactorIcosahedron *icosahedron
                 = dynamic_cast<const FormFactorIcosahedron *>(p_ff)) {
            result << " = FormFactorIcosahedron("
                   << PyGenTools::printNm(icosahedron->getEdge()) << ")\n";
        }

        else if (const FormFactorLorentz *lorentz = dynamic_cast<const FormFactorLorentz *>(p_ff)) {
            if (lorentz->getRadius() == lorentz->getHeight()) {
                result << " = FormFactorLorentz("
                       << PyGenTools::printDouble(lorentz->getVolume()) << "*(nanometer)**3)\n";

            } else {
                result << " = FormFactorLorentz("
                       << PyGenTools::printNm(lorentz->getRadius()) << ", "
                       << PyGenTools::printNm(lorentz->getHeight()) << ")\n";
            }
        }

        else if (const FormFactorPrism3 *prism3 = dynamic_cast<const FormFactorPrism3 *>(p_ff)) {
            result << " = FormFactorPrism3("
                   << PyGenTools::printNm(prism3->getBaseEdge()) << ", "
                   << PyGenTools::printNm(prism3->getHeight()) << ")\n";
        }

        else if (const FormFactorPrism6 *prism6 = dynamic_cast<const FormFactorPrism6 *>(p_ff)) {
            result << " = FormFactorPrism6("
                   << PyGenTools::printNm(prism6->getBaseEdge()) << ", "
                   << PyGenTools::printNm(prism6->getHeight()) << ")\n";
        }

        else if (const FormFactorPyramid *pyramid = dynamic_cast<const FormFactorPyramid *>(p_ff)) {
            result << " = FormFactorPyramid("
                   << PyGenTools::printNm(pyramid->getBaseEdge()) << ", "
                   << PyGenTools::printNm(pyramid->getHeight()) << ", "
                   << PyGenTools::printDegrees(pyramid->getAlpha()) << ")\n";
        }

        else if (const FormFactorRipple1 *ripple1 = dynamic_cast<const FormFactorRipple1 *>(p_ff)) {
            result << " = FormFactorRipple1("
                   << PyGenTools::printNm(ripple1->getLength()) << ", "
                   << PyGenTools::printNm(ripple1->getWidth()) << ", "
                   << PyGenTools::printNm(ripple1->getHeight()) << ")\n";
        }

        else if (const FormFactorRipple2 *ripple2 = dynamic_cast<const FormFactorRipple2 *>(p_ff)) {
            result << " = FormFactorRipple2("
                   << PyGenTools::printNm(ripple2->getLength()) << ", "
                   << PyGenTools::printNm(ripple2->getWidth()) << ", "
                   << PyGenTools::printNm(ripple2->getHeight()) << ", "
                   << PyGenTools::printNm(ripple2->getAsymmetry()) << ")\n";
        }

        else if (const FormFactorTetrahedron *tetrahedron
                 = dynamic_cast<const FormFactorTetrahedron *>(p_ff)) {
            result << " = FormFactorTetrahedron("
                   << PyGenTools::printNm(tetrahedron->getBaseEdge()) << ", "
                   << PyGenTools::printNm(tetrahedron->getHeight()) << ", "
                   << PyGenTools::printDegrees(tetrahedron->getAlpha()) << ")\n";
        }

        else if (const FormFactorTruncatedCube *truncatedCube
                 = dynamic_cast<const FormFactorTruncatedCube *>(p_ff)) {
            result << " = FormFactorTruncatedCube("
                   << PyGenTools::printNm(truncatedCube->getLength()) << ", "
                   << PyGenTools::printNm(truncatedCube->getRemovedLength()) << ")\n";
        }

        else if (const FormFactorTruncatedSphere *truncatedSphere
                 = dynamic_cast<const FormFactorTruncatedSphere *>(p_ff)) {
            result << " = FormFactorTruncatedSphere("
                   << PyGenTools::printNm(truncatedSphere->getRadius()) << ", "
                   << PyGenTools::printNm(truncatedSphere->getHeight()) << ")\n";
        }

        else if (const FormFactorTruncatedSpheroid *truncatedSpheroid
                 = dynamic_cast<const FormFactorTruncatedSpheroid *>(p_ff)) {
            result << " = FormFactorTruncatedSpheroid("
                   << PyGenTools::printNm(truncatedSpheroid->getRadius()) << ", "
                   << PyGenTools::printNm(truncatedSpheroid->getHeight()) << ", "
                   << PyGenTools::printNm(truncatedSpheroid->getHeightFlattening()) << ")\n";
        }

        else {
            std::ostringstream formFactorException;
            formFactorException << "\n" << p_ff->getName() << " :: Not Casted To Any "
                                << "Form Factor\n";
            throw NotImplementedException(formFactorException.str());
        }
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineParticles() const
{
    if (m_label->getParticleMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Particles\n";
    SampleLabelHandler::particles_t::iterator it = m_label->getParticleMap()->begin();
    while (it != m_label->getParticleMap()->end()) {
        const Particle *p_particle = it->first;
        std::string particle_name = it->second;
        result << indent() << particle_name << " = Particle("
               << m_label->getLabel(p_particle->getMaterial()) << ", "
               << m_label->getLabel(p_particle->getFormFactor());
        result << ")\n";
        setRotationInformation(p_particle, particle_name, result);
        setPositionInformation(p_particle, particle_name, result);
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineCoreShellParticles() const
{
    if (m_label->getParticleCoreShellMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Core Shell Particles\n";
    SampleLabelHandler::particlescoreshell_t::iterator it
        = m_label->getParticleCoreShellMap()->begin();

    while (it != m_label->getParticleCoreShellMap()->end()) {
        const ParticleCoreShell* p_coreshell = it->first;
        result << "\n" << indent() << it->second << " = ParticleCoreShell("
               << m_label->getLabel(p_coreshell->getShellParticle()) << ", "
               << m_label->getLabel(p_coreshell->getCoreParticle()) << ")\n";
        std::string core_shell_name = it->second;
        setRotationInformation(p_coreshell, core_shell_name, result);
        setPositionInformation(p_coreshell, core_shell_name, result);
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineParticleDistributions() const
{
    if (m_label->getParticleDistributionsMap()->size() == 0)
        return "";

    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining particles with parameter following a distribution\n";
    SampleLabelHandler::particledistributions_t::iterator it
        = m_label->getParticleDistributionsMap()->begin();

    int index(1);
    while (it != m_label->getParticleDistributionsMap()->end()) {
        ParameterDistribution par_distr = it->first->getParameterDistribution();

        // building distribution functions
        std::stringstream s_distr;
        s_distr << "distr_" << index;

        result << indent() << s_distr.str() << " = "
               << PyGenTools::getRepresentation(par_distr.getDistribution()) << "\n";

        // building parameter distribution
        std::stringstream s_par_distr;
        s_par_distr << "par_distr_" << index;

        result << indent() << s_par_distr.str() << " = ParameterDistribution("
               << "\"" << par_distr.getMainParameterName() << "\""
               << ", " << s_distr.str() << ", " << par_distr.getNbrSamples() << ", "
               << PyGenTools::printDouble(par_distr.getSigmaFactor()) << ")\n";

        // linked parameters
        std::vector<std::string> linked_pars = par_distr.getLinkedParameterNames();
        if(linked_pars.size()) {
            result << indent() << s_par_distr.str();
            for(size_t i=0; i<linked_pars.size(); ++i) {
                result << ".linkParameter(\"" << linked_pars[i] << "\")";
            }
            result << "\n";
        }

        result << indent() << it->second << " = ParticleDistribution("
               << m_label->getLabel(it->first->getParticle()) << ", " << s_par_distr.str() << ")\n";
        it++;
        index++;
    }
    return result.str();
}

std::string PyGenVisitor::defineParticleCompositions() const
{
    if (m_label->getParticleCompositionMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining composition of particles at specific positions\n";
    SampleLabelHandler::particlecompositions_t::iterator it
        = m_label->getParticleCompositionMap()->begin();

    while (it != m_label->getParticleCompositionMap()->end()) {
        const ParticleComposition *p_particle_composition = it->first;
        std::string particle_composition_name = it->second;
        result << indent() << particle_composition_name << " = ParticleComposition()\n";
        for (size_t i = 0; i < p_particle_composition->getNbrParticles(); ++i) {
            result << indent() << particle_composition_name << ".addParticle("
                   << m_label->getLabel(p_particle_composition->getParticle(i))
            << ")\n";
        }
        setRotationInformation(p_particle_composition, particle_composition_name, result);
        setPositionInformation(p_particle_composition, particle_composition_name, result);
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineInterferenceFunctions() const
{
    if (m_label->getInterferenceFunctionMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Interference Functions\n";
    SampleLabelHandler::interferences_t::iterator it
        = m_label->getInterferenceFunctionMap()->begin();
    while (it != m_label->getInterferenceFunctionMap()->end()) {
        const IInterferenceFunction *interference = it->first;

        if (const InterferenceFunctionNone *none
            = dynamic_cast<const InterferenceFunctionNone *>(interference)) {
            (void)none;
            result << indent() << it->second << " = InterferenceFunctionNone()\n";
        }

        else if (const InterferenceFunction1DLattice *oneDLattice
                 = dynamic_cast<const InterferenceFunction1DLattice *>(interference)) {
            const Lattice1DParameters latticeParameters = oneDLattice->getLatticeParameters();
            result << indent() << it->second << " = InterferenceFunction1DLattice("
                   << PyGenTools::printNm(latticeParameters.m_length) << ", "
                   << PyGenTools::printDegrees(latticeParameters.m_xi) << ")\n";

            const IFTDecayFunction1D *pdf = oneDLattice->getDecayFunction();

            if (const FTDecayFunction1DVoigt *fTD1DVoigt
                = dynamic_cast<const FTDecayFunction1DVoigt *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDecayFunction1DVoigt("
                       << PyGenTools::printDouble(fTD1DVoigt->getOmega()) << ", "
                       << PyGenTools::printDouble(fTD1DVoigt->getEta()) << ")\n";
            }

            if (pdf->getOmega() != 0.0) {
                if (const FTDecayFunction1DCauchy *fTD1DCauchy
                    = dynamic_cast<const FTDecayFunction1DCauchy *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDecayFunction1DCauchy("
                           << PyGenTools::printDouble(fTD1DCauchy->getOmega()) << ")\n";
                }

                else if (const FTDecayFunction1DGauss *fTD1DGauss
                         = dynamic_cast<const FTDecayFunction1DGauss *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDecayFunction1DGauss("
                           << PyGenTools::printDouble(fTD1DGauss->getOmega()) << ")\n";
                }

                else if (const FTDecayFunction1DTriangle *fTD1DTriangle
                         = dynamic_cast<const FTDecayFunction1DTriangle *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDecayFunction1DTriangle("
                           << PyGenTools::printDouble(fTD1DTriangle->getOmega()) << ")\n";
                }

                else {
                    std::ostringstream pdfException;
                    pdfException << "\n" << pdf->getName() << " :: Not Casted To Any "
                                 << "Decay Function\n";
                    throw NotImplementedException(pdfException.str());
                }

                result << indent() << it->second << ".setDecayFunction(" << it->second
                       << "_pdf)\n";
            }
        }

        else if (const InterferenceFunctionRadialParaCrystal *oneDParaCrystal
                 = dynamic_cast<const InterferenceFunctionRadialParaCrystal *>(interference)) {
            result << indent() << it->second << " = InterferenceFunctionRadialParaCrystal("
                   << PyGenTools::printNm(oneDParaCrystal->getPeakDistance()) << ", "
                   << PyGenTools::printNm(oneDParaCrystal->getDampingLength()) << ")\n";

            if (oneDParaCrystal->getKappa() != 0.0) {
                result << indent() << it->second << ".setKappa("
                       << PyGenTools::printDouble(oneDParaCrystal->getKappa()) << ")\n";
            }

            if (oneDParaCrystal->getDomainSize() != 0.0) {
                result << indent() << it->second << ".setDomainSize("
                       << PyGenTools::printDouble(oneDParaCrystal->getDomainSize()) << ")\n";
            }

            const IFTDistribution1D *pdf = oneDParaCrystal->getProbabilityDistribution();

            if (const FTDistribution1DVoigt *fTD1DVoigt
                = dynamic_cast<const FTDistribution1DVoigt *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDistribution1DVoigt("
                       << PyGenTools::printDouble(fTD1DVoigt->getOmega()) << ", "
                       << PyGenTools::printDouble(fTD1DVoigt->getEta()) << ")\n";
            }

            if (pdf->getOmega() != 0.0) {
                if (const FTDistribution1DCauchy *fTD1DCauchy
                    = dynamic_cast<const FTDistribution1DCauchy *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDistribution1DCauchy("
                           << PyGenTools::printDouble(fTD1DCauchy->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DCosine *fTD1DCosine
                         = dynamic_cast<const FTDistribution1DCosine *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDistribution1DCosine("
                           << PyGenTools::printDouble(fTD1DCosine->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DGate *fTD1DGate
                         = dynamic_cast<const FTDistribution1DGate *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDistribution1DGate("
                           << PyGenTools::printDouble(fTD1DGate->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DGauss *fTD1DGauss
                         = dynamic_cast<const FTDistribution1DGauss *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDistribution1DGauss("
                           << PyGenTools::printDouble(fTD1DGauss->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DTriangle *fTD1DTriangle
                         = dynamic_cast<const FTDistribution1DTriangle *>(pdf)) {
                    result << indent() << it->second << "_pdf  = FTDistribution1DTriangle("
                           << PyGenTools::printDouble(fTD1DTriangle->getOmega()) << ")\n";
                }

                else {
                    std::ostringstream pdfException;
                    pdfException << "\n" << pdf->getName() << " :: Not Casted To Any "
                                 << "Probability Distribution Function\n";
                    throw NotImplementedException(pdfException.str());
                }

                result << indent() << it->second << ".setProbabilityDistribution(" << it->second
                       << "_pdf)\n";
            }
        }

        else if (const InterferenceFunction2DLattice *twoDLattice
                 = dynamic_cast<const InterferenceFunction2DLattice *>(interference)) {
            const Lattice2DParameters latticeParameters = twoDLattice->getLatticeParameters();
            result << indent() << it->second << " = InterferenceFunction2DLattice("
                   << PyGenTools::printNm(latticeParameters.m_length_1) << ", "
                   << PyGenTools::printNm(latticeParameters.m_length_2) << ", "
                   << PyGenTools::printDegrees(latticeParameters.m_angle) << ", "
                   << PyGenTools::printDegrees(latticeParameters.m_xi) << ")\n";

            const IFTDecayFunction2D *pdf = twoDLattice->getDecayFunction();

            if (const FTDecayFunction2DCauchy *fTD2DCauchy
                = dynamic_cast<const FTDecayFunction2DCauchy *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDecayFunction2DCauchy("
                       << PyGenTools::printNm(fTD2DCauchy->getDecayLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DCauchy->getDecayLengthY()) << ")\n";
                if (fTD2DCauchy->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf"
                           << ".setGamma(" << PyGenTools::printDegrees(fTD2DCauchy->getGamma())
                           << ")\n";
                }
            }

            else if (const FTDecayFunction2DGauss *fTD2DGauss
                     = dynamic_cast<const FTDecayFunction2DGauss *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDecayFunction2DGauss("
                       << PyGenTools::printNm(fTD2DGauss->getDecayLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DGauss->getDecayLengthY()) << ")\n";

                if (fTD2DGauss->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf"
                           << ".setGamma(" << PyGenTools::printDegrees(fTD2DGauss->getGamma())
                           << ")\n";
                }
            }

            else if (const FTDecayFunction2DVoigt *fTD2DVoigt
                     = dynamic_cast<const FTDecayFunction2DVoigt *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDecayFunction2DVoigt("
                       << PyGenTools::printNm(fTD2DVoigt->getDecayLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DVoigt->getDecayLengthY()) << ", "
                       << PyGenTools::printDouble(fTD2DVoigt->getEta()) << ")\n";

                if (fTD2DVoigt->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf"
                           << ".setGamma(" << PyGenTools::printDegrees(fTD2DVoigt->getGamma())
                           << ")\n";
                }
            }

            else {
                std::ostringstream pdfException;
                pdfException << "\n" << pdf->getName() << " :: Not Casted To Any "
                             << "Probability Distribution Function\n";
                throw NotImplementedException(pdfException.str());
            }

            result << indent() << it->second << ".setDecayFunction(" << it->second
                   << "_pdf)\n";

        }

        else if (const InterferenceFunction2DParaCrystal *twoDParaCrystal
                 = dynamic_cast<const InterferenceFunction2DParaCrystal *>(interference)) {
            std::vector<double> domainSize = twoDParaCrystal->getDomainSizes();
            if (PyGenTools::isSquare(twoDParaCrystal->getLatticeParameters().m_length_1,
                                     twoDParaCrystal->getLatticeParameters().m_length_2,
                                     twoDParaCrystal->getLatticeParameters().m_angle)) {
                result << indent() << it->second
                       << " = InterferenceFunction2DParaCrystal.createSquare("
                       << PyGenTools::printNm(twoDParaCrystal->getLatticeParameters().m_length_1) << ", "
                       << PyGenTools::printNm(twoDParaCrystal->getDampingLength()) << ", "
                       << PyGenTools::printNm(domainSize[0]) << ", "
                       << PyGenTools::printNm(domainSize[1]) << ")\n";
            }

            else if (PyGenTools::isHexagonal(twoDParaCrystal->getLatticeParameters().m_length_1,
                                             twoDParaCrystal->getLatticeParameters().m_length_2,
                                             twoDParaCrystal->getLatticeParameters().m_angle)) {
                result << indent() << it->second
                       << " = InterferenceFunction2DParaCrystal.createHexagonal("
                       << PyGenTools::printNm(twoDParaCrystal->getLatticeParameters().m_length_1) << ", "
                       << PyGenTools::printNm(twoDParaCrystal->getDampingLength()) << ", "
                       << PyGenTools::printNm(domainSize[0]) << ", "
                       << PyGenTools::printNm(domainSize[1]) << ")\n";
            }

            else {
                result << indent() << it->second << " = InterferenceFunction2DParaCrystal("
                       << PyGenTools::printNm(twoDParaCrystal->getLatticeParameters().m_length_1) << ", "
                       << PyGenTools::printNm(twoDParaCrystal->getLatticeParameters().m_length_2) << ", "
                       << PyGenTools::printDegrees(twoDParaCrystal->getLatticeParameters().m_angle) << ", "
                       << PyGenTools::printDegrees(twoDParaCrystal->getLatticeParameters().m_xi) << ", "
                       << PyGenTools::printNm(twoDParaCrystal->getDampingLength()) << ")\n";

                if (domainSize[0] != 0 || domainSize[1] != 0) {
                    result << indent() << it->second << ".setDomainSizes("
                           << PyGenTools::printNm(domainSize[0]) << ", "
                           << PyGenTools::printNm(domainSize[1]) << ")\n";
                }

                if (twoDParaCrystal->getIntegrationOverXi() == true) {
                    result << indent() << it->second << ".setIntegrationOverXi(True)\n";
                }
            }

            std::vector<const IFTDistribution2D *> pdf_vector
                = twoDParaCrystal->getProbabilityDistributions();
            const IFTDistribution2D *pdf_1 = pdf_vector[0];

            if (const FTDistribution2DCauchy *fTD2DCauchy
                = dynamic_cast<const FTDistribution2DCauchy *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DCauchy("
                       << PyGenTools::printNm(fTD2DCauchy->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DCauchy->getCoherenceLengthY()) << ")\n";

                if (fTD2DCauchy->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DCauchy->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DCone *fTD2DCone
                     = dynamic_cast<const FTDistribution2DCone *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DCone("
                       << PyGenTools::printNm(fTD2DCone->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DCone->getCoherenceLengthY()) << ")\n";

                if (fTD2DCone->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DCone->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGate *fTD2DGate
                     = dynamic_cast<const FTDistribution2DGate *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DGate("
                       << PyGenTools::printNm(fTD2DGate->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DGate->getCoherenceLengthY()) << ")\n";

                if (fTD2DGate->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DGate->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGauss *fTD2DGauss
                     = dynamic_cast<const FTDistribution2DGauss *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DGauss("
                       << PyGenTools::printNm(fTD2DGauss->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DGauss->getCoherenceLengthY()) << ")\n";

                if (fTD2DGauss->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DGauss->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DVoigt *fTD2DVoigt
                     = dynamic_cast<const FTDistribution2DVoigt *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DVoigt("
                       << PyGenTools::printNm(fTD2DVoigt->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DVoigt->getCoherenceLengthY()) << ", "
                       << PyGenTools::printDouble(fTD2DVoigt->getEta()) << ")\n";

                if (fTD2DVoigt->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DVoigt->getGamma()) << ")\n";
                }
            }

            else {
                std::ostringstream pdfException;
                pdfException << "\n" << pdf_1->getName() << " :: Not Casted To Any "
                             << "Probability Distribution Function\n";
                throw NotImplementedException(pdfException.str());
            }

            const IFTDistribution2D *pdf_2 = pdf_vector[1];

            if (const FTDistribution2DCauchy *fTD2DCauchy
                = dynamic_cast<const FTDistribution2DCauchy *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2   = FTDistribution2DCauchy("
                       << PyGenTools::printNm(fTD2DCauchy->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DCauchy->getCoherenceLengthY()) << ")\n";

                if (fTD2DCauchy->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DCauchy->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DCone *fTD2DCone
                     = dynamic_cast<const FTDistribution2DCone *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2   = FTDistribution2DCone("
                       << PyGenTools::printNm(fTD2DCone->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DCone->getCoherenceLengthY()) << ")\n";

                if (fTD2DCone->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DCone->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGate *fTD2DGate
                     = dynamic_cast<const FTDistribution2DGate *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2   = FTDistribution2DGate("
                       << PyGenTools::printNm(fTD2DGate->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DGate->getCoherenceLengthY()) << ")\n";

                if (fTD2DGate->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DGate->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGauss *fTD2DGauss
                     = dynamic_cast<const FTDistribution2DGauss *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2 = FTDistribution2DGauss("
                       << PyGenTools::printNm(fTD2DGauss->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DGauss->getCoherenceLengthY()) << ")\n";

                if (fTD2DGauss->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DGauss->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DVoigt *fTD2DVoigt
                     = dynamic_cast<const FTDistribution2DVoigt *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2 = FTDistribution2DVoigt("
                       << PyGenTools::printNm(fTD2DVoigt->getCoherenceLengthX()) << ", "
                       << PyGenTools::printNm(fTD2DVoigt->getCoherenceLengthY()) << ", "
                       << PyGenTools::printDouble(fTD2DVoigt->getEta()) << ")\n";

                if (fTD2DVoigt->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DVoigt->getGamma()) << ")\n";
                }
            }

            else {
                std::ostringstream pdfException;
                pdfException << "\n" << pdf_2->getName() << " :: Not Casted To Any "
                             << "Probability Distribution Function\n";
                throw NotImplementedException(pdfException.str());
            }

            result << indent() << it->second << ".setProbabilityDistributions(" << it->second
                   << "_pdf_1, " << it->second << "_pdf_2)\n";
        }

        else {
            std::ostringstream interferenceException;
            interferenceException << "\n" << interference->getName() << " :: Not Casted To Any "
                                  << "Interference Function\n";
            throw NotImplementedException(interferenceException.str());
        }

        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineParticleLayouts() const
{
    if (m_label->getParticleLayoutMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Particle Layouts and adding Particles\n";
    SampleLabelHandler::layouts_t::iterator it = m_label->getParticleLayoutMap()->begin();
    while (it != m_label->getParticleLayoutMap()->end()) {
        const ILayout *iLayout = it->first;
        if (const ParticleLayout *particleLayout = dynamic_cast<const ParticleLayout *>(iLayout)) {
            result << indent() << it->second << " = ParticleLayout()\n";
            size_t numberOfParticles = particleLayout->getNumberOfParticles();
            size_t particleIndex = 0;

            while (particleIndex != numberOfParticles) {
                const IAbstractParticle *p_particle = particleLayout->getParticle(particleIndex);
                double abundance = particleLayout->getAbundanceOfParticle(particleIndex);
                result << indent() << it->second << ".addParticle("
                       << m_label->getLabel(p_particle) << ", "
                       << PyGenTools::printDouble(abundance) << ")\n";
                particleIndex++;
            }

            const IInterferenceFunction* p_iff = particleLayout->getInterferenceFunction();
            if (p_iff) {
                result << indent() << it->second << ".addInterferenceFunction("
                       << m_label->getLabel(p_iff) << ")\n";
            }

            switch (particleLayout->getApproximation()) {
            case ILayout::DA:
                break;
            case ILayout::SSCA:
                result << indent() << it->second << ".setApproximation(ILayout.";
                result << "SSCA)\n";
                break;
            }
            result << indent() << it->second << ".setTotalParticleSurfaceDensity("
                   << it->first->getTotalParticleSurfaceDensity() << ")\n";
        }
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineRoughnesses() const
{
    if (m_label->getLayerRoughnessMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Roughness Parameters\n";
    SampleLabelHandler::roughnesses_t::iterator it = m_label->getLayerRoughnessMap()->begin();
    while (it != m_label->getLayerRoughnessMap()->end()) {
        result << indent() << it->second << " = LayerRoughness("
               << PyGenTools::printNm(it->first->getSigma()) << ", "
               << it->first->getHurstParameter() << ", "
               << PyGenTools::printNm(it->first->getLatteralCorrLength()) << ")\n";
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::addLayoutsToLayers() const
{
    if (m_label->getParticleLayoutMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Adding layouts to layers";
    SampleLabelHandler::layers_t::iterator it = m_label->getLayerMap()->begin();
    while (it != m_label->getLayerMap()->end()) {
        const Layer *layer = it->first;
        size_t numberOfLayouts = layer->getNumberOfLayouts();
        size_t i = 0;
        while (i < numberOfLayouts) {
            result << "\n" << indent() << it->second << ".addLayout("
                   << m_label->getLabel(layer->getLayout(i)) << ")\n";
            i++;
        }
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineMultiLayers() const
{
    if (m_label->getMultiLayerMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Multilayers\n";
    SampleLabelHandler::multilayers_t::iterator it = m_label->getMultiLayerMap()->begin();
    while (it != m_label->getMultiLayerMap()->end()) {
        result << indent() << it->second << " = MultiLayer()\n";

        size_t numberOfLayers = it->first->getNumberOfLayers();

        if (numberOfLayers) {
            result << indent() << it->second << ".addLayer("
                   << m_label->getLabel(it->first->getLayer(0)) << ")\n";

            size_t layerIndex = 1;
            while (layerIndex != numberOfLayers) {
                const LayerInterface *layerInterface = it->first->getLayerInterface(layerIndex - 1);
                if (m_label->getLayerRoughnessMap()->find(layerInterface->getRoughness())
                    == m_label->getLayerRoughnessMap()->end()) {
                    result << indent() << it->second << ".addLayer("
                           << m_label->getLabel(it->first->getLayer(layerIndex)) << ")\n";
                }

                else {
                    result << indent() << it->second << ".addLayerWithTopRoughness("
                           << m_label->getLabel(it->first->getLayer(layerIndex)) << ", "
                           << m_label->getLabel(layerInterface->getRoughness()) << ")\n";
                }
                layerIndex++;
            }
        }
        result << indent() << "return " << it->second << std::endl;
        it++;
    }
    return result.str();
}

std::string PyGenVisitor::defineDetector(const GISASSimulation *simulation) const
{
    const IDetector2D *iDetector = simulation->getInstrument().getDetector();

    if (iDetector->getDimension() != 2) {
        throw Exceptions::RuntimeErrorException("PyGenVisitor::defineDetector: "
                                                "detector must be two-dimensional for GISAS");
    }

    std::ostringstream result;
    result << std::setprecision(12);

    if(auto detector = dynamic_cast<const SphericalDetector *>(iDetector)) {
        result << indent() << "simulation.setDetectorParameters(";
        for(size_t index=0; index<detector->getDimension(); ++index) {
            if (index != 0) result << ", ";
            result << detector->getAxis(index).getSize() << ", "
                   << PyGenTools::printDegrees(
                          detector->getAxis(index).getMin()) << ", "
                   << PyGenTools::printDegrees(
                          detector->getAxis(index).getMax());
        }
        result << ")\n";

    } else if(auto detector = dynamic_cast<const RectangularDetector *>(iDetector)) {
        result << indent() << "\n";
        result << indent() << "detector = RectangularDetector("
               << detector->getNbinsX() << ", "
               << PyGenTools::printDouble(detector->getWidth()) << ", "
               << detector->getNbinsY() << ", "
               << PyGenTools::printDouble(detector->getHeight()) << ")\n";
        if(detector->getDetectorArrangment() == RectangularDetector::GENERIC) {
            result << indent() << "detector.setPosition("
                   << PyGenTools::printKvector(detector->getNormalVector()) << ", "
                   << PyGenTools::printDouble(detector->getU0()) << ", "
                   << PyGenTools::printDouble(detector->getV0());
            if(PyGenTools::isDefaultDirection(detector->getDirectionVector())) {
                result << ")\n";
            } else {
                result << ", " << PyGenTools::printKvector(detector->getDirectionVector()) << ")\n";
            }

        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
            result << indent() << "detector.setPerpendicularToSampleX("
                   << PyGenTools::printDouble(detector->getDistance()) << ", "
                   << PyGenTools::printDouble(detector->getU0()) << ", "
                   << PyGenTools::printDouble(detector->getV0()) << ")\n";

        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
            result << indent() << "detector.setPerpendicularToDirectBeam("
                   << PyGenTools::printDouble(detector->getDistance()) << ", "
                   << PyGenTools::printDouble(detector->getU0()) << ", "
                   << PyGenTools::printDouble(detector->getV0()) << ")\n";

        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << PyGenTools::printDouble(detector->getDistance()) << ", "
                   << PyGenTools::printDouble(detector->getU0()) << ", "
                   << PyGenTools::printDouble(detector->getV0()) << ")\n";


        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << PyGenTools::printDouble(detector->getDistance()) << ")\n";
            result << indent() << "detector.setDirectBeamPosition("
                   << PyGenTools::printDouble(detector->getDirectBeamU0()) << ", "
                   << PyGenTools::printDouble(detector->getDirectBeamV0()) << ")\n";

        } else {
            throw Exceptions::RuntimeErrorException(
                "PyGenVisitor::defineDetector: unknown alignment");
        }

        result << indent() << "simulation.setDetector(detector)\n\n";

    }


    else {
        throw Exceptions::RuntimeErrorException("PyGenVisitor::defineDetector: unknown detector");
    }

    return result.str();
}

std::string PyGenVisitor::defineDetectorResolutionFunction(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    const IDetector2D *detector = simulation->getInstrument().getDetector();

    if (const IDetectorResolution *p_resfunc = detector->getDetectorResolutionFunction()) {
        if (const ConvolutionDetectorResolution *p_convfunc
            = dynamic_cast<const ConvolutionDetectorResolution *>(p_resfunc)) {
            if (const ResolutionFunction2DGaussian *resfunc
                = dynamic_cast<const ResolutionFunction2DGaussian *>(
                    p_convfunc->getResolutionFunction2D())) {

                result << indent() << "simulation.setDetectorResolutionFunction(";
                result << "ResolutionFunction2DGaussian(";
                if(detector->getDefaultAxesUnits() == IDetector2D::RADIANS) {
                    result << PyGenTools::printDegrees(resfunc->getSigmaX()) << ", ";
                    result << PyGenTools::printDegrees(resfunc->getSigmaY()) << "))\n";
                } else {
                    result << PyGenTools::printDouble(resfunc->getSigmaX()) << ", ";
                    result << PyGenTools::printDouble(resfunc->getSigmaY()) << "))\n";
                }

            } else {
                std::string message("PyGenVisitor::defineDetectorResolutionFunction() -> Error.");
                message += "Unknown detector resolution function";
                throw Exceptions::RuntimeErrorException(message);
            }
        } else {
            std::string message("PyGenVisitor::defineDetectorResolutionFunction() -> Error.");
            message += "Not a ConvolutionDetectorResolution function";
            throw Exceptions::RuntimeErrorException(message);
        }
    }

    return result.str();
}

std::string PyGenVisitor::defineBeam(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);
    // result << indent() << "# Defining Beam Parameters\n";
    result << indent() << "simulation.setBeamParameters(";
    result << PyGenTools::printNm(simulation->getInstrument().getBeam().getWavelength()) << ", "
           << PyGenTools::printDegrees(simulation->getInstrument().getBeam().getAlpha()) << ", "
           << PyGenTools::printDegrees(simulation->getInstrument().getBeam().getPhi()) << ")\n";
    double beam_intensity = simulation->getInstrument().getBeamIntensity();
    if(beam_intensity > 0.0) {
        result << indent() << "simulation.setBeamIntensity("
               << PyGenTools::printScientificDouble(beam_intensity) << ")\n";
    }
    return result.str();
}

std::string PyGenVisitor::defineParameterDistributions(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    const std::vector<ParameterDistribution>& distributions =
            simulation->getDistributionHandler().getDistributions();
    if (distributions.size()==0) return "";
    for (size_t i=0; i<distributions.size(); ++i) {
        std::string main_par_name = distributions[i].getMainParameterName();
        size_t nbr_samples = distributions[i].getNbrSamples();
        double sigma_factor = distributions[i].getSigmaFactor();
        const IDistribution1D *p_distr = distributions[i].getDistribution();
        result << indent() << "distribution_" << i+1 << " = "
               << PyGenTools::getRepresentation(p_distr) << "\n";
        result << indent() << "simulation.addParameterDistribution(\"" << main_par_name << "\", "
               << "distribution_" << i+1 << ", " << nbr_samples << ", "
               << PyGenTools::printDouble(sigma_factor) << ")\n";
    }
    return result.str();
}

std::string PyGenVisitor::defineMasks(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);

    const IDetector2D *detector = simulation->getInstrument().getDetector();
    const DetectorMask *detectorMask = detector->getDetectorMask();
    if(detectorMask && detectorMask->getNumberOfMasks()) {
        result << "\n";
        for(size_t i_mask=0; i_mask<detectorMask->getNumberOfMasks(); ++i_mask) {
            bool mask_value(false);
            const Geometry::IShape2D *shape = detectorMask->getMaskShape(i_mask, mask_value);
            result << PyGenTools::getRepresentation(indent(), shape, mask_value);
        }
        result << "\n";
    }

    return result.str();
}

std::string PyGenVisitor::defineSimulationOptions(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);

    const SimulationOptions &options = simulation->getOptions();
    if(options.getHardwareConcurrency() != options.getNumberOfThreads()) {
        result << indent() << "simulation.getOptions().setNumberOfThreads("
               << options.getNumberOfThreads() << ")\n";
    }
    if(options.isIntegrate()) {
        result << indent() << "simulation.getOptions().setMonteCarloIntegration(True, "
               << options.getMcPoints() << ")\n";
    }

    return result.str();
}

std::string PyGenVisitor::definePlotting(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);
    //    result << "#NOTE: Uncomment the next function for plotting\n";
    //    result << "#NOTE: This requires the presence of matplotlib library\n";
    result << "def plotSimulation(simulation):\n";
    result << "" << indent() << "result = simulation.getIntensityData()\n";
    result << "" << indent() << "im = plt.imshow(result.getArray(), "
           << "norm=matplotlib.colors.LogNorm(1, result.getMaximum()), extent=[";
    size_t index = 0;
    size_t numberOfDetectorDimensions = simulation->getInstrument().getDetectorDimension();
    while (index < numberOfDetectorDimensions) {
        if (index != 0) {
            result << ", ";
        }
        result << PyGenTools::printDegrees(
                      simulation->getInstrument().getDetectorAxis(index).getMin()) << ", "
               << PyGenTools::printDegrees(
                      simulation->getInstrument().getDetectorAxis(index).getMax());
        index++;
    }
    result << "]) \n";
    result << indent() << "plt.colorbar(im)\n";
    result << indent() << "plt.show()\n\n\n";
    return result.str();
}

std::string PyGenVisitor::defineRunSimulation() const
{
    std::ostringstream result;
    result << "def runSimulation(filename = ''):\n";
    //    result << "def runSimulation():\n";
    result << indent() << "# Run Simulation\n";
    result << indent() << "sample = getSample()\n";
    result << indent() << "simulation = getSimulation()\n";
    result << indent() << "simulation.setSample(sample)\n";
    result << indent() << "simulation.runSimulation()\n";
    result << indent() << "if filename != '':\n";
    result << indent() << indent() << "IntensityDataIOFactory.writeIntensityData(simulation."
           << "getIntensityData(), filename + '.int')\n\n\n";
    return result.str();
}

std::string PyGenVisitor::indent() const
{
    std::string result("    ");
    return result;
}

void PyGenVisitor::setRotationInformation(const IParticle *p_particle, std::string name,
                                          std::ostringstream &result) const
{
    if (p_particle->getRotation()) {
        double alpha, beta, gamma;
        p_particle->getRotation()->getTransform3D().calculateEulerAngles(&alpha, &beta, &gamma);
        switch (p_particle->getRotation()->getTransform3D().getRotationType()) {
        case Geometry::Transform3D::EULER:
            result << indent() << name << "_rotation = RotationEuler("
                   << PyGenTools::printDegrees(alpha) << ", " << PyGenTools::printDegrees(beta)
                   << ", " << PyGenTools::printDegrees(gamma) << ")\n";
            break;
        case Geometry::Transform3D::XAXIS:
            result << indent() << name << "_rotation = RotationX("
                   << PyGenTools::printDegrees(beta) << ")\n";
            break;
        case Geometry::Transform3D::YAXIS:
            result << indent() << name << "_rotation = RotationY("
                   << PyGenTools::printDegrees(gamma) << ")\n";
            break;
        case Geometry::Transform3D::ZAXIS:
            result << indent() << name << "_rotation = RotationZ("
                   << PyGenTools::printDegrees(alpha) << ")\n";
            break;
        default:
            break;
        }
        result << indent() << name << ".setRotation("
               << name << "_rotation)\n";
    }
}

void PyGenVisitor::setPositionInformation(const IParticle *p_particle, std::string name,
                                          std::ostringstream &result) const
{
    kvector_t pos = p_particle->getPosition();
    bool has_position_info = (pos != kvector_t());

    if (has_position_info) {
        result << indent() << name
               << "_position = kvector_t("
               << PyGenTools::printNm(pos.x()) << ", "
               << PyGenTools::printNm(pos.y()) << ", "
               << PyGenTools::printNm(pos.z()) << ")\n";

        result << indent()
               << name << ".setPosition("
               << name << "_position)\n";
    }
}

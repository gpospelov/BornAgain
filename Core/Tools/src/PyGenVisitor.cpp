// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/PyGenVisitor.cpp
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
#include "ParticleInfo.h"
#include "ParticleLayout.h"
#include "PyGenVisitor.h"
#include "PyGenTools.h"
#include "ParameterDistribution.h"
#include "Rotations.h"

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
    result << "#import pylab\n";
    result << "#import matplotlib\n";
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
    result << defineParticleDistributions();
    result << defineParticleCompositions();
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
    result << defineBeam(simulation);
    result << defineParameterDistributions(simulation);
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
            result << " = FormFactorAnisoPyramid(" << anisoPyramid->getLength() << "*nanometer, "
                   << anisoPyramid->getWidth() << "*nanometer, " << anisoPyramid->getHeight()
                   << "*nanometer, " << PyGenTools::printDegrees(anisoPyramid->getAlpha()) << ")\n";
        }

        else if (const FormFactorBox *box = dynamic_cast<const FormFactorBox *>(p_ff)) {
            result << " = FormFactorBox(" << box->getLength() << "*nanometer, " << box->getWidth()
                   << "*nanometer, " << box->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorCone *cone = dynamic_cast<const FormFactorCone *>(p_ff)) {
            result << " = FormFactorCone(" << cone->getRadius() << "*nanometer, "
                   << cone->getHeight() << "*nanometer, "
                   << PyGenTools::printDegrees(cone->getAlpha()) << ")\n";
        }

        else if (const FormFactorCone6 *cone6 = dynamic_cast<const FormFactorCone6 *>(p_ff)) {
            result << " = FormFactorCone6(" << cone6->getRadius() << "*nanometer, "
                   << cone6->getHeight() << "*nanometer, "
                   << PyGenTools::printDegrees(cone6->getAlpha()) << ")\n";
        }

        else if (const FormFactorCuboctahedron *cuboctahedron
                 = dynamic_cast<const FormFactorCuboctahedron *>(p_ff)) {
            result << " = FormFactorCuboctahedron(" << cuboctahedron->getLength() << "*nanometer, "
                   << cuboctahedron->getHeight() << "*nanometer, "
                   << cuboctahedron->getHeightRatio() << "*nanometer, "
                   << PyGenTools::printDegrees(cuboctahedron->getAlpha()) << ")\n";
        }

        else if (const FormFactorCylinder *cylinder
                 = dynamic_cast<const FormFactorCylinder *>(p_ff)) {
            result << " = FormFactorCylinder(" << cylinder->getHeight() << "*nanometer, "
                   << cylinder->getRadius() << "*nanometer)\n";
        }

        else if (const FormFactorEllipsoidalCylinder *ellipsoidalCylinder
                 = dynamic_cast<const FormFactorEllipsoidalCylinder *>(p_ff)) {
            result << " = FormFactorEllipsoidalCylinder(" << ellipsoidalCylinder->getRadiusA()
                   << "*nanometer, " << ellipsoidalCylinder->getRadiusB() << "*nanometer, "
                   << ellipsoidalCylinder->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorFullSphere *fullSphere
                 = dynamic_cast<const FormFactorFullSphere *>(p_ff)) {
            result << " = FormFactorFullSphere(" << fullSphere->getRadius() << "*nanometer)\n";
        }

        else if (const FormFactorFullSpheroid *fullSpheroid
                 = dynamic_cast<const FormFactorFullSpheroid *>(p_ff)) {
            result << " = FormFactorFullSpheroid(" << fullSpheroid->getRadius() << "*nanometer, "
                   << fullSpheroid->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorGauss *gauss = dynamic_cast<const FormFactorGauss *>(p_ff)) {
            if (gauss->getRadius() == gauss->getHeight()) {
                result << " = FormFactorGauss(" << gauss->getVolume() << "*(nanometer)**3)\n";
            } else {
                result << " = FormFactorGauss(" << gauss->getRadius() << "*nanometer, "
                       << gauss->getHeight() << "*nanometer)\n";
            }
        }

        else if (const FormFactorHemiEllipsoid *hemiEllipsoid
                 = dynamic_cast<const FormFactorHemiEllipsoid *>(p_ff)) {
            result << " = FormFactorHemiEllipsoid(" << hemiEllipsoid->getRadiusA() << "*nanometer, "
                   << hemiEllipsoid->getRadiusB() << "*nanometer, " << hemiEllipsoid->getHeight()
                   << "*nanometer)\n";
        }

        else if (const FormFactorInfLongBox *infLongBox
                 = dynamic_cast<const FormFactorInfLongBox *>(p_ff)) {
            result << " = FormFactorInfLongBox(" << infLongBox->getWidth() << "*nanometer, "
                   << infLongBox->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorInfLongRipple1 *infLongRipple1
                 = dynamic_cast<const FormFactorInfLongRipple1 *>(p_ff)) {
            result << " = FormFactorInfLongRipple1(" << infLongRipple1->getWidth() << "*nanometer, "
                   << infLongRipple1->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorInfLongRipple2 *infLongRipple2
                 = dynamic_cast<const FormFactorInfLongRipple2 *>(p_ff)) {
            result << " = FormFactorInfLongRipple2(" << infLongRipple2->getWidth() << "*nanometer, "
                   << infLongRipple1->getHeight() << "*nanometer, " << infLongRipple2->getAsymetry()
                   << "*nanometer)\n";
        }

        else if (const FormFactorLorentz *lorentz = dynamic_cast<const FormFactorLorentz *>(p_ff)) {
            if (lorentz->getRadius() == lorentz->getHeight()) {
                result << " = FormFactorLorentz(" << lorentz->getVolume() << "*(nanometer)**3)\n";
            } else {
                result << " = FormFactorLorentz(" << lorentz->getRadius() << "*nanometer, "
                       << lorentz->getHeight() << "*nanometer)\n";
            }
        }

        else if (const FormFactorPrism3 *prism3 = dynamic_cast<const FormFactorPrism3 *>(p_ff)) {
            result << " = FormFactorPrism3(" << prism3->getLength() << "*nanometer, "
                   << prism3->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorPrism6 *prism6 = dynamic_cast<const FormFactorPrism6 *>(p_ff)) {
            result << " = FormFactorPrism6(" << prism6->getRadius() << "*nanometer, "
                   << prism6->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorPyramid *pyramid = dynamic_cast<const FormFactorPyramid *>(p_ff)) {
            result << " = FormFactorPyramid(" << pyramid->getLength() << "*nanometer, "
                   << pyramid->getHeight() << "*nanometer, "
                   << PyGenTools::printDegrees(pyramid->getAlpha()) << ")\n";
        }

        else if (const FormFactorRipple1 *ripple1 = dynamic_cast<const FormFactorRipple1 *>(p_ff)) {
            result << " = FormFactorRipple1(" << ripple1->getLength() << "*nanometer, "
                   << ripple1->getWidth() << "*nanometer, " << ripple1->getHeight()
                   << "*nanometer)\n";
        }

        else if (const FormFactorRipple2 *ripple2 = dynamic_cast<const FormFactorRipple2 *>(p_ff)) {
            result << " = FormFactorRipple2(" << ripple2->getLength() << "*nanometer, "
                   << ripple2->getWidth() << "*nanometer, " << ripple2->getHeight() << "nanometer, "
                   << ripple2->getAsymmetry() << "*nanometer)\n";
        }

        else if (const FormFactorTetrahedron *tetrahedron
                 = dynamic_cast<const FormFactorTetrahedron *>(p_ff)) {
            result << " = FormFactorTetrahedron(" << tetrahedron->getLength() << "*nanometer, "
                   << tetrahedron->getHeight() << "*nanometer, "
                   << PyGenTools::printDegrees(tetrahedron->getAlpha()) << ")\n";
        }

        else if (const FormFactorTruncatedCube *truncatedCube
                 = dynamic_cast<const FormFactorTruncatedCube *>(p_ff)) {
            result << " = FormFactorTruncatedCube(" << truncatedCube->getLength() << "*nanometer, "
                   << truncatedCube->getRemovedLength() << "*nanometer)\n";
        }

        else if (const FormFactorTruncatedSphere *truncatedSphere
                 = dynamic_cast<const FormFactorTruncatedSphere *>(p_ff)) {
            result << " = FormFactorTruncatedSphere(" << truncatedSphere->getRadius()
                   << "*nanometer, " << truncatedSphere->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorTruncatedSpheroid *truncatedSpheroid
                 = dynamic_cast<const FormFactorTruncatedSpheroid *>(p_ff)) {
            result << " = FormFactorTruncatedSpheroid(" << truncatedSpheroid->getRadius()
                   << "*nanometer, " << truncatedSpheroid->getHeight() << "*nanometer, "
                   << truncatedSpheroid->getHeightFlattening() << "*nanometer)\n";
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
        const Particle *particle = it->first;

        if (particle->getRotation()) {
            double alpha, beta, gamma;
            particle->getRotation()->getTransform3D().calculateEulerAngles(&alpha, &beta, &gamma);
            switch (particle->getRotation()->getTransform3D().getRotationType()) {
            case Geometry::Transform3D::EULER:
                result << indent() << it->second << "_rotation = RotationEuler("
                       << PyGenTools::printDegrees(alpha) << ", " << PyGenTools::printDegrees(beta)
                       << ", " << PyGenTools::printDegrees(gamma) << ")\n";
                break;
            case Geometry::Transform3D::XAXIS:
                result << indent() << it->second << "_rotation = RotationX("
                       << PyGenTools::printDegrees(beta) << ")\n";
                break;
            case Geometry::Transform3D::YAXIS:
                result << indent() << it->second << "_rotation = RotationY("
                       << PyGenTools::printDegrees(gamma) << ")\n";
                break;
            case Geometry::Transform3D::ZAXIS:
                result << indent() << it->second << "_rotation = RotationZ("
                       << PyGenTools::printDegrees(alpha) << ")\n";
                break;
            default:
                break;
            }
        }
        result << indent() << it->second << " = Particle("
               << m_label->getLabel(particle->getMaterial()) << ", "
               << m_label->getLabel(particle->getFormFactor());

        if (particle->getRotation()) {
            result << ", " << it->second << "_rotation";
        }

        result << ")\n";
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
        kvector_t position = it->first->getRelativeCorePosition();
        result << indent() << it->second << "_relPosition = kvector_t(" << position.x()
               << "*nanometer, " << position.y() << "*nanometer, " << position.z() << "*nanometer)";
        result << "\n" << indent() << it->second << " = ParticleCoreShell("
               << m_label->getLabel(it->first->getShellParticle()) << ", "
               << m_label->getLabel(it->first->getCoreParticle()) << ", " << it->second
               << "_relPosition)\n";
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
    result << "\n" << indent() << "# Defining collection of particles with size distribution\n";
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
    result << "\n" << indent() << "# Defining collection of particles with specific positions\n";
    SampleLabelHandler::particlecompositions_t::iterator it
        = m_label->getParticleCompositionMap()->begin();

    while (it != m_label->getParticleCompositionMap()->end()) {
        result << indent() << it->second << " = ParticleComposition()\n";
        for (size_t i = 0; i < it->first->getNbrParticles(); ++i) {
            kvector_t position = it->first->getParticlePosition(i);
            result << indent() << "particle_" << i + 1 << "_position"
                   << " = kvector_t(" << position.x() << "*nanometer, " << position.y()
                   << "*nanometer, " << position.z() << "*nanometer)\n";
            result << indent() << it->second << ".addParticle("
                   << m_label->getLabel(it->first->getParticle(i)) << ", ";
            result << "particle_" << i + 1 << "_position"
                   << ")\n";
        }
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
            const Lattice1DIFParameters latticeParameters = oneDLattice->getLatticeParameters();
            result << indent() << it->second << "_latticeParameters = Lattice1DIFParameters()\n";
            if (latticeParameters.m_length != 0) {
                result << indent() << it->second
                       << "_latticeParameters.m_length = " << latticeParameters.m_length
                       << "*nanometer\n";
            }

            if (latticeParameters.m_xi != 0) {
                result << indent() << it->second << "_latticeParameters.m_xi = "
                       << PyGenTools::printDegrees(latticeParameters.m_xi) << "\n";
            }

            result << indent() << it->second << " = InterferenceFunction1DLattice(" << it->second
                   << "_latticeParameters)\n";

            const IFTDistribution1D *pdf = oneDLattice->getProbabilityDistribution();

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

        else if (const InterferenceFunctionRadialParaCrystal *oneDParaCrystal
                 = dynamic_cast<const InterferenceFunctionRadialParaCrystal *>(interference)) {
            result << indent() << it->second << " = InterferenceFunctionRadialParaCrystal("
                   << oneDParaCrystal->getPeakDistance() << "*nanometer, "
                   << oneDParaCrystal->getDampingLength() << "*nanometer)\n";

            if (oneDParaCrystal->getKappa() != 0.0) {
                result << indent() << it->second << ".setKappa("
                       << PyGenTools::printDouble(oneDParaCrystal->getKappa()) << ")\n";
            }

            if (oneDParaCrystal->getDomainSize() != 0.0) {
                result << indent() << it->second << ".setDomainSize("
                       << PyGenTools::printDouble(oneDParaCrystal->getDomainSize()) << ")\n";
            }

            const IFTDistribution1D *pdf = oneDParaCrystal->getPropabilityDistribution();

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
            const Lattice2DIFParameters latticeParameters = twoDLattice->getLatticeParameters();
            result << indent() << it->second << " = InterferenceFunction2DLattice("
                   << latticeParameters.m_length_1 << "*nanometer, " << latticeParameters.m_length_2
                   << "*nanometer, " << PyGenTools::printDegrees(latticeParameters.m_angle) << ", "
                   << PyGenTools::printDegrees(latticeParameters.m_xi) << ")\n";

            const IFTDistribution2D *pdf = twoDLattice->getProbabilityDistribution();

            if (const FTDistribution2DCauchy *fTD2DCauchy
                = dynamic_cast<const FTDistribution2DCauchy *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDistribution2DCauchy("
                       << PyGenTools::printDouble(fTD2DCauchy->getCoherenceLengthX())
                       << "*nanometer, "
                       << PyGenTools::printDouble(fTD2DCauchy->getCoherenceLengthY())
                       << "*nanometer"
                       << ")\n";
                if (fTD2DCauchy->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf"
                           << ".setGamma(" << PyGenTools::printDegrees(fTD2DCauchy->getGamma())
                           << ")\n";
                }
            }

            else if (const FTDistribution2DCone *fTD2DCone
                     = dynamic_cast<const FTDistribution2DCone *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDistribution2DCone("
                       << fTD2DCone->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DCone->getCoherenceLengthY() << "*nanometer"
                       << ")\n";

                if (fTD2DCone->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf"
                           << ".setGamma(" << PyGenTools::printDegrees(fTD2DCone->getGamma())
                           << ")\n";
                }
            }

            else if (const FTDistribution2DGate *fTD2DGate
                     = dynamic_cast<const FTDistribution2DGate *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDistribution2DGate("
                       << fTD2DGate->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DGate->getCoherenceLengthY() << "*nanometer"
                       << ")\n";

                if (fTD2DGate->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf"
                           << ".setGamma(" << PyGenTools::printDegrees(fTD2DGate->getGamma())
                           << ")\n";
                }
            }

            else if (const FTDistribution2DGauss *fTD2DGauss
                     = dynamic_cast<const FTDistribution2DGauss *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDistribution2DGauss("
                       << fTD2DGauss->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DGauss->getCoherenceLengthY() << "*nanometer"
                       << ")\n";

                if (fTD2DGauss->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf"
                           << ".setGamma(" << PyGenTools::printDegrees(fTD2DGauss->getGamma())
                           << ")\n";
                }
            }

            else if (const FTDistribution2DVoigt *fTD2DVoigt
                     = dynamic_cast<const FTDistribution2DVoigt *>(pdf)) {
                result << indent() << it->second << "_pdf  = FTDistribution2DVoigt("
                       << fTD2DVoigt->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DVoigt->getCoherenceLengthY() << "*nanometer, "
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

            result << indent() << it->second << ".setProbabilityDistribution(" << it->second
                   << "_pdf)\n";

        }

        else if (const InterferenceFunction2DParaCrystal *twoDParaCrystal
                 = dynamic_cast<const InterferenceFunction2DParaCrystal *>(interference)) {
            std::vector<double> domainSize = twoDParaCrystal->getDomainSizes();
            if (PyGenTools::isSquare(twoDParaCrystal->getLatticeLengths()[0],
                                     twoDParaCrystal->getLatticeLengths()[1],
                                     twoDParaCrystal->getAlphaLattice())) {
                result << indent() << it->second
                       << " = InterferenceFunction2DParaCrystal.createSquare("
                       << twoDParaCrystal->getLatticeLengths()[0] << "*nanometer, "
                       << twoDParaCrystal->getDampingLength() << "*nanometer, " << domainSize[0]
                       << "*nanometer, " << domainSize[1] << "*nanometer)\n";
            }

            else if (PyGenTools::isHexagonal(twoDParaCrystal->getLatticeLengths()[0],
                                             twoDParaCrystal->getLatticeLengths()[1],
                                             twoDParaCrystal->getAlphaLattice())) {
                result << indent() << it->second
                       << " = InterferenceFunction2DParaCrystal.createHexagonal("
                       << twoDParaCrystal->getLatticeLengths()[0] << "*nanometer, "
                       << twoDParaCrystal->getDampingLength() << "*nanometer, " << domainSize[0]
                       << "*nanometer, " << domainSize[1] << "*nanometer)\n";
            }

            else {
                result << indent() << it->second << " = InterferenceFunction2DParaCrystal"
                       << twoDParaCrystal->getLatticeLengths()[0] << "*nanometer, "
                       << twoDParaCrystal->getLatticeLengths()[1] << "*nanometer, "
                       << PyGenTools::printDegrees(twoDParaCrystal->getAlphaLattice()) << ", "
                       << PyGenTools::printDegrees(twoDParaCrystal->getLatticeOrientation()) << ", "
                       << twoDParaCrystal->getDampingLength() << "*nanometer)\n";

                if (domainSize[0] != 0 || domainSize[1] != 0) {
                    result << indent() << it->second << ".setDomainSizes(" << domainSize[0]
                           << "*nanometer, " << domainSize[1] << "*nanometer)\n";
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
                       << fTD2DCauchy->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DCauchy->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DCauchy->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DCauchy->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DCone *fTD2DCone
                     = dynamic_cast<const FTDistribution2DCone *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DCone("
                       << fTD2DCone->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DCone->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DCone->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DCone->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGate *fTD2DGate
                     = dynamic_cast<const FTDistribution2DGate *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DGate("
                       << fTD2DGate->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DGate->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DGate->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DGate->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGauss *fTD2DGauss
                     = dynamic_cast<const FTDistribution2DGauss *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DGauss("
                       << fTD2DGauss->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DGauss->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DGauss->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_1.setGamma("
                           << PyGenTools::printDegrees(fTD2DGauss->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DVoigt *fTD2DVoigt
                     = dynamic_cast<const FTDistribution2DVoigt *>(pdf_1)) {
                result << indent() << it->second << "_pdf_1  = FTDistribution2DVoigt("
                       << fTD2DVoigt->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DVoigt->getCoherenceLengthY() << "*nanometer, "
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
                       << fTD2DCauchy->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DCauchy->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DCauchy->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DCauchy->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DCone *fTD2DCone
                     = dynamic_cast<const FTDistribution2DCone *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2   = FTDistribution2DCone("
                       << fTD2DCone->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DCone->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DCone->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DCone->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGate *fTD2DGate
                     = dynamic_cast<const FTDistribution2DGate *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2   = FTDistribution2DGate("
                       << fTD2DGate->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DGate->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DGate->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DGate->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DGauss *fTD2DGauss
                     = dynamic_cast<const FTDistribution2DGauss *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2 = FTDistribution2DGauss("
                       << fTD2DGauss->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DGauss->getCoherenceLengthY() << "*nanometer)\n";

                if (fTD2DGauss->getGamma() != 0.0) {
                    result << indent() << it->second << "_pdf_2.setGamma("
                           << PyGenTools::printDegrees(fTD2DGauss->getGamma()) << ")\n";
                }
            }

            else if (const FTDistribution2DVoigt *fTD2DVoigt
                     = dynamic_cast<const FTDistribution2DVoigt *>(pdf_2)) {
                result << indent() << it->second << "_pdf_2 = FTDistribution2DVoigt("
                       << fTD2DVoigt->getCoherenceLengthX() << "*nanometer, "
                       << fTD2DVoigt->getCoherenceLengthY() << "*nanometer, "
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
                   << "_pdf_2, " << it->second << "_pdf_2)\n";
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
                const ParticleInfo *particleInfo = particleLayout->getParticleInfo(particleIndex);
                kvector_t pos = particleInfo->getPosition();
                if (pos.x() != 0.0 || pos.y() != 0.0) {
                    result << indent() << m_label->getLabel(particleInfo->getParticle())
                           << "_position = kvector_t(" << pos.x() << "*nanometer, " << pos.y()
                           << "*nanometer, " << pos.z() << "*nanometer)\n";

                    result << indent() << m_label->getLabel(particleInfo->getParticle())
                           << "_positionInfo = ParticleInfo("
                           << m_label->getLabel(particleInfo->getParticle()) << ", "
                           << m_label->getLabel(particleInfo->getParticle()) << "_position, "
                           << PyGenTools::printDouble(particleInfo->getAbundance()) << ")\n";

                    result << indent() << it->second << ".addParticleInfo("
                           << m_label->getLabel(particleInfo->getParticle()) << "_positionInfo)\n";
                } else {
                    result << indent() << it->second << ".addParticle("
                           << m_label->getLabel(particleInfo->getParticle()) << ", "
                           << PyGenTools::printDouble(particleInfo->getDepth()) << ", "
                           << PyGenTools::printDouble(particleInfo->getAbundance()) << ")\n";
                }
                particleIndex++;
            }

            size_t numberOfInterferenceFunctions
                = particleLayout->getNumberOfInterferenceFunctions();
            size_t interferenceIndex = 0;

            while (interferenceIndex != numberOfInterferenceFunctions) {
                result << indent() << it->second << ".addInterferenceFunction("
                       << m_label->getLabel(
                              particleLayout->getInterferenceFunction(interferenceIndex)) << ")\n";
                interferenceIndex++;
            }

            switch (particleLayout->getApproximation()) {
            case ILayout::DA:
                break;
            case ILayout::SSCA:
                result << indent() << it->second << ".setApproximation(ILayout.";
                result << "SSCA)\n";
                break;
            case ILayout::ISGISAXSMOR:
                result << indent() << it->second << ".setApproximation(ILayout.";
                result << "ISGISAXSMOR)\n";
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
        result << indent() << it->second << " = LayerRoughness(" << it->first->getSigma()
               << "*nanometer, " << it->first->getHurstParameter() << ", "
               << it->first->getLatteralCorrLength() << "*nanometer)\n";
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
    size_t numberOfDetectorDimensions = simulation->getInstrument().getDetectorDimension();
    if (numberOfDetectorDimensions != 2) {
        throw Exceptions::RuntimeErrorException("PyGenVisitor::defineDetector: "
                                                "detector must be two-dimensional for GISAS");
    }
    std::ostringstream result;
    result << std::setprecision(12);
    // result << indent() << "# Defining Detector Parameters\n";
    result << indent() << "simulation.setDetectorParameters(";
    size_t index = 0;
    while (index < numberOfDetectorDimensions) {
        if (index != 0) {
            result << ", ";
        }
        result << simulation->getInstrument().getDetectorAxis(index).getSize() << ", "
               << PyGenTools::printDegrees(
                      simulation->getInstrument().getDetectorAxis(index).getMin()) << ", "
               << PyGenTools::printDegrees(
                      simulation->getInstrument().getDetectorAxis(index).getMax());
        index++;
    }
    result << ")\n";
    return result.str();
}

std::string PyGenVisitor::defineBeam(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);
    // result << indent() << "# Defining Beam Parameters\n";
    result << indent() << "simulation.setBeamParameters(";
    result << simulation->getInstrument().getBeam().getWavelength() << "*nanometer, "
           << PyGenTools::printDegrees(simulation->getInstrument().getBeam().getAlpha()) << ", "
           << PyGenTools::printDegrees(simulation->getInstrument().getBeam().getPhi()) << ")\n";
    return result.str();
}

std::string PyGenVisitor::defineParameterDistributions(const GISASSimulation *simulation) const
{
    std::ostringstream result;

    return result.str();
}

std::string PyGenVisitor::definePlotting(const GISASSimulation *simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);
    //    result << "#NOTE: Uncomment the next function for plotting\n";
    //    result << "#NOTE: This requires the presence of matplotlib library\n";
    result << "def plotSimulation(simulation):\n";
    result << "" << indent() << "result = simulation.getIntensityData().getArray()"
           << "+ 1 # +1 for log scale\n";
    result << "" << indent() << "im = pylab.imshow(numpy.rot90(result, 1), "
           << "norm=matplotlib.colors.LogNorm(), extent=[";
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
    result << indent() << "pylab.colorbar(im)\n";
    result << indent() << "pylab.show()\n\n\n";
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

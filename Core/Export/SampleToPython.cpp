//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleToPython.cpp
//! @brief     Implements class SampleToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Export/SampleToPython.h"
#include "Base/Vector/Transform3D.h"
#include "Core/Export/INodeUtils.h"
#include "Core/Export/PyFmt.h"
#include "Core/Export/PyFmt2.h"
#include "Core/Export/SampleLabelHandler.h"
#include "Param/Varia/ParameterUtils.h"
#include "Sample/Aggregate/InterferenceFunctions.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/MesoCrystal.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/Particle/ParticleCoreShell.h"
#include "Sample/Particle/ParticleDistribution.h"
#include "Sample/Scattering/IFormFactor.h"
#include "Sample/Slice/LayerInterface.h"
#include "Sample/Slice/LayerRoughness.h"
#include <iomanip>
#include <map>
#include <set>

using pyfmt::indent;

namespace {

void setRotationInformation(const IParticle* particle, std::string name,
                            std::ostringstream& result) {
    if (particle->rotation()) {
        switch (particle->rotation()->getTransform3D().getRotationType()) {
        case Transform3D::EULER: {
            double alpha, beta, gamma;
            particle->rotation()->getTransform3D().calculateEulerAngles(&alpha, &beta, &gamma);
            result << indent() << name << "_rotation = ba.RotationEuler("
                   << pyfmt::printDegrees(alpha) << ", " << pyfmt::printDegrees(beta) << ", "
                   << pyfmt::printDegrees(gamma) << ")\n";
            break;
        }
        case Transform3D::XAXIS: {
            double alpha = particle->rotation()->getTransform3D().calculateRotateXAngle();
            result << indent() << name << "_rotation = ba.RotationX(" << pyfmt::printDegrees(alpha)
                   << ")\n";
            break;
        }
        case Transform3D::YAXIS: {
            double alpha = particle->rotation()->getTransform3D().calculateRotateYAngle();
            result << indent() << name << "_rotation = ba.RotationY(" << pyfmt::printDegrees(alpha)
                   << ")\n";
            break;
        }
        case Transform3D::ZAXIS: {
            double alpha = particle->rotation()->getTransform3D().calculateRotateZAngle();
            result << indent() << name << "_rotation = ba.RotationZ(" << pyfmt::printDegrees(alpha)
                   << ")\n";
            break;
        }
        }
        result << indent() << name << ".setRotation(" << name << "_rotation)\n";
    }
}

void setPositionInformation(const IParticle* particle, std::string name,
                            std::ostringstream& result) {
    kvector_t pos = particle->position();
    if (pos == kvector_t())
        return;

    result << indent() << name << "_position = kvector_t(" << pyfmt::printNm(pos.x()) << ", "
           << pyfmt::printNm(pos.y()) << ", " << pyfmt::printNm(pos.z()) << ")\n";
    result << indent() << name << ".setPosition(" << name << "_position)\n";
}

} // namespace

//  ************************************************************************************************
//  class SampleToPython
//  ************************************************************************************************

std::string SampleToPython::generateSampleCode(const MultiLayer& multilayer) {
    initLabels(multilayer);
    return defineGetSample();
}

void SampleToPython::initLabels(const MultiLayer& multilayer) {
    m_objs.reset(new SampleLabelHandler());

    m_objs->insertMultiLayer(&multilayer);

    for (const auto* x : multilayer.containedMaterials())
        m_objs->insertMaterial(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Layer>(multilayer))
        m_objs->insertKeyedObject("layer", x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<LayerRoughness>(multilayer))
        m_objs->insertKeyedObject("roughness", x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<IFormFactor>(multilayer))
        m_objs->insertKeyedObject("ff", x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<IInterferenceFunction>(multilayer))
        m_objs->insertInterferenceFunction(x);
//        m_objs->insertKeyedObject("iff", x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleLayout>(multilayer))
        m_objs->insertLayout(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Particle>(multilayer))
        m_objs->insertParticle(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleCoreShell>(multilayer))
        m_objs->insertParticleCoreShell(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleComposition>(multilayer))
        m_objs->insertParticleComposition(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleDistribution>(multilayer))
        m_objs->insertParticleDistribution(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Lattice2D>(multilayer))
        m_objs->insertLattice2D(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Lattice3D>(multilayer))
        m_objs->insertLattice3D(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Crystal>(multilayer))
        m_objs->insertCrystal(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<MesoCrystal>(multilayer))
        m_objs->insertMesoCrystal(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<IRotation>(multilayer))
        m_objs->insertRotation(x);
}

SampleToPython::SampleToPython() = default;

SampleToPython::~SampleToPython() = default;

std::string SampleToPython::defineGetSample() const {
    return "def get_sample():\n" + defineMaterials() + defineFormFactors() + defineParticles()
           + defineCoreShellParticles() + defineParticleCompositions() + defineLattices2D()
           + defineLattices3D() + defineCrystals() + defineMesoCrystals()
           + defineParticleDistributions() + defineInterferenceFunctions() + defineParticleLayouts()
           + defineRoughnesses() + defineLayers() + defineMultiLayers() + "\n\n";
}

const std::map<MATERIAL_TYPES, std::string> factory_names{
    {MATERIAL_TYPES::RefractiveMaterial, "HomogeneousMaterial"},
    {MATERIAL_TYPES::MaterialBySLD, "MaterialBySLD"}};

std::string SampleToPython::defineMaterials() const {
    const LabelMap<const Material*>* themap = m_objs->materialMap();
    if (themap->empty())
        return "# No materials.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << indent() << "# Define materials\n";
    std::set<std::string> visitedMaterials;
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        if (visitedMaterials.find(it->second) != visitedMaterials.end())
            continue;
        visitedMaterials.insert(it->second);
        const Material* material = it->first;
        const auto factory_name = factory_names.find(material->typeID());
        if (factory_name == factory_names.cend())
            throw std::runtime_error(
                "Error in ExportToPython::defineMaterials(): unknown material type");
        const complex_t& material_data = material->materialData();
        if (material->isScalarMaterial()) {
            result << indent() << m_objs->labelMaterial(material) << " = ba."
                   << factory_name->second << "(\"" << material->getName() << "\", "
                   << pyfmt::printDouble(material_data.real()) << ", "
                   << pyfmt::printDouble(material_data.imag()) << ")\n";
        } else {
            kvector_t magnetic_field = material->magnetization();
            result << indent() << "magnetic_field = kvector_t(" << magnetic_field.x() << ", "
                   << magnetic_field.y() << ", " << magnetic_field.z() << ")\n";
            result << indent() << m_objs->labelMaterial(material) << " = ba."
                   << factory_name->second << "(\"" << material->getName();
            result << "\", " << pyfmt::printDouble(material_data.real()) << ", "
                   << pyfmt::printDouble(material_data.imag()) << ", "
                   << "magnetic_field)\n";
        }
    }
    return result.str();
}

std::string SampleToPython::defineLayers() const {
    std::vector<const Layer*> v = m_objs->objectsOfType<Layer>();
    if (v.empty())
        return "";
    std::ostringstream result;
    result << "\n" << indent() << "# Define layers\n";
    result << std::setprecision(12);
    for (const auto* s : v) {
        const std::string& label = m_objs->obj2label(s);
        result << indent() << label << " = ba.Layer(" << m_objs->labelMaterial(s->material());
        if (s->thickness() != 0)
            result << ", " << pyfmt::printNm(s->thickness());
        result << ")\n";
        if (s->numberOfSlices() != 1)
            result << indent() << label << ".setNumberOfSlices(" << s->numberOfSlices()
                   << ")\n";
        for (const auto* layout : s->layouts())
            result << indent() << label << ".addLayout(" << m_objs->labelLayout(layout) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineRoughnesses() const {
    std::vector<const LayerRoughness*> v = m_objs->objectsOfType<LayerRoughness>();
    if (v.empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define roughness\n";
    for (const auto* s : v) {
        const std::string& label = m_objs->obj2label(s);
        result << indent() << label << " = ba.LayerRoughness("
               << pyfmt2::argumentList(s) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineFormFactors() const {
    std::vector<const IFormFactor*> v = m_objs->objectsOfType<IFormFactor>();
    if (v.empty())
        return "";
    std::ostringstream result;
    result << "\n" << indent() << "# Define form factors\n";
    result << std::setprecision(12);
    for (const auto* s : v) {
        const std::string& label = m_objs->obj2label(s);
        result << indent() << label << " = ba.FormFactor" << s->getName() << "("
               << pyfmt2::argumentList(s) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineInterferenceFunctions() const {
    const auto* themap = m_objs->interferenceFunctionMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define interference functions\n";
    for (auto it: *themap) {
        const IInterferenceFunction* interference = it.first;
        const std::string& key = it.second;

        if (dynamic_cast<const InterferenceFunctionNone*>(interference))
            result << indent() << key << " = ba.InterferenceFunctionNone()\n";

        else if (const auto* iff =
                     dynamic_cast<const InterferenceFunction1DLattice*>(interference)) {
            result << indent() << key << " = ba.InterferenceFunction1DLattice("
                   << pyfmt::printNm(iff->getLength()) << ", " << pyfmt::printDegrees(iff->getXi())
                   << ")\n";

            const auto* pdf = INodeUtils::OnlyChildOfType<IFTDecayFunction1D>(*iff);

            if (pdf->decayLength() != 0.0)
                result << indent() << key << "_pdf  = ba." << pdf->getName() << "("
                       << pyfmt2::argumentList(pdf) << ")\n"
                       << indent() << key << ".setDecayFunction(" << key << "_pdf)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(interference)) {
            result << indent() << key << " = ba.InterferenceFunctionRadialParaCrystal("
                   << pyfmt::printNm(iff->peakDistance()) << ", "
                   << pyfmt::printNm(iff->dampingLength()) << ")\n";

            if (iff->kappa() != 0.0)
                result << indent() << key << ".setKappa(" << pyfmt::printDouble(iff->kappa())
                       << ")\n";

            if (iff->domainSize() != 0.0)
                result << indent() << key << ".setDomainSize("
                       << pyfmt::printDouble(iff->domainSize()) << ")\n";

            const auto* pdf = INodeUtils::OnlyChildOfType<IFTDistribution1D>(*iff);

            if (pdf->omega() != 0.0)
                result << indent() << key << "_pdf  = ba." << pdf->getName() << "("
                       << pyfmt2::argumentList(pdf) << ")\n"
                       << indent() << key << ".setProbabilityDistribution(" << key
                       << "_pdf)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunction2DLattice*>(interference)) {
            const auto* lattice = INodeUtils::OnlyChildOfType<Lattice2D>(*iff);

            result << indent() << key << " = ba.InterferenceFunction2DLattice("
                   << m_objs->labelLattice2D(lattice) << ")\n";

            const auto* pdf = INodeUtils::OnlyChildOfType<IFTDecayFunction2D>(*iff);

            result << indent() << key << "_pdf  = ba." << pdf->getName() << "("
                   << pyfmt2::argumentList(pdf) << ")\n"
                   << indent() << key << ".setDecayFunction(" << key << "_pdf)\n";

            if (iff->integrationOverXi() == true)
                result << indent() << key << ".setIntegrationOverXi(True)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunctionFinite2DLattice*>(interference)) {
            const auto* lattice = INodeUtils::OnlyChildOfType<Lattice2D>(*iff);

            result << indent() << key << " = ba.InterferenceFunctionFinite2DLattice("
                   << m_objs->labelLattice2D(lattice) << ", " << iff->numberUnitCells1() << ", "
                   << iff->numberUnitCells2() << ")\n";

            if (iff->integrationOverXi() == true)
                result << indent() << key << ".setIntegrationOverXi(True)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunction2DParaCrystal*>(interference)) {
            const auto* lattice = INodeUtils::OnlyChildOfType<Lattice2D>(*iff);
            std::vector<double> domainSize = iff->domainSizes();

            result << indent() << key << " = ba.InterferenceFunction2DParaCrystal("
                   << m_objs->labelLattice2D(lattice) << ", "
                   << pyfmt::printNm(iff->dampingLength()) << ", " << pyfmt::printNm(domainSize[0])
                   << ", " << pyfmt::printNm(domainSize[1]) << ")\n";

            if (iff->integrationOverXi() == true)
                result << indent() << key << ".setIntegrationOverXi(True)\n";

            const auto pdf_vector = INodeUtils::ChildNodesOfType<IFTDistribution2D>(*iff);
            if (pdf_vector.size() != 2)
                continue;
            const IFTDistribution2D* pdf = pdf_vector[0];

            result << indent() << key << "_pdf_1  = ba." << pdf->getName() << "("
                   << pyfmt2::argumentList(pdf) << ")\n";

            pdf = pdf_vector[1];

            result << indent() << key << "_pdf_2  = ba." << pdf->getName() << "("
                   << pyfmt2::argumentList(pdf) << ")\n";
            result << indent() << key << ".setProbabilityDistributions(" << key
                   << "_pdf_1, " << key << "_pdf_2)\n";

        } else if (const auto* lattice_hd =
                       dynamic_cast<const InterferenceFunctionHardDisk*>(interference)) {
            result << indent() << key << " = ba.InterferenceFunctionHardDisk("
                   << pyfmt::printNm(lattice_hd->radius()) << ", "
                   << pyfmt::printDouble(lattice_hd->density()) << ")\n";

        } else
            throw std::runtime_error(
                "Bug: ExportToPython::defineInterferenceFunctions() called with unexpected "
                "IInterferenceFunction "
                + interference->getName());

        if (interference->positionVariance() > 0.0) {
            result << indent() << key << ".setPositionVariance("
                   << pyfmt::printNm2(interference->positionVariance()) << ")\n";
        }
    }
    return result.str();
}

std::string SampleToPython::defineParticles() const {
    const auto* themap = m_objs->particleMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Particle* particle = it->first;
        std::string particle_name = it->second;
        const auto* ff = INodeUtils::OnlyChildOfType<IFormFactor>(*particle);
        if (!ff)
            continue;
        result << indent() << particle_name << " = ba.Particle("
               << m_objs->labelMaterial(particle->material()) << ", "
               << m_objs->obj2label(ff) << ")\n";
        setRotationInformation(particle, particle_name, result);
        setPositionInformation(particle, particle_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineCoreShellParticles() const {
    const auto* themap = m_objs->particleCoreShellMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define core shell particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleCoreShell* coreshell = it->first;
        result << indent() << it->second << " = ba.ParticleCoreShell("
               << m_objs->labelParticle(coreshell->shellParticle()) << ", "
               << m_objs->labelParticle(coreshell->coreParticle()) << ")\n";
        std::string core_shell_name = it->second;
        setRotationInformation(coreshell, core_shell_name, result);
        setPositionInformation(coreshell, core_shell_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineParticleDistributions() const {
    const auto* themap = m_objs->particleDistributionsMap();
    if (themap->empty())
        return "";

    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define particles with parameter following a distribution\n";

    int index(1);
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleDistribution* particle_distr = it->first;

        const std::string units = particle_distr->mainUnits();

        ParameterDistribution par_distr = particle_distr->parameterDistribution();

        // building distribution functions
        std::string s_distr = "distr_" + std::to_string(index);
        result << indent() << s_distr << " = "
               << pyfmt2::printDistribution(*par_distr.getDistribution(), units) << "\n";

        // building parameter distribution
        std::string s_par_distr = "par_distr_" + std::to_string(index);

        result << indent() << s_par_distr << " = "
               << pyfmt2::printParameterDistribution(par_distr, s_distr, units) << "\n";

        // linked parameters
        std::vector<std::string> linked_pars = par_distr.getLinkedParameterNames();
        if (!linked_pars.empty()) {
            result << indent() << s_par_distr;
            for (size_t i = 0; i < linked_pars.size(); ++i)
                result << ".linkParameter(\"" << linked_pars[i] << "\")";
            result << "\n";
        }

        auto particle = INodeUtils::OnlyChildOfType<IParticle>(*particle_distr);
        if (!particle)
            continue;
        result << indent() << it->second << " = ba.ParticleDistribution("
               << m_objs->labelParticle(particle) << ", " << s_par_distr << ")\n";
        index++;
    }
    return result.str();
}

std::string SampleToPython::defineParticleCompositions() const {
    const auto* themap = m_objs->particleCompositionMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define composition of particles at specific positions\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleComposition* particle_composition = it->first;
        std::string particle_composition_name = it->second;
        result << indent() << particle_composition_name << " = ba.ParticleComposition()\n";
        const auto particle_list = INodeUtils::ChildNodesOfType<IParticle>(*particle_composition);
        for (const auto* particle : particle_list) {
            result << indent() << particle_composition_name << ".addParticle("
                   << m_objs->labelParticle(particle) << ")\n";
        }
        setRotationInformation(particle_composition, particle_composition_name, result);
        setPositionInformation(particle_composition, particle_composition_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineLattices2D() const {
    const auto* themap = m_objs->lattice2DMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define 2D lattices\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Lattice2D* lattice = it->first;
        std::string lattice_name = it->second;
        result << indent() << lattice_name << " = ba.BasicLattice2D(\n";
        result << indent() << indent() << pyfmt::printNm(lattice->length1()) << ", "
               << pyfmt::printNm(lattice->length2()) << ", "
               << pyfmt::printDegrees(lattice->latticeAngle()) << ", "
               << pyfmt::printDegrees(lattice->rotationAngle()) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineLattices3D() const {
    const auto* themap = m_objs->lattice3DMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define 3D lattices\n";
    for (auto it: *themap) {
        const Lattice3D* s = it.first;
        const std::string& key = it.second;
        kvector_t bas_a = s->getBasisVectorA();
        kvector_t bas_b = s->getBasisVectorB();
        kvector_t bas_c = s->getBasisVectorC();
        result << indent() << key << " = ba.Lattice3D(\n";
        result << indent() << indent() << "ba.kvector_t(" << pyfmt::printNm(bas_a.x()) << ", "
               << pyfmt::printNm(bas_a.y()) << ", " << pyfmt::printNm(bas_a.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t(" << pyfmt::printNm(bas_b.x()) << ", "
               << pyfmt::printNm(bas_b.y()) << ", " << pyfmt::printNm(bas_b.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t(" << pyfmt::printNm(bas_c.x()) << ", "
               << pyfmt::printNm(bas_c.y()) << ", " << pyfmt::printNm(bas_c.z()) << "))\n";
    }
    return result.str();
}

std::string SampleToPython::defineCrystals() const {
    const auto* themap = m_objs->crystalMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define crystals: basis particle + lattice\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Crystal* crystal = it->first;
        std::string crystal_name = it->second;
        const auto* lattice = INodeUtils::OnlyChildOfType<Lattice3D>(*crystal);
        const auto* basis = INodeUtils::OnlyChildOfType<IParticle>(*crystal);
        if (!lattice || !basis)
            continue;
        result << indent() << crystal_name << " = ba.Crystal(";
        result << m_objs->labelParticle(basis) << ", ";
        result << m_objs->labelLattice3D(lattice) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineMesoCrystals() const {
    const auto* themap = m_objs->mesocrystalMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define mesocrystals\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const MesoCrystal* mesocrystal = it->first;
        std::string mesocrystal_name = it->second;
        auto crystal = INodeUtils::OnlyChildOfType<Crystal>(*mesocrystal);
        auto outer_shape = INodeUtils::OnlyChildOfType<IFormFactor>(*mesocrystal);
        if (!crystal || !outer_shape)
            continue;
        result << indent() << mesocrystal_name << " = ba.MesoCrystal(";
        result << m_objs->labelCrystal(crystal) << ", ";
        result << m_objs->obj2label(outer_shape) << ")\n";
        setRotationInformation(mesocrystal, mesocrystal_name, result);
        setPositionInformation(mesocrystal, mesocrystal_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineParticleLayouts() const {
    const auto* themap = m_objs->particleLayoutMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define particle layouts and adding particles\n";
    for (auto it: *themap) {
        const ParticleLayout* s = it.first;
        const std::string& key = it.second;
        result << indent() << key << " = ba.ParticleLayout()\n";
        const auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(*s);
        for (const auto* particle : particles) {
            double abundance = particle->abundance();
            result << indent() << key << ".addParticle("
                   << m_objs->labelParticle(particle) << ", " << pyfmt::printDouble(abundance)
                   << ")\n";
        }
        if (const auto* iff =
            INodeUtils::OnlyChildOfType<IInterferenceFunction>(*s))
            result << indent() << key << ".setInterferenceFunction("
                   << m_objs->labelInterferenceFunction(iff) << ")\n";
        result << indent() << key << ".setWeight(" << s->weight() << ")\n";
        result << indent() << key << ".setTotalParticleSurfaceDensity("
               << s->totalParticleSurfaceDensity() << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineMultiLayers() const {
    const auto* themap = m_objs->multiLayerMap();
    if (themap->empty())
        return "# No MultiLayers.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define multilayers\n";
    for (auto it: *themap) {
        const MultiLayer* s = it.first;
        const std::string& key = it.second;
        result << indent() << key << " = ba.MultiLayer()\n";
        double ccl = s->crossCorrLength();
        if (ccl > 0.0)
            result << indent() << key << ".setCrossCorrLength(" << ccl << ")\n";
        auto external_field = s->externalField();
        if (external_field.mag() > 0.0) {
            std::string field_name = key + "_external_field";
            result << indent() << field_name << " = kvector_t("
                   << pyfmt::printScientificDouble(external_field.x()) << ", "
                   << pyfmt::printScientificDouble(external_field.y()) << ", "
                   << pyfmt::printScientificDouble(external_field.z()) << ")\n";
            result << indent() << key << ".setExternalField(" << field_name << ")\n";
        }
        size_t numberOfLayers = s->numberOfLayers();
        if (numberOfLayers) {
            result << indent() << key << ".addLayer("
                   << m_objs->obj2label(s->layer(0)) << ")\n";

            size_t layerIndex = 1;
            while (layerIndex != numberOfLayers) {
                const LayerInterface* layerInterface = s->layerInterface(layerIndex - 1);
                if (const LayerRoughness* rough = layerInterface->getRoughness())
                    result << indent() << key << ".addLayerWithTopRoughness("
                           << m_objs->obj2label(s->layer(layerIndex))
                           << ", " << m_objs->obj2label(rough)
                           << ")\n";
                else
                    result << indent() << key << ".addLayer("
                           << m_objs->obj2label(s->layer(layerIndex))
                           << ")\n";
                layerIndex++;
            }
        }
        result << "\n" << indent() << "return " << key << "\n";
    }
    return result.str();
}

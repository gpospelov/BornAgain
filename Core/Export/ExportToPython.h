// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ExportToPython.h
//! @brief     Defines class ExportToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef EXPORTTOPYTHON_H
#define EXPORTTOPYTHON_H

#include "WinDllMacros.h"
#include <string>
#include <memory>

class Simulation;
class GISASSimulation;
class IParticle;
class MultiLayer;
class SampleLabelHandler;

//! Write a Python script that allows to run the current simulation.

class BA_CORE_API_ ExportToPython
{
public:
    enum EMainType
    {
        RUN_SIMULATION, //!< main function runs simulation
        SAVE_DATA       //!< main function saves intensity data
    };

    ExportToPython();
    virtual ~ExportToPython();

    std::string generateSampleCode(const MultiLayer& multilayer);
    std::string generateSimulationCode(const Simulation& simulation, EMainType mainType);

private:
    void initSample(const MultiLayer& multilayer);
    std::string defineGetSample() const;
    std::string definePreamble() const;
    std::string defineGetSimulation(const Simulation* simulation) const;
    std::string defineGISASSimulation(const GISASSimulation* simulation) const;
    std::string defineMaterials() const;
    std::string defineLayers() const;
    std::string defineFormFactors() const;
    std::string defineParticles() const;
    std::string defineCoreShellParticles() const;
    std::string defineParticleDistributions() const;
    std::string defineParticleCompositions() const;
    std::string defineLattices() const;
    std::string defineCrystals() const;
    std::string defineMesoCrystals() const;
    std::string defineInterferenceFunctions() const;
    std::string defineParticleLayouts() const;
    std::string defineRoughnesses() const;
    std::string addLayoutsToLayers() const;
    std::string defineMultiLayers() const;
    std::string defineDetector(const Simulation* simulation) const;
    std::string defineDetectorResolutionFunction(const Simulation* simulation) const;
    std::string defineDetectorPolarizationAnalysis(const Simulation* simulation) const;
    std::string defineBeam(const Simulation* simulation) const;
    std::string defineParameterDistributions(const Simulation* simulation) const;
    std::string defineMasks(const Simulation* simulation) const;
    std::string defineSimulationOptions(const Simulation* simulation) const;
    std::string defineBackground(const Simulation* simulation) const;
    std::string defineMain(EMainType mainType = RUN_SIMULATION);

    std::string indent() const;

    void setRotationInformation(const IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;
    void setPositionInformation(const IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;

    std::unique_ptr<SampleLabelHandler> m_label;
};

#endif // EXPORTTOPYTHON_H

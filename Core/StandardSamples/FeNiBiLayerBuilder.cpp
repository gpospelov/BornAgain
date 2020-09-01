// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/FeNiBiLayerBuilder.cpp
//! @brief     Defines various sample builder classes to
//!            test polarized specular computations
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/FeNiBiLayerBuilder.h"
#include "Core/Basics/PhysicalConstants.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"

namespace
{
auto constexpr rhoMconst = -PhysConsts::m_n * PhysConsts::g_factor_n * PhysConsts::mu_N
                           / PhysConsts::h_bar / PhysConsts::h_bar * 1e-27;
}

std::unique_ptr<MultiLayer> FeNiBiLayer::constructSample()
{
    auto sample = std::make_unique<MultiLayer>();

    auto m_ambient = MaterialBySLD("Ambient", 0.0, 0.0);
    auto m_Fe =
        effectiveSLD == 0
            ? MaterialBySLD("Fe", sldFe.real(), sldFe.imag(), magnetizationVector)
            : MaterialBySLD("Fe", sldFe.real() + effectiveSLD * rhoMconst * magnetizationMagnitude,
                            sldFe.imag(), kvector_t{0, 0, 0});

    auto m_Ni = MaterialBySLD("Ni", sldNi.real(), sldNi.imag());
    auto m_Substrate = MaterialBySLD("Au", sldAu.real(), sldAu.imag());

    Layer l_Fe{m_Fe, thicknessFe};
    Layer l_Ni{m_Ni, thicknessNi};

    LayerRoughness roughness{sigmaRoughness, 0., 0.};
    sample->addLayer(Layer{m_ambient});

    for (auto i = 0; i < NBiLayers; ++i) {
        sample->addLayerWithTopRoughness(l_Fe, roughness);
        sample->addLayerWithTopRoughness(l_Ni, roughness);
    }

    sample->addLayerWithTopRoughness(Layer{m_Substrate}, roughness);
    sample->setRoughnessModel(roughnessModel);
    return sample;
}

MultiLayer* FeNiBiLayerBuilder::buildSample() const
{
    auto sample = FeNiBiLayer{FeNiBiLayer::Options()};
    return sample.release();
}

MultiLayer* FeNiBiLayerTanhBuilder::buildSample() const
{
    auto sample = FeNiBiLayer{FeNiBiLayer::Options()
                                  .sigmaRoughness(2. * Units::angstrom)
                                  .roughnessModel(RoughnessModel::TANH)};
    return sample.release();
}

MultiLayer* FeNiBiLayerNCBuilder::buildSample() const
{
    auto sample = FeNiBiLayer{FeNiBiLayer::Options()
                                  .sigmaRoughness(2. * Units::angstrom)
                                  .roughnessModel(RoughnessModel::NEVOT_CROCE)};
    return sample.release();
}

MultiLayer* FeNiBiLayerSpinFlipBuilder::buildSample() const
{
    auto sample = FeNiBiLayer{FeNiBiLayer::Options().angle(38. * Units::degree)};
    return sample.release();
}

MultiLayer* FeNiBiLayerSpinFlipTanhBuilder::buildSample() const
{
    auto sample = FeNiBiLayer{FeNiBiLayer::Options()
                                  .angle(38 * Units::degree)
                                  .sigmaRoughness(2. * Units::angstrom)
                                  .roughnessModel(RoughnessModel::TANH)};
    return sample.release();
}

MultiLayer* FeNiBiLayerSpinFlipNCBuilder::buildSample() const
{
    auto sample = FeNiBiLayer{FeNiBiLayer::Options()
                                  .angle(38 * Units::degree)
                                  .sigmaRoughness(2. * Units::angstrom)
                                  .roughnessModel(RoughnessModel::NEVOT_CROCE)};
    return sample.release();
}

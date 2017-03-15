// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayoutStrategyBuilder.cpp
//! @brief     Implements class LayoutStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayoutStrategyBuilder.h"
#include "DecouplingApproximationStrategy.h"
#include "Exceptions.h"
#include "FormFactorCoherentSum.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "IFresnelMap.h"
#include "ILayout.h"
#include "IParticle.h"
#include "InterferenceFunctionNone.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "SlicedFormFactorList.h"
#include "SSCApproximationStrategy.h"

LayoutStrategyBuilder::LayoutStrategyBuilder(
    const MultiLayer* p_multilayer, const ILayout* p_layout,
    const IFresnelMap* p_fresnel_map, bool polarized,
    const SimulationOptions& sim_params, size_t layer_index)
    : mp_multilayer(p_multilayer)
    , mp_layout(p_layout)
    , mp_fresnel_map(p_fresnel_map)
    , m_polarized {polarized}
    , m_sim_params (sim_params)
    , m_layer_index(layer_index)
{}

LayoutStrategyBuilder::~LayoutStrategyBuilder()
{} // needs class definitions => don't move to .h

//! Returns a new strategy object that is able to calculate the scattering for fixed k_f.
IInterferenceFunctionStrategy* LayoutStrategyBuilder::createStrategy() const
{
    SafePointerVector<class FormFactorCoherentSum> ff_wrappers = collectFormFactorList();

    IInterferenceFunctionStrategy* p_result = nullptr;
    switch (mp_layout->getApproximation())
    {
    case ILayout::DA:
        p_result = new DecouplingApproximationStrategy(m_sim_params, m_polarized);
        break;
    case ILayout::SSCA:
        double kappa = mp_layout ? mp_layout->interferenceFunction()->getKappa()
                                 : 0.0;
        if (kappa<=0.0)
            throw Exceptions::ClassInitializationException(
                "SSCA requires a nontrivial interference function "
                "with a strictly positive coupling coefficient kappa");
        p_result = new SSCApproximationStrategy(m_sim_params, kappa, m_polarized);
        break;
    }
    if (!p_result)
        throw Exceptions::ClassInitializationException(
            "Could not create appropriate strategy");
    p_result->init(ff_wrappers, mp_layout->interferenceFunction());
    return p_result;
}

//! Sets m_formfactor_wrappers, the list of weighted form factors.
SafePointerVector<class FormFactorCoherentSum> LayoutStrategyBuilder::collectFormFactorList() const
{
    SafePointerVector<class FormFactorCoherentSum> result;
    double layout_abundance = mp_layout->getTotalAbundance();
    for (const IParticle* particle: mp_layout->particles()) {
        auto p_ff_coh = createFormFactorCoherentSum(particle);
        p_ff_coh->scaleRelativeAbundance(layout_abundance);
        result.push_back(p_ff_coh);
    }
    return result;
}

//! Returns a new formfactor wrapper for a given particle in given ambient material.
FormFactorCoherentSum* LayoutStrategyBuilder::createFormFactorCoherentSum(
    const IParticle* particle) const
{
    std::unique_ptr<FormFactorCoherentSum> P_result(
                new FormFactorCoherentSum(particle->abundance()));
    auto sliced_ffs = CreateSlicedFormFactors(*particle, *mp_multilayer, m_layer_index);
    for (size_t i=0; i < sliced_ffs.size(); ++i) {
        auto ff_pair = sliced_ffs[i];
        std::unique_ptr<IFormFactor> P_ff_framework;
        if (mp_multilayer->numberOfLayers()>1) {
            if (m_polarized)
                P_ff_framework.reset(new FormFactorDWBAPol(*ff_pair.first));
            else
                P_ff_framework.reset(new FormFactorDWBA(*ff_pair.first));
        } else
            P_ff_framework.reset(ff_pair.first->clone());

        size_t layer_index = ff_pair.second;
        const HomogeneousMaterial* p_layer_material = mp_multilayer->layer(layer_index)->material();
        P_ff_framework->setAmbientMaterial(*p_layer_material);

        auto part = FormFactorCoherentPart(P_ff_framework.release());
        part.setSpecularInfo(mp_fresnel_map, layer_index);

        P_result->addCoherentPart(part);
    }
    return P_result.release();
}

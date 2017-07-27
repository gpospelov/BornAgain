// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SampleProvider.cpp
//! @brief     Implements class SampleProvider.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleProvider.h"
#include "MultiLayer.h"
#include <cassert>

SampleProvider::SampleProvider()
{
}

SampleProvider::SampleProvider(const SampleProvider& other)
{
    if (other.m_multilayer)
        setSample(*other.m_multilayer);

    if(other.m_sample_builder)
        setSampleBuilder(other.m_sample_builder.builder());
}

SampleProvider& SampleProvider::operator=(const SampleProvider& other)
{
    if ( this != &other ) {
        SampleProvider tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void SampleProvider::setSample(const MultiLayer& multilayer)
{
    m_multilayer.reset(multilayer.clone());
    m_multilayer->setParent(parent());
    m_sample_builder.reset();
}

void SampleProvider::setSampleBuilder(const std::shared_ptr<IMultiLayerBuilder> sample_builder)
{
    m_sample_builder.setSampleBuilder(sample_builder);
    m_sample_builder.setParent(parent());
    m_multilayer.reset();
}

//! Returns current sample.

const MultiLayer* SampleProvider::sample() const
{
    return m_multilayer.get();
}

//! Generates new sample if sample builder defined.

void SampleProvider::updateSample()
{
    if(m_sample_builder)
        m_multilayer = m_sample_builder.createMultiLayer();

    if (!m_multilayer)
        throw std::runtime_error("SampleProvider::updateSample() -> Error. No sample.");
}

//! Returns a child for GISAS simulation. If sample builder is defined, the result will
//! be a special node, presenting a builder. Is no sample builder defined, the
//! result will be current multi layer.

//const INode* SampleProvider::provideChild(INode* parent)
//{
//    INode* result(nullptr);

//    if (m_sample_builder) {
//        result = &m_sample_builder;
//    } else {
//        result = m_multilayer.get();
//    }

//    // Before returning a child, its parent will be set.
//    if(result)
//        result->setParent(parent);
//    return result;
//}

std::vector<const INode*> SampleProvider::getChildren() const
{
    std::vector<const INode*> result;
    if (m_sample_builder) {
        result.push_back(&m_sample_builder);
    } else {
        if(m_multilayer)
            result.push_back(m_multilayer.get());
    }
    return result;
}

void SampleProvider::setParent(const INode* newParent)
{
    INode::setParent(newParent);
    if ( m_sample_builder) {
        m_sample_builder.setParent(parent());
    } else {
        if (m_multilayer)
            m_multilayer->setParent(parent());
    }
}

void SampleProvider::swapContent(SampleProvider& other)
{
    std::swap(m_multilayer, other.m_multilayer);
    std::swap(m_sample_builder, other.m_sample_builder);
}




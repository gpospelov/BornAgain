// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/SamplePreprocessor.cpp
//! @brief     Implements class SamplePreprocessor
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SamplePreprocessor.h"
#include "ICompositeIterator.h"
#include "ParticleCollection.h"



SamplePreprocessor::SamplePreprocessor()
    : mp_root(0)
    , m_it(0)
{
}

void SamplePreprocessor::process(ISample *p_sample)
{
    if (!p_sample) return;
    // If a sample object was replaced, the whole procedure should
    // start again to avoid having conflicts in the iterator
    bool replacement_occured = true;
    while (replacement_occured) {
        reset(p_sample);
        // First preprocess the root of the ISample tree:
        replacement_occured = p_sample->preprocess();
        if (replacement_occured) {
            continue;
        }
        if (mp_root) {
            while (!m_it.is_done()) {
                replacement_occured = processSingle(m_it.get_current());
                if (replacement_occured) {
                    break;
                }
                next();
            }
        }
    }
}

bool SamplePreprocessor::processSingle(ISample *p_child)
{
    return p_child->preprocess();
}

void SamplePreprocessor::reset(ISample *p_sample)
{
    clear();
    const ICompositeSample *composite = p_sample->getCompositeSample();
    if (!composite) return;
    mp_root = p_sample;
    m_it = composite->createIterator();
    m_it.first();
}

void SamplePreprocessor::next()
{
    m_it.next();
}

void SamplePreprocessor::clear()
{
    mp_root = 0;
    m_it = ICompositeIterator(0);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/SamplePreprocessor.h
//! @brief     Defines class SamplePreprocessor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEPREPROCESSOR_H
#define SAMPLEPREPROCESSOR_H

#include "ISample.h"
#include "ICompositeIterator.h"

//! @class SamplePreprocessor
//! @ingroup tools_internal
//! @brief Class that preprocesses an ISample object before actual simulation

class SamplePreprocessor
{
public:
    SamplePreprocessor();
    virtual ~SamplePreprocessor() {}

    void process(ISample *p_sample);
private:
    bool processSingle(ISample *p_child);
    void reset(ISample *p_sample);
    void next();
    void clear();
    ISample *mp_root;
    ICompositeIterator m_it;
};

#endif // SAMPLEPREPROCESSOR_H



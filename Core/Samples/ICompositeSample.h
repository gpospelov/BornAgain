// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/ICompositeSample.h
//! @brief     Declares interface class ICompositeSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPOSITESAMPLE_H
#define ICOMPOSITESAMPLE_H

#include "ISample.h"
#include <list>

//! @class ICompositeSample
//! @ingroup samples_internal
//! @brief Interface to describe the tree-like composition of samples

class BA_CORE_API_ ICompositeSample : public ISample
{
public:
    ICompositeSample() {}
    virtual ~ICompositeSample() {}

    ICompositeSample *clone() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! Registers child in the container.
    virtual void registerChild(ISample *sample);

    //! Removes registered child from the container
    virtual void deregisterChild(ISample *sample);

    //! Returns child pointer by index (with range checking)
    ISample *operator[](size_t index);

    //! Returns child pointer by index (with range checking)
    const ISample *operator[](size_t index) const;

    //! Returns a vector of children (const).
    virtual std::vector<const ISample*> getChildren() const;

    //! Returns number of children.
    virtual size_t size() const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

private:
    //! Check child index
    bool childIndexInRange(size_t index) const;

    //! List of registered children.
    std::vector<ISample*> m_samples;
};

inline void ICompositeSample::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

inline size_t ICompositeSample::size() const
{
    return m_samples.size();
}

#endif // ICOMPOSITESAMPLE_H



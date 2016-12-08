// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INode.h
//! @brief     Defines class INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INODE_H
#define INODE_H

#include "IParameterized.h"
#include <vector>

class ISampleVisitor;

//! Base class for tree-like structures containing parameterized objects.
//! @ingroup tools_internal

class BA_CORE_API_ INode : public IParameterized
{
public:
    INode(){}
    virtual ~INode(){}

    //! Calls the ISampleVisitor's visit method.
    virtual void accept(ISampleVisitor* p_visitor) const=0;

    //! Returns multiline string representing tree structure below the node.
    virtual std::string to_str() const;

    //! Registers child in the container.
    void registerChild(INode* sample);

    //! Removes registered child from the container
    void deregisterChild(INode *sample);

    //! Returns a vector of children (const).
    virtual std::vector<const INode*> getChildren() const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const;

private:
    //! List of registered children.
    std::vector<INode*> m_samples;
};

#endif // INODE_H

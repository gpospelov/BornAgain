// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INode.h
//! @brief     Defines class INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INODE_H
#define INODE_H

#include "IParameterized.h"
#include "INodeVisitor.h"
#include <vector>
#include <memory>

//! Base class for tree-like structures containing parameterized objects.
//! @ingroup tools_internal

class BA_CORE_API_ INode : public IParameterized
{
public:
    INode();
    virtual ~INode(){}

    //! Calls the INodeVisitor's visit method
    virtual void accept(INodeVisitor* visitor) const=0;

    //! Returns multiline string representing tree structure below the node.
    virtual std::string treeToString() const;

    void registerChild(INode* node);

    //! Returns a vector of children (const).
    virtual std::vector<const INode*> getChildren() const;

    void setParent(const INode* parent);
    const INode* parent() const;
    INode* parent();

    //! Returns copyNumber of child, which takes into account existence of children with same name.
    int copyNumber(const INode* node) const;

    //! Returns display name, composed from the name of node and it's copy number.
    std::string displayName() const;

    //! Creates new parameter pool, with all local parameters and those of its children.
    ParameterPool* createParameterTree() const;

private:
    const INode* m_parent;
};

template <class T>
std::vector<const INode*>& operator<<(std::vector<const INode*>& v_node,
                                      const std::unique_ptr<T>& node)
{
    if (node)
        v_node.push_back(node.get());
    return v_node;
}

template <class T>
std::vector<const INode*>& operator<<(std::vector<const INode*>&& v_node,
                                      const std::unique_ptr<T>& node)
{
    if (node)
        v_node.push_back(node.get());
    return v_node;
}

inline std::vector<const INode*>& operator<<(std::vector<const INode*>& v_node,
                                             const std::vector<const INode*>& other)
{
    v_node.insert(v_node.end(), other.begin(), other.end());
    return v_node;
}

inline std::vector<const INode*>& operator<<(std::vector<const INode*>&& v_node,
                                             const std::vector<const INode*>& other)
{
    v_node.insert(v_node.end(), other.begin(), other.end());
    return v_node;
}

#endif // INODE_H

#ifndef INODETEST_H
#define INODETEST_H

#include "INode.h"
#include "NodeUtils.h"
#include "Exceptions.h"
#include <memory>

namespace {
    const std::string test_class_name = "TestClass";
    const std::string another_test_class_name = "AnotherTestClass";
}

class INodeTest : public ::testing::Test
{
public:
    class TestClass : public INode {
    public:        
        TestClass(const std::string& name = test_class_name) { setName(name); }
        virtual ~TestClass() {for(auto child : m_nodes) delete child;}
        void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }
        void appendChild(INode *node) { m_nodes.push_back(node); registerChild(node); }
        virtual std::vector<const INode*> getChildren() const
        {
            return {m_nodes.begin(), m_nodes.end()};
        }

        std::vector<INode *> m_nodes;
    };

protected:
    INodeTest(){}
    virtual ~INodeTest(){}
};

TEST_F(INodeTest, initialState)
{
    INodeTest::TestClass node;
    EXPECT_EQ(node.getChildren().size(), 0u);
    EXPECT_EQ(node.parent(), nullptr);
}

TEST_F(INodeTest, appendChild)
{
    INodeTest::TestClass node;

    INodeTest::TestClass* child0 = new INodeTest::TestClass();

    // inserting single child
    node.appendChild(child0);

    // accessing vector of children
    auto children = node.getChildren();
    EXPECT_EQ(children.size(), 1u);
    EXPECT_TRUE(std::find(children.begin(), children.end(), child0) != children.end());
}

//! Checks change of parentship on insert/detach.

TEST_F(INodeTest, parentship)
{
    INodeTest::TestClass node;
    EXPECT_EQ(node.parent(), nullptr);

    INodeTest::TestClass *child = new INodeTest::TestClass();
    node.appendChild(child);
    EXPECT_EQ(child->parent(), &node);
}

//! Checks the display name.

TEST_F(INodeTest, displayName)
{
    INodeTest::TestClass node;
    EXPECT_EQ(node.getName(), test_class_name);
    EXPECT_EQ(node.getName(), node.displayName());

    // Adding first child and checking its displayName
    INodeTest::TestClass *child0 = new INodeTest::TestClass();
    node.appendChild(child0);
    EXPECT_EQ(child0->displayName(), test_class_name);

    // Adding second child with same name and checking change in displayName
    INodeTest::TestClass *child1 = new INodeTest::TestClass();
    node.appendChild(child1);
    EXPECT_EQ(child0->displayName(), test_class_name+"0");
    EXPECT_EQ(child1->displayName(), test_class_name+"1");

    // Adding second child with another name and checking
    INodeTest::TestClass *child2 = new INodeTest::TestClass(another_test_class_name);
    node.appendChild(child2);
    EXPECT_EQ(child2->displayName(), another_test_class_name);
}

TEST_F(INodeTest, nodePath)
{
    INodeTest::TestClass root("root");
    EXPECT_EQ(NodeUtils::nodePath(root), "/root");

    // adding first child
    INodeTest::TestClass *child0 = new INodeTest::TestClass("child");
    root.appendChild(child0);
    EXPECT_EQ(NodeUtils::nodePath(*child0), "/root/child");

    // adding second child with the same name
    INodeTest::TestClass *child1 = new INodeTest::TestClass("child");
    root.appendChild(child1);
    EXPECT_EQ(NodeUtils::nodePath(*child0), "/root/child0");
    EXPECT_EQ(NodeUtils::nodePath(*child1), "/root/child1");

    // adding grandchild
    INodeTest::TestClass *grandchild = new INodeTest::TestClass("grandchild");
    child0->appendChild(grandchild);
    EXPECT_EQ(NodeUtils::nodePath(*grandchild), "/root/child0/grandchild");
}


#endif // INODETEST_H

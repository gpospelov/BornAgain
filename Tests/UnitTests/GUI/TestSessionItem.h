#include "google_test.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "GUIHelpers.h"

class TestSessionItem : public ::testing::Test
{
public:
    // TODO refactor whole unit test together with SessionTagInfo refactoring
    ~TestSessionItem();
    void verify_get_item(SessionItem* item, const QString& tag, QVector<SessionItem*> list)
    {
        if (list.size() > 0)
            EXPECT_TRUE(item->getItem(tag) == list[0]);
        else
            EXPECT_TRUE(item->getItem(tag) == nullptr);
        auto items = item->getItems(tag);
        EXPECT_TRUE(items.size() == list.size());
        EXPECT_TRUE(items == list);
        EXPECT_TRUE(item->getItem(tag, -1) == nullptr);
        EXPECT_TRUE(item->getItem(tag, list.size()) == nullptr);
        for (int i = 0; i < list.size(); i++) {
            EXPECT_TRUE(item->getItem(tag, i) == list[i]);
        }
    }
};

TestSessionItem::~TestSessionItem() = default;

TEST_F(TestSessionItem, initialState)
{
    const QString modeltype = "This is the model type";
    std::unique_ptr<SessionItem> item(new SessionItem(modeltype));
    EXPECT_TRUE(item->modelType() == modeltype);
    EXPECT_TRUE(item->model() == nullptr);
    EXPECT_TRUE(item->parent() == nullptr);
    // TODO add some more tests for children, roles, tags ...
}

TEST_F(TestSessionItem, defaultTag)
{
    const QString modelType = "TestItem";

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));
    EXPECT_TRUE(item->defaultTag().isEmpty());

    // insertion without tag is forbidden
    SessionItem* child = new SessionItem(modelType);
    EXPECT_THROW(item->insertItem(0, child), GUIHelpers::Error);
    delete child;
    EXPECT_EQ(item->numberOfChildren(), 0);
}

TEST_F(TestSessionItem, singleTagAndItems)
{
    const QString tag1 = "TAG1";
    const QString modelType = "TestItem";

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));

    // before using a tag, it must be registered
    EXPECT_TRUE(item->registerTag(tag1));
    EXPECT_TRUE(item->isTag(tag1));

    // register twice returns false
    EXPECT_FALSE(item->registerTag(tag1));

    // register empty string returns false
    EXPECT_FALSE(item->registerTag(""));

    // inserting single item
    SessionItem* child = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(0, child, tag1));
    // double insertion is forbidden
    EXPECT_THROW(item->insertItem(0, child, tag1), GUIHelpers::Error);
    EXPECT_TRUE(child->parent() == item.get());
    EXPECT_EQ(item->numberOfChildren(), 1);

    // checking list of children
    auto expected = QVector<SessionItem*>() << child;
    EXPECT_EQ(item->children(), expected);

    // checking getItems method
    EXPECT_EQ(item->getItems(), QVector<SessionItem*>());
    EXPECT_EQ(item->getItems(tag1), expected);

    // checking getItem method
    EXPECT_EQ(item->getItem(tag1), child);

    // adding second child at the beginning
    SessionItem* child1 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(0, child1, tag1));

    expected = QVector<SessionItem*>() << child1 << child;
    EXPECT_EQ(item->children(), expected);
    EXPECT_EQ(item->getItems(), QVector<SessionItem*>());
    EXPECT_EQ(item->getItems(tag1), expected);
    EXPECT_EQ(item->getItem(tag1, 0), child1);
    EXPECT_EQ(item->getItem(tag1, 1), child);
    EXPECT_THROW(item->getItem(tag1, 2), GUIHelpers::Error);

    // adding third item at the end
    SessionItem* child2 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(-1, child2, tag1));
    expected = QVector<SessionItem*>() << child1 << child << child2;
    EXPECT_EQ(item->children(), expected);
    EXPECT_EQ(item->getItems(), QVector<SessionItem*>());
    EXPECT_EQ(item->getItems(tag1), expected);
    EXPECT_EQ(item->getItem(tag1, 0), child1);
    EXPECT_EQ(item->getItem(tag1, 1), child);
    EXPECT_EQ(item->getItem(tag1, 2), child2);
}

TEST_F(TestSessionItem, insertAndTake)
{
    const QString tag1 = "TAG1";
    const QString modelType = "TestItem";

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));
    EXPECT_TRUE(item->registerTag(tag1));

    // inserting two children
    SessionItem* child1 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(-1, child1, tag1));
    SessionItem* child2 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(-1, child2, tag1));
    auto expected = QVector<SessionItem*>() << child1 << child2;
    EXPECT_EQ(item->getItems(tag1), expected);

    // taking first
    SessionItem* first = item->takeItem(0, tag1);
    EXPECT_EQ(first, child1);
    EXPECT_TRUE(first->parent() == nullptr);
    expected = QVector<SessionItem*>() << child2;
    EXPECT_EQ(item->getItems(tag1), expected);
    delete first;
}

TEST_F(TestSessionItem, tagWithLimits)
{
    const QString tag1 = "TAG1";
    const QString modelType = "TestItem";
    const int maxItems(3);

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));
    EXPECT_TRUE(item->registerTag(tag1, 0, maxItems));

    QVector<SessionItem*> expected;
    for (int i=0; i<maxItems; ++i) {
        auto child = new SessionItem(modelType);
        expected.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag1));
    }
    auto extra = new SessionItem(modelType);
    EXPECT_THROW(item->insertItem(-1, extra, tag1), GUIHelpers::Error);
}

TEST_F(TestSessionItem, tagsAndModelTypes)
{
    const QString tag1 = "tag1";
    const QString tag2 = "tag2";
    const QString modelType1 = "ModelType1";
    const QString modelType2 = "ModelType2";
    const int maxItems1(3);
    const int maxItems2(4);

    std::unique_ptr<SessionItem> item(new SessionItem("ModelType"));
    EXPECT_TRUE(item->registerTag(tag1, 0, -1, QStringList() << modelType1));
    EXPECT_TRUE(item->registerTag(tag2, 0, -1, QStringList() << modelType2));

    // adding two types of items under different tags
    QVector<SessionItem*> expected1;
    for (int i=0; i<maxItems1; ++i) {
        auto child = new SessionItem(modelType1);
        expected1.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag1));
    }

    QVector<SessionItem*> expected2;
    for (int i=0; i<maxItems2; ++i) {
        auto child = new SessionItem(modelType2);
        expected2.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag2));
    }

    // checking list of children separated according tag
    EXPECT_EQ(item->getItems(tag1), expected1);
    EXPECT_EQ(item->getItems(tag2), expected2);

    // removing child from tag1, tag2 should remain intact
    auto taken = item->takeItem(0, tag1);
    EXPECT_EQ(taken, expected1.front());
    EXPECT_EQ(item->getItems(tag2), expected2);
}

TEST_F(TestSessionItem, takeRow)
{
    const QString tag1 = "tag1";
    const QString tag2 = "tag2";
    const QString modelType1 = "ModelType1";
    const QString modelType2 = "ModelType2";
    const int maxItems1(3);
    const int maxItems2(4);

    std::unique_ptr<SessionItem> item(new SessionItem("ModelType"));
    EXPECT_TRUE(item->registerTag(tag1, 0, -1, QStringList() << modelType1));
    EXPECT_TRUE(item->registerTag(tag2, 0, -1, QStringList() << modelType2));

    // adding two types of items under different tags
    QVector<SessionItem*> expected1;
    for (int i=0; i<maxItems1; ++i) {
        auto child = new SessionItem(modelType1);
        expected1.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag1));
    }

    QVector<SessionItem*> expected2;
    for (int i=0; i<maxItems2; ++i) {
        auto child = new SessionItem(modelType2);
        expected2.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag2));
    }

    auto taken1 = item->takeRow(1);
    EXPECT_EQ(taken1, expected1.at(1));
    delete taken1;

    auto taken2 = item->takeRow(maxItems1-1); // one item less already
    EXPECT_EQ(taken2, expected2.at(0));
    delete taken2;

    expected1.removeAll(taken1);
    expected2.pop_front();

    EXPECT_EQ(item->getItems(tag1), expected1);
    EXPECT_EQ(item->getItems(tag2), expected2);
}

TEST_F(TestSessionItem, test_tags)
{
//    const QString modeltype = "This is the model type";
//    const QString tag1 = "TAG1";
//    const QString tag2 = "TAG2";
//    const QString tag3 = "TAG3";
//    const QString tag4 = "TAG4";
//    std::unique_ptr<SessionItem> item(new SessionItem(modeltype));

//    // before using a tag, it must be registered
//    EXPECT_TRUE(item->registerTag(tag1));

//    // register twice returns false
//    EXPECT_TRUE(item->registerTag(tag1) == false);

//    // register empty string returns false
//    EXPECT_TRUE(item->registerTag("") == false);

//    // now we insert one element at the beginning
//    SessionItem* child = new SessionItem(modeltype);
//    EXPECT_TRUE(item->insertItem(0, child, tag1));

//    // insertion out of range is forbidden
//    EXPECT_TRUE(item->insertItem(-1, child, tag1) == false);
//    EXPECT_TRUE(item->insertItem(2, child, tag1) == false);

//    // double insertion is forbidden
//    EXPECT_TRUE(item->insertItem(0, child, tag1) == false);

//    // we try to access tagged items
//    QVector<SessionItem*> expected = {child};
//    verify_get_item(item.get(), tag1, expected);

//    // nullptr is not allowed
//    EXPECT_TRUE(item->insertItem(1, nullptr, tag1) == false);
//    verify_get_item(item.get(), tag1, expected);

//    // LIMITS
//    // register tag with limit 0 - 1
//    EXPECT_TRUE(item->registerTag(tag2, 0, 1));

//    SessionItem* child2 = new SessionItem(modeltype);
//    EXPECT_TRUE(item->insertItem(0, child2, tag2));
//    expected = {child2};
//    verify_get_item(item.get(), tag2, expected);
//    EXPECT_TRUE(item->insertItem(1, child2, tag2) == false);

//    // register tag with limit 0 - 3 (using item 2 - 5)
//    EXPECT_TRUE(item->registerTag(tag3, 0, 4));

//    // add four items
//    QVector<SessionItem*> expected_tag3;
//    for (int i = 0; i < 4; i++) {
//        auto child = new SessionItem(modeltype);
//        expected_tag3.push_back(child);
//        EXPECT_TRUE(item->insertItem(i, child, tag3));
//    }
//    verify_get_item(item.get(), tag3, expected_tag3);

//    // the fifth should fail
//    child = new SessionItem(modeltype);
//    EXPECT_TRUE(item->insertItem(0, child, tag3) == false);
//    delete child;

//    // items should be unchanged
//    verify_get_item(item.get(), tag3, expected_tag3);

//    // register tag with limit 4 - 4 add items to fill up limit
//    EXPECT_TRUE(item->registerTag(tag4, 4, 4));

//    // add four items
//    QVector<SessionItem*> expected_tag4;
//    for (int i = 0; i < 4; i++) {
//        auto child = new SessionItem(modeltype);
//        expected_tag4.push_back(child);
//        EXPECT_TRUE(item->insertItem(i, child, tag4));
//    }
//    verify_get_item(item.get(), tag4, expected_tag4);

//    child = new SessionItem(modeltype);
//    EXPECT_TRUE(item->insertItem(0, child, tag4) == false);
//    delete child;

//    // REMOVAL

//    // tag4 can not be removed
//    SessionItem* last = item->takeItem(3, tag4);
//    EXPECT_TRUE(last == nullptr);
//    verify_get_item(item.get(), tag4, expected_tag4);

//    // remove all from tag3, checking access of tag4
//    for (int i = 3; i >= 0; i--) {
//        last = item->takeItem(i, tag3);
//        EXPECT_TRUE(last == expected_tag3[i]);
//        delete last;
//    }
//    verify_get_item(item.get(), tag4, expected_tag4);
}

TEST_F(TestSessionItem, test_data_roles)
{
    std::unique_ptr<SessionItem> item(new SessionItem("Some model type"));
    item->setData(Qt::DisplayRole, 1234);
    EXPECT_TRUE(item->data(Qt::DisplayRole) == 1234);
    EXPECT_TRUE(item->data(Qt::EditRole) == 1234);
    item->setData(Qt::EditRole, 5432);
    EXPECT_TRUE(item->data(Qt::DisplayRole) == 5432);
    EXPECT_TRUE(item->data(Qt::EditRole) == 5432);
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(item->data(SessionFlags::EndSessionRoles + i).isValid() == false);
        item->setData(SessionFlags::EndSessionRoles + i, i);
        EXPECT_TRUE(item->data(SessionFlags::EndSessionRoles + i) == i);
    }
}

TEST_F(TestSessionItem, test_model_types)
{
    const QString model1 = "modeltype 1";
    const QString model2 = "modeltype 2";
    const QString model3 = "modeltype 3";
    const QString model4 = "modeltype 4";
    const QString model5 = "modeltype 5";

    std::unique_ptr<SessionItem> item(new SessionItem("modeltype does not matter"));
    EXPECT_TRUE(item->registerTag("Tag1", 0, -1, QStringList() << model1 << model2));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model1), "Tag1"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model2), "Tag1"));

    auto child = new SessionItem(model3);
    EXPECT_THROW(item->insertItem(0, child, "Tag1"), GUIHelpers::Error);
    delete child;

    child = new SessionItem(model4);
    EXPECT_THROW(item->insertItem(0, child, "Tag1"), GUIHelpers::Error);
    delete child;

    child = new SessionItem(model5);
    EXPECT_THROW(item->insertItem(0, child, "Tag1"), GUIHelpers::Error);
    delete child;

    EXPECT_TRUE(item->registerTag("Tag2", 0, -1, QStringList() << model3 << model4 << model5));

    child = new SessionItem(model1);
    EXPECT_THROW(item->insertItem(0, child, "Tag2"), GUIHelpers::Error);
    delete child;

    child = new SessionItem(model2);
    EXPECT_THROW(item->insertItem(0, child, "Tag2"), GUIHelpers::Error);
    delete child;

    EXPECT_TRUE(item->insertItem(0, new SessionItem(model3), "Tag2"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model4), "Tag2"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model5), "Tag2"));
}

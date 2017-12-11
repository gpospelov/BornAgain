#include "google_test.h"
#include "SessionItem.h"
#include "SessionModel.h"

class TestSessionItem : public ::testing::Test
{
public:
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

TEST_F(TestSessionItem, test_constructor)
{
    const QString modeltype = "This is the model type";
    SessionItem* item = new SessionItem(modeltype);
    EXPECT_TRUE(item->modelType() == modeltype);
    EXPECT_TRUE(item->model() == nullptr);
    EXPECT_TRUE(item->parent() == nullptr);
    // TODO add some more tests for children, roles, tags ...
}

TEST_F(TestSessionItem, test_tags)
{
    const QString modeltype = "This is the model type";
    const QString tag1 = "TAG1";
    const QString tag2 = "TAG2";
    const QString tag3 = "TAG3";
    const QString tag4 = "TAG4";
    SessionItem* item = new SessionItem(modeltype);
    QVector<SessionItem*> items;
    for (int i = 0; i < 10; i++)
        items.append(new SessionItem(modeltype));

    // before using a tag, it must be registered
    EXPECT_TRUE(item->registerTag(tag1));

    // register twice returns false
    EXPECT_TRUE(item->registerTag(tag1) == false);

    // register empty string returns false
    EXPECT_TRUE(item->registerTag("") == false);

    // now we insert one element at the beginning
    EXPECT_TRUE(item->insertItem(0, items[0], tag1));

    // insertion out of range is forbidden
    EXPECT_TRUE(item->insertItem(-1, items[0], tag1) == false);
    EXPECT_TRUE(item->insertItem(2, items[0], tag1) == false);

    // double insertion is forbidden
    EXPECT_TRUE(item->insertItem(0, items[0], tag1) == false);

    // we try to access tagged items
    verify_get_item(item, tag1, items.mid(0, 1));

    // nullptr is not allowed
    EXPECT_TRUE(item->insertItem(1, nullptr, tag1) == false);
    verify_get_item(item, tag1, items.mid(0, 1));

    // LIMITS
    // register tag with limit 0 - 1
    EXPECT_TRUE(item->registerTag(tag2, 0, 1));

    EXPECT_TRUE(item->insertItem(0, items[1], tag2));
    verify_get_item(item, tag2, items.mid(1, 1));
    EXPECT_TRUE(item->insertItem(1, items[1], tag2) == false);

    // register tag with limit 0 - 3 (using item 2 - 5)
    EXPECT_TRUE(item->registerTag(tag3, 0, 4));

    // add four items
    for (int i = 0; i < 4; i++) {
        EXPECT_TRUE(item->insertItem(i, items[2 + i], tag3));
        verify_get_item(item, tag3, items.mid(2, i + 1));
    }

    // the fifth should fail
    EXPECT_TRUE(item->insertItem(0, items[6], tag3) == false);

    // items should be unchanged
    verify_get_item(item, tag3, items.mid(2, 4));

    // register tag with limit 4 - 4 add items to fill up limit
    EXPECT_TRUE(item->registerTag(tag4, 4, 4));

    // add four items
    for (int i = 0; i < 4; i++) {
        EXPECT_TRUE(item->insertItem(i, items[6 + i], tag4));
        verify_get_item(item, tag4, items.mid(6, i + 1));
    }
    EXPECT_TRUE(item->insertItem(0, items[6], tag4) == false);

    // REMOVAL

    // tag4 can not be removed
    SessionItem* last = item->takeItem(3, tag4);
    EXPECT_TRUE(last == nullptr);
    verify_get_item(item, tag4, items.mid(6, 4));

    // remove all from tag3, checking access of tag4
    for (int i = 0; i < 4; i++) {
        last = item->takeItem(3 - i, tag3);
        EXPECT_TRUE(last == items[5 - i]);
        verify_get_item(item, tag3, items.mid(2, 3 - i));
        verify_get_item(item, tag4, items.mid(6, 4));
    }

    delete item;
}

TEST_F(TestSessionItem, test_data_roles)
{
    SessionItem* item = new SessionItem("Some model type");
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

    SessionItem* item = new SessionItem("modeltype does not matter");
    EXPECT_TRUE(item->registerTag("Tag1", 0, -1, QStringList() << model1 << model2));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model1), "Tag1"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model2), "Tag1"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model3), "Tag1") == false);
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model4), "Tag1") == false);
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model5), "Tag1") == false);
    EXPECT_TRUE(item->registerTag("Tag2", 0, -1, QStringList() << model3 << model4 << model5));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model1), "Tag2") == false);
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model2), "Tag2") == false);
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model3), "Tag2"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model4), "Tag2"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model5), "Tag2"));
}

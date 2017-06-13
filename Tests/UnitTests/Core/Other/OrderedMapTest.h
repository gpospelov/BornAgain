#include "OrderedMap.h"
#include "INamed.h"

class OrderedMapTest : public ::testing::Test
{
protected:
    OrderedMapTest(){}
    virtual ~OrderedMapTest(){}
};


TEST_F(OrderedMapTest, OrderedMapInsert)
{
    OrderedMap<int, std::string> omap;
    EXPECT_EQ( size_t(0), omap.size());

    std::vector<int> keys = {3, 2, 1};
    std::vector<std::string> values = {"aaa", "bbb", "ccc"};

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);
    EXPECT_EQ( size_t(3), omap.size());

    // check that <key,value> are stored in the order of insertion and that there is no sorting
    // along key as in normal map
    int npos(0);
    for(OrderedMap<int, std::string>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    omap.clear();
    EXPECT_EQ( size_t(0), omap.size());
}

TEST_F(OrderedMapTest, OrderedMapErase)
{
    OrderedMap<std::string, double> omap;

    std::vector<std::string> keys = {"ccc", "bbb", "aaa"};
    std::vector<double> values = {2.0, 1.0, 3.0};

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);

    int npos(0);
    for(OrderedMap<std::string, double>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    EXPECT_EQ(size_t(3), omap.size());

    EXPECT_EQ(omap.erase("ddd"), size_t(0));
    EXPECT_EQ(size_t(3), omap.size());

    EXPECT_EQ(omap.erase("bbb"), size_t(1));
    EXPECT_EQ(size_t(2), omap.size());

    keys = {"ccc", "aaa"};
    values = {2.0, 3.0};
    npos = 0;
    for(OrderedMap<std::string, double>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    EXPECT_EQ(omap.erase("ccc"), size_t(1));
    EXPECT_EQ(omap.erase("aaa"), size_t(1));
    EXPECT_EQ(size_t(0), omap.size());

    omap.insert("ddd", 99.0);
    EXPECT_EQ(size_t(1), omap.size());
}

TEST_F(OrderedMapTest, OrderedMapGetValue)
{
    OrderedMap<const INamed *, INamed *> omap;

    std::unique_ptr<INamed> key1(new INamed("key1"));
    std::unique_ptr<INamed> key2(new INamed("key2"));
    std::unique_ptr<INamed> key3(new INamed("key3"));
    std::unique_ptr<INamed> val1(new INamed("val1"));
    std::unique_ptr<INamed> val2(new INamed("val2"));
    std::unique_ptr<INamed> val3(new INamed("val3"));

    omap.insert(key1.get(), val1.get());
    omap.insert(key2.get(), val2.get());
    omap.insert(key3.get(), val3.get());

    EXPECT_EQ(omap.value(key1.get()), val1.get());
    EXPECT_EQ(omap.value(key2.get()), val2.get());
    EXPECT_EQ(omap.value(key3.get()), val3.get());
}

TEST_F(OrderedMapTest, OrderedMapFind)
{
    OrderedMap<const INamed *, std::string> omap;

    std::unique_ptr<INamed> n1(new INamed("named1"));
    std::unique_ptr<INamed> n2(new INamed("named2"));
    std::unique_ptr<INamed> n3(new INamed("named3"));
    std::unique_ptr<INamed> n4(new INamed("named4"));

    omap.insert(n1.get(), "aaa");
    omap.insert(n2.get(), "bbb");
    omap.insert(n3.get(), "ccc");
    EXPECT_EQ( size_t(3), omap.size());

    EXPECT_EQ(omap.find(n1.get())->first, n1.get());
    EXPECT_EQ(omap.find(n1.get())->first->getName(), "named1");
    EXPECT_EQ(omap.find(n1.get())->second, std::string("aaa"));

    EXPECT_EQ(omap.find(n2.get())->first, n2.get());
    EXPECT_EQ(omap.find(n2.get())->first->getName(), "named2");
    EXPECT_EQ(omap.find(n2.get())->second, std::string("bbb"));

    EXPECT_EQ(omap.find(n3.get())->first, n3.get());
    EXPECT_EQ(omap.find(n3.get())->first->getName(), "named3");
    EXPECT_EQ(omap.find(n3.get())->second, std::string("ccc"));

    EXPECT_EQ(omap.find(n4.get()), omap.end());
}

TEST_F(OrderedMapTest, OrderedMapReInsert)
{
    std::unique_ptr<INamed> P_n1(new INamed("named1"));
    std::unique_ptr<INamed> P_n2(new INamed("named2"));
    std::unique_ptr<INamed> P_n3(new INamed("named3"));

    OrderedMap<INamed *, double> omap;
    omap.insert(P_n1.get(), 1.0);
    omap.insert(P_n2.get(), 2.0);
    omap.insert(P_n3.get(), 3.0);
    EXPECT_EQ(omap.size(), size_t(3));

    omap.insert(P_n2.get(), 99.0);
    EXPECT_EQ(omap.size(), size_t(3));
    EXPECT_EQ(omap.value(P_n2.get()), 99.0);
}

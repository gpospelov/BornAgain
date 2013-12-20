#ifndef TESTBUGS_H
#define TESTBUGS_H

#include "IApplicationTest.h"


class TestBugs : public IApplicationTest
{
public:
    TestBugs();
    virtual ~TestBugs(){}

    virtual void execute();

    void test_item339();

};

#endif // TESTBUGS_H

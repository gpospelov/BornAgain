#ifndef TESTBUGS_H
#define TESTBUGS_H

#include "IFunctionalTest.h"


class TestBugs : public IFunctionalTest
{
public:
    TestBugs();
    virtual ~TestBugs(){}

    virtual void execute();

    void test_item339();

};

#endif // TESTBUGS_H

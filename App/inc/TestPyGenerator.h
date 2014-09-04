#ifndef TESTPYGENERATOR_H
#define TESTPYGENERATOR_H

#include "IApplicationTest.h"

class MultiLayer;

class TestPyGenerator : public IApplicationTest
{
public:
    TestPyGenerator();
    virtual ~TestPyGenerator(){}
    virtual void execute();

private:
    MultiLayer *makeSample();
    MultiLayer *m_sample;
};

#endif //


#ifndef _IFUNCTIONALTEST_H
#define _IFUNCTIONALTEST_H


#include "OutputData.h"




//! basic functional test
class FunctionalTest
{
public:
    IFunctionalTest() : m_result(0), m_reference(0) {}
    ~IFunctionalTest() { delete m_result; delete m_reference; }

    const OutputData<double> *getResult() const { return m_result; }
    void setResult(OutputData<double> *result) { m_result = result; }

    const OutputData<double> *getReference() const { return m_reference; }
    void setReference(OutputData<double> *reference) { m_reference = reference; }

private:
    OutputData<double> *m_result;
    OutputData<double> *m_reference;
};




#endif

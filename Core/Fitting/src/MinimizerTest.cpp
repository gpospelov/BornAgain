#include "MinimizerTest.h"


// run minimization
void MinimizerTest::minimize()
{
    std::vector<double > buffer;
    buffer.resize(m_values.size(), 0.0);
    for(std::map<int, double >::iterator it=m_values.begin(); it!= m_values.end(); ++it ) {
        buffer[it->first] = it->second;
        std::cout << " minimize(): " << it->first << " " << it->second << std::endl;
    }
    std::cout << "TestMinimizer::minimize() -> Info. Calling fcn" << std::endl;
    m_fcn(&buffer[0]);
}


// return pointer to the parameters values at the minimum
double MinimizerTest::getValueOfVariableAtMinimum(size_t index) const
{
    std::map<int, double >::const_iterator pos = m_values.find((int)index);
    if(pos != m_values.end()){
        return pos->second;
    } else {
        throw LogicErrorException("TestMinimizer::getValueOfVariableAtMinimum() -> Not found!");
    }
}

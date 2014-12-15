#include "MultiLayerRTCoefficients.h"



MultiLayerRTCoefficients::~MultiLayerRTCoefficients()
{
    for(std::vector<ILayerRTCoefficients *>::iterator it = m_data.begin(); it!= m_data.end(); ++it) {
        delete (*it);
    }
}

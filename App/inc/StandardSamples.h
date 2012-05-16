#ifndef STANDARDSAMPLES_H
#define STANDARDSAMPLES_H

#include "ISample.h"
#include "SampleFactory.h"


namespace StandardSamples{

ISample *AirOnSubstrate();
ISample *SubstrateOnSubstrate();
ISample *SimpleMultilayer();
ISample *MultilayerWithRoughness();

}



#endif // STANDARDSAMPLES_H

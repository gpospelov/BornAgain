#ifndef STANDARDSAMPLES_H
#define STANDARDSAMPLES_H

#include "ISample.h"
#include "SampleFactory.h"


namespace StandardSamples{

ISample *AirOnSubstrate();
const int id_AirOnSubstrate = 0;
const bool reg_AirOnSubstrate = SampleFactory::instance().RegisterSample(id_AirOnSubstrate, AirOnSubstrate);

ISample *SubstrateOnSubstrate();
const int id_SubstrateOnSubstrate = 1;
const bool reg_SubstrateOnSubstrate = SampleFactory::instance().RegisterSample(id_SubstrateOnSubstrate, SubstrateOnSubstrate);

ISample *SimpleMultilayer();
const int id_SimpleMultilayer = 2;
const bool reg_SimpleMultilayer = SampleFactory::instance().RegisterSample(id_SimpleMultilayer, SimpleMultilayer);

}



#endif // STANDARDSAMPLES_H

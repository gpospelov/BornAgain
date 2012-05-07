#ifndef STANDARDSAMPLES_H
#define STANDARDSAMPLES_H

#include "ISample.h"
#include "SampleFactory.h"

//class StandardSample : public ISample
//{
//public:
//    StandardSample();
//};

namespace StandardSamples{

ISample *SampleAirOnSubstrate();
const int Id_AirOnSubstrate = 1;
const bool registered_AirOnSubstrate = SampleFactory::instance().RegisterSample(Id_AirOnSubstrate, SampleAirOnSubstrate);

ISample *SampleSubstrateOnSubstrate();
const int Id_SubstrateOnSubstrate = 1;
const bool registered_SubstrateOnSubstrate = SampleFactory::instance().RegisterSample(Id_SubstrateOnSubstrate, SampleSubstrateOnSubstrate);

}



#endif // STANDARDSAMPLES_H

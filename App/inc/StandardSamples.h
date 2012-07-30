#ifndef STANDARDSAMPLES_H
#define STANDARDSAMPLES_H

#include "ISample.h"
#include "SampleFactory.h"


namespace StandardSamples{

ISample *AirOnSubstrate();
ISample *SubstrateOnSubstrate();
ISample *SimpleMultilayer();
ISample *MultilayerOffspecTestcase1a();
ISample *MultilayerOffspecTestcase1b();
ISample *MultilayerOffspecTestcase2a();
ISample *MultilayerOffspecTestcase2b();
ISample *IsGISAXS9_RotatedPyramid();
ISample *MesoCrystal1();

}



#endif // STANDARDSAMPLES_H

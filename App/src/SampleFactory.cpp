#include "SampleFactory.h"
#include "Exceptions.h"
#include "StandardSamples.h"

#include <iostream>


SampleFactory::SampleFactory()
{
    registerItem("AirOnSubstrate", StandardSamples::AirOnSubstrate);
    registerItem("SubstrateOnSubstrate", StandardSamples::SubstrateOnSubstrate);
    registerItem("SimpleMultilayer", StandardSamples::SimpleMultilayer);
    registerItem("MultilayerWithRoughness", StandardSamples::MultilayerWithRoughness);
}

#include "SampleFactory.h"
#include "Layer.h"


SampleFactory::SampleFactory()
{
    registerItem("Layer",   IFactoryCreateFunction<Layer, ISample>, "some layer");
    registerItem("SampleIsGISAXS9_Rotated",   IFactoryCreateFunction<SampleIsGISAXS9_Rotated, ISample>, "some isgisaxs9 sample");

}



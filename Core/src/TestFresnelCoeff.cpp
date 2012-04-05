#include "TestFresnelCoeff.h"
#include <iostream>

#include "Layer.h"
#include "MultiLayer.h"
#include "HomogeneousMaterial.h"


TestFresnelCoeff::TestFresnelCoeff()
{
    std::cout << "TestFresnelCoeff::TestFresnelCoeff() -> Info." << std::endl;
}



void TestFresnelCoeff::Run()
{
    std::cout << "TestFresnelCoeff::Run() -> Info." << std::endl;

    MultiLayer mySample;

    HomogeneousMaterial mAmbience;

    Layer ag1;
    ag1.setThickness(1500.0);
    ag1.setMaterial( &mAmbience );

    mySample.addLayerWithTopRoughness(&ag1, 0);
}



//mySample.AddLayer( BLayerHomogenious("Ambience", 0.0, 1.0) );
//BLayerHomogenious ag1("Ag1", 1500.,  complex_t(0.99999653774962993,0) );
//BLayerHomogenious cr1("Cr1", 1200.0, complex_t(0.99999701914797656,0) );
//mySample.AddLayer( ag1, cr1, nrepetitions );
//mySample.AddLayer( BLayerHomogenious("Substrate", 0.0, 0.99999692440971188) );

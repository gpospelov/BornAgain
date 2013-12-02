#include "StandardSimulations.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "ResolutionFunction2DSimple.h"
#include "Units.h"

Simulation *StandardSimulations::IsGISAXS01()
{
    SampleBuilderFactory factory;
    ISampleBuilder *builder = factory.createBuilder("isgisaxs01");

    Simulation *result = new Simulation();

    result->setDetectorParameters(
        100,-1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::MesoCrystal01()
{
    SampleBuilderFactory factory;
    ISampleBuilder *builder = factory.createBuilder("mesocrystal01");

    Simulation *result = new Simulation();
    result->setBeamParameters(1.77*Units::angstrom, 0.4*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(5.0090e+12);
//    result->setDetectorResolutionFunction(
//            new ResolutionFunction2DSimple(0.0002, 0.0002));

    result->setSampleBuilder( builder );

    return result;
}


Simulation *StandardSimulations::PolarizedDWBAZeroMag()
{
    SampleBuilderFactory factory;
    ISampleBuilder *builder = factory.createBuilder("PolarizedDWBAZeroMag");

    Simulation *result = new Simulation();

	result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree,
                                     true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

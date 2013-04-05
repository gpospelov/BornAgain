#ifndef PYTHONCORELIST_H
#define PYTHONCORELIST_H

//! list of files to process with Py++

#include "BasicVector3D.h"
#include "Bin.h"
#include "Crystal.h"
#include "DiffuseParticleInfo.h"
#include "FTDistributions.h"
#include "FormFactorBox.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorParallelepiped.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "HomogeneousMaterial.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDecoration.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "IResolutionFunction2D.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "IStochasticParameter.h"
#include "ITransform3D.h"
#include "Instrument.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "Lattice.h"
#include "Lattice2DIFParameters.h"
#include "Lattice2DIFParameters.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"
#include "OutputData.h"
#include "OutputDataIOFactory.h"
#include "ParameterPool.h"
#include "Particle.h"
#include "ParticleBuilder.h"
#include "ParticleCoreShell.h"
#include "ParticleDecoration.h"
#include "ParticleInfo.h"
#include "PositionParticleInfo.h"
#include "PythonOutputData.h"
#include "RealParameterWrapper.h"
#include "ResolutionFunction2DSimple.h"
#include "Rotate3D.h"
#include "Simulation.h"
#include "SimulationParameters.h"
#include "StochasticDoubleGate.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "Types.h"
#include "Units.h"

#include "FormFactorCone.h"
#include "FormFactorEllipsoid.h"
#include "FormFactorFullSpheroid.h"
#include "FormFactorHemiSpheroid.h"
#include "FormFactorPrism6.h"
#include "FormFactorSphere.h"

//! file containig additional exposers
#include "PythonCoreExposer.h"

//namespace pyplusplus {
//    namespace aliases {
//        using namespace Geometry;
//        //typedef Geometry::BasicVector3D<double > kvector_t;
//        typedef BasicVector3D<double > kvector_t;
//        typedef std::vector<kvector_t > vector_kvector_t;
//        typedef BasicVector3D<std::complex<double> > cvector_t;
//        typedef std::vector<cvector_t > vector_cvector_t;
//        typedef std::vector<DiffuseParticleInfo *> vector_DiffuseParticleInfoPtr_t;
//        typedef std::vector<IFormFactor *> vector_IFormFactorPtr_t;
//        typedef ISingleton<MaterialManager> MaterialManagerSingleton_t;
//        typedef StochasticParameter<double> StochasticParameter_t;
//        typedef OutputData<double > ndimdata_t;
////        typedef std::vector<int > vector_integer_t;
////        typedef std::vector<unsigned long int > vector_longinteger_t;
////        static const kvector_t dummy1 = 2.0*kvector_t(0,0,0);
////        static const kvector_t dummy2 = kvector_t(0,0,0)*2.0;
////        static const kvector_t dummy3 = kvector_t(0,0,0)/2.0;
//        //typedef boost::shared_ptr<Geometry::ITransform3D> PTransform3D;
//    }
//}




#endif // PYTHONCOREAPI_H

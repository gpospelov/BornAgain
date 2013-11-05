#include "Python.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION 
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY 
#include "numpy/arrayobject.h"
// the order of 3 guys above is important

#include "RotateZ_3D.pypp.h" 
#include "IFTDistribution2D.pypp.h" 
#include "Detector.pypp.h" 
#include "LatticeBasis.pypp.h" 
#include "ParticleCoreShell.pypp.h" 
#include "Beam.pypp.h" 
#include "Lattice.pypp.h" 
#include "FormFactorCylinder.pypp.h" 
#include "ICloneable.pypp.h" 
#include "StochasticSampledParameter.pypp.h" 
#include "HomogeneousMaterial.pypp.h" 
#include "vector_integer_t.pypp.h" 
#include "AxisDouble.pypp.h" 
#include "IAxis.pypp.h" 
#include "Layer.pypp.h" 
#include "IFormFactor.pypp.h" 
#include "FormFactorParallelepiped.pypp.h" 
#include "RealParameterWrapper.pypp.h" 
#include "MaterialManager.pypp.h" 
#include "ResolutionFunction2DSimple.pypp.h" 
#include "SimulationParameters.pypp.h" 
#include "AxisBin.pypp.h" 
#include "FormFactorGauss.pypp.h" 
#include "FormFactorFullSpheroid.pypp.h" 
#include "PythonInterface_global_variables.pypp.h" 
#include "ISampleBuilder.pypp.h" 
#include "StochasticParameter_t.pypp.h" 
#include "StochasticDoubleGaussian.pypp.h" 
#include "FormFactorPrism6.pypp.h" 
#include "InterferenceFunction2DLattice.pypp.h" 
#include "FormFactorPyramid.pypp.h" 
#include "FormFactorBox.pypp.h" 
#include "IResolutionFunction2D.pypp.h" 
#include "IFormFactorBorn.pypp.h" 
#include "MultiLayer.pypp.h" 
#include "ITransform3D.pypp.h" 
#include "ParticleDecoration.pypp.h" 
#include "IDecoration.pypp.h" 
#include "FTDistribution2DCauchy.pypp.h" 
#include "ICompositeSample.pypp.h" 
#include "cvector_t.pypp.h" 
#include "ParameterPool.pypp.h" 
#include "Particle.pypp.h" 
#include "FormFactorCone.pypp.h" 
#include "FormFactorPrism3.pypp.h" 
#include "InterferenceFunction2DParaCrystal.pypp.h" 
#include "vdouble1d_t.pypp.h" 
#include "MesoCrystal.pypp.h" 
#include "RotateY_3D.pypp.h" 
#include "FormFactorDecoratorDebyeWaller.pypp.h" 
#include "vector_IFormFactorPtr_t.pypp.h" 
#include "IMaterial.pypp.h" 
#include "IFormFactorDecorator.pypp.h" 
#include "Instrument.pypp.h" 
#include "IDetectorResolution.pypp.h" 
#include "ISelectionRule.pypp.h" 
#include "Bin1D.pypp.h" 
#include "ParticleInfo.pypp.h" 
#include "vector_longinteger_t.pypp.h" 
#include "FormFactorHemiSpheroid.pypp.h" 
#include "LayerInterface.pypp.h" 
#include "FormFactorFullSphere.pypp.h" 
#include "PositionParticleInfo.pypp.h" 
#include "LayerRoughness.pypp.h" 
#include "FormFactorCrystal.pypp.h" 
#include "IntensityData.pypp.h" 
#include "IParameterized.pypp.h" 
#include "Bin1DCVector.pypp.h" 
#include "StochasticDoubleGate.pypp.h" 
#include "IClusteredParticles.pypp.h" 
#include "IInterferenceFunction.pypp.h" 
#include "SimpleSelectionRule.pypp.h" 
#include "FormFactorLorentz.pypp.h" 
#include "OutputDataIOFactory.pypp.h" 
#include "vector_kvector_t.pypp.h" 
#include "InterferenceFunction1DParaCrystal.pypp.h" 
#include "InterferenceFunctionNone.pypp.h" 
#include "Crystal.pypp.h" 
#include "PythonInterface_free_functions.pypp.h" 
#include "kvector_t.pypp.h" 
#include "FormFactorEllipsoid.pypp.h" 
#include "Simulation.pypp.h" 
#include "ISample.pypp.h" 
#include "ParticleBuilder.pypp.h" 
#include "FormFactorSphereGaussianRadius.pypp.h" 
#include "Lattice2DIFParameters.pypp.h" 
#include "FormFactorSphere.pypp.h" 
#include "__call_policies.pypp.hpp" 
#include "__convenience.pypp.hpp" 

#include "PythonListConverter.h"

BOOST_PYTHON_MODULE(libBornAgainCore){

    register_vector_longinteger_t_class();
    register_vector_integer_t_class();
    register_vdouble1d_t_class();
    register_vector_IFormFactorPtr_t_class();
    register_vector_kvector_t_class();
    register_IAxis_class();
    register_AxisBin_class();
    register_AxisDouble_class();
    register_IParameterized_class();
    register_Beam_class();
    register_Bin1D_class();
    register_Bin1DCVector_class();
    register_ICloneable_class();
    register_ISample_class();
    register_ICompositeSample_class();
    register_IClusteredParticles_class();
    register_Crystal_class();
    register_Detector_class();
    register_IFTDistribution2D_class();
    register_FTDistribution2DCauchy_class();
    register_IFormFactor_class();
    register_IFormFactorBorn_class();
    register_FormFactorBox_class();
    register_FormFactorCone_class();
    register_FormFactorCrystal_class();
    register_FormFactorCylinder_class();
    register_IFormFactorDecorator_class();
    register_FormFactorDecoratorDebyeWaller_class();
    register_FormFactorEllipsoid_class();
    register_FormFactorFullSphere_class();
    register_FormFactorFullSpheroid_class();
    register_FormFactorGauss_class();
    register_FormFactorHemiSpheroid_class();
    register_FormFactorLorentz_class();
    register_FormFactorParallelepiped_class();
    register_FormFactorPrism3_class();
    register_FormFactorPrism6_class();
    register_FormFactorPyramid_class();
    register_FormFactorSphere_class();
    register_FormFactorSphereGaussianRadius_class();
    register_kvector_t_class();
    register_cvector_t_class();
    register_ITransform3D_class();
    register_RotateY_3D_class();
    register_RotateZ_3D_class();
    register_IMaterial_class();
    register_HomogeneousMaterial_class();
    register_IDecoration_class();
    register_IDetectorResolution_class();
    register_IInterferenceFunction_class();
    register_IResolutionFunction2D_class();
    register_ISampleBuilder_class();
    register_ISelectionRule_class();
    register_Instrument_class();
    register_InterferenceFunction1DParaCrystal_class();
    register_InterferenceFunction2DLattice_class();
    register_InterferenceFunction2DParaCrystal_class();
    register_InterferenceFunctionNone_class();
    register_Lattice_class();
    register_Lattice2DIFParameters_class();
    register_Particle_class();
    register_LatticeBasis_class();
    register_Layer_class();
    register_LayerInterface_class();
    register_LayerRoughness_class();
    register_MaterialManager_class();
    register_MesoCrystal_class();
    register_MultiLayer_class();
    register_IntensityData_class();
    register_OutputDataIOFactory_class();
    register_ParameterPool_class();
    register_ParticleBuilder_class();
    register_ParticleCoreShell_class();
    register_ParticleDecoration_class();
    register_ParticleInfo_class();
    register_PositionParticleInfo_class();
    register_RealParameterWrapper_class();
    register_ResolutionFunction2DSimple_class();
    register_SimpleSelectionRule_class();
    register_Simulation_class();
    register_SimulationParameters_class();
    register_StochasticParameter_t_class();
    register_StochasticDoubleGate_class();
    register_StochasticDoubleGaussian_class();
    register_StochasticSampledParameter_class();
    register_global_variables();
    register_free_functions();

    register_python2cpp_converters();

    import_array();
    /* IMPORTANT
    this is initialisation function from C-API of python-numpy package. It has to be called once in the
    initialisation section of the module (i.e. here), when module is going to use any of python numpy C-API.
    Additional rule: when initialisation of the module, and functions that use python-numpy C-API are located in
    different files (different compilation units) - and this is exactly our case - additional defines has
    to be inserted before #include "numpy/arrayobject.h". See explanations
    http://docs.scipy.org/doc/numpy/reference/c-api.array.html#import_array
    */
}

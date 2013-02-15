#include "Python.h"
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY 
#include "numpy/arrayobject.h"
// the order of 3 guys above is important

#include "Crystal.pypp.h" 
#include "DiffuseDWBASimulation.pypp.h" 
#include "DiffuseParticleInfo.pypp.h" 
#include "FormFactorCrystal.pypp.h" 
#include "FormFactorCylinder.pypp.h" 
#include "FormFactorDecoratorDebyeWaller.pypp.h" 
#include "FormFactorFullSphere.pypp.h" 
#include "FormFactorGauss.pypp.h" 
#include "FormFactorLorentz.pypp.h" 
#include "FormFactorPrism3.pypp.h" 
#include "FormFactorPyramid.pypp.h" 
#include "FormFactorSphereGaussianRadius.pypp.h" 
#include "HomogeneousMaterial.pypp.h" 
#include "ICloneable.pypp.h" 
#include "IClusteredParticles.pypp.h" 
#include "ICompositeSample.pypp.h" 
#include "IDecoration.pypp.h" 
#include "IFormFactor.pypp.h" 
#include "IFormFactorBorn.pypp.h" 
#include "IFormFactorDecorator.pypp.h" 
#include "IInterferenceFunction.pypp.h" 
#include "IMaterial.pypp.h" 
#include "IParameterized.pypp.h" 
#include "ISample.pypp.h" 
#include "ISampleBuilder.pypp.h" 
#include "ISelectionRule.pypp.h" 
#include "ISimulation.pypp.h" 
#include "InterferenceFunction1DParaCrystal.pypp.h" 
#include "InterferenceFunctionNone.pypp.h" 
#include "Lattice.pypp.h" 
#include "LatticeBasis.pypp.h" 
#include "Layer.pypp.h" 
#include "LayerDWBASimulation.pypp.h" 
#include "LayerDecorator.pypp.h" 
#include "LayerDecoratorDWBASimulation.pypp.h" 
#include "LayerRoughness.pypp.h" 
#include "MaterialManager.pypp.h" 
#include "MaterialManagerSingleton_t.pypp.h" 
#include "MesoCrystal.pypp.h" 
#include "MultiLayer.pypp.h" 
#include "MultiLayerDWBASimulation.pypp.h" 
#include "OpticalFresnel.pypp.h" 
#include "ParameterPool.pypp.h" 
#include "Particle.pypp.h" 
#include "ParticleDecoration.pypp.h" 
#include "ParticleInfo.pypp.h" 
#include "PythonInterface_free_functions.pypp.h" 
#include "PythonInterface_global_variables.pypp.h" 
#include "RealParameterWrapper.pypp.h" 
#include "Reflect3D.pypp.h" 
#include "ReflectX3D.pypp.h" 
#include "ReflectY3D.pypp.h" 
#include "ReflectZ3D.pypp.h" 
#include "Rotate3D.pypp.h" 
#include "RotateX3D.pypp.h" 
#include "RotateY3D.pypp.h" 
#include "RotateZ3D.pypp.h" 
#include "Scale3D.pypp.h" 
#include "ScaleX3D.pypp.h" 
#include "ScaleY3D.pypp.h" 
#include "ScaleZ3D.pypp.h" 
#include "SimpleSelectionRule.pypp.h" 
#include "Simulation.pypp.h" 
#include "Transform3D.pypp.h" 
#include "Translate3D.pypp.h" 
#include "TranslateX3D.pypp.h" 
#include "TranslateY3D.pypp.h" 
#include "TranslateZ3D.pypp.h" 
#include "cvector_t.pypp.h" 
#include "kvector_t.pypp.h" 
#include "vdouble1d_t.pypp.h" 
#include "vector_DiffuseParticleInfoPtr_t.pypp.h" 
#include "vector_IFormFactorPtr_t.pypp.h" 
#include "vector_kvector_t.pypp.h" 
#include "__call_policies.pypp.hpp" 

#include "PythonListConverter.h"

BOOST_PYTHON_MODULE(libBornAgainCore){

    register_vdouble1d_t_class();
    register_vector_IFormFactorPtr_t_class();
    register_vector_kvector_t_class();
    register_vector_DiffuseParticleInfoPtr_t_class();
    register_ICloneable_class();
    register_IParameterized_class();
    register_ISample_class();
    register_ICompositeSample_class();
    register_IClusteredParticles_class();
    register_Crystal_class();
    register_LayerDWBASimulation_class();
    register_DiffuseDWBASimulation_class();
    register_Transform3D_class();
    register_ParticleInfo_class();
    register_DiffuseParticleInfo_class();
    register_IFormFactor_class();
    register_IFormFactorBorn_class();
    register_FormFactorCrystal_class();
    register_FormFactorCylinder_class();
    register_IFormFactorDecorator_class();
    register_FormFactorDecoratorDebyeWaller_class();
    register_FormFactorFullSphere_class();
    register_FormFactorGauss_class();
    register_FormFactorLorentz_class();
    register_FormFactorPrism3_class();
    register_FormFactorPyramid_class();
    register_FormFactorSphereGaussianRadius_class();
    register_kvector_t_class();
    register_cvector_t_class();
    register_Reflect3D_class();
    register_ReflectX3D_class();
    register_ReflectY3D_class();
    register_ReflectZ3D_class();
    register_Rotate3D_class();
    register_RotateX3D_class();
    register_RotateY3D_class();
    register_RotateZ3D_class();
    register_Scale3D_class();
    register_ScaleX3D_class();
    register_ScaleY3D_class();
    register_ScaleZ3D_class();
    register_Translate3D_class();
    register_TranslateX3D_class();
    register_TranslateY3D_class();
    register_TranslateZ3D_class();
    register_IMaterial_class();
    register_HomogeneousMaterial_class();
    register_IDecoration_class();
    register_IInterferenceFunction_class();
    register_ISampleBuilder_class();
    register_ISelectionRule_class();
    register_ISimulation_class();
    register_MaterialManagerSingleton_t_class();
    register_InterferenceFunction1DParaCrystal_class();
    register_InterferenceFunctionNone_class();
    register_Lattice_class();
    register_Particle_class();
    register_LatticeBasis_class();
    register_Layer_class();
    register_LayerDecorator_class();
    register_LayerDecoratorDWBASimulation_class();
    register_LayerRoughness_class();
    register_MaterialManager_class();
    register_MesoCrystal_class();
    register_MultiLayer_class();
    register_MultiLayerDWBASimulation_class();
    register_OpticalFresnel_class();
    register_ParameterPool_class();
    register_ParticleDecoration_class();
    register_RealParameterWrapper_class();
    register_SimpleSelectionRule_class();
    register_Simulation_class();
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

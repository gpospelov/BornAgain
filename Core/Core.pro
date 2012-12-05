###############################################################################
# qmake project file to compile shared library
###############################################################################
TARGET   = ScattCore
TEMPLATE = lib
CONFIG  += plugin # to remove versions from file name
QT      -= core gui
#CONFIG  += BUILD_PYTHON_BOOST_MODULE # to  generate python interface

# including common project properties
include($$PWD/../shared.pri)

# making standard shared library extension
QMAKE_EXTENSION_SHLIB = so

# -----------------------------------------------------------------------------
# Our source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    Algorithms/src/Beam.cpp \
    Algorithms/src/ChiSquaredFrequency.cpp \
    Algorithms/src/ChiSquaredModule.cpp \
    Algorithms/src/ConvolutionDetectorResolution.cpp \
    Algorithms/src/DecouplingApproximationStrategy.cpp \
    Algorithms/src/Detector.cpp \
    Algorithms/src/DiffuseDWBASimulation.cpp \
    Algorithms/src/DWBADiffuseReflection.cpp \
    Algorithms/src/DWBASimulation.cpp \
    Algorithms/src/Experiment.cpp \
    Algorithms/src/FTDistributions.cpp \
    Algorithms/src/GISASExperiment.cpp \
    Algorithms/src/IChiSquaredModule.cpp \
    Algorithms/src/IFittingDataSelector.cpp \
    Algorithms/src/IOutputDataNormalizer.cpp \
    Algorithms/src/LayerDecoratorDWBASimulation.cpp \
    Algorithms/src/LayerDWBASimulation.cpp \
    Algorithms/src/LocalMonodisperseApproximationStrategy.cpp \
    Algorithms/src/Mask.cpp \
    Algorithms/src/MaskCoordinateFunction.cpp \
    Algorithms/src/MultiLayerDWBASimulation.cpp \
    Algorithms/src/MultiLayerRoughnessDWBASimulation.cpp \
    Algorithms/src/OpticalFresnel.cpp \
    Algorithms/src/ResolutionFunction2DSimple.cpp \
    \
    FormFactors/src/FormFactorDWBA.cpp \
    FormFactors/src/FormFactorDWBAConstZ.cpp \
    FormFactors/src/FormFactorDecoratorTransformation.cpp \
    FormFactors/src/FormFactorCylinder.cpp \
    FormFactors/src/FormFactorFullSphere.cpp \
    FormFactors/src/FormFactorGauss.cpp \
    FormFactors/src/FormFactorParallelepiped.cpp \
    FormFactors/src/FormFactorPrism3.cpp \
    FormFactors/src/FormFactorPyramid.cpp \
    FormFactors/src/FormFactorLorentz.cpp \
    FormFactors/src/FormFactorWeighted.cpp \
    FormFactors/src/FormFactorCrystal.cpp \
    FormFactors/src/IFormFactorBorn.cpp \
    \
    Geometry/src/BasicVector3D.cpp \
    Geometry/src/Normal3D.cpp \
    Geometry/src/Plane3D.cpp \
    Geometry/src/Point3D.cpp \
    Geometry/src/Transform3D.cpp \
    Geometry/src/Vector3D.cpp \
    \
    Samples/src/Crystal.cpp \
    Samples/src/DiffuseParticleInfo.cpp \
    Samples/src/HomogeneousMaterial.cpp \
    Samples/src/ICompositeIterator.cpp \
    Samples/src/ICompositeSample.cpp \
    Samples/src/IMaterial.cpp \
    Samples/src/InterferenceFunction1DParaCrystal.cpp \
    Samples/src/InterferenceFunction2DParaCrystal.cpp \
    Samples/src/IRoughness.cpp \
    Samples/src/ISample.cpp \
    Samples/src/Lattice.cpp \
    Samples/src/LatticeBasis.cpp \
    Samples/src/Layer.cpp \
    Samples/src/LayerDecorator.cpp \
    Samples/src/LayerInterface.cpp \
    Samples/src/LayerRoughness.cpp \
    Samples/src/MaterialManager.cpp \
    Samples/src/MesoCrystal.cpp \
    Samples/src/MultiLayer.cpp \
    Samples/src/Particle.cpp \
    Samples/src/ParticleBuilder.cpp \
    Samples/src/ParticleCoreShell.cpp \
    Samples/src/ParticleDecoration.cpp \
    Samples/src/ParticleInfo.cpp \
    \
    Tools/src/Axisdouble.cpp \
    Tools/src/Convolve.cpp \
    Tools/src/CoreOptionsDescription.cpp \
    Tools/src/DoubleToComplexInterpolatingFunction.cpp \
    Tools/src/Exceptions.cpp \
    Tools/src/FitObject.cpp \
    Tools/src/FitParameter.cpp \
    Tools/src/FitParameterLinked.cpp \
    Tools/src/FitSuite.cpp \
    Tools/src/FitSuiteObjects.cpp \
    Tools/src/FitSuiteParameters.cpp \
    Tools/src/FitSuiteStrategy.cpp \
    Tools/src/IFactory.cpp \
    Tools/src/IObserver.cpp \
    Tools/src/IParameterized.cpp \
    Tools/src/ISingleton.cpp \
    Tools/src/MathFunctions.cpp \
    Tools/src/OutputData.cpp \
    Tools/src/OutputDataFunctions.cpp \
    Tools/src/OutputDataIOFactory.cpp \
    Tools/src/OutputDataReader.cpp \
    Tools/src/OutputDataWriter.cpp \
    Tools/src/ParameterPool.cpp \
    Tools/src/ProgramOptions.cpp \
    Tools/src/StochasticGaussian.cpp \
    Tools/src/StochasticSampledParameter.cpp \
    Tools/src/Types.cpp \
    Tools/src/Utils.cpp \
    \
    PythonAPI/src/PythonInterface_classes_1.cpp \
    PythonAPI/src/PythonInterface_classes_2.cpp \
    PythonAPI/src/PythonInterface_classes_3.cpp \
    PythonAPI/src/PythonInterface_free_functions.cpp \
    PythonAPI/src/PythonInterface_global_variables.cpp \
    PythonAPI/src/PythonListConverter.cpp \
    PythonAPI/src/PythonModule.cpp \
    PythonAPI/src/PythonPlusplusHelper.cpp \
    PythonAPI/src/PythonOutputData.cpp

HEADERS += \
    Algorithms/inc/Beam.h \
    Algorithms/inc/ChiSquaredFrequency.h \
    Algorithms/inc/ChiSquaredModule.h \
    Algorithms/inc/ConvolutionDetectorResolution.h \
    Algorithms/inc/DecouplingApproximationStrategy.h \
    Algorithms/inc/Detector.h \
    Algorithms/inc/DiffuseDWBASimulation.h \
    Algorithms/inc/DWBADiffuseReflection.h \
    Algorithms/inc/DWBASimulation.h \
    Algorithms/inc/Experiment.h \
    Algorithms/inc/FTDistributions.h \
    Algorithms/inc/GISASExperiment.h \
    Algorithms/inc/IChiSquaredModule.h \
    Algorithms/inc/IDetectorResolution.h \
    Algorithms/inc/IFittingDataSelector.h \
    Algorithms/inc/IInterferenceFunctionStrategy.h \
    Algorithms/inc/IOutputDataNormalizer.h \
    Algorithms/inc/IResolutionFunction2D.h \
    Algorithms/inc/ISampleBuilder.h \
    Algorithms/inc/ISimulation.h \
    Algorithms/inc/ISquaredFunction.h \
    Algorithms/inc/LayerDecoratorDWBASimulation.h \
    Algorithms/inc/LayerDWBASimulation.h \
    Algorithms/inc/LocalMonodisperseApproximationStrategy.h \
    Algorithms/inc/Mask.h \
    Algorithms/inc/MaskCoordinateFunction.h \
    Algorithms/inc/MultiLayerDWBASimulation.h \
    Algorithms/inc/MultiLayerRoughnessDWBASimulation.h \
    Algorithms/inc/OpticalFresnel.h \
    Algorithms/inc/ResolutionFunction2DSimple.h \
    Algorithms/inc/ThreadInfo.h \
    \
    FormFactors/inc/FormFactorDWBA.h \
    FormFactors/inc/FormFactorDWBAConstZ.h \
    FormFactors/inc/FormFactorDecoratorDebyeWaller.h \
    FormFactors/inc/FormFactorDecoratorFactor.h \
    FormFactors/inc/FormFactorDecoratorMultiPositionFactor.h \
    FormFactors/inc/FormFactorDecoratorPositionFactor.h \
    FormFactors/inc/FormFactorDecoratorRefractiveIndex.h \
    FormFactors/inc/FormFactorDecoratorTransformation.h \
    FormFactors/inc/FormFactorCylinder.h \
    FormFactors/inc/FormFactorFullSphere.h \
    FormFactors/inc/FormFactorGauss.h \
    FormFactors/inc/FormFactorParallelepiped.h \
    FormFactors/inc/FormFactorPrism3.h \
    FormFactors/inc/FormFactorPyramid.h \
    FormFactors/inc/FormFactorLorentz.h \
    FormFactors/inc/FormFactors.h \
    FormFactors/inc/FormFactorSphereGaussianRadius.h \
    FormFactors/inc/FormFactorCrystal.h \
    FormFactors/inc/FormFactorWeighted.h \
    FormFactors/inc/IFormFactor.h \
    FormFactors/inc/IFormFactorBorn.h \
    FormFactors/inc/IFormFactorBornSeparable.h \
    FormFactors/inc/IFormFactorDecorator.h \
    \
    Geometry/inc/BasicVector3D.h \
    Geometry/inc/Normal3D.h \
    Geometry/inc/Plane3D.h \
    Geometry/inc/Point3D.h \
    Geometry/inc/Transform3D.h \
    Geometry/inc/Transform3D.icc \
    Geometry/inc/Vector3D.h \
    \
    Samples/inc/Crystal.h \
    Samples/inc/DiffuseParticleInfo.h \
    Samples/inc/HomogeneousMaterial.h \
    Samples/inc/IClusteredParticles.h \
    Samples/inc/ICompositeIterator.h \
    Samples/inc/ICompositeSample.h \
    Samples/inc/IDecoration.h \
    Samples/inc/IDispersalState.h \
    Samples/inc/IInterferenceFunction.h \
    Samples/inc/IMaterial.h \
    Samples/inc/InterferenceFunction1DParaCrystal.h \
    Samples/inc/InterferenceFunction2DParaCrystal.h \
    Samples/inc/InterferenceFunctionNone.h \
    Samples/inc/IRoughness.h \
    Samples/inc/ISample.h \
    Samples/inc/ISelectionRule.h \
    Samples/inc/Lattice.h \
    Samples/inc/LatticeBasis.h \
    Samples/inc/Layer.h \
    Samples/inc/LayerDecorator.h \
    Samples/inc/LayerInterface.h \
    Samples/inc/LayerRoughness.h \
    Samples/inc/MaterialManager.h \
    Samples/inc/MesoCrystal.h \
    Samples/inc/MultiLayer.h \
    Samples/inc/Particle.h \
    Samples/inc/ParticleBuilder.h \
    Samples/inc/ParticleCoreShell.h \
    Samples/inc/ParticleDecoration.h \
    Samples/inc/ParticleInfo.h \
    \
    Tools/inc/AttLimits.h \
    Tools/inc/Axisdouble.h \
    Tools/inc/Convolve.h \
    Tools/inc/Coordinate3D.h \
    Tools/inc/DoubleToComplexInterpolatingFunction.h \
    Tools/inc/DoubleToComplexMap.h \
    Tools/inc/Exceptions.h \
    Tools/inc/FitObject.h \
    Tools/inc/FitParameter.h \
    Tools/inc/FitParameterLinked.h \
    Tools/inc/FitSuite.h \
    Tools/inc/FitSuiteObjects.h \
    Tools/inc/FitSuiteParameters.h \
    Tools/inc/FitSuiteStrategy.h \
    Tools/inc/IDoubleToComplexFunction.h \
    Tools/inc/IFactory.h \
    Tools/inc/IMinimizer.h \
    Tools/inc/INamed.h \
    Tools/inc/IObserver.h \
    Tools/inc/OutputDataFunctions.h \
    Tools/inc/IParameterized.h \
    Tools/inc/ISingleton.h \
    Tools/inc/IStochasticParameter.h \
    Tools/inc/LLData.h \
    Tools/inc/Macros.h \
    Tools/inc/MathFunctions.h \
    Tools/inc/MemberFunctionIntegrator.h \
    Tools/inc/Numeric.h \
    Tools/inc/OutputData.h \
    Tools/inc/OutputDataIOFactory.h \
    Tools/inc/OutputDataIterator.h \
    Tools/inc/OutputDataReader.h \
    Tools/inc/OutputDataWriter.h \
    Tools/inc/ParameterPool.h \
    Tools/inc/ProgramOptions.h \
    Tools/inc/TRange.h \
    Tools/inc/StochasticDiracDelta.h \
    Tools/inc/StochasticGaussian.h \
    Tools/inc/StochasticSampledParameter.h \
    Tools/inc/Types.h \
    Tools/inc/Units.h \
    Tools/inc/Utils.h \
    Tools/inc/CoreOptionsDescription.h \
    \
    PythonAPI/inc/PythonInterface_classes_1.h \
    PythonAPI/inc/PythonInterface_classes_2.h \
    PythonAPI/inc/PythonInterface_classes_3.h \
    PythonAPI/inc/PythonInterface_free_functions.h \
    PythonAPI/inc/PythonInterface_global_variables.h \
    PythonAPI/inc/PythonListConverter.h \
    PythonAPI/inc/PythonModule.h \
    PythonAPI/inc/PythonOutputData.h \
    PythonAPI/inc/PythonPlusplusHelper.h \
    PythonAPI/inc/IPythonWrapper.h \
    Algorithms/inc/IIntensityFunction.h

INCLUDEPATH += ./Algorithms/inc ./FormFactors/inc ./Geometry/inc ./Samples/inc ./Tools/inc ./PythonAPI/inc
DEPENDPATH  += ./Algorithms/inc ./FormFactors/inc ./Geometry/inc ./Samples/inc ./Tools/inc ./PythonAPI/inc

# excluding files with python interface to not to expose library in python
!contains(CONFIG, BUILD_PYTHON_BOOST_MODULE) {
  HEADERS -= \
    PythonAPI/inc/PythonInterface_classes_1.h \
    PythonAPI/inc/PythonInterface_classes_2.h \
    PythonAPI/inc/PythonInterface_classes_3.h \
    PythonAPI/inc/PythonInterface_free_functions.h \
    PythonAPI/inc/PythonInterface_global_variables.h \
    PythonAPI/inc/PythonListConverter.h \
    PythonAPI/inc/PythonModule.h \
    PythonAPI/inc/PythonOutputData.h \
    PythonAPI/inc/PythonPlusplusHelper.h

  SOURCES -= \
    PythonAPI/src/PythonInterface_classes_1.cpp \
    PythonAPI/src/PythonInterface_classes_2.cpp \
    PythonAPI/src/PythonInterface_classes_3.cpp \
    PythonAPI/src/PythonInterface_free_functions.cpp \
    PythonAPI/src/PythonInterface_global_variables.cpp \
    PythonAPI/src/PythonListConverter.cpp \
    PythonAPI/src/PythonModule.cpp \
    PythonAPI/src/PythonOutputData.cpp \
    PythonAPI/src/PythonPlusplusHelper.cpp

  INCLUDEPATH -= ./PythonAPI/inc
  DEPENDPATH -= ./PythonAPI/inc
}

OBJECTS_DIR = obj

# -----------------------------------------------------------------------------
# checking python configuration
# -----------------------------------------------------------------------------
# TODO - implement check for following files
# numpy/arrayobject.h

CONFIG(BUILD_PYTHON_BOOST_MODULE) {
  # user wants to compile python module

  WhichPython=$$system(which python)
  isEmpty(WhichPython) {
    # we do not have python
    error("Can not find any sign of python")
  } else {
    # we have python
    pythonvers=$$system("python -c 'import sys; sys.stdout.write(sys.version[:3])'")
    pythonsysincdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/include/python\" + sys.version[:3])'")
    #pythonsyslibdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/lib/python\" + sys.version[:3])'")
    pythonsyslibdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/lib\" )'")
    #message(we have python)
    #message($$pythonvers)
    #message($$pythonsysincdir)
    #message($$pythonsyslibdir)
    lessThan(pythonvers, 2.6): error("GISASFW requires python 2.6 or greater")
    INCLUDEPATH += $$pythonsysincdir
    LIBS += -L$$pythonsyslibdir -lpython$$pythonvers -lboost_python

    # we need to know to location of numpy
    pythonnumpy=$$system("python -c 'import sys; import numpy; sys.stdout.write(numpy.get_include())'")
    INCLUDEPATH += $$pythonnumpy
  }

}


# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
MYPREFIX = $$PWD/.. # place to install library and headers
target.path = $$MYPREFIX/lib
INSTALLS += target
#includes.files = $$PWD/inc/*.h
#includes.path = $$MYPREFIX/inc/ScattCore
#INSTALLS += includes
# there is a soft bug here in qmake, it looks like flag '-r' works
# only when it appears at the beginning of QMAKE_DISTCLEAN variable
# i.e. the order below is important
#QMAKE_DISTCLEAN += -r $$includes.path
#QMAKE_DISTCLEAN += $$MYPREFIX/inc/ScattCore
QMAKE_DISTCLEAN += $$target.path/$(TARGET)

QMAKE_POST_LINK = (make install)


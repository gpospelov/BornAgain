###############################################################################
# qmake project file to compile shared library
###############################################################################
TARGET   = ScattCore
TEMPLATE = lib
CONFIG  += plugin # to remove versions from file name
CONFIG  += debug
QT      -= core gui
CONFIG  += BUILD_PYTHON_BOOST_MODULE # to  generate python interface

# including common project properties
include($$PWD/../shared.pri)

# making standard shared library extension
QMAKE_EXTENSION_SHLIB = so


# -----------------------------------------------------------------------------
# Our source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    Algorithms/src/Beam.cpp \
    Algorithms/src/ChiSquaredModule.cpp \
    Algorithms/src/ConvolutionDetectorResolution.cpp \
    Algorithms/src/DecouplingApproximationStrategy.cpp \
    Algorithms/src/Detector.cpp \
    Algorithms/src/DWBADiffuseReflection.cpp \
    Algorithms/src/DWBAFormFactor.cpp \
    Algorithms/src/DWBAFormFactorConstZ.cpp \
    Algorithms/src/DWBASimulation.cpp \
    Algorithms/src/Experiment.cpp \
    Algorithms/src/FormFactorDecoratorTransformation.cpp \
    Algorithms/src/GISASExperiment.cpp \
    Algorithms/src/IFittingDataSelector.cpp \
    Algorithms/src/LayerDecoratorDWBASimulation.cpp \
    Algorithms/src/LayerDWBASimulation.cpp \
    Algorithms/src/LocalMonodisperseApproximationStrategy.cpp \
    Algorithms/src/MultiLayerDWBASimulation.cpp \
    Algorithms/src/OpticalFresnel.cpp \
    \
    Geometry/src/BasicVector3D.cpp \
    Geometry/src/Normal3D.cpp \
    Geometry/src/Plane3D.cpp \
    Geometry/src/Point3D.cpp \
    Geometry/src/Transform3D.cpp \
    Geometry/src/Vector3D.cpp \
    \
    Samples/src/FormFactorCylinder.cpp \
    Samples/src/FormFactorFullSphere.cpp \
    Samples/src/FormFactorPrism3.cpp \
    Samples/src/FormFactorPyramid.cpp \
    Samples/src/HomogeneousMaterial.cpp \
    Samples/src/ICompositeIterator.cpp \
    Samples/src/ICompositeSample.cpp \
    Samples/src/IMaterial.cpp \
    Samples/src/InterferenceFunction1DParaCrystal.cpp \
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
    Samples/src/NanoParticle.cpp \
    Samples/src/NanoParticleCrystal.cpp \
    Samples/src/NanoParticleCrystalFormFactor.cpp \
    Samples/src/NanoParticleDecoration.cpp \
    Samples/src/NanoParticleInfo.cpp \
    Samples/src/ParameterPool.cpp \
    Samples/src/WeightedFormFactor.cpp \
    \
    Tools/src/Convolve.cpp \
    Tools/src/DoubleToComplexInterpolatingFunction.cpp \
    Tools/src/Exceptions.cpp \
    Tools/src/FitMultiParameter.cpp \
    Tools/src/FitParameter.cpp \
    Tools/src/IFactory.cpp \
    Tools/src/INamed.cpp \
    Tools/src/ISingleton.cpp \
    Tools/src/MathFunctions.cpp \
    Tools/src/OutputData.cpp \
    Tools/src/StochasticGaussian.cpp \
    Tools/src/Types.cpp \
    Tools/src/Utils.cpp \
    \
    PythonAPI/src/PythonInterface_classes_1.cpp \
    PythonAPI/src/PythonInterface_classes_2.cpp \
    PythonAPI/src/PythonInterface_classes_3.cpp \
    PythonAPI/src/PythonInterface_free_functions.cpp \
    PythonAPI/src/PythonInterface_global_variables.cpp \
    PythonAPI/src/PythonModule.cpp \
    PythonAPI/src/PythonPlusplusHelper.cpp

HEADERS += \
    Algorithms/inc/Beam.h \
    Algorithms/inc/ChiSquaredModule.h \
    Algorithms/inc/ConvolutionDetectorResolution.h \
    Algorithms/inc/DecouplingApproximationStrategy.h \
    Algorithms/inc/Detector.h \
    Algorithms/inc/DWBADiffuseReflection.h \
    Algorithms/inc/DWBAFormFactor.h \
    Algorithms/inc/DWBAFormFactorConstZ.h \
    Algorithms/inc/DWBASimulation.h \
    Algorithms/inc/Experiment.h \
    Algorithms/inc/FormFactorDecoratorFactor.h \
    Algorithms/inc/FormFactorDecoratorPositionFactor.h \
    Algorithms/inc/FormFactorDecoratorRefractiveIndex.h \
    Algorithms/inc/FormFactorDecoratorTransformation.h \
    Algorithms/inc/GISASExperiment.h \
    Algorithms/inc/IDetectorResolution.h \
    Algorithms/inc/IFittingDataSelector.h \
    Algorithms/inc/ISimulation.h \
    Algorithms/inc/ISquaredFunction.h \
    Algorithms/inc/IInterferenceFunctionStrategy.h \
    Algorithms/inc/LayerDecoratorDWBASimulation.h \
    Algorithms/inc/LayerDWBASimulation.h \
    Algorithms/inc/LocalMonodisperseApproximationStrategy.h \
    Algorithms/inc/MultiLayerDWBASimulation.h \
    Algorithms/inc/OpticalFresnel.h \
    \
    Geometry/inc/BasicVector3D.h \
    Geometry/inc/Normal3D.h \
    Geometry/inc/Plane3D.h \
    Geometry/inc/Point3D.h \
    Geometry/inc/Transform3D.h \
    Geometry/inc/Transform3D.icc \
    Geometry/inc/Vector3D.h \
    \
    Samples/inc/FormFactorCylinder.h \
    Samples/inc/FormFactorFullSphere.h \
    Samples/inc/FormFactorPrism3.h \
    Samples/inc/FormFactorPyramid.h \
    Samples/inc/FormFactors.h \
    Samples/inc/HomogeneousMaterial.h \
    Samples/inc/IClusteredNanoParticles.h \
    Samples/inc/ICompositeIterator.h \
    Samples/inc/ICompositeSample.h \
    Samples/inc/IDecoration.h \
    Samples/inc/IDispersalState.h \
    Samples/inc/IFormFactor.h \
    Samples/inc/IInterferenceFunction.h \
    Samples/inc/IMaterial.h \
    Samples/inc/InterferenceFunction1DParaCrystal.h \
    Samples/inc/InterferenceFunctionNone.h \
    Samples/inc/IRoughness.h \
    Samples/inc/ISample.h \
    Samples/inc/Lattice.h \
    Samples/inc/LatticeBasis.h \
    Samples/inc/Layer.h \
    Samples/inc/LayerDecorator.h \
    Samples/inc/LayerInterface.h \
    Samples/inc/LayerRoughness.h \
    Samples/inc/MaterialManager.h \
    Samples/inc/MesoCrystal.h \
    Samples/inc/MultiLayer.h \
    Samples/inc/NanoParticle.h \
    Samples/inc/NanoParticleCrystal.h \
    Samples/inc/NanoParticleCrystalFormFactor.h \
    Samples/inc/NanoParticleDecoration.h \
    Samples/inc/NanoParticleInfo.h \
    Samples/inc/ParameterPool.h \
    Samples/inc/WeightedFormFactor.h \
    \
    Tools/inc/Convolve.h \
    Tools/inc/Coordinate3D.h \
    Tools/inc/DoubleToComplexInterpolatingFunction.h \
    Tools/inc/Exceptions.h \
    Tools/inc/FitMultiParameter.h \
    Tools/inc/FitParameter.h \
    Tools/inc/IDoubleToComplexFunction.h \
    Tools/inc/IFactory.h \
    Tools/inc/INamed.h \
    Tools/inc/ISingleton.h \
    Tools/inc/IStochasticParameter.h \
    Tools/inc/MathFunctions.h \
    Tools/inc/NamedVector.h \
    Tools/inc/Numeric.h \
    Tools/inc/OutputData.h \
    Tools/inc/StochasticDiracDelta.h \
    Tools/inc/StochasticGaussian.h \
    Tools/inc/Types.h \
    Tools/inc/Units.h \
    Tools/inc/Utils.h \
    \
    PythonAPI/inc/PythonInterface_classes_1.h \
    PythonAPI/inc/PythonInterface_classes_2.h \
    PythonAPI/inc/PythonInterface_classes_3.h \
    PythonAPI/inc/PythonInterface_free_functions.h \
    PythonAPI/inc/PythonInterface_global_variables.h \
    PythonAPI/inc/PythonModule.h \
    PythonAPI/inc/PythonPlusplusHelper.h

INCLUDEPATH += ./Algorithms/inc ./Geometry/inc ./Samples/inc ./Tools/inc ./PythonAPI/inc
DEPENDPATH  += ./Algorithms/inc ./Geometry/inc ./Samples/inc ./Tools/inc ./PythonAPI/inc

# excluding files with python interface to not to expose library in python
!contains(CONFIG, BUILD_PYTHON_BOOST_MODULE) {
  HEADERS -= \
    PythonAPI/inc/PythonInterface_classes_1.h \
    PythonAPI/inc/PythonInterface_classes_2.h \
    PythonAPI/inc/PythonInterface_classes_3.h \
    PythonAPI/inc/PythonInterface_free_functions.h \
    PythonAPI/inc/PythonInterface_global_variables.h \
    PythonAPI/inc/PythonModule.h \
    PythonAPI/inc/PythonPlusplusHelper.h

  SOURCES -= \
    PythonAPI/src/PythonInterface_classes_1.cpp \
    PythonAPI/src/PythonInterface_classes_2.cpp \
    PythonAPI/src/PythonInterface_classes_3.cpp \
    PythonAPI/src/PythonInterface_free_functions.cpp \
    PythonAPI/src/PythonInterface_global_variables.cpp \
    PythonAPI/src/PythonModule.cpp \
    PythonAPI/src/PythonPlusplusHelper.cpp

  INCLUDEPATH -= ./PythonAPI/inc
  DEPENDPATH -= ./PythonAPI/inc
}

OBJECTS_DIR = obj


# -----------------------------------------------------------------------------
# external libraries
# -----------------------------------------------------------------------------
macx {
  INCLUDEPATH += /opt/local/include
  LIBS += -L/opt/local/lib
}
!macx:unix {
  INCLUDEPATH += /usr/local/include
  LIBS += -L/usr/local/lib -L/usr/lib64
}
# normally it should be done like that
LIBS += -lgsl -lgslcblas -lfftw3 -lboost_system -lboost_filesystem -lboost_regex

# here is workaround since JCNS /usr/local doesn't have shared fftw3
# qmake CONFIG+=JCNS
CONFIG(JCNS) {
  LIBS -= -lfftw3
  LIBS += -Bstatic -lfftw3f -Bdynamic # request for static (with fPIC option)
  # "-lfftw3f" - with fPIC option, "-lfftw3" - without fPIC option
}


# -----------------------------------------------------------------------------
# checking python configuration
# -----------------------------------------------------------------------------
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


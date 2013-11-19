# encoding: utf-8
# module libBornAgainCore
# from /home/pospelov/development/git/BornAgain-build/lib/libBornAgainCore.so
# by generator 1.130
# no doc

# imports
import Boost.Python as __Boost_Python


# Variables with simple values

angstrom = 0.1

deg = 0.017453292519943295
degree = 0.017453292519943295

gauss = 0.0001

meter = 1000000000.0

micrometer = 1000.0
millimeter = 1000000.0
milliradian = 0.001

mrad = 0.001

nanometer = 1.0

nm = 1.0

PI = 3.1415927410125732
PI2 = 6.2831854820251465
PID2 = 1.5707963705062866
PI_SQR = 9.869604110717773

rad = 1.0
radian = 1.0

sr = 1.0

steradian = 1.0

tesla = 1.0

# functions

def deg2rad(p_float, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
    """ deg2rad( (float)angle) -> float """
    pass

def GenerateNormalRandom(p_float, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
    """ GenerateNormalRandom( (float)average, (float)std_dev) -> float """
    pass

def GetMajorVersionNumber(): # real signature unknown; restored from __doc__
    """ GetMajorVersionNumber() -> int """
    return 0

def GetMinorVersionNumber(): # real signature unknown; restored from __doc__
    """ GetMinorVersionNumber() -> int """
    return 0

def GetPatchVersionNumber(): # real signature unknown; restored from __doc__
    """ GetPatchVersionNumber() -> int """
    return 0

def GetVersionNumber(): # real signature unknown; restored from __doc__
    """ GetVersionNumber() -> str """
    return ""

def rad2deg(p_float, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
    """ rad2deg( (float)angle) -> float """
    pass

# classes

class IAxis(__Boost_Python.instance):
    # no doc
    def clone(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IAxis)arg1) -> IAxis
        
        clone( (IAxis)arg1) -> None
        """
        pass

    def createDoubleBinSize(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDoubleBinSize( (IAxis)arg1) -> IAxis
        
        createDoubleBinSize( (IAxis)arg1) -> None
        """
        pass

    def findClosestIndex(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        findClosestIndex( (IAxis)arg1, (float)value) -> int
        
        findClosestIndex( (IAxis)arg1, (float)arg2) -> None
        """
        pass

    def getBin(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getBin( (IAxis)arg1, (int)index) -> Bin1D
        
        getBin( (IAxis)arg1, (int)arg2) -> None
        """
        pass

    def getMax(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMax( (IAxis)arg1) -> float
        
        getMax( (IAxis)arg1) -> None
        """
        pass

    def getMin(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMin( (IAxis)arg1) -> float
        
        getMin( (IAxis)arg1) -> None
        """
        pass

    def getName(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getName( (IAxis)arg1) -> str """
        pass

    def getSize(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getSize( (IAxis)arg1) -> int
        
        getSize( (IAxis)arg1) -> None
        """
        pass

    def setName(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setName( (IAxis)arg1, (str)name) -> None """
        pass

    def __getitem__(self, IAxis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __getitem__( (IAxis)arg1, (int)index) -> float
        
        __getitem__( (IAxis)arg1, (int)arg2) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (str)name) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 40


class AxisBin(IAxis):
    # no doc
    def clone(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (AxisBin)arg1) -> AxisBin
        
        clone( (AxisBin)arg1) -> AxisBin
        """
        pass

    def createDoubleBinSize(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDoubleBinSize( (AxisBin)arg1) -> AxisBin
        
        createDoubleBinSize( (AxisBin)arg1) -> AxisBin
        """
        pass

    def findClosestIndex(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        findClosestIndex( (AxisBin)arg1, (float)value) -> int
        
        findClosestIndex( (AxisBin)arg1, (float)value) -> int
        """
        pass

    def getBin(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getBin( (AxisBin)arg1, (int)index) -> Bin1D
        
        getBin( (AxisBin)arg1, (int)index) -> Bin1D
        """
        pass

    def getMax(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMax( (AxisBin)arg1) -> float
        
        getMax( (AxisBin)arg1) -> float
        """
        pass

    def getMin(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMin( (AxisBin)arg1) -> float
        
        getMin( (AxisBin)arg1) -> float
        """
        pass

    def getSize(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getSize( (AxisBin)arg1) -> int
        
        getSize( (AxisBin)arg1) -> int
        """
        pass

    def getVector(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getVector( (AxisBin)arg1) -> vdouble1d_t """
        pass

    def initBins(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ initBins( (AxisBin)arg1, (int)nbr_bins, (float)start, (float)end) -> None """
        pass

    def push_back(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ push_back( (AxisBin)arg1, (float)limit) -> None """
        pass

    def __getitem__(self, AxisBin, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __getitem__( (AxisBin)arg1, (int)index) -> float
        
        __getitem__( (AxisBin)arg1, (int)index) -> float
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1, (str)name) -> None
        
        __init__( (object)arg1, (str)name, (int)nbr_bins, (float)start, (float)end) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 64


class AxisDouble(IAxis):
    # no doc
    def findClosestIndex(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        findClosestIndex( (AxisDouble)arg1, (float)value) -> int
        
        findClosestIndex( (AxisDouble)arg1, (float)value) -> int
        """
        pass

    def getBin(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getBin( (AxisDouble)arg1, (int)index) -> Bin1D
        
        getBin( (AxisDouble)arg1, (int)index) -> Bin1D
        """
        pass

    def getLowerBoundIndex(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLowerBoundIndex( (AxisDouble)arg1, (float)value) -> int """
        pass

    def getMax(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMax( (AxisDouble)arg1) -> float
        
        getMax( (AxisDouble)arg1) -> float
        """
        pass

    def getMin(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMin( (AxisDouble)arg1) -> float
        
        getMin( (AxisDouble)arg1) -> float
        """
        pass

    def getSize(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getSize( (AxisDouble)arg1) -> int
        
        getSize( (AxisDouble)arg1) -> int
        """
        pass

    def getUpperBoundIndex(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getUpperBoundIndex( (AxisDouble)arg1, (float)value) -> int """
        pass

    def getVector(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getVector( (AxisDouble)arg1) -> vdouble1d_t """
        pass

    def initElements(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ initElements( (AxisDouble)arg1, (int)size, (float)start, (float)end) -> None """
        pass

    def push_back(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ push_back( (AxisDouble)arg1, (float)element) -> None """
        pass

    def __getitem__(self, AxisDouble, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __getitem__( (AxisDouble)arg1, (int)index) -> float
        
        __getitem__( (AxisDouble)arg1, (int)index) -> float
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1, (str)name) -> None
        
        __init__( (object)arg1, (str)name, (int)size, (float)start, (float)end) -> None
        
        __init__( (object)arg1, (AxisBin)source) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 72


class IParameterized(__Boost_Python.instance):
    # no doc
    def areParametersChanged(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IParameterized)arg1) -> bool
        
        areParametersChanged( (IParameterized)arg1) -> bool
        """
        pass

    def assign(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ assign( (IParameterized)arg1, (IParameterized)other) -> IParameterized """
        pass

    def clearParameterPool(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IParameterized)arg1) -> None
        
        clearParameterPool( (IParameterized)arg1) -> None
        """
        pass

    def createParameterTree(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IParameterized)arg1) -> ParameterPool
        
        createParameterTree( (IParameterized)arg1) -> ParameterPool
        """
        pass

    def getParameterPool(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getParameterPool( (IParameterized)arg1) -> ParameterPool """
        pass

    def printParameters(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IParameterized)arg1) -> None
        
        printParameters( (IParameterized)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IParameterized)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IParameterized)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IParameterized)arg1) -> None
        
        setParametersAreChanged( (IParameterized)arg1) -> None
        """
        pass

    def setParameterValue(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IParameterized)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IParameterized)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (str)name) -> None
        
        __init__( (object)arg1, (IParameterized)other) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 112


class Beam(IParameterized):
    # no doc
    def areParametersChanged(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (Beam)arg1) -> bool
        
        areParametersChanged( (Beam)arg1) -> bool
        """
        pass

    def assign(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ assign( (Beam)arg1, (Beam)other) -> Beam """
        pass

    def clearParameterPool(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (Beam)arg1) -> None
        
        clearParameterPool( (Beam)arg1) -> None
        """
        pass

    def createParameterTree(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (Beam)arg1) -> ParameterPool
        
        createParameterTree( (Beam)arg1) -> ParameterPool
        """
        pass

    def getCentralK(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getCentralK( (Beam)arg1) -> cvector_t """
        pass

    def getIntensity(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getIntensity( (Beam)arg1) -> float """
        pass

    def printParameters(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (Beam)arg1) -> None
        
        printParameters( (Beam)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setCentralK(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setCentralK( (Beam)arg1, (cvector_t)k_i) -> None
        
        setCentralK( (Beam)arg1, (float)lambda, (float)alpha_i, (float)phi_i) -> None
        """
        pass

    def setIntensity(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setIntensity( (Beam)arg1, (float)intensity) -> None """
        pass

    def setMatchedParametersValue(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (Beam)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (Beam)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (Beam)arg1) -> None
        
        setParametersAreChanged( (Beam)arg1) -> None
        """
        pass

    def setParameterValue(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (Beam)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (Beam)arg1, (str)name, (float)value) -> bool
        """
        pass

    def SetSpinUpFraction(self, Beam, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ SetSpinUpFraction( (Beam)arg1, (float)up_fraction) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (Beam)other) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 240


class Bin1D(__Boost_Python.instance):
    # no doc
    def getMidPoint(self, Bin1D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getMidPoint( (Bin1D)arg1) -> float """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    m_lower = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_upper = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default


    __instance_size__ = 32


class Bin1DCVector(__Boost_Python.instance):
    # no doc
    def getDelta(self, Bin1DCVector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDelta( (Bin1DCVector)arg1) -> cvector_t """
        pass

    def getMidPoint(self, Bin1DCVector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getMidPoint( (Bin1DCVector)arg1) -> cvector_t """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (cvector_t)lower, (cvector_t)upper) -> None
        
        __init__( (object)arg1, (float)wavelength, (Bin1D)alpha_bin, (Bin1D)phi_bin) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    m_q_lower = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_q_upper = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default


    __instance_size__ = 112


class ICloneable(__Boost_Python.instance):
    # no doc
    def clone(self, ICloneable, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (ICloneable)arg1) -> ICloneable
        
        clone( (ICloneable)arg1) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 32


class ISample(ICloneable, IParameterized):
    # no doc
    def accept(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        accept( (ISample)arg1, (object)p_visitor) -> None
        
        accept( (ISample)arg1, (object)arg2) -> None
        """
        pass

    def areParametersChanged(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (ISample)arg1) -> bool
        
        areParametersChanged( (ISample)arg1) -> bool
        """
        pass

    def clearParameterPool(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (ISample)arg1) -> None
        
        clearParameterPool( (ISample)arg1) -> None
        """
        pass

    def clone(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (ISample)arg1) -> ISample
        
        clone( (ISample)arg1) -> ISample
        """
        pass

    def cloneInvertB(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (ISample)arg1) -> ISample
        
        cloneInvertB( (ISample)arg1) -> ISample
        """
        pass

    def containsMagneticMaterial(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ containsMagneticMaterial( (ISample)arg1) -> bool """
        pass

    def createParameterTree(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (ISample)arg1) -> ParameterPool
        
        createParameterTree( (ISample)arg1) -> ParameterPool
        """
        pass

    def getCompositeSample(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (ISample)arg1) -> ICompositeSample
        
        getCompositeSample( (ISample)arg1) -> ICompositeSample
        """
        pass

    def printParameters(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (ISample)arg1) -> None
        
        printParameters( (ISample)arg1) -> None
        """
        pass

    def printSampleTree(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (ISample)arg1) -> None
        
        printSampleTree( (ISample)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (ISample)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (ISample)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (ISample)arg1) -> None
        
        setParametersAreChanged( (ISample)arg1) -> None
        """
        pass

    def setParameterValue(self, ISample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (ISample)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (ISample)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 120


class ICompositeSample(ISample):
    # no doc
    def accept(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        accept( (ICompositeSample)arg1, (object)p_visitor) -> None
        
        accept( (ICompositeSample)arg1, (object)arg2) -> None
        """
        pass

    def areParametersChanged(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (ICompositeSample)arg1) -> bool
        
        areParametersChanged( (ICompositeSample)arg1) -> bool
        """
        pass

    def clearParameterPool(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (ICompositeSample)arg1) -> None
        
        clearParameterPool( (ICompositeSample)arg1) -> None
        """
        pass

    def cloneInvertB(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (ICompositeSample)arg1) -> ISample
        
        cloneInvertB( (ICompositeSample)arg1) -> ISample
        """
        pass

    def createParameterTree(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (ICompositeSample)arg1) -> ParameterPool
        
        createParameterTree( (ICompositeSample)arg1) -> ParameterPool
        """
        pass

    def printParameters(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (ICompositeSample)arg1) -> None
        
        printParameters( (ICompositeSample)arg1) -> None
        """
        pass

    def printSampleTree(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (ICompositeSample)arg1) -> None
        
        printSampleTree( (ICompositeSample)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (ICompositeSample)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (ICompositeSample)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (ICompositeSample)arg1) -> None
        
        setParametersAreChanged( (ICompositeSample)arg1) -> None
        """
        pass

    def setParameterValue(self, ICompositeSample, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (ICompositeSample)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (ICompositeSample)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 136


class IClusteredParticles(ICompositeSample):
    # no doc
    def areParametersChanged(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IClusteredParticles)arg1) -> bool
        
        areParametersChanged( (IClusteredParticles)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IClusteredParticles)arg1) -> None
        
        clearParameterPool( (IClusteredParticles)arg1) -> None
        """
        pass

    def clone(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IClusteredParticles)arg1) -> IClusteredParticles
        
        clone( (IClusteredParticles)arg1) -> IClusteredParticles
        """
        pass

    def cloneInvertB(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (IClusteredParticles)arg1) -> IClusteredParticles
        
        cloneInvertB( (IClusteredParticles)arg1) -> IClusteredParticles
        """
        pass

    def createParameterTree(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IClusteredParticles)arg1) -> ParameterPool
        
        createParameterTree( (IClusteredParticles)arg1) -> ParameterPool
        """
        pass

    def printParameters(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IClusteredParticles)arg1) -> None
        
        printParameters( (IClusteredParticles)arg1) -> None
        """
        pass

    def printSampleTree(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (IClusteredParticles)arg1) -> None
        
        printSampleTree( (IClusteredParticles)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setAmbientMaterial(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setAmbientMaterial( (IClusteredParticles)arg1, (IMaterial)p_ambient_material) -> None
        
        setAmbientMaterial( (IClusteredParticles)arg1, (IMaterial)arg2) -> None
        """
        pass

    def setMatchedParametersValue(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IClusteredParticles)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IClusteredParticles)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IClusteredParticles)arg1) -> None
        
        setParametersAreChanged( (IClusteredParticles)arg1) -> None
        """
        pass

    def setParameterValue(self, IClusteredParticles, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IClusteredParticles)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IClusteredParticles)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 136


class Crystal(IClusteredParticles):
    # no doc
    def areParametersChanged(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (Crystal)arg1) -> bool
        
        areParametersChanged( (Crystal)arg1) -> bool
        """
        pass

    def clearParameterPool(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (Crystal)arg1) -> None
        
        clearParameterPool( (Crystal)arg1) -> None
        """
        pass

    def clone(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (Crystal)arg1) -> Crystal
        
        clone( (Crystal)arg1) -> Crystal
        """
        pass

    def cloneInvertB(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (Crystal)arg1) -> Crystal
        
        cloneInvertB( (Crystal)arg1) -> Crystal
        """
        pass

    def createBasis(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ createBasis( (Crystal)arg1) -> LatticeBasis """
        pass

    def createParameterTree(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (Crystal)arg1) -> ParameterPool
        
        createParameterTree( (Crystal)arg1) -> ParameterPool
        """
        pass

    def getLattice(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLattice( (Crystal)arg1) -> Lattice """
        pass

    def getLatticeBasis(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLatticeBasis( (Crystal)arg1) -> LatticeBasis """
        pass

    def printParameters(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (Crystal)arg1) -> None
        
        printParameters( (Crystal)arg1) -> None
        """
        pass

    def printSampleTree(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (Crystal)arg1) -> None
        
        printSampleTree( (Crystal)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setDWFactor(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setDWFactor( (Crystal)arg1, (float)dw_factor) -> None """
        pass

    def setMatchedParametersValue(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (Crystal)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (Crystal)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (Crystal)arg1) -> None
        
        setParametersAreChanged( (Crystal)arg1) -> None
        """
        pass

    def setParameterValue(self, Crystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (Crystal)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (Crystal)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (LatticeBasis)lattice_basis, (Lattice)lattice) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 352


class cvector_t(__Boost_Python.instance):
    # no doc
    def assign(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ assign( (cvector_t)arg1, (cvector_t)v) -> cvector_t """
        pass

    def mag(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ mag( (cvector_t)arg1) -> complex """
        pass

    def mag2(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ mag2( (cvector_t)arg1) -> complex """
        pass

    def magxy(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ magxy( (cvector_t)arg1) -> complex """
        pass

    def magxy2(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ magxy2( (cvector_t)arg1) -> complex """
        pass

    def setLambdaAlphaPhi(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setLambdaAlphaPhi( (cvector_t)arg1, (complex)_lambda, (complex)_alpha, (complex)_phi) -> None """
        pass

    def setX(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setX( (cvector_t)arg1, (complex)a) -> None """
        pass

    def setXYZ(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setXYZ( (cvector_t)arg1, (complex)x1, (complex)y1, (complex)z1) -> None """
        pass

    def setY(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setY( (cvector_t)arg1, (complex)a) -> None """
        pass

    def setZ(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setZ( (cvector_t)arg1, (complex)a) -> None """
        pass

    def x(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ x( (cvector_t)arg1) -> complex """
        pass

    def y(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ y( (cvector_t)arg1) -> complex """
        pass

    def z(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ z( (cvector_t)arg1) -> complex """
        pass

    def __getitem__(self, cvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __getitem__( (cvector_t)arg1, (int)i) -> complex
        
        __getitem__( (cvector_t)arg1, (int)i) -> object
        """
        pass

    def __iadd__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iadd__( (object)arg1, (cvector_t)arg2) -> object """
        pass

    def __idiv__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __idiv__( (object)arg1, (float)arg2) -> object """
        pass

    def __imul__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __imul__( (object)arg1, (float)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (complex)x1, (complex)y1, (complex)z1) -> None
        """
        pass

    def __isub__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __isub__( (object)arg1, (cvector_t)arg2) -> object """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 64


class Detector(IParameterized):
    # no doc
    def areParametersChanged(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (Detector)arg1) -> bool
        
        areParametersChanged( (Detector)arg1) -> bool
        """
        pass

    def assign(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ assign( (Detector)arg1, (Detector)other) -> Detector """
        pass

    def clear(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ clear( (Detector)arg1) -> None """
        pass

    def clearParameterPool(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (Detector)arg1) -> None
        
        clearParameterPool( (Detector)arg1) -> None
        """
        pass

    def createParameterTree(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (Detector)arg1) -> ParameterPool
        
        createParameterTree( (Detector)arg1) -> ParameterPool
        """
        pass

    def getAxis(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getAxis( (Detector)arg1, (int)index) -> IAxis """
        pass

    def getDetectorResolutionFunction(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDetectorResolutionFunction( (Detector)arg1) -> IDetectorResolution """
        pass

    def getDimension(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDimension( (Detector)arg1) -> int """
        pass

    def printParameters(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (Detector)arg1) -> None
        
        printParameters( (Detector)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (Detector)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (Detector)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (Detector)arg1) -> None
        
        setParametersAreChanged( (Detector)arg1) -> None
        """
        pass

    def setParameterValue(self, Detector, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (Detector)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (Detector)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (Detector)other) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 152


class IFormFactor(ISample):
    # no doc
    def areParametersChanged(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IFormFactor)arg1) -> bool
        
        areParametersChanged( (IFormFactor)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IFormFactor)arg1) -> None
        
        clearParameterPool( (IFormFactor)arg1) -> None
        """
        pass

    def clone(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IFormFactor)arg1) -> IFormFactor
        
        clone( (IFormFactor)arg1) -> None
        """
        pass

    def cloneInvertB(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (IFormFactor)arg1) -> ISample
        
        cloneInvertB( (IFormFactor)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (IFormFactor)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (IFormFactor)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IFormFactor)arg1) -> ParameterPool
        
        createParameterTree( (IFormFactor)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (IFormFactor)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (IFormFactor)arg1, (cvector_t)arg2, (Bin1DCVector)arg3, (Bin1D)arg4) -> None
        """
        pass

    def getCompositeSample(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (IFormFactor)arg1) -> ICompositeSample
        
        getCompositeSample( (IFormFactor)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (IFormFactor)arg1) -> float
        
        getHeight( (IFormFactor)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (IFormFactor)arg1) -> int
        
        getNumberOfStochasticParameters( (IFormFactor)arg1) -> int
        """
        pass

    def getRadius(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (IFormFactor)arg1) -> float
        
        getRadius( (IFormFactor)arg1) -> float
        """
        pass

    def getVolume(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (IFormFactor)arg1) -> float
        
        getVolume( (IFormFactor)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (IFormFactor)arg1) -> bool
        
        isDistributedFormFactor( (IFormFactor)arg1) -> bool
        """
        pass

    def printParameters(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IFormFactor)arg1) -> None
        
        printParameters( (IFormFactor)arg1) -> None
        """
        pass

    def printSampleTree(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (IFormFactor)arg1) -> None
        
        printSampleTree( (IFormFactor)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IFormFactor)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IFormFactor)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IFormFactor)arg1) -> None
        
        setParametersAreChanged( (IFormFactor)arg1) -> None
        """
        pass

    def setParameterValue(self, IFormFactor, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IFormFactor)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IFormFactor)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 120


class IFormFactorBorn(IFormFactor):
    # no doc
    def areParametersChanged(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IFormFactorBorn)arg1) -> bool
        
        areParametersChanged( (IFormFactorBorn)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IFormFactorBorn)arg1) -> None
        
        clearParameterPool( (IFormFactorBorn)arg1) -> None
        """
        pass

    def clone(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IFormFactorBorn)arg1) -> IFormFactorBorn
        
        clone( (IFormFactorBorn)arg1) -> None
        """
        pass

    def cloneInvertB(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (IFormFactorBorn)arg1) -> ISample
        
        cloneInvertB( (IFormFactorBorn)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (IFormFactorBorn)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (IFormFactorBorn)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IFormFactorBorn)arg1) -> ParameterPool
        
        createParameterTree( (IFormFactorBorn)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (IFormFactorBorn)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (IFormFactorBorn)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (IFormFactorBorn)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (IFormFactorBorn)arg1, (cvector_t)arg2) -> None
        """
        pass

    def getCompositeSample(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (IFormFactorBorn)arg1) -> ICompositeSample
        
        getCompositeSample( (IFormFactorBorn)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (IFormFactorBorn)arg1) -> float
        
        getHeight( (IFormFactorBorn)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (IFormFactorBorn)arg1) -> int
        
        getNumberOfStochasticParameters( (IFormFactorBorn)arg1) -> int
        """
        pass

    def getRadius(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (IFormFactorBorn)arg1) -> float
        
        getRadius( (IFormFactorBorn)arg1) -> float
        """
        pass

    def getVolume(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (IFormFactorBorn)arg1) -> float
        
        getVolume( (IFormFactorBorn)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (IFormFactorBorn)arg1) -> bool
        
        isDistributedFormFactor( (IFormFactorBorn)arg1) -> bool
        """
        pass

    def printParameters(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IFormFactorBorn)arg1) -> None
        
        printParameters( (IFormFactorBorn)arg1) -> None
        """
        pass

    def printSampleTree(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (IFormFactorBorn)arg1) -> None
        
        printSampleTree( (IFormFactorBorn)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IFormFactorBorn)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IFormFactorBorn)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IFormFactorBorn)arg1) -> None
        
        setParametersAreChanged( (IFormFactorBorn)arg1) -> None
        """
        pass

    def setParameterValue(self, IFormFactorBorn, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IFormFactorBorn)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IFormFactorBorn)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 120


class FormFactorBox(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorBox)arg1) -> bool
        
        areParametersChanged( (FormFactorBox)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorBox)arg1) -> None
        
        clearParameterPool( (FormFactorBox)arg1) -> None
        """
        pass

    def clone(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorBox)arg1) -> FormFactorBox
        
        clone( (FormFactorBox)arg1) -> FormFactorBox
        """
        pass

    def cloneInvertB(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorBox)arg1) -> ISample
        
        cloneInvertB( (FormFactorBox)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorBox)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorBox)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorBox)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorBox)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorBox)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorBox)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorBox)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorBox)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorBox)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorBox)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorBox)arg1) -> float
        
        getHeight( (FormFactorBox)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorBox)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorBox)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorBox)arg1) -> float
        
        getRadius( (FormFactorBox)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorBox)arg1) -> float
        
        getVolume( (FormFactorBox)arg1) -> float
        """
        pass

    def getWidth(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getWidth( (FormFactorBox)arg1) -> float """
        pass

    def isDistributedFormFactor(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorBox)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorBox)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorBox)arg1) -> None
        
        printParameters( (FormFactorBox)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorBox)arg1) -> None
        
        printSampleTree( (FormFactorBox)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorBox)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorBox)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorBox)arg1) -> None
        
        setParametersAreChanged( (FormFactorBox)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorBox, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorBox)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorBox)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)length, (float)width, (float)height) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class FormFactorCone(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorCone)arg1) -> bool
        
        areParametersChanged( (FormFactorCone)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorCone)arg1) -> None
        
        clearParameterPool( (FormFactorCone)arg1) -> None
        """
        pass

    def clone(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorCone)arg1) -> FormFactorCone
        
        clone( (FormFactorCone)arg1) -> FormFactorCone
        """
        pass

    def cloneInvertB(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorCone)arg1) -> ISample
        
        cloneInvertB( (FormFactorCone)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorCone)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorCone)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorCone)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorCone)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorCone)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorCone)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorCone)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorCone)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorCone)arg1) -> float
        
        getHeight( (FormFactorCone)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorCone)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorCone)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorCone)arg1) -> float
        
        getRadius( (FormFactorCone)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorCone)arg1) -> float
        
        getVolume( (FormFactorCone)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorCone)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorCone)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorCone)arg1) -> None
        
        printParameters( (FormFactorCone)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorCone)arg1) -> None
        
        printSampleTree( (FormFactorCone)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorCone)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorCone)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorCone)arg1) -> None
        
        setParametersAreChanged( (FormFactorCone)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorCone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorCone)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorCone)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)radius, (float)height, (float)alpha) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 192


class FormFactorCrystal(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorCrystal)arg1) -> bool
        
        areParametersChanged( (FormFactorCrystal)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorCrystal)arg1) -> None
        
        clearParameterPool( (FormFactorCrystal)arg1) -> None
        """
        pass

    def clone(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorCrystal)arg1) -> FormFactorCrystal
        
        clone( (FormFactorCrystal)arg1) -> FormFactorCrystal
        """
        pass

    def cloneInvertB(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorCrystal)arg1) -> ISample
        
        cloneInvertB( (FormFactorCrystal)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorCrystal)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorCrystal)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorCrystal)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorCrystal)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorCrystal)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorCrystal)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorCrystal)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorCrystal)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorCrystal)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorCrystal)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorCrystal)arg1) -> float
        
        getHeight( (FormFactorCrystal)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorCrystal)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorCrystal)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorCrystal)arg1) -> float
        
        getRadius( (FormFactorCrystal)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorCrystal)arg1) -> float
        
        getVolume( (FormFactorCrystal)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorCrystal)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorCrystal)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorCrystal)arg1) -> None
        
        printParameters( (FormFactorCrystal)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorCrystal)arg1) -> None
        
        printSampleTree( (FormFactorCrystal)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorCrystal)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorCrystal)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorCrystal)arg1) -> None
        
        setParametersAreChanged( (FormFactorCrystal)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorCrystal)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorCrystal)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, *args, **kwargs): # real signature unknown
        """
        Raises an exception
        This class cannot be instantiated from Python
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass


class FormFactorCylinder(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorCylinder)arg1) -> bool
        
        areParametersChanged( (FormFactorCylinder)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorCylinder)arg1) -> None
        
        clearParameterPool( (FormFactorCylinder)arg1) -> None
        """
        pass

    def clone(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorCylinder)arg1) -> FormFactorCylinder
        
        clone( (FormFactorCylinder)arg1) -> FormFactorCylinder
        """
        pass

    def cloneInvertB(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorCylinder)arg1) -> ISample
        
        cloneInvertB( (FormFactorCylinder)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorCylinder)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorCylinder)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorCylinder)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorCylinder)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorCylinder)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorCylinder)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorCylinder)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorCylinder)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorCylinder)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorCylinder)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorCylinder)arg1) -> float
        
        getHeight( (FormFactorCylinder)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorCylinder)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorCylinder)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorCylinder)arg1) -> float
        
        getRadius( (FormFactorCylinder)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorCylinder)arg1) -> float
        
        getVolume( (FormFactorCylinder)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorCylinder)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorCylinder)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorCylinder)arg1) -> None
        
        printParameters( (FormFactorCylinder)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorCylinder)arg1) -> None
        
        printSampleTree( (FormFactorCylinder)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setHeight(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setHeight( (FormFactorCylinder)arg1, (float)height) -> None
        
        setHeight( (FormFactorCylinder)arg1, (float)height) -> None
        """
        pass

    def setMatchedParametersValue(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorCylinder)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorCylinder)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorCylinder)arg1) -> None
        
        setParametersAreChanged( (FormFactorCylinder)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorCylinder)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorCylinder)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setRadius(self, FormFactorCylinder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setRadius( (FormFactorCylinder)arg1, (float)radius) -> None
        
        setRadius( (FormFactorCylinder)arg1, (float)radius) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)height, (float)radius) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 136


class IFormFactorDecorator(IFormFactor):
    # no doc
    def areParametersChanged(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IFormFactorDecorator)arg1) -> bool
        
        areParametersChanged( (IFormFactorDecorator)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IFormFactorDecorator)arg1) -> None
        
        clearParameterPool( (IFormFactorDecorator)arg1) -> None
        """
        pass

    def clone(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IFormFactorDecorator)arg1) -> IFormFactorDecorator
        
        clone( (IFormFactorDecorator)arg1) -> None
        """
        pass

    def cloneInvertB(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (IFormFactorDecorator)arg1) -> ISample
        
        cloneInvertB( (IFormFactorDecorator)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (IFormFactorDecorator)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (IFormFactorDecorator)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IFormFactorDecorator)arg1) -> ParameterPool
        
        createParameterTree( (IFormFactorDecorator)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (IFormFactorDecorator)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (IFormFactorDecorator)arg1, (cvector_t)arg2, (Bin1DCVector)arg3, (Bin1D)arg4) -> None
        """
        pass

    def getCompositeSample(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (IFormFactorDecorator)arg1) -> ICompositeSample
        
        getCompositeSample( (IFormFactorDecorator)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (IFormFactorDecorator)arg1) -> float
        
        getHeight( (IFormFactorDecorator)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (IFormFactorDecorator)arg1) -> int
        
        getNumberOfStochasticParameters( (IFormFactorDecorator)arg1) -> int
        """
        pass

    def getRadius(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (IFormFactorDecorator)arg1) -> float
        
        getRadius( (IFormFactorDecorator)arg1) -> float
        """
        pass

    def getVolume(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (IFormFactorDecorator)arg1) -> float
        
        getVolume( (IFormFactorDecorator)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (IFormFactorDecorator)arg1) -> bool
        
        isDistributedFormFactor( (IFormFactorDecorator)arg1) -> bool
        """
        pass

    def printParameters(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IFormFactorDecorator)arg1) -> None
        
        printParameters( (IFormFactorDecorator)arg1) -> None
        """
        pass

    def printSampleTree(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (IFormFactorDecorator)arg1) -> None
        
        printSampleTree( (IFormFactorDecorator)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IFormFactorDecorator)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IFormFactorDecorator)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IFormFactorDecorator)arg1) -> None
        
        setParametersAreChanged( (IFormFactorDecorator)arg1) -> None
        """
        pass

    def setParameterValue(self, IFormFactorDecorator, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IFormFactorDecorator)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IFormFactorDecorator)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, *args, **kwargs): # real signature unknown
        """
        Raises an exception
        This class cannot be instantiated from Python
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass


class FormFactorDecoratorDebyeWaller(IFormFactorDecorator):
    # no doc
    def areParametersChanged(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorDecoratorDebyeWaller)arg1) -> bool
        
        areParametersChanged( (FormFactorDecoratorDebyeWaller)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorDecoratorDebyeWaller)arg1) -> None
        
        clearParameterPool( (FormFactorDecoratorDebyeWaller)arg1) -> None
        """
        pass

    def clone(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorDecoratorDebyeWaller)arg1) -> FormFactorDecoratorDebyeWaller
        
        clone( (FormFactorDecoratorDebyeWaller)arg1) -> FormFactorDecoratorDebyeWaller
        """
        pass

    def cloneInvertB(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorDecoratorDebyeWaller)arg1) -> ISample
        
        cloneInvertB( (FormFactorDecoratorDebyeWaller)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorDecoratorDebyeWaller)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorDecoratorDebyeWaller)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorDecoratorDebyeWaller)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorDecoratorDebyeWaller)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorDecoratorDebyeWaller)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorDecoratorDebyeWaller)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorDecoratorDebyeWaller)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorDecoratorDebyeWaller)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorDecoratorDebyeWaller)arg1) -> float
        
        getHeight( (FormFactorDecoratorDebyeWaller)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorDecoratorDebyeWaller)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorDecoratorDebyeWaller)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorDecoratorDebyeWaller)arg1) -> float
        
        getRadius( (FormFactorDecoratorDebyeWaller)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorDecoratorDebyeWaller)arg1) -> float
        
        getVolume( (FormFactorDecoratorDebyeWaller)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorDecoratorDebyeWaller)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorDecoratorDebyeWaller)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorDecoratorDebyeWaller)arg1) -> None
        
        printParameters( (FormFactorDecoratorDebyeWaller)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorDecoratorDebyeWaller)arg1) -> None
        
        printSampleTree( (FormFactorDecoratorDebyeWaller)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorDecoratorDebyeWaller)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorDecoratorDebyeWaller)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorDecoratorDebyeWaller)arg1) -> None
        
        setParametersAreChanged( (FormFactorDecoratorDebyeWaller)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorDecoratorDebyeWaller, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorDecoratorDebyeWaller)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorDecoratorDebyeWaller)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (IFormFactor)p_form_factor, (float)dw_h_factor, (float)dw_r_factor) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class FormFactorEllipsoid(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorEllipsoid)arg1) -> bool
        
        areParametersChanged( (FormFactorEllipsoid)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorEllipsoid)arg1) -> None
        
        clearParameterPool( (FormFactorEllipsoid)arg1) -> None
        """
        pass

    def clone(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorEllipsoid)arg1) -> FormFactorEllipsoid
        
        clone( (FormFactorEllipsoid)arg1) -> FormFactorEllipsoid
        """
        pass

    def cloneInvertB(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorEllipsoid)arg1) -> ISample
        
        cloneInvertB( (FormFactorEllipsoid)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorEllipsoid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorEllipsoid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorEllipsoid)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorEllipsoid)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorEllipsoid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorEllipsoid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorEllipsoid)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorEllipsoid)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorEllipsoid)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorEllipsoid)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorEllipsoid)arg1) -> float
        
        getHeight( (FormFactorEllipsoid)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorEllipsoid)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorEllipsoid)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorEllipsoid)arg1) -> float
        
        getRadius( (FormFactorEllipsoid)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorEllipsoid)arg1) -> float
        
        getVolume( (FormFactorEllipsoid)arg1) -> float
        """
        pass

    def getWidth(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getWidth( (FormFactorEllipsoid)arg1) -> float """
        pass

    def isDistributedFormFactor(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorEllipsoid)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorEllipsoid)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorEllipsoid)arg1) -> None
        
        printParameters( (FormFactorEllipsoid)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorEllipsoid)arg1) -> None
        
        printSampleTree( (FormFactorEllipsoid)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorEllipsoid)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorEllipsoid)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorEllipsoid)arg1) -> None
        
        setParametersAreChanged( (FormFactorEllipsoid)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorEllipsoid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorEllipsoid)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorEllipsoid)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)radius, (float)width, (float)height, (float)alpha) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 152


class FormFactorFullSphere(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorFullSphere)arg1) -> bool
        
        areParametersChanged( (FormFactorFullSphere)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorFullSphere)arg1) -> None
        
        clearParameterPool( (FormFactorFullSphere)arg1) -> None
        """
        pass

    def clone(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorFullSphere)arg1) -> FormFactorFullSphere
        
        clone( (FormFactorFullSphere)arg1) -> FormFactorFullSphere
        """
        pass

    def cloneInvertB(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorFullSphere)arg1) -> ISample
        
        cloneInvertB( (FormFactorFullSphere)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorFullSphere)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorFullSphere)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorFullSphere)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorFullSphere)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorFullSphere)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorFullSphere)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorFullSphere)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorFullSphere)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorFullSphere)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorFullSphere)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorFullSphere)arg1) -> float
        
        getHeight( (FormFactorFullSphere)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorFullSphere)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorFullSphere)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorFullSphere)arg1) -> float
        
        getRadius( (FormFactorFullSphere)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorFullSphere)arg1) -> float
        
        getVolume( (FormFactorFullSphere)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorFullSphere)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorFullSphere)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorFullSphere)arg1) -> None
        
        printParameters( (FormFactorFullSphere)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorFullSphere)arg1) -> None
        
        printSampleTree( (FormFactorFullSphere)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorFullSphere)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorFullSphere)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorFullSphere)arg1) -> None
        
        setParametersAreChanged( (FormFactorFullSphere)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorFullSphere)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorFullSphere)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setRadius(self, FormFactorFullSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setRadius( (FormFactorFullSphere)arg1, (float)radius) -> None
        
        setRadius( (FormFactorFullSphere)arg1, (float)radius) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)radius) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 128


class FormFactorFullSpheroid(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorFullSpheroid)arg1) -> bool
        
        areParametersChanged( (FormFactorFullSpheroid)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorFullSpheroid)arg1) -> None
        
        clearParameterPool( (FormFactorFullSpheroid)arg1) -> None
        """
        pass

    def clone(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorFullSpheroid)arg1) -> FormFactorFullSpheroid
        
        clone( (FormFactorFullSpheroid)arg1) -> FormFactorFullSpheroid
        """
        pass

    def cloneInvertB(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorFullSpheroid)arg1) -> ISample
        
        cloneInvertB( (FormFactorFullSpheroid)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorFullSpheroid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorFullSpheroid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorFullSpheroid)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorFullSpheroid)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorFullSpheroid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorFullSpheroid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorFullSpheroid)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorFullSpheroid)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorFullSpheroid)arg1) -> float
        
        getHeight( (FormFactorFullSpheroid)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorFullSpheroid)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorFullSpheroid)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorFullSpheroid)arg1) -> float
        
        getRadius( (FormFactorFullSpheroid)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorFullSpheroid)arg1) -> float
        
        getVolume( (FormFactorFullSpheroid)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorFullSpheroid)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorFullSpheroid)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorFullSpheroid)arg1) -> None
        
        printParameters( (FormFactorFullSpheroid)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorFullSpheroid)arg1) -> None
        
        printSampleTree( (FormFactorFullSpheroid)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorFullSpheroid)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorFullSpheroid)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorFullSpheroid)arg1) -> None
        
        setParametersAreChanged( (FormFactorFullSpheroid)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorFullSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorFullSpheroid)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorFullSpheroid)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)radius, (float)height) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 184


class FormFactorGauss(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorGauss)arg1) -> bool
        
        areParametersChanged( (FormFactorGauss)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorGauss)arg1) -> None
        
        clearParameterPool( (FormFactorGauss)arg1) -> None
        """
        pass

    def clone(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorGauss)arg1) -> FormFactorGauss
        
        clone( (FormFactorGauss)arg1) -> FormFactorGauss
        """
        pass

    def cloneInvertB(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorGauss)arg1) -> ISample
        
        cloneInvertB( (FormFactorGauss)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorGauss)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorGauss)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorGauss)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorGauss)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorGauss)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorGauss)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorGauss)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorGauss)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorGauss)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorGauss)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorGauss)arg1) -> float
        
        getHeight( (FormFactorGauss)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorGauss)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorGauss)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorGauss)arg1) -> float
        
        getRadius( (FormFactorGauss)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorGauss)arg1) -> float
        
        getVolume( (FormFactorGauss)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorGauss)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorGauss)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorGauss)arg1) -> None
        
        printParameters( (FormFactorGauss)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorGauss)arg1) -> None
        
        printSampleTree( (FormFactorGauss)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorGauss)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorGauss)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorGauss)arg1) -> None
        
        setParametersAreChanged( (FormFactorGauss)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorGauss, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorGauss)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorGauss)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1, (float)volume) -> None
        
        __init__( (object)arg1, (float)height, (float)width) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class FormFactorHemiSpheroid(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorHemiSpheroid)arg1) -> bool
        
        areParametersChanged( (FormFactorHemiSpheroid)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorHemiSpheroid)arg1) -> None
        
        clearParameterPool( (FormFactorHemiSpheroid)arg1) -> None
        """
        pass

    def clone(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorHemiSpheroid)arg1) -> FormFactorHemiSpheroid
        
        clone( (FormFactorHemiSpheroid)arg1) -> FormFactorHemiSpheroid
        """
        pass

    def cloneInvertB(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorHemiSpheroid)arg1) -> ISample
        
        cloneInvertB( (FormFactorHemiSpheroid)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorHemiSpheroid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorHemiSpheroid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorHemiSpheroid)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorHemiSpheroid)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorHemiSpheroid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorHemiSpheroid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorHemiSpheroid)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorHemiSpheroid)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorHemiSpheroid)arg1) -> float
        
        getHeight( (FormFactorHemiSpheroid)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorHemiSpheroid)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorHemiSpheroid)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorHemiSpheroid)arg1) -> float
        
        getRadius( (FormFactorHemiSpheroid)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorHemiSpheroid)arg1) -> float
        
        getVolume( (FormFactorHemiSpheroid)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorHemiSpheroid)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorHemiSpheroid)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorHemiSpheroid)arg1) -> None
        
        printParameters( (FormFactorHemiSpheroid)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorHemiSpheroid)arg1) -> None
        
        printSampleTree( (FormFactorHemiSpheroid)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorHemiSpheroid)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorHemiSpheroid)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorHemiSpheroid)arg1) -> None
        
        setParametersAreChanged( (FormFactorHemiSpheroid)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorHemiSpheroid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorHemiSpheroid)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorHemiSpheroid)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)radius, (float)width, (float)height) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 192


class FormFactorLorentz(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorLorentz)arg1) -> bool
        
        areParametersChanged( (FormFactorLorentz)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorLorentz)arg1) -> None
        
        clearParameterPool( (FormFactorLorentz)arg1) -> None
        """
        pass

    def clone(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorLorentz)arg1) -> FormFactorLorentz
        
        clone( (FormFactorLorentz)arg1) -> FormFactorLorentz
        """
        pass

    def cloneInvertB(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorLorentz)arg1) -> ISample
        
        cloneInvertB( (FormFactorLorentz)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorLorentz)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorLorentz)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorLorentz)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorLorentz)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorLorentz)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorLorentz)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorLorentz)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorLorentz)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorLorentz)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorLorentz)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorLorentz)arg1) -> float
        
        getHeight( (FormFactorLorentz)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorLorentz)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorLorentz)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorLorentz)arg1) -> float
        
        getRadius( (FormFactorLorentz)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorLorentz)arg1) -> float
        
        getVolume( (FormFactorLorentz)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorLorentz)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorLorentz)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorLorentz)arg1) -> None
        
        printParameters( (FormFactorLorentz)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorLorentz)arg1) -> None
        
        printSampleTree( (FormFactorLorentz)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorLorentz)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorLorentz)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorLorentz)arg1) -> None
        
        setParametersAreChanged( (FormFactorLorentz)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorLorentz, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorLorentz)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorLorentz)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1, (float)volume) -> None
        
        __init__( (object)arg1, (float)height, (float)width) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 136


class FormFactorParallelepiped(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorParallelepiped)arg1) -> bool
        
        areParametersChanged( (FormFactorParallelepiped)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorParallelepiped)arg1) -> None
        
        clearParameterPool( (FormFactorParallelepiped)arg1) -> None
        """
        pass

    def clone(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorParallelepiped)arg1) -> FormFactorParallelepiped
        
        clone( (FormFactorParallelepiped)arg1) -> FormFactorParallelepiped
        """
        pass

    def cloneInvertB(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorParallelepiped)arg1) -> ISample
        
        cloneInvertB( (FormFactorParallelepiped)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorParallelepiped)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorParallelepiped)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorParallelepiped)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorParallelepiped)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorParallelepiped)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorParallelepiped)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorParallelepiped)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorParallelepiped)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorParallelepiped)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorParallelepiped)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorParallelepiped)arg1) -> float
        
        getHeight( (FormFactorParallelepiped)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorParallelepiped)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorParallelepiped)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorParallelepiped)arg1) -> float
        
        getRadius( (FormFactorParallelepiped)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorParallelepiped)arg1) -> float
        
        getVolume( (FormFactorParallelepiped)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorParallelepiped)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorParallelepiped)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorParallelepiped)arg1) -> None
        
        printParameters( (FormFactorParallelepiped)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorParallelepiped)arg1) -> None
        
        printSampleTree( (FormFactorParallelepiped)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorParallelepiped)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorParallelepiped)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorParallelepiped)arg1) -> None
        
        setParametersAreChanged( (FormFactorParallelepiped)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorParallelepiped, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorParallelepiped)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorParallelepiped)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)height, (float)radius) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 136


class FormFactorPrism3(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorPrism3)arg1) -> bool
        
        areParametersChanged( (FormFactorPrism3)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorPrism3)arg1) -> None
        
        clearParameterPool( (FormFactorPrism3)arg1) -> None
        """
        pass

    def clone(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorPrism3)arg1) -> FormFactorPrism3
        
        clone( (FormFactorPrism3)arg1) -> FormFactorPrism3
        """
        pass

    def cloneInvertB(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorPrism3)arg1) -> ISample
        
        cloneInvertB( (FormFactorPrism3)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorPrism3)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorPrism3)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorPrism3)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorPrism3)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorPrism3)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorPrism3)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorPrism3)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorPrism3)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorPrism3)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorPrism3)arg1) -> ICompositeSample
        """
        pass

    def getHalfSide(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHalfSide( (FormFactorPrism3)arg1) -> float
        
        getHalfSide( (FormFactorPrism3)arg1) -> float
        """
        pass

    def getHeight(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorPrism3)arg1) -> float
        
        getHeight( (FormFactorPrism3)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorPrism3)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorPrism3)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorPrism3)arg1) -> float
        
        getRadius( (FormFactorPrism3)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorPrism3)arg1) -> float
        
        getVolume( (FormFactorPrism3)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorPrism3)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorPrism3)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorPrism3)arg1) -> None
        
        printParameters( (FormFactorPrism3)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorPrism3)arg1) -> None
        
        printSampleTree( (FormFactorPrism3)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setHalfSide(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setHalfSide( (FormFactorPrism3)arg1, (float)half_side) -> None
        
        setHalfSide( (FormFactorPrism3)arg1, (float)half_side) -> None
        """
        pass

    def setHeight(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setHeight( (FormFactorPrism3)arg1, (float)height) -> None
        
        setHeight( (FormFactorPrism3)arg1, (float)height) -> None
        """
        pass

    def setMatchedParametersValue(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorPrism3)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorPrism3)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorPrism3)arg1) -> None
        
        setParametersAreChanged( (FormFactorPrism3)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorPrism3, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorPrism3)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorPrism3)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)height, (float)half_side) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class FormFactorPrism6(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorPrism6)arg1) -> bool
        
        areParametersChanged( (FormFactorPrism6)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorPrism6)arg1) -> None
        
        clearParameterPool( (FormFactorPrism6)arg1) -> None
        """
        pass

    def clone(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorPrism6)arg1) -> FormFactorPrism6
        
        clone( (FormFactorPrism6)arg1) -> FormFactorPrism6
        """
        pass

    def cloneInvertB(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorPrism6)arg1) -> ISample
        
        cloneInvertB( (FormFactorPrism6)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorPrism6)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorPrism6)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorPrism6)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorPrism6)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorPrism6)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorPrism6)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorPrism6)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorPrism6)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorPrism6)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorPrism6)arg1) -> ICompositeSample
        """
        pass

    def getHalfSide(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHalfSide( (FormFactorPrism6)arg1) -> float
        
        getHalfSide( (FormFactorPrism6)arg1) -> float
        """
        pass

    def getHeight(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorPrism6)arg1) -> float
        
        getHeight( (FormFactorPrism6)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorPrism6)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorPrism6)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorPrism6)arg1) -> float
        
        getRadius( (FormFactorPrism6)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorPrism6)arg1) -> float
        
        getVolume( (FormFactorPrism6)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorPrism6)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorPrism6)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorPrism6)arg1) -> None
        
        printParameters( (FormFactorPrism6)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorPrism6)arg1) -> None
        
        printSampleTree( (FormFactorPrism6)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setHalfSide(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setHalfSide( (FormFactorPrism6)arg1, (float)half_side) -> None
        
        setHalfSide( (FormFactorPrism6)arg1, (float)half_side) -> None
        """
        pass

    def setHeight(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setHeight( (FormFactorPrism6)arg1, (float)height) -> None
        
        setHeight( (FormFactorPrism6)arg1, (float)height) -> None
        """
        pass

    def setMatchedParametersValue(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorPrism6)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorPrism6)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorPrism6)arg1) -> None
        
        setParametersAreChanged( (FormFactorPrism6)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorPrism6, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorPrism6)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorPrism6)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)height, (float)half_side) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class FormFactorPyramid(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorPyramid)arg1) -> bool
        
        areParametersChanged( (FormFactorPyramid)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorPyramid)arg1) -> None
        
        clearParameterPool( (FormFactorPyramid)arg1) -> None
        """
        pass

    def clone(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorPyramid)arg1) -> FormFactorPyramid
        
        clone( (FormFactorPyramid)arg1) -> FormFactorPyramid
        """
        pass

    def cloneInvertB(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorPyramid)arg1) -> ISample
        
        cloneInvertB( (FormFactorPyramid)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorPyramid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorPyramid)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorPyramid)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorPyramid)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorPyramid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorPyramid)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorPyramid)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorPyramid)arg1, (cvector_t)q) -> complex
        """
        pass

    def getAlpha(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getAlpha( (FormFactorPyramid)arg1) -> float
        
        getAlpha( (FormFactorPyramid)arg1) -> float
        """
        pass

    def getCompositeSample(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorPyramid)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorPyramid)arg1) -> ICompositeSample
        """
        pass

    def getHalfSide(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHalfSide( (FormFactorPyramid)arg1) -> float
        
        getHalfSide( (FormFactorPyramid)arg1) -> float
        """
        pass

    def getHeight(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorPyramid)arg1) -> float
        
        getHeight( (FormFactorPyramid)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorPyramid)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorPyramid)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorPyramid)arg1) -> float
        
        getRadius( (FormFactorPyramid)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorPyramid)arg1) -> float
        
        getVolume( (FormFactorPyramid)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorPyramid)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorPyramid)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorPyramid)arg1) -> None
        
        printParameters( (FormFactorPyramid)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorPyramid)arg1) -> None
        
        printSampleTree( (FormFactorPyramid)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setAlpha(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setAlpha( (FormFactorPyramid)arg1, (float)alpha) -> None
        
        setAlpha( (FormFactorPyramid)arg1, (float)alpha) -> None
        """
        pass

    def setHalfSide(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setHalfSide( (FormFactorPyramid)arg1, (float)half_side) -> None
        
        setHalfSide( (FormFactorPyramid)arg1, (float)half_side) -> None
        """
        pass

    def setHeight(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setHeight( (FormFactorPyramid)arg1, (float)height) -> None
        
        setHeight( (FormFactorPyramid)arg1, (float)height) -> None
        """
        pass

    def setMatchedParametersValue(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorPyramid)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorPyramid)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorPyramid)arg1) -> None
        
        setParametersAreChanged( (FormFactorPyramid)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorPyramid, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorPyramid)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorPyramid)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)height, (float)half_side, (float)alpha) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class FormFactorSphere(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorSphere)arg1) -> bool
        
        areParametersChanged( (FormFactorSphere)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorSphere)arg1) -> None
        
        clearParameterPool( (FormFactorSphere)arg1) -> None
        """
        pass

    def clone(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorSphere)arg1) -> FormFactorSphere
        
        clone( (FormFactorSphere)arg1) -> FormFactorSphere
        """
        pass

    def cloneInvertB(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorSphere)arg1) -> ISample
        
        cloneInvertB( (FormFactorSphere)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorSphere)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorSphere)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorSphere)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorSphere)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorSphere)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorSphere)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorSphere)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorSphere)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorSphere)arg1) -> float
        
        getHeight( (FormFactorSphere)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorSphere)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorSphere)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorSphere)arg1) -> float
        
        getRadius( (FormFactorSphere)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorSphere)arg1) -> float
        
        getVolume( (FormFactorSphere)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorSphere)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorSphere)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorSphere)arg1) -> None
        
        printParameters( (FormFactorSphere)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorSphere)arg1) -> None
        
        printSampleTree( (FormFactorSphere)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorSphere)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorSphere)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorSphere)arg1) -> None
        
        setParametersAreChanged( (FormFactorSphere)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorSphere, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorSphere)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorSphere)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)radius, (float)height) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 192


class FormFactorSphereGaussianRadius(IFormFactorBorn):
    # no doc
    def areParametersChanged(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FormFactorSphereGaussianRadius)arg1) -> bool
        
        areParametersChanged( (FormFactorSphereGaussianRadius)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FormFactorSphereGaussianRadius)arg1) -> None
        
        clearParameterPool( (FormFactorSphereGaussianRadius)arg1) -> None
        """
        pass

    def clone(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FormFactorSphereGaussianRadius)arg1) -> FormFactorSphereGaussianRadius
        
        clone( (FormFactorSphereGaussianRadius)arg1) -> FormFactorSphereGaussianRadius
        """
        pass

    def cloneInvertB(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (FormFactorSphereGaussianRadius)arg1) -> ISample
        
        cloneInvertB( (FormFactorSphereGaussianRadius)arg1) -> ISample
        """
        pass

    def createDistributedFormFactors(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createDistributedFormFactors( (FormFactorSphereGaussianRadius)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        
        createDistributedFormFactors( (FormFactorSphereGaussianRadius)arg1, (vector_IFormFactorPtr_t)form_factors, (vdouble1d_t)probabilities, (int)nbr_samples) -> None
        """
        pass

    def createParameterTree(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FormFactorSphereGaussianRadius)arg1) -> ParameterPool
        
        createParameterTree( (FormFactorSphereGaussianRadius)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FormFactorSphereGaussianRadius)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        
        evaluate( (FormFactorSphereGaussianRadius)arg1, (cvector_t)k_i, (Bin1DCVector)k_f_bin, (Bin1D)alpha_f_bin) -> complex
        """
        pass

    def evaluate_for_q(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate_for_q( (FormFactorSphereGaussianRadius)arg1, (cvector_t)q) -> complex
        
        evaluate_for_q( (FormFactorSphereGaussianRadius)arg1, (cvector_t)q) -> complex
        """
        pass

    def getCompositeSample(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (FormFactorSphereGaussianRadius)arg1) -> ICompositeSample
        
        getCompositeSample( (FormFactorSphereGaussianRadius)arg1) -> ICompositeSample
        """
        pass

    def getHeight(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHeight( (FormFactorSphereGaussianRadius)arg1) -> float
        
        getHeight( (FormFactorSphereGaussianRadius)arg1) -> float
        """
        pass

    def getNumberOfStochasticParameters(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfStochasticParameters( (FormFactorSphereGaussianRadius)arg1) -> int
        
        getNumberOfStochasticParameters( (FormFactorSphereGaussianRadius)arg1) -> int
        """
        pass

    def getRadius(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRadius( (FormFactorSphereGaussianRadius)arg1) -> float
        
        getRadius( (FormFactorSphereGaussianRadius)arg1) -> float
        """
        pass

    def getVolume(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getVolume( (FormFactorSphereGaussianRadius)arg1) -> float
        
        getVolume( (FormFactorSphereGaussianRadius)arg1) -> float
        """
        pass

    def isDistributedFormFactor(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isDistributedFormFactor( (FormFactorSphereGaussianRadius)arg1) -> bool
        
        isDistributedFormFactor( (FormFactorSphereGaussianRadius)arg1) -> bool
        """
        pass

    def printParameters(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FormFactorSphereGaussianRadius)arg1) -> None
        
        printParameters( (FormFactorSphereGaussianRadius)arg1) -> None
        """
        pass

    def printSampleTree(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (FormFactorSphereGaussianRadius)arg1) -> None
        
        printSampleTree( (FormFactorSphereGaussianRadius)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FormFactorSphereGaussianRadius)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FormFactorSphereGaussianRadius)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FormFactorSphereGaussianRadius)arg1) -> None
        
        setParametersAreChanged( (FormFactorSphereGaussianRadius)arg1) -> None
        """
        pass

    def setParameterValue(self, FormFactorSphereGaussianRadius, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FormFactorSphereGaussianRadius)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FormFactorSphereGaussianRadius)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)mean, (float)sigma) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 200


class IFTDistribution2D(IParameterized):
    # no doc
    def areParametersChanged(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IFTDistribution2D)arg1) -> bool
        
        areParametersChanged( (IFTDistribution2D)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IFTDistribution2D)arg1) -> None
        
        clearParameterPool( (IFTDistribution2D)arg1) -> None
        """
        pass

    def clone(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IFTDistribution2D)arg1) -> IFTDistribution2D
        
        clone( (IFTDistribution2D)arg1) -> None
        """
        pass

    def createParameterTree(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IFTDistribution2D)arg1) -> ParameterPool
        
        createParameterTree( (IFTDistribution2D)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (IFTDistribution2D)arg1, (float)qx, (float)qy) -> float
        
        evaluate( (IFTDistribution2D)arg1, (float)arg2, (float)arg3) -> None
        """
        pass

    def getDelta(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDelta( (IFTDistribution2D)arg1) -> float """
        pass

    def getGamma(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getGamma( (IFTDistribution2D)arg1) -> float """
        pass

    def printParameters(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IFTDistribution2D)arg1) -> None
        
        printParameters( (IFTDistribution2D)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setGamma(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setGamma( (IFTDistribution2D)arg1, (float)gamma) -> None """
        pass

    def setMatchedParametersValue(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IFTDistribution2D)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IFTDistribution2D)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IFTDistribution2D)arg1) -> None
        
        setParametersAreChanged( (IFTDistribution2D)arg1) -> None
        """
        pass

    def setParameterValue(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IFTDistribution2D)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IFTDistribution2D)arg1, (str)name, (float)value) -> bool
        """
        pass

    def transformToStarBasis(self, IFTDistribution2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        transformToStarBasis( (IFTDistribution2D)arg1, (float)qX, (float)qY, (float)alpha, (float)a, (float)b, (float)qa, (float)qb) -> None
        
        transformToStarBasis( (IFTDistribution2D)arg1, (float)arg2, (float)arg3, (float)arg4, (float)arg5, (float)arg6, (float)arg7, (float)arg8) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)omega_x, (float)omega_y) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class FTDistribution2DCauchy(IFTDistribution2D):
    # no doc
    def areParametersChanged(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (FTDistribution2DCauchy)arg1) -> bool
        
        areParametersChanged( (FTDistribution2DCauchy)arg1) -> bool
        """
        pass

    def clearParameterPool(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (FTDistribution2DCauchy)arg1) -> None
        
        clearParameterPool( (FTDistribution2DCauchy)arg1) -> None
        """
        pass

    def clone(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (FTDistribution2DCauchy)arg1) -> FTDistribution2DCauchy
        
        clone( (FTDistribution2DCauchy)arg1) -> FTDistribution2DCauchy
        """
        pass

    def createParameterTree(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (FTDistribution2DCauchy)arg1) -> ParameterPool
        
        createParameterTree( (FTDistribution2DCauchy)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (FTDistribution2DCauchy)arg1, (float)qx, (float)qy) -> float
        
        evaluate( (FTDistribution2DCauchy)arg1, (float)qx, (float)qy) -> float
        """
        pass

    def printParameters(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (FTDistribution2DCauchy)arg1) -> None
        
        printParameters( (FTDistribution2DCauchy)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (FTDistribution2DCauchy)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (FTDistribution2DCauchy)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (FTDistribution2DCauchy)arg1) -> None
        
        setParametersAreChanged( (FTDistribution2DCauchy)arg1) -> None
        """
        pass

    def setParameterValue(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (FTDistribution2DCauchy)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (FTDistribution2DCauchy)arg1, (str)name, (float)value) -> bool
        """
        pass

    def transformToStarBasis(self, FTDistribution2DCauchy, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        transformToStarBasis( (FTDistribution2DCauchy)arg1, (float)qX, (float)qY, (float)alpha, (float)a, (float)b, (float)qa, (float)qb) -> None
        
        transformToStarBasis( (FTDistribution2DCauchy)arg1, (float)qX, (float)qY, (float)alpha, (float)a, (float)b, (float)qa, (float)qb) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)omega_x, (float)omega_y) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class IMaterial(__Boost_Python.instance):
    # no doc
    def getRefractiveIndex(self, IMaterial, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRefractiveIndex( (IMaterial)arg1) -> complex
        
        getRefractiveIndex( (IMaterial)arg1) -> complex
        """
        pass

    def isScalarMaterial(self, IMaterial, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isScalarMaterial( (IMaterial)arg1) -> bool
        
        isScalarMaterial( (IMaterial)arg1) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (str)name) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 40


class HomogeneousMaterial(IMaterial):
    # no doc
    def getRefractiveIndex(self, HomogeneousMaterial, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRefractiveIndex( (HomogeneousMaterial)arg1) -> complex
        
        getRefractiveIndex( (HomogeneousMaterial)arg1) -> complex
        """
        pass

    def isScalarMaterial(self, HomogeneousMaterial, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        isScalarMaterial( (HomogeneousMaterial)arg1) -> bool
        
        isScalarMaterial( (HomogeneousMaterial)arg1) -> bool
        """
        pass

    def setRefractiveIndex(self, HomogeneousMaterial, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setRefractiveIndex( (HomogeneousMaterial)arg1, (complex)refractive_index) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1, (str)name, (complex)refractive_index) -> None
        
        __init__( (object)arg1, (str)name, (float)refractive_index_delta, (float)refractive_index_beta) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 56


class IDecoration(ICompositeSample):
    # no doc
    def accept(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        accept( (IDecoration)arg1, (object)p_visitor) -> None
        
        accept( (IDecoration)arg1, (object)arg2) -> None
        """
        pass

    def areParametersChanged(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IDecoration)arg1) -> bool
        
        areParametersChanged( (IDecoration)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IDecoration)arg1) -> None
        
        clearParameterPool( (IDecoration)arg1) -> None
        """
        pass

    def clone(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IDecoration)arg1) -> IDecoration
        
        clone( (IDecoration)arg1) -> None
        """
        pass

    def cloneInvertB(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (IDecoration)arg1) -> IDecoration
        
        cloneInvertB( (IDecoration)arg1) -> None
        """
        pass

    def createParameterTree(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IDecoration)arg1) -> ParameterPool
        
        createParameterTree( (IDecoration)arg1) -> ParameterPool
        """
        pass

    def getAbundanceFractionOfParticle(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getAbundanceFractionOfParticle( (IDecoration)arg1, (int)index) -> float
        
        getAbundanceFractionOfParticle( (IDecoration)arg1, (int)arg2) -> None
        """
        pass

    def getInterferenceFunctions(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getInterferenceFunctions( (IDecoration)arg1) -> object
        
        getInterferenceFunctions( (IDecoration)arg1) -> None
        """
        pass

    def getNumberOfInterferenceFunctions(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfInterferenceFunctions( (IDecoration)arg1) -> int
        
        getNumberOfInterferenceFunctions( (IDecoration)arg1) -> int
        """
        pass

    def getNumberOfParticles(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfParticles( (IDecoration)arg1) -> int
        
        getNumberOfParticles( (IDecoration)arg1) -> None
        """
        pass

    def getParticleInfo(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getParticleInfo( (IDecoration)arg1, (int)index) -> ParticleInfo
        
        getParticleInfo( (IDecoration)arg1, (int)arg2) -> None
        """
        pass

    def getTotalParticleSurfaceDensity(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getTotalParticleSurfaceDensity( (IDecoration)arg1) -> float """
        pass

    def printParameters(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IDecoration)arg1) -> None
        
        printParameters( (IDecoration)arg1) -> None
        """
        pass

    def printSampleTree(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (IDecoration)arg1) -> None
        
        printSampleTree( (IDecoration)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IDecoration)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IDecoration)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IDecoration)arg1) -> None
        
        setParametersAreChanged( (IDecoration)arg1) -> None
        """
        pass

    def setParameterValue(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IDecoration)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IDecoration)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setTotalParticleSurfaceDensity(self, IDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setTotalParticleSurfaceDensity( (IDecoration)arg1, (float)surface_density) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class IDetectorResolution(ICloneable, IParameterized):
    # no doc
    def applyDetectorResolution(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        applyDetectorResolution( (IDetectorResolution)arg1, (IntensityData)p_intensity_map) -> None
        
        applyDetectorResolution( (IDetectorResolution)arg1, (IntensityData)arg2) -> None
        """
        pass

    def areParametersChanged(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IDetectorResolution)arg1) -> bool
        
        areParametersChanged( (IDetectorResolution)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IDetectorResolution)arg1) -> None
        
        clearParameterPool( (IDetectorResolution)arg1) -> None
        """
        pass

    def clone(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IDetectorResolution)arg1) -> IDetectorResolution
        
        clone( (IDetectorResolution)arg1) -> None
        """
        pass

    def createParameterTree(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IDetectorResolution)arg1) -> ParameterPool
        
        createParameterTree( (IDetectorResolution)arg1) -> ParameterPool
        """
        pass

    def printParameters(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IDetectorResolution)arg1) -> None
        
        printParameters( (IDetectorResolution)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IDetectorResolution)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IDetectorResolution)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IDetectorResolution)arg1) -> None
        
        setParametersAreChanged( (IDetectorResolution)arg1) -> None
        """
        pass

    def setParameterValue(self, IDetectorResolution, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IDetectorResolution)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IDetectorResolution)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 120


class IInterferenceFunction(ISample):
    # no doc
    def areParametersChanged(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IInterferenceFunction)arg1) -> bool
        
        areParametersChanged( (IInterferenceFunction)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IInterferenceFunction)arg1) -> None
        
        clearParameterPool( (IInterferenceFunction)arg1) -> None
        """
        pass

    def clone(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IInterferenceFunction)arg1) -> IInterferenceFunction
        
        clone( (IInterferenceFunction)arg1) -> None
        """
        pass

    def cloneInvertB(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (IInterferenceFunction)arg1) -> ISample
        
        cloneInvertB( (IInterferenceFunction)arg1) -> ISample
        """
        pass

    def createParameterTree(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IInterferenceFunction)arg1) -> ParameterPool
        
        createParameterTree( (IInterferenceFunction)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (IInterferenceFunction)arg1, (cvector_t)q) -> float
        
        evaluate( (IInterferenceFunction)arg1, (cvector_t)arg2) -> None
        """
        pass

    def getCompositeSample(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (IInterferenceFunction)arg1) -> ICompositeSample
        
        getCompositeSample( (IInterferenceFunction)arg1) -> ICompositeSample
        """
        pass

    def getKappa(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getKappa( (IInterferenceFunction)arg1) -> float
        
        getKappa( (IInterferenceFunction)arg1) -> float
        """
        pass

    def printParameters(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IInterferenceFunction)arg1) -> None
        
        printParameters( (IInterferenceFunction)arg1) -> None
        """
        pass

    def printSampleTree(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (IInterferenceFunction)arg1) -> None
        
        printSampleTree( (IInterferenceFunction)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IInterferenceFunction)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IInterferenceFunction)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IInterferenceFunction)arg1) -> None
        
        setParametersAreChanged( (IInterferenceFunction)arg1) -> None
        """
        pass

    def setParameterValue(self, IInterferenceFunction, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IInterferenceFunction)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IInterferenceFunction)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 120


class Instrument(IParameterized):
    # no doc
    def areParametersChanged(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (Instrument)arg1) -> bool
        
        areParametersChanged( (Instrument)arg1) -> bool
        """
        pass

    def clearParameterPool(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (Instrument)arg1) -> None
        
        clearParameterPool( (Instrument)arg1) -> None
        """
        pass

    def createParameterTree(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (Instrument)arg1) -> ParameterPool
        
        createParameterTree( (Instrument)arg1) -> ParameterPool
        """
        pass

    def getBeam(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getBeam( (Instrument)arg1) -> Beam """
        pass

    def getDetector(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDetector( (Instrument)arg1) -> Detector """
        pass

    def getDetectorAxis(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDetectorAxis( (Instrument)arg1, (int)index) -> IAxis """
        pass

    def getDetectorDimension(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDetectorDimension( (Instrument)arg1) -> int """
        pass

    def getIntensity(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getIntensity( (Instrument)arg1) -> float """
        pass

    def matchDetectorParameters(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ matchDetectorParameters( (Instrument)arg1, (IntensityData)output_data) -> None """
        pass

    def printParameters(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (Instrument)arg1) -> None
        
        printParameters( (Instrument)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setBeam(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setBeam( (Instrument)arg1, (Beam)beam) -> None """
        pass

    def setBeamIntensity(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setBeamIntensity( (Instrument)arg1, (float)intensity) -> None """
        pass

    def setBeamParameters(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setBeamParameters( (Instrument)arg1, (float)lambda, (float)alpha_i, (float)phi_i) -> None """
        pass

    def setDetectorParameters(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setDetectorParameters( (Instrument)arg1, (int)n_phi, (float)phi_f_min, (float)phi_f_max, (int)n_alpha, (float)alpha_f_min, (float)alpha_f_max [, (bool)isgisaxs_style=False]) -> None
        
        setDetectorParameters( (Instrument)arg1, (object)params) -> None
        """
        pass

    def setDetectorResolutionFunction(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setDetectorResolutionFunction( (Instrument)arg1, (IResolutionFunction2D)p_resolution_function) -> None """
        pass

    def setMatchedParametersValue(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (Instrument)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (Instrument)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (Instrument)arg1) -> None
        
        setParametersAreChanged( (Instrument)arg1) -> None
        """
        pass

    def setParameterValue(self, Instrument, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (Instrument)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (Instrument)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (Instrument)other) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 464


class IntensityData(__Boost_Python.instance):
    # no doc
    def addAxis(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        addAxis( (IntensityData)arg1, (IAxis)new_axis) -> None
        
        addAxis( (IntensityData)arg1, (str)name, (int)size, (float)start, (float)end) -> None
        """
        pass

    def clear(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ clear( (IntensityData)arg1) -> None """
        pass

    def clone(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ clone( (IntensityData)arg1) -> IntensityData """
        pass

    def copyFrom(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ copyFrom( (IntensityData)arg1, (IntensityData)other) -> None """
        pass

    def getAllocatedSize(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getAllocatedSize( (IntensityData)arg1) -> int """
        pass

    def getAllSizes(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getAllSizes( (IntensityData)arg1) -> vector_longinteger_t """
        pass

    def getArray(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getArray( (IntensityData)arg1) -> object """
        pass

    def getAxis(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getAxis( (IntensityData)arg1, (int)index) -> IAxis
        
        getAxis( (IntensityData)arg1, (str)label) -> IAxis
        """
        pass

    def getAxisIndex(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getAxisIndex( (IntensityData)arg1, (str)label) -> int """
        pass

    def getIndexOfAxis(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getIndexOfAxis( (IntensityData)arg1, (str)axis_name, (int)total_index) -> int """
        pass

    def getRank(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getRank( (IntensityData)arg1) -> int """
        pass

    def getRawDataVector(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getRawDataVector( (IntensityData)arg1) -> vdouble1d_t """
        pass

    def getValueOfAxis(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getValueOfAxis( (IntensityData)arg1, (str)axis_name, (int)index) -> float """
        pass

    def hasSameDimensions(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ hasSameDimensions( (IntensityData)arg1, (IntensityData)right) -> bool """
        pass

    def hasSameShape(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ hasSameShape( (IntensityData)arg1, (IntensityData)right) -> bool """
        pass

    def removeAllMasks(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ removeAllMasks( (IntensityData)arg1) -> None """
        pass

    def scaleAll(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ scaleAll( (IntensityData)arg1, (float)factor) -> None """
        pass

    def setAllTo(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setAllTo( (IntensityData)arg1, (float)value) -> None """
        pass

    def setRawDataVector(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setRawDataVector( (IntensityData)arg1, (vdouble1d_t)data_vector) -> None """
        pass

    def toCoordinate(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ toCoordinate( (IntensityData)arg1, (int)index, (int)i_selected_axis) -> int """
        pass

    def toCoordinates(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ toCoordinates( (IntensityData)arg1, (int)index) -> vector_integer_t """
        pass

    def toIndex(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ toIndex( (IntensityData)arg1, (vector_integer_t)coordinates) -> int """
        pass

    def totalSum(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ totalSum( (IntensityData)arg1) -> float """
        pass

    def __getitem__(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __getitem__( (IntensityData)arg1, (int)index) -> float
        
        __getitem__( (IntensityData)arg1, (int)index) -> float
        """
        pass

    def __iadd__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iadd__( (object)arg1, (IntensityData)arg2) -> object """
        pass

    def __idiv__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __idiv__( (object)arg1, (IntensityData)arg2) -> object """
        pass

    def __imul__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __imul__( (object)arg1, (IntensityData)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __isub__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __isub__( (object)arg1, (IntensityData)arg2) -> object """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    def __setitem__(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __setitem__( (IntensityData)arg1, (int)arg2, (float)arg3) -> None """
        pass

    __instance_size__ = 64


class InterferenceFunction1DParaCrystal(IInterferenceFunction):
    # no doc
    def areParametersChanged(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (InterferenceFunction1DParaCrystal)arg1) -> bool
        
        areParametersChanged( (InterferenceFunction1DParaCrystal)arg1) -> bool
        """
        pass

    def clearParameterPool(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (InterferenceFunction1DParaCrystal)arg1) -> None
        
        clearParameterPool( (InterferenceFunction1DParaCrystal)arg1) -> None
        """
        pass

    def clone(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (InterferenceFunction1DParaCrystal)arg1) -> InterferenceFunction1DParaCrystal
        
        clone( (InterferenceFunction1DParaCrystal)arg1) -> InterferenceFunction1DParaCrystal
        """
        pass

    def cloneInvertB(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (InterferenceFunction1DParaCrystal)arg1) -> ISample
        
        cloneInvertB( (InterferenceFunction1DParaCrystal)arg1) -> ISample
        """
        pass

    def createParameterTree(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (InterferenceFunction1DParaCrystal)arg1) -> ParameterPool
        
        createParameterTree( (InterferenceFunction1DParaCrystal)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (InterferenceFunction1DParaCrystal)arg1, (cvector_t)q) -> float
        
        evaluate( (InterferenceFunction1DParaCrystal)arg1, (cvector_t)q) -> float
        """
        pass

    def FTGaussianCorrLength(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ FTGaussianCorrLength( (InterferenceFunction1DParaCrystal)arg1, (float)qpar) -> complex """
        pass

    def getCompositeSample(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (InterferenceFunction1DParaCrystal)arg1) -> ICompositeSample
        
        getCompositeSample( (InterferenceFunction1DParaCrystal)arg1) -> ICompositeSample
        """
        pass

    def getKappa(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getKappa( (InterferenceFunction1DParaCrystal)arg1) -> float
        
        getKappa( (InterferenceFunction1DParaCrystal)arg1) -> float
        """
        pass

    def printParameters(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (InterferenceFunction1DParaCrystal)arg1) -> None
        
        printParameters( (InterferenceFunction1DParaCrystal)arg1) -> None
        """
        pass

    def printSampleTree(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (InterferenceFunction1DParaCrystal)arg1) -> None
        
        printSampleTree( (InterferenceFunction1DParaCrystal)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setKappa(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setKappa( (InterferenceFunction1DParaCrystal)arg1, (float)kappa) -> None """
        pass

    def setMatchedParametersValue(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (InterferenceFunction1DParaCrystal)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (InterferenceFunction1DParaCrystal)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (InterferenceFunction1DParaCrystal)arg1) -> None
        
        setParametersAreChanged( (InterferenceFunction1DParaCrystal)arg1) -> None
        """
        pass

    def setParameterValue(self, InterferenceFunction1DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (InterferenceFunction1DParaCrystal)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (InterferenceFunction1DParaCrystal)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)peak_distance, (float)width [, (float)corr_length=0.0]) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 160


class InterferenceFunction2DLattice(IInterferenceFunction):
    # no doc
    def areParametersChanged(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (InterferenceFunction2DLattice)arg1) -> bool
        
        areParametersChanged( (InterferenceFunction2DLattice)arg1) -> bool
        """
        pass

    def clearParameterPool(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (InterferenceFunction2DLattice)arg1) -> None
        
        clearParameterPool( (InterferenceFunction2DLattice)arg1) -> None
        """
        pass

    def clone(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (InterferenceFunction2DLattice)arg1) -> InterferenceFunction2DLattice
        
        clone( (InterferenceFunction2DLattice)arg1) -> InterferenceFunction2DLattice
        """
        pass

    def cloneInvertB(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (InterferenceFunction2DLattice)arg1) -> ISample
        
        cloneInvertB( (InterferenceFunction2DLattice)arg1) -> ISample
        """
        pass

    def createParameterTree(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (InterferenceFunction2DLattice)arg1) -> ParameterPool
        
        createParameterTree( (InterferenceFunction2DLattice)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (InterferenceFunction2DLattice)arg1, (cvector_t)q) -> float
        
        evaluate( (InterferenceFunction2DLattice)arg1, (cvector_t)q) -> float
        """
        pass

    def getCompositeSample(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (InterferenceFunction2DLattice)arg1) -> ICompositeSample
        
        getCompositeSample( (InterferenceFunction2DLattice)arg1) -> ICompositeSample
        """
        pass

    def getKappa(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getKappa( (InterferenceFunction2DLattice)arg1) -> float
        
        getKappa( (InterferenceFunction2DLattice)arg1) -> float
        """
        pass

    def printParameters(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (InterferenceFunction2DLattice)arg1) -> None
        
        printParameters( (InterferenceFunction2DLattice)arg1) -> None
        """
        pass

    def printSampleTree(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (InterferenceFunction2DLattice)arg1) -> None
        
        printSampleTree( (InterferenceFunction2DLattice)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (InterferenceFunction2DLattice)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (InterferenceFunction2DLattice)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (InterferenceFunction2DLattice)arg1) -> None
        
        setParametersAreChanged( (InterferenceFunction2DLattice)arg1) -> None
        """
        pass

    def setParameterValue(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (InterferenceFunction2DLattice)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (InterferenceFunction2DLattice)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setProbabilityDistribution(self, InterferenceFunction2DLattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setProbabilityDistribution( (InterferenceFunction2DLattice)arg1, (IFTDistribution2D)pdf) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (Lattice2DIFParameters)lattice_params) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 240


class InterferenceFunction2DParaCrystal(IInterferenceFunction):
    # no doc
    def areParametersChanged(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (InterferenceFunction2DParaCrystal)arg1) -> bool
        
        areParametersChanged( (InterferenceFunction2DParaCrystal)arg1) -> bool
        """
        pass

    def clearParameterPool(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (InterferenceFunction2DParaCrystal)arg1) -> None
        
        clearParameterPool( (InterferenceFunction2DParaCrystal)arg1) -> None
        """
        pass

    def clone(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (InterferenceFunction2DParaCrystal)arg1) -> InterferenceFunction2DParaCrystal
        
        clone( (InterferenceFunction2DParaCrystal)arg1) -> InterferenceFunction2DParaCrystal
        """
        pass

    def cloneInvertB(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (InterferenceFunction2DParaCrystal)arg1) -> ISample
        
        cloneInvertB( (InterferenceFunction2DParaCrystal)arg1) -> ISample
        """
        pass

    def createHexagonal(self, p_float, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ createHexagonal( (float)peak_distance [, (float)corr_length=0.0 [, (float)domain_size_1=0.0 [, (float)domain_size_2=0.0]]]) -> InterferenceFunction2DParaCrystal """
        pass

    def createParameterTree(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (InterferenceFunction2DParaCrystal)arg1) -> ParameterPool
        
        createParameterTree( (InterferenceFunction2DParaCrystal)arg1) -> ParameterPool
        """
        pass

    def createSquare(self, p_float, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ createSquare( (float)peak_distance [, (float)corr_length=0.0 [, (float)domain_size_1=0.0 [, (float)domain_size_2=0.0]]]) -> InterferenceFunction2DParaCrystal """
        pass

    def evaluate(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (InterferenceFunction2DParaCrystal)arg1, (cvector_t)q) -> float
        
        evaluate( (InterferenceFunction2DParaCrystal)arg1, (cvector_t)q) -> float
        """
        pass

    def getCompositeSample(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (InterferenceFunction2DParaCrystal)arg1) -> ICompositeSample
        
        getCompositeSample( (InterferenceFunction2DParaCrystal)arg1) -> ICompositeSample
        """
        pass

    def getKappa(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getKappa( (InterferenceFunction2DParaCrystal)arg1) -> float
        
        getKappa( (InterferenceFunction2DParaCrystal)arg1) -> float
        """
        pass

    def printParameters(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (InterferenceFunction2DParaCrystal)arg1) -> None
        
        printParameters( (InterferenceFunction2DParaCrystal)arg1) -> None
        """
        pass

    def printSampleTree(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (InterferenceFunction2DParaCrystal)arg1) -> None
        
        printSampleTree( (InterferenceFunction2DParaCrystal)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setDomainSizes(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setDomainSizes( (InterferenceFunction2DParaCrystal)arg1, (float)size_1, (float)size_2) -> None """
        pass

    def setIntegrationOverXi(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setIntegrationOverXi( (InterferenceFunction2DParaCrystal)arg1, (bool)integrate_xi) -> None """
        pass

    def setMatchedParametersValue(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (InterferenceFunction2DParaCrystal)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (InterferenceFunction2DParaCrystal)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (InterferenceFunction2DParaCrystal)arg1) -> None
        
        setParametersAreChanged( (InterferenceFunction2DParaCrystal)arg1) -> None
        """
        pass

    def setParameterValue(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (InterferenceFunction2DParaCrystal)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (InterferenceFunction2DParaCrystal)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setProbabilityDistributions(self, InterferenceFunction2DParaCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setProbabilityDistributions( (InterferenceFunction2DParaCrystal)arg1, (IFTDistribution2D)pdf_1, (IFTDistribution2D)pdf_2) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)length_1, (float)length_2, (float)alpha_lattice [, (float)xi=0.0 [, (float)corr_length=0.0]]) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 224


class InterferenceFunctionNone(IInterferenceFunction):
    # no doc
    def areParametersChanged(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (InterferenceFunctionNone)arg1) -> bool
        
        areParametersChanged( (InterferenceFunctionNone)arg1) -> bool
        """
        pass

    def clearParameterPool(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (InterferenceFunctionNone)arg1) -> None
        
        clearParameterPool( (InterferenceFunctionNone)arg1) -> None
        """
        pass

    def clone(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (InterferenceFunctionNone)arg1) -> InterferenceFunctionNone
        
        clone( (InterferenceFunctionNone)arg1) -> InterferenceFunctionNone
        """
        pass

    def cloneInvertB(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (InterferenceFunctionNone)arg1) -> ISample
        
        cloneInvertB( (InterferenceFunctionNone)arg1) -> ISample
        """
        pass

    def createParameterTree(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (InterferenceFunctionNone)arg1) -> ParameterPool
        
        createParameterTree( (InterferenceFunctionNone)arg1) -> ParameterPool
        """
        pass

    def evaluate(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluate( (InterferenceFunctionNone)arg1, (cvector_t)q) -> float
        
        evaluate( (InterferenceFunctionNone)arg1, (cvector_t)q) -> float
        """
        pass

    def getCompositeSample(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (InterferenceFunctionNone)arg1) -> ICompositeSample
        
        getCompositeSample( (InterferenceFunctionNone)arg1) -> ICompositeSample
        """
        pass

    def getKappa(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getKappa( (InterferenceFunctionNone)arg1) -> float
        
        getKappa( (InterferenceFunctionNone)arg1) -> float
        """
        pass

    def printParameters(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (InterferenceFunctionNone)arg1) -> None
        
        printParameters( (InterferenceFunctionNone)arg1) -> None
        """
        pass

    def printSampleTree(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (InterferenceFunctionNone)arg1) -> None
        
        printSampleTree( (InterferenceFunctionNone)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (InterferenceFunctionNone)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (InterferenceFunctionNone)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (InterferenceFunctionNone)arg1) -> None
        
        setParametersAreChanged( (InterferenceFunctionNone)arg1) -> None
        """
        pass

    def setParameterValue(self, InterferenceFunctionNone, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (InterferenceFunctionNone)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (InterferenceFunctionNone)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 120


class IObservable(__Boost_Python.instance):
    # no doc
    def attachObserver(self, IObservable, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        attachObserver( (IObservable)arg1, (IObserver)obj) -> None
        
        attachObserver( (IObservable)arg1, (IObserver)obj) -> None
        """
        pass

    def notifyObservers(self, IObservable, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        notifyObservers( (IObservable)arg1) -> None
        
        notifyObservers( (IObservable)arg1) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 48


class IObserver(__Boost_Python.instance):
    # no doc
    def update(self, IObserver, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        update( (IObserver)arg1, (IObservable)arg0) -> None
        
        update( (IObserver)arg1, (IObservable)arg0) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 32


class IResolutionFunction2D(IParameterized):
    # no doc
    def areParametersChanged(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (IResolutionFunction2D)arg1) -> bool
        
        areParametersChanged( (IResolutionFunction2D)arg1) -> bool
        """
        pass

    def clearParameterPool(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (IResolutionFunction2D)arg1) -> None
        
        clearParameterPool( (IResolutionFunction2D)arg1) -> None
        """
        pass

    def clone(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (IResolutionFunction2D)arg1) -> IResolutionFunction2D
        
        clone( (IResolutionFunction2D)arg1) -> None
        """
        pass

    def createParameterTree(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (IResolutionFunction2D)arg1) -> ParameterPool
        
        createParameterTree( (IResolutionFunction2D)arg1) -> ParameterPool
        """
        pass

    def evaluateCDF(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluateCDF( (IResolutionFunction2D)arg1, (float)x, (float)y) -> float
        
        evaluateCDF( (IResolutionFunction2D)arg1, (float)arg2, (float)arg3) -> None
        """
        pass

    def printParameters(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (IResolutionFunction2D)arg1) -> None
        
        printParameters( (IResolutionFunction2D)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (IResolutionFunction2D)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (IResolutionFunction2D)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (IResolutionFunction2D)arg1) -> None
        
        setParametersAreChanged( (IResolutionFunction2D)arg1) -> None
        """
        pass

    def setParameterValue(self, IResolutionFunction2D, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (IResolutionFunction2D)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (IResolutionFunction2D)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 112


class ISampleBuilder(IParameterized):
    # no doc
    def areParametersChanged(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (ISampleBuilder)arg1) -> bool
        
        areParametersChanged( (ISampleBuilder)arg1) -> bool
        """
        pass

    def buildSample(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        buildSample( (ISampleBuilder)arg1) -> ISample
        
        buildSample( (ISampleBuilder)arg1) -> ISample
        """
        pass

    def clearParameterPool(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (ISampleBuilder)arg1) -> None
        
        clearParameterPool( (ISampleBuilder)arg1) -> None
        """
        pass

    def createParameterTree(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (ISampleBuilder)arg1) -> ParameterPool
        
        createParameterTree( (ISampleBuilder)arg1) -> ParameterPool
        """
        pass

    def printParameters(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (ISampleBuilder)arg1) -> None
        
        printParameters( (ISampleBuilder)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (ISampleBuilder)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (ISampleBuilder)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (ISampleBuilder)arg1) -> None
        
        setParametersAreChanged( (ISampleBuilder)arg1) -> None
        """
        pass

    def setParameterValue(self, ISampleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (ISampleBuilder)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (ISampleBuilder)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 112


class ISelectionRule(__Boost_Python.instance):
    # no doc
    def clone(self, ISelectionRule, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (ISelectionRule)arg1) -> ISelectionRule
        
        clone( (ISelectionRule)arg1) -> None
        """
        pass

    def coordinateSelected(self, ISelectionRule, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        coordinateSelected( (ISelectionRule)arg1, (object)coordinate) -> bool
        
        coordinateSelected( (ISelectionRule)arg1, (object)arg2) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 32


class ITransform3D(__Boost_Python.instance):
    # no doc
    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 32


class kvector_t(__Boost_Python.instance):
    # no doc
    def assign(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ assign( (kvector_t)arg1, (kvector_t)v) -> kvector_t """
        pass

    def mag(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ mag( (kvector_t)arg1) -> float """
        pass

    def mag2(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ mag2( (kvector_t)arg1) -> float """
        pass

    def magxy(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ magxy( (kvector_t)arg1) -> float """
        pass

    def magxy2(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ magxy2( (kvector_t)arg1) -> float """
        pass

    def setLambdaAlphaPhi(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setLambdaAlphaPhi( (kvector_t)arg1, (float)_lambda, (float)_alpha, (float)_phi) -> None """
        pass

    def setX(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setX( (kvector_t)arg1, (float)a) -> None """
        pass

    def setXYZ(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setXYZ( (kvector_t)arg1, (float)x1, (float)y1, (float)z1) -> None """
        pass

    def setY(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setY( (kvector_t)arg1, (float)a) -> None """
        pass

    def setZ(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setZ( (kvector_t)arg1, (float)a) -> None """
        pass

    def x(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ x( (kvector_t)arg1) -> float """
        pass

    def y(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ y( (kvector_t)arg1) -> float """
        pass

    def z(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ z( (kvector_t)arg1) -> float """
        pass

    def __add__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __add__( (kvector_t)arg1, (kvector_t)arg2) -> object """
        pass

    def __div__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __div__( (kvector_t)arg1, (float)arg2) -> object """
        pass

    def __getitem__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __getitem__( (kvector_t)arg1, (int)i) -> float
        
        __getitem__( (kvector_t)arg1, (int)i) -> float
        """
        pass

    def __iadd__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iadd__( (object)arg1, (kvector_t)arg2) -> object """
        pass

    def __idiv__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __idiv__( (object)arg1, (float)arg2) -> object """
        pass

    def __imul__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __imul__( (object)arg1, (float)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (float)x1, (float)y1, (float)z1) -> None
        """
        pass

    def __isub__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __isub__( (object)arg1, (kvector_t)arg2) -> object """
        pass

    def __mul__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __mul__( (kvector_t)arg1, (float)arg2) -> object """
        pass

    def __neg__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __neg__( (kvector_t)arg1) -> object """
        pass

    def __pos__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __pos__( (kvector_t)arg1) -> object """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    def __rmul__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __rmul__( (kvector_t)arg1, (float)arg2) -> object """
        pass

    def __str__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __str__( (kvector_t)arg1) -> object """
        pass

    def __sub__(self, kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __sub__( (kvector_t)arg1, (kvector_t)arg2) -> object """
        pass

    __instance_size__ = 40


class Lattice(__Boost_Python.instance):
    # no doc
    def createTrigonalLattice(self, p_float, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ createTrigonalLattice( (float)a, (float)c) -> Lattice """
        pass

    def getBasisVectorA(self, Lattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getBasisVectorA( (Lattice)arg1) -> kvector_t """
        pass

    def getBasisVectorB(self, Lattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getBasisVectorB( (Lattice)arg1) -> kvector_t """
        pass

    def getBasisVectorC(self, Lattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getBasisVectorC( (Lattice)arg1) -> kvector_t """
        pass

    def setSelectionRule(self, Lattice, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setSelectionRule( (Lattice)arg1, (ISelectionRule)p_selection_rule) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (kvector_t)a1, (kvector_t)a2, (kvector_t)a3) -> None
        
        __init__( (object)arg1, (Lattice)lattice) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 216


class Lattice2DIFParameters(__Boost_Python.instance):
    # no doc
    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    m_angle = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_corr_length_1 = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_corr_length_2 = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_domain_size_1 = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_domain_size_2 = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_length_1 = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_length_2 = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    m_xi = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default


    __instance_size__ = 80


class Particle(ICompositeSample):
    # no doc
    def areParametersChanged(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (Particle)arg1) -> bool
        
        areParametersChanged( (Particle)arg1) -> bool
        """
        pass

    def clearParameterPool(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (Particle)arg1) -> None
        
        clearParameterPool( (Particle)arg1) -> None
        """
        pass

    def clone(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (Particle)arg1) -> Particle
        
        clone( (Particle)arg1) -> Particle
        """
        pass

    def cloneInvertB(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (Particle)arg1) -> Particle
        
        cloneInvertB( (Particle)arg1) -> Particle
        """
        pass

    def createFormFactor(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createFormFactor( (Particle)arg1, (complex)wavevector_scattering_factor) -> IFormFactor
        
        createFormFactor( (Particle)arg1, (complex)wavevector_scattering_factor) -> IFormFactor
        """
        pass

    def createParameterTree(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (Particle)arg1) -> ParameterPool
        
        createParameterTree( (Particle)arg1) -> ParameterPool
        """
        pass

    def getMaterial(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMaterial( (Particle)arg1) -> IMaterial
        
        getMaterial( (Particle)arg1) -> IMaterial
        """
        pass

    def getPTransform3D(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getPTransform3D( (Particle)arg1) -> ITransform3D """
        pass

    def getRefractiveIndex(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRefractiveIndex( (Particle)arg1) -> complex
        
        getRefractiveIndex( (Particle)arg1) -> complex
        """
        pass

    def getSimpleFormFactor(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getSimpleFormFactor( (Particle)arg1) -> IFormFactor
        
        getSimpleFormFactor( (Particle)arg1) -> IFormFactor
        """
        pass

    def hasDistributedFormFactor(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        hasDistributedFormFactor( (Particle)arg1) -> bool
        
        hasDistributedFormFactor( (Particle)arg1) -> bool
        """
        pass

    def printParameters(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (Particle)arg1) -> None
        
        printParameters( (Particle)arg1) -> None
        """
        pass

    def printSampleTree(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (Particle)arg1) -> None
        
        printSampleTree( (Particle)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (Particle)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (Particle)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (Particle)arg1) -> None
        
        setParametersAreChanged( (Particle)arg1) -> None
        """
        pass

    def setParameterValue(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (Particle)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (Particle)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setTransform(self, Particle, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setTransform( (Particle)arg1, (ITransform3D)transform) -> None
        
        setTransform( (Particle)arg1, (ITransform3D)transform) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (IMaterial)p_material, (IFormFactor)form_factor) -> None
        
        __init__( (object)arg1, (IMaterial)p_material, (IFormFactor)form_factor, (ITransform3D)transform) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 176


class LatticeBasis(Particle):
    # no doc
    def addParticle(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ addParticle( (LatticeBasis)arg1, (Particle)particle, (vector_kvector_t)positions) -> None """
        pass

    def areParametersChanged(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (LatticeBasis)arg1) -> bool
        
        areParametersChanged( (LatticeBasis)arg1) -> bool
        """
        pass

    def clearParameterPool(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (LatticeBasis)arg1) -> None
        
        clearParameterPool( (LatticeBasis)arg1) -> None
        """
        pass

    def createParameterTree(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (LatticeBasis)arg1) -> ParameterPool
        
        createParameterTree( (LatticeBasis)arg1) -> ParameterPool
        """
        pass

    def getMaterial(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMaterial( (LatticeBasis)arg1) -> IMaterial
        
        getMaterial( (LatticeBasis)arg1) -> IMaterial
        """
        pass

    def getRefractiveIndex(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRefractiveIndex( (LatticeBasis)arg1) -> complex
        
        getRefractiveIndex( (LatticeBasis)arg1) -> complex
        """
        pass

    def getSimpleFormFactor(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getSimpleFormFactor( (LatticeBasis)arg1) -> IFormFactor
        
        getSimpleFormFactor( (LatticeBasis)arg1) -> IFormFactor
        """
        pass

    def hasDistributedFormFactor(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        hasDistributedFormFactor( (LatticeBasis)arg1) -> bool
        
        hasDistributedFormFactor( (LatticeBasis)arg1) -> bool
        """
        pass

    def printParameters(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (LatticeBasis)arg1) -> None
        
        printParameters( (LatticeBasis)arg1) -> None
        """
        pass

    def printSampleTree(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (LatticeBasis)arg1) -> None
        
        printSampleTree( (LatticeBasis)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (LatticeBasis)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (LatticeBasis)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (LatticeBasis)arg1) -> None
        
        setParametersAreChanged( (LatticeBasis)arg1) -> None
        """
        pass

    def setParameterValue(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (LatticeBasis)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (LatticeBasis)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setTransform(self, LatticeBasis, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setTransform( (LatticeBasis)arg1, (ITransform3D)transform) -> None
        
        setTransform( (LatticeBasis)arg1, (ITransform3D)transform) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 224


class Layer(ICompositeSample):
    # no doc
    def areParametersChanged(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (Layer)arg1) -> bool
        
        areParametersChanged( (Layer)arg1) -> bool
        """
        pass

    def clearParameterPool(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (Layer)arg1) -> None
        
        clearParameterPool( (Layer)arg1) -> None
        """
        pass

    def clone(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (Layer)arg1) -> Layer
        
        clone( (Layer)arg1) -> Layer
        """
        pass

    def cloneInvertB(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (Layer)arg1) -> Layer
        
        cloneInvertB( (Layer)arg1) -> Layer
        """
        pass

    def createParameterTree(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (Layer)arg1) -> ParameterPool
        
        createParameterTree( (Layer)arg1) -> ParameterPool
        """
        pass

    def getDecoration(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getDecoration( (Layer)arg1) -> IDecoration
        
        getDecoration( (Layer)arg1) -> IDecoration
        """
        pass

    def getMaterial(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMaterial( (Layer)arg1) -> IMaterial
        
        getMaterial( (Layer)arg1) -> IMaterial
        """
        pass

    def getRefractiveIndex(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRefractiveIndex( (Layer)arg1) -> complex
        
        getRefractiveIndex( (Layer)arg1) -> complex
        """
        pass

    def getThickness(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getThickness( (Layer)arg1) -> float
        
        getThickness( (Layer)arg1) -> float
        """
        pass

    def getTotalParticleSurfaceDensity(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getTotalParticleSurfaceDensity( (Layer)arg1) -> float
        
        getTotalParticleSurfaceDensity( (Layer)arg1) -> float
        """
        pass

    def printParameters(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (Layer)arg1) -> None
        
        printParameters( (Layer)arg1) -> None
        """
        pass

    def printSampleTree(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (Layer)arg1) -> None
        
        printSampleTree( (Layer)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setDecoration(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setDecoration( (Layer)arg1, (IDecoration)decoration) -> None
        
        setDecoration( (Layer)arg1, (IDecoration)decoration) -> None
        """
        pass

    def setMatchedParametersValue(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (Layer)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (Layer)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setMaterial(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMaterial( (Layer)arg1, (IMaterial)material) -> None
        
        setMaterial( (Layer)arg1, (IMaterial)material) -> None
        
        setMaterial( (Layer)arg1, (IMaterial)material, (float)thickness) -> None
        
        setMaterial( (Layer)arg1, (IMaterial)material, (float)thickness) -> None
        """
        pass

    def setParametersAreChanged(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (Layer)arg1) -> None
        
        setParametersAreChanged( (Layer)arg1) -> None
        """
        pass

    def setParameterValue(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (Layer)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (Layer)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setThickness(self, Layer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setThickness( (Layer)arg1, (float)thickness) -> None
        
        setThickness( (Layer)arg1, (float)thickness) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (IMaterial)material [, (float)thickness=0 [, (IDecoration)decoration=None]]) -> None
        
        __init__( (object)arg1, (IMaterial)material, (float)thickness, (IDecoration)decoration) -> None
        
        __init__( (object)arg1, (Layer)other) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 160


class LayerInterface(ICompositeSample):
    # no doc
    def areParametersChanged(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (LayerInterface)arg1) -> bool
        
        areParametersChanged( (LayerInterface)arg1) -> bool
        """
        pass

    def clearParameterPool(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (LayerInterface)arg1) -> None
        
        clearParameterPool( (LayerInterface)arg1) -> None
        """
        pass

    def cloneInvertB(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (LayerInterface)arg1) -> ISample
        
        cloneInvertB( (LayerInterface)arg1) -> ISample
        """
        pass

    def createParameterTree(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (LayerInterface)arg1) -> ParameterPool
        
        createParameterTree( (LayerInterface)arg1) -> ParameterPool
        """
        pass

    def getLayerBottom(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayerBottom( (LayerInterface)arg1) -> Layer """
        pass

    def getLayerTop(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayerTop( (LayerInterface)arg1) -> Layer """
        pass

    def getRoughness(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getRoughness( (LayerInterface)arg1) -> LayerRoughness """
        pass

    def printParameters(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (LayerInterface)arg1) -> None
        
        printParameters( (LayerInterface)arg1) -> None
        """
        pass

    def printSampleTree(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (LayerInterface)arg1) -> None
        
        printSampleTree( (LayerInterface)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (LayerInterface)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (LayerInterface)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (LayerInterface)arg1) -> None
        
        setParametersAreChanged( (LayerInterface)arg1) -> None
        """
        pass

    def setParameterValue(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (LayerInterface)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (LayerInterface)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setRoughness(self, LayerInterface, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setRoughness( (LayerInterface)arg1, (LayerRoughness)roughness) -> None """
        pass

    def __init__(self, *args, **kwargs): # real signature unknown
        """
        Raises an exception
        This class cannot be instantiated from Python
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass


class LayerRoughness(__Boost_Python.instance):
    # no doc
    def areParametersChanged(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (LayerRoughness)arg1) -> bool
        
        areParametersChanged( (LayerRoughness)arg1) -> bool
        """
        pass

    def clearParameterPool(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (LayerRoughness)arg1) -> None
        
        clearParameterPool( (LayerRoughness)arg1) -> None
        """
        pass

    def clone(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (LayerRoughness)arg1) -> LayerRoughness
        
        clone( (LayerRoughness)arg1) -> LayerRoughness
        """
        pass

    def cloneInvertB(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (LayerRoughness)arg1) -> ISample
        
        cloneInvertB( (LayerRoughness)arg1) -> ISample
        """
        pass

    def createParameterTree(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (LayerRoughness)arg1) -> ParameterPool
        
        createParameterTree( (LayerRoughness)arg1) -> ParameterPool
        """
        pass

    def getCompositeSample(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getCompositeSample( (LayerRoughness)arg1) -> ICompositeSample
        
        getCompositeSample( (LayerRoughness)arg1) -> ICompositeSample
        """
        pass

    def getCorrFun(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getCorrFun( (LayerRoughness)arg1, (kvector_t)k) -> float """
        pass

    def getHurstParameter(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getHurstParameter( (LayerRoughness)arg1) -> float """
        pass

    def getLatteralCorrLength(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLatteralCorrLength( (LayerRoughness)arg1) -> float """
        pass

    def getSigma(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getSigma( (LayerRoughness)arg1) -> float """
        pass

    def getSpectralFun(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getSpectralFun( (LayerRoughness)arg1, (kvector_t)kvec) -> float """
        pass

    def printParameters(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (LayerRoughness)arg1) -> None
        
        printParameters( (LayerRoughness)arg1) -> None
        """
        pass

    def printSampleTree(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (LayerRoughness)arg1) -> None
        
        printSampleTree( (LayerRoughness)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setHurstParameter(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setHurstParameter( (LayerRoughness)arg1, (float)hurstParameter) -> None """
        pass

    def setLatteralCorrLength(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setLatteralCorrLength( (LayerRoughness)arg1, (float)latteralCorrLength) -> None """
        pass

    def setMatchedParametersValue(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (LayerRoughness)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (LayerRoughness)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (LayerRoughness)arg1) -> None
        
        setParametersAreChanged( (LayerRoughness)arg1) -> None
        """
        pass

    def setParameterValue(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (LayerRoughness)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (LayerRoughness)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setSigma(self, LayerRoughness, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setSigma( (LayerRoughness)arg1, (float)sigma) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1) -> None
        
        __init__( (object)arg1, (float)sigma, (float)hurstParameter, (float)latteralCorrLength) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 144


class MaterialManager(__Boost_Python.instance):
    # no doc
    def deleteMaterial(self, MaterialManager, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ deleteMaterial( (MaterialManager)arg1, (str)name) -> bool """
        pass

    def getHomogeneousMagneticMaterial(self, p_str, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHomogeneousMagneticMaterial( (str)name, (complex)refractive_index, (kvector_t)magnetic_field) -> IMaterial
        
        getHomogeneousMagneticMaterial( (str)name, (float)refractive_index_delta, (float)refractive_index_beta, (kvector_t)magnetic_field) -> IMaterial
        """
        pass

    def getHomogeneousMaterial(self, p_str, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getHomogeneousMaterial( (str)name, (complex)refractive_index) -> IMaterial
        
        getHomogeneousMaterial( (str)name, (float)refractive_index_delta, (float)refractive_index_beta) -> IMaterial
        """
        pass

    def getInvertedMaterial(self, p_str, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getInvertedMaterial( (str)name) -> IMaterial """
        pass

    def getMaterial(self, p_str, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getMaterial( (str)name) -> IMaterial """
        pass

    def getNumberOfMaterials(self): # real signature unknown; restored from __doc__
        """ getNumberOfMaterials() -> int """
        return 0

    def setMaterialName(self, MaterialManager, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setMaterialName( (MaterialManager)arg1, (str)old_name, (str)new_name) -> bool """
        pass

    def setMaterialRefractiveIndex(self, MaterialManager, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setMaterialRefractiveIndex( (MaterialManager)arg1, (str)name, (complex)index) -> bool """
        pass

    def __init__(self, *args, **kwargs): # real signature unknown
        """
        Raises an exception
        This class cannot be instantiated from Python
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass


class MesoCrystal(Particle):
    # no doc
    def areParametersChanged(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (MesoCrystal)arg1) -> bool
        
        areParametersChanged( (MesoCrystal)arg1) -> bool
        """
        pass

    def clearParameterPool(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (MesoCrystal)arg1) -> None
        
        clearParameterPool( (MesoCrystal)arg1) -> None
        """
        pass

    def createParameterTree(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (MesoCrystal)arg1) -> ParameterPool
        
        createParameterTree( (MesoCrystal)arg1) -> ParameterPool
        """
        pass

    def getMaterial(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMaterial( (MesoCrystal)arg1) -> IMaterial
        
        getMaterial( (MesoCrystal)arg1) -> IMaterial
        """
        pass

    def getRefractiveIndex(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRefractiveIndex( (MesoCrystal)arg1) -> complex
        
        getRefractiveIndex( (MesoCrystal)arg1) -> complex
        """
        pass

    def hasDistributedFormFactor(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        hasDistributedFormFactor( (MesoCrystal)arg1) -> bool
        
        hasDistributedFormFactor( (MesoCrystal)arg1) -> bool
        """
        pass

    def printParameters(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (MesoCrystal)arg1) -> None
        
        printParameters( (MesoCrystal)arg1) -> None
        """
        pass

    def printSampleTree(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (MesoCrystal)arg1) -> None
        
        printSampleTree( (MesoCrystal)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (MesoCrystal)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (MesoCrystal)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (MesoCrystal)arg1) -> None
        
        setParametersAreChanged( (MesoCrystal)arg1) -> None
        """
        pass

    def setParameterValue(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (MesoCrystal)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (MesoCrystal)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setTransform(self, MesoCrystal, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setTransform( (MesoCrystal)arg1, (ITransform3D)transform) -> None
        
        setTransform( (MesoCrystal)arg1, (ITransform3D)transform) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (IClusteredParticles)particle_structure, (IFormFactor)form_factor) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 192


class MultiLayer(ICompositeSample):
    # no doc
    def addLayer(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ addLayer( (MultiLayer)arg1, (Layer)p_child) -> None """
        pass

    def addLayerWithTopRoughness(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ addLayerWithTopRoughness( (MultiLayer)arg1, (Layer)layer, (LayerRoughness)roughness) -> None """
        pass

    def areParametersChanged(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (MultiLayer)arg1) -> bool
        
        areParametersChanged( (MultiLayer)arg1) -> bool
        """
        pass

    def clear(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ clear( (MultiLayer)arg1) -> None """
        pass

    def clearParameterPool(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (MultiLayer)arg1) -> None
        
        clearParameterPool( (MultiLayer)arg1) -> None
        """
        pass

    def clone(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (MultiLayer)arg1) -> MultiLayer
        
        clone( (MultiLayer)arg1) -> MultiLayer
        """
        pass

    def cloneInvertB(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (MultiLayer)arg1) -> MultiLayer
        
        cloneInvertB( (MultiLayer)arg1) -> MultiLayer
        """
        pass

    def createParameterTree(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (MultiLayer)arg1) -> ParameterPool
        
        createParameterTree( (MultiLayer)arg1) -> ParameterPool
        """
        pass

    def getCrossCorrLength(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getCrossCorrLength( (MultiLayer)arg1) -> float """
        pass

    def getCrossCorrSpectralFun(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getCrossCorrSpectralFun( (MultiLayer)arg1, (kvector_t)kvec, (int)j, (int)k) -> float """
        pass

    def getLayer(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayer( (MultiLayer)arg1, (int)i_layer) -> Layer """
        pass

    def getLayerBottomInterface(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayerBottomInterface( (MultiLayer)arg1, (int)i_layer) -> LayerInterface """
        pass

    def getLayerBottomZ(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayerBottomZ( (MultiLayer)arg1, (int)i_layer) -> float """
        pass

    def getLayerInterface(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayerInterface( (MultiLayer)arg1, (int)i_interface) -> LayerInterface """
        pass

    def getLayerThickness(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayerThickness( (MultiLayer)arg1, (int)i_layer) -> float """
        pass

    def getLayerTopInterface(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getLayerTopInterface( (MultiLayer)arg1, (int)i_layer) -> LayerInterface """
        pass

    def getNumberOfInterfaces(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getNumberOfInterfaces( (MultiLayer)arg1) -> int """
        pass

    def getNumberOfLayers(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getNumberOfLayers( (MultiLayer)arg1) -> int """
        pass

    def printParameters(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (MultiLayer)arg1) -> None
        
        printParameters( (MultiLayer)arg1) -> None
        """
        pass

    def printSampleTree(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (MultiLayer)arg1) -> None
        
        printSampleTree( (MultiLayer)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setCrossCorrLength(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setCrossCorrLength( (MultiLayer)arg1, (float)crossCorrLength) -> None """
        pass

    def setLayerThickness(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setLayerThickness( (MultiLayer)arg1, (int)i_layer, (float)thickness) -> None """
        pass

    def setMatchedParametersValue(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (MultiLayer)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (MultiLayer)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (MultiLayer)arg1) -> None
        
        setParametersAreChanged( (MultiLayer)arg1) -> None
        """
        pass

    def setParameterValue(self, MultiLayer, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (MultiLayer)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (MultiLayer)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 216


class OutputDataIOFactory(__Boost_Python.instance):
    # no doc
    def getReader(self, p_str, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getReader( (str)file_name) -> object """
        pass

    def getWriter(self, p_str, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getWriter( (str)file_name) -> object """
        pass

    def readIntensityData(self, p_str, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ readIntensityData( (str)file_name) -> IntensityData """
        pass

    def writeIntensityData(self, IntensityData, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ writeIntensityData( (IntensityData)data, (str)file_name) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 24


class ParameterPool(ICloneable):
    # no doc
    def addParameter(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ addParameter( (ParameterPool)arg1, (str)name, (RealParameterWrapper)par) -> bool """
        pass

    def clear(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ clear( (ParameterPool)arg1) -> None """
        pass

    def clone(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (ParameterPool)arg1) -> ParameterPool
        
        clone( (ParameterPool)arg1) -> ParameterPool
        """
        pass

    def cloneWithPrefix(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ cloneWithPrefix( (ParameterPool)arg1, (str)prefix) -> ParameterPool """
        pass

    def fixRatioBetweenParameters(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ fixRatioBetweenParameters( (ParameterPool)arg1, (str)to_change, (str)source, (float)ratio) -> int """
        pass

    def getParameter(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getParameter( (ParameterPool)arg1, (str)name) -> RealParameterWrapper """
        pass

    def setMatchedParametersValue(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setMatchedParametersValue( (ParameterPool)arg1, (str)wildcards, (float)value) -> int """
        pass

    def setParameterValue(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setParameterValue( (ParameterPool)arg1, (str)name, (float)value) -> bool """
        pass

    def size(self, ParameterPool, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ size( (ParameterPool)arg1) -> int """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 80


class ParticleBuilder(__Boost_Python.instance):
    # no doc
    def plantParticles(self, ParticleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ plantParticles( (ParticleBuilder)arg1, (ParticleDecoration)decor) -> None """
        pass

    def setPrototype(self, ParticleBuilder, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setPrototype( (ParticleBuilder)arg1, (Particle)particle, (str)name, (StochasticParameter_t)param [, (float)scale=1.0]) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 56


class ParticleCoreShell(Particle):
    # no doc
    def areParametersChanged(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (ParticleCoreShell)arg1) -> bool
        
        areParametersChanged( (ParticleCoreShell)arg1) -> bool
        """
        pass

    def clearParameterPool(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (ParticleCoreShell)arg1) -> None
        
        clearParameterPool( (ParticleCoreShell)arg1) -> None
        """
        pass

    def createParameterTree(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (ParticleCoreShell)arg1) -> ParameterPool
        
        createParameterTree( (ParticleCoreShell)arg1) -> ParameterPool
        """
        pass

    def getMaterial(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getMaterial( (ParticleCoreShell)arg1) -> IMaterial
        
        getMaterial( (ParticleCoreShell)arg1) -> IMaterial
        """
        pass

    def getRefractiveIndex(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRefractiveIndex( (ParticleCoreShell)arg1) -> complex
        
        getRefractiveIndex( (ParticleCoreShell)arg1) -> complex
        """
        pass

    def hasDistributedFormFactor(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        hasDistributedFormFactor( (ParticleCoreShell)arg1) -> bool
        
        hasDistributedFormFactor( (ParticleCoreShell)arg1) -> bool
        """
        pass

    def printParameters(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (ParticleCoreShell)arg1) -> None
        
        printParameters( (ParticleCoreShell)arg1) -> None
        """
        pass

    def printSampleTree(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (ParticleCoreShell)arg1) -> None
        
        printSampleTree( (ParticleCoreShell)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (ParticleCoreShell)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (ParticleCoreShell)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (ParticleCoreShell)arg1) -> None
        
        setParametersAreChanged( (ParticleCoreShell)arg1) -> None
        """
        pass

    def setParameterValue(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (ParticleCoreShell)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (ParticleCoreShell)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setTransform(self, ParticleCoreShell, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setTransform( (ParticleCoreShell)arg1, (ITransform3D)transform) -> None
        
        setTransform( (ParticleCoreShell)arg1, (ITransform3D)transform) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (Particle)shell, (Particle)core, (kvector_t)relative_core_position) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 216


class ParticleDecoration(IDecoration):
    # no doc
    def addInterferenceFunction(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ addInterferenceFunction( (ParticleDecoration)arg1, (IInterferenceFunction)interference_function) -> None """
        pass

    def addParticle(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        addParticle( (ParticleDecoration)arg1, (Particle)p_particle, (ITransform3D)transform [, (float)depth=0 [, (float)abundance=1.0]]) -> None
        
        addParticle( (ParticleDecoration)arg1, (Particle)particle [, (float)depth=0.0 [, (float)abundance=1.0]]) -> None
        """
        pass

    def addParticleInfo(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ addParticleInfo( (ParticleDecoration)arg1, (ParticleInfo)info) -> None """
        pass

    def areParametersChanged(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (ParticleDecoration)arg1) -> bool
        
        areParametersChanged( (ParticleDecoration)arg1) -> bool
        """
        pass

    def clearParameterPool(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (ParticleDecoration)arg1) -> None
        
        clearParameterPool( (ParticleDecoration)arg1) -> None
        """
        pass

    def clone(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (ParticleDecoration)arg1) -> ParticleDecoration
        
        clone( (ParticleDecoration)arg1) -> ParticleDecoration
        """
        pass

    def cloneInvertB(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (ParticleDecoration)arg1) -> ParticleDecoration
        
        cloneInvertB( (ParticleDecoration)arg1) -> ParticleDecoration
        """
        pass

    def createParameterTree(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (ParticleDecoration)arg1) -> ParameterPool
        
        createParameterTree( (ParticleDecoration)arg1) -> ParameterPool
        """
        pass

    def getAbundanceFractionOfParticle(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getAbundanceFractionOfParticle( (ParticleDecoration)arg1, (int)index) -> float
        
        getAbundanceFractionOfParticle( (ParticleDecoration)arg1, (int)index) -> float
        """
        pass

    def getInterferenceFunction(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getInterferenceFunction( (ParticleDecoration)arg1, (int)index) -> IInterferenceFunction """
        pass

    def getInterferenceFunctions(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getInterferenceFunctions( (ParticleDecoration)arg1) -> object
        
        getInterferenceFunctions( (ParticleDecoration)arg1) -> object
        """
        pass

    def getNumberOfInterferenceFunctions(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfInterferenceFunctions( (ParticleDecoration)arg1) -> int
        
        getNumberOfInterferenceFunctions( (ParticleDecoration)arg1) -> int
        """
        pass

    def getNumberOfParticles(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getNumberOfParticles( (ParticleDecoration)arg1) -> int
        
        getNumberOfParticles( (ParticleDecoration)arg1) -> int
        """
        pass

    def getParticleInfo(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getParticleInfo( (ParticleDecoration)arg1, (int)index) -> ParticleInfo
        
        getParticleInfo( (ParticleDecoration)arg1, (int)index) -> ParticleInfo
        """
        pass

    def printParameters(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (ParticleDecoration)arg1) -> None
        
        printParameters( (ParticleDecoration)arg1) -> None
        """
        pass

    def printSampleTree(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (ParticleDecoration)arg1) -> None
        
        printSampleTree( (ParticleDecoration)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (ParticleDecoration)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (ParticleDecoration)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (ParticleDecoration)arg1) -> None
        
        setParametersAreChanged( (ParticleDecoration)arg1) -> None
        """
        pass

    def setParameterValue(self, ParticleDecoration, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (ParticleDecoration)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (ParticleDecoration)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 208


class ParticleInfo(ICompositeSample):
    # no doc
    def areParametersChanged(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (ParticleInfo)arg1) -> bool
        
        areParametersChanged( (ParticleInfo)arg1) -> bool
        """
        pass

    def clearParameterPool(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (ParticleInfo)arg1) -> None
        
        clearParameterPool( (ParticleInfo)arg1) -> None
        """
        pass

    def clone(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (ParticleInfo)arg1) -> ParticleInfo
        
        clone( (ParticleInfo)arg1) -> ParticleInfo
        """
        pass

    def cloneInvertB(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (ParticleInfo)arg1) -> ParticleInfo
        
        cloneInvertB( (ParticleInfo)arg1) -> ParticleInfo
        """
        pass

    def createParameterTree(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (ParticleInfo)arg1) -> ParameterPool
        
        createParameterTree( (ParticleInfo)arg1) -> ParameterPool
        """
        pass

    def getAbundance(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getAbundance( (ParticleInfo)arg1) -> float """
        pass

    def getDepth(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getDepth( (ParticleInfo)arg1) -> float """
        pass

    def getParticle(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getParticle( (ParticleInfo)arg1) -> Particle """
        pass

    def printParameters(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (ParticleInfo)arg1) -> None
        
        printParameters( (ParticleInfo)arg1) -> None
        """
        pass

    def printSampleTree(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (ParticleInfo)arg1) -> None
        
        printSampleTree( (ParticleInfo)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setAbundance(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setAbundance( (ParticleInfo)arg1, (float)abundance) -> None """
        pass

    def setDepth(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setDepth( (ParticleInfo)arg1, (float)depth) -> None """
        pass

    def setMatchedParametersValue(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (ParticleInfo)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (ParticleInfo)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (ParticleInfo)arg1) -> None
        
        setParametersAreChanged( (ParticleInfo)arg1) -> None
        """
        pass

    def setParameterValue(self, ParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (ParticleInfo)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (ParticleInfo)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (Particle)p_particle [, (float)depth=0 [, (float)abundance=0]]) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 160


class PositionParticleInfo(ParticleInfo):
    # no doc
    def areParametersChanged(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (PositionParticleInfo)arg1) -> bool
        
        areParametersChanged( (PositionParticleInfo)arg1) -> bool
        """
        pass

    def clearParameterPool(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (PositionParticleInfo)arg1) -> None
        
        clearParameterPool( (PositionParticleInfo)arg1) -> None
        """
        pass

    def clone(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (PositionParticleInfo)arg1) -> PositionParticleInfo
        
        clone( (PositionParticleInfo)arg1) -> PositionParticleInfo
        """
        pass

    def cloneInvertB(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        cloneInvertB( (PositionParticleInfo)arg1) -> ParticleInfo
        
        cloneInvertB( (PositionParticleInfo)arg1) -> ParticleInfo
        """
        pass

    def createParameterTree(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (PositionParticleInfo)arg1) -> ParameterPool
        
        createParameterTree( (PositionParticleInfo)arg1) -> ParameterPool
        """
        pass

    def getParticle(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getParticle( (PositionParticleInfo)arg1) -> Particle """
        pass

    def getPosition(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getPosition( (PositionParticleInfo)arg1) -> kvector_t """
        pass

    def printParameters(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (PositionParticleInfo)arg1) -> None
        
        printParameters( (PositionParticleInfo)arg1) -> None
        """
        pass

    def printSampleTree(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printSampleTree( (PositionParticleInfo)arg1) -> None
        
        printSampleTree( (PositionParticleInfo)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (PositionParticleInfo)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (PositionParticleInfo)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (PositionParticleInfo)arg1) -> None
        
        setParametersAreChanged( (PositionParticleInfo)arg1) -> None
        """
        pass

    def setParameterValue(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (PositionParticleInfo)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (PositionParticleInfo)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setPosition(self, PositionParticleInfo, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setPosition( (PositionParticleInfo)arg1, (kvector_t)position) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (Particle)particle, (kvector_t)position [, (float)abundance=0]) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 176


class RealParameterWrapper(__Boost_Python.instance):
    # no doc
    def assign(self, RealParameterWrapper, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ assign( (RealParameterWrapper)arg1, (RealParameterWrapper)other) -> RealParameterWrapper """
        pass

    def getValue(self, RealParameterWrapper, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getValue( (RealParameterWrapper)arg1) -> float """
        pass

    def isNull(self, RealParameterWrapper, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ isNull( (RealParameterWrapper)arg1) -> bool """
        pass

    def setValue(self, RealParameterWrapper, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setValue( (RealParameterWrapper)arg1, (float)value) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (RealParameterWrapper)other) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass


class ResolutionFunction2DSimple(IResolutionFunction2D):
    # no doc
    def areParametersChanged(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (ResolutionFunction2DSimple)arg1) -> bool
        
        areParametersChanged( (ResolutionFunction2DSimple)arg1) -> bool
        """
        pass

    def clearParameterPool(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (ResolutionFunction2DSimple)arg1) -> None
        
        clearParameterPool( (ResolutionFunction2DSimple)arg1) -> None
        """
        pass

    def clone(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (ResolutionFunction2DSimple)arg1) -> ResolutionFunction2DSimple
        
        clone( (ResolutionFunction2DSimple)arg1) -> ResolutionFunction2DSimple
        """
        pass

    def createParameterTree(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (ResolutionFunction2DSimple)arg1) -> ParameterPool
        
        createParameterTree( (ResolutionFunction2DSimple)arg1) -> ParameterPool
        """
        pass

    def evaluateCDF(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        evaluateCDF( (ResolutionFunction2DSimple)arg1, (float)x, (float)y) -> float
        
        evaluateCDF( (ResolutionFunction2DSimple)arg1, (float)x, (float)y) -> float
        """
        pass

    def printParameters(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (ResolutionFunction2DSimple)arg1) -> None
        
        printParameters( (ResolutionFunction2DSimple)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def setMatchedParametersValue(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (ResolutionFunction2DSimple)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (ResolutionFunction2DSimple)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (ResolutionFunction2DSimple)arg1) -> None
        
        setParametersAreChanged( (ResolutionFunction2DSimple)arg1) -> None
        """
        pass

    def setParameterValue(self, ResolutionFunction2DSimple, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (ResolutionFunction2DSimple)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (ResolutionFunction2DSimple)arg1, (str)name, (float)value) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)sigma_x, (float)sigma_y) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 128


class RotateY_3D(ITransform3D):
    # no doc
    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)a) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 48


class RotateZ_3D(ITransform3D):
    # no doc
    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)a) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 48


class SimpleSelectionRule(ISelectionRule):
    # no doc
    def clone(self, SimpleSelectionRule, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (SimpleSelectionRule)arg1) -> SimpleSelectionRule
        
        clone( (SimpleSelectionRule)arg1) -> SimpleSelectionRule
        """
        pass

    def coordinateSelected(self, SimpleSelectionRule, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        coordinateSelected( (SimpleSelectionRule)arg1, (object)coordinate) -> bool
        
        coordinateSelected( (SimpleSelectionRule)arg1, (object)coordinate) -> bool
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (int)a, (int)b, (int)c, (int)modulus) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 48


class Simulation(ICloneable, IParameterized):
    # no doc
    def areParametersChanged(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        areParametersChanged( (Simulation)arg1) -> bool
        
        areParametersChanged( (Simulation)arg1) -> bool
        """
        pass

    def clearParameterPool(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clearParameterPool( (Simulation)arg1) -> None
        
        clearParameterPool( (Simulation)arg1) -> None
        """
        pass

    def clone(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (Simulation)arg1) -> Simulation
        
        clone( (Simulation)arg1) -> Simulation
        """
        pass

    def createParameterTree(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        createParameterTree( (Simulation)arg1) -> ParameterPool
        
        createParameterTree( (Simulation)arg1) -> ParameterPool
        """
        pass

    def getInstrument(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getInstrument( (Simulation)arg1) -> Instrument """
        pass

    def getIntensityData(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getIntensityData( (Simulation)arg1) -> IntensityData """
        pass

    def getPolarizedIntensityData(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getPolarizedIntensityData( (Simulation)arg1, (int)row, (int)column) -> IntensityData """
        pass

    def getSample(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getSample( (Simulation)arg1) -> ISample """
        pass

    def getSimulationParameters(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getSimulationParameters( (Simulation)arg1) -> SimulationParameters """
        pass

    def normalize(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ normalize( (Simulation)arg1) -> None """
        pass

    def prepareSimulation(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ prepareSimulation( (Simulation)arg1) -> None """
        pass

    def printParameters(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        printParameters( (Simulation)arg1) -> None
        
        printParameters( (Simulation)arg1) -> None
        """
        pass

    def registerParameter(self, IParameterized, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ registerParameter( (IParameterized)inst, (str)name, (int)parpointer) -> None """
        pass

    def runSimulation(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ runSimulation( (Simulation)arg1) -> None """
        pass

    def runSimulationElement(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ runSimulationElement( (Simulation)arg1, (int)index) -> None """
        pass

    def setBeamIntensity(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setBeamIntensity( (Simulation)arg1, (float)intensity) -> None """
        pass

    def setBeamParameters(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setBeamParameters( (Simulation)arg1, (float)lambda, (float)alpha_i, (float)phi_i) -> None """
        pass

    def setDetectorParameters(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setDetectorParameters( (Simulation)arg1, (IntensityData)output_data) -> None
        
        setDetectorParameters( (Simulation)arg1, (int)n_phi, (float)phi_f_min, (float)phi_f_max, (int)n_alpha, (float)alpha_f_min, (float)alpha_f_max [, (bool)isgisaxs_style=False]) -> None
        
        setDetectorParameters( (Simulation)arg1, (object)params) -> None
        """
        pass

    def setDetectorResolutionFunction(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setDetectorResolutionFunction( (Simulation)arg1, (IResolutionFunction2D)p_resolution_function) -> None """
        pass

    def setInstrument(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setInstrument( (Simulation)arg1, (Instrument)instrument) -> None """
        pass

    def setMatchedParametersValue(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setMatchedParametersValue( (Simulation)arg1, (str)wildcards, (float)value) -> int
        
        setMatchedParametersValue( (Simulation)arg1, (str)wildcards, (float)value) -> int
        """
        pass

    def setParametersAreChanged(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParametersAreChanged( (Simulation)arg1) -> None
        
        setParametersAreChanged( (Simulation)arg1) -> None
        """
        pass

    def setParameterValue(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setParameterValue( (Simulation)arg1, (str)name, (float)value) -> bool
        
        setParameterValue( (Simulation)arg1, (str)name, (float)value) -> bool
        """
        pass

    def setSample(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setSample( (Simulation)arg1, (ISample)sample) -> None """
        pass

    def setSampleBuilder(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setSampleBuilder( (Simulation)arg1, (ISampleBuilder)p_sample_builder) -> None """
        pass

    def setSimulationParameters(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setSimulationParameters( (Simulation)arg1, (SimulationParameters)sim_params) -> None """
        pass

    def setThreadInfo(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ setThreadInfo( (Simulation)arg1, (object)thread_info) -> None """
        pass

    def smearIntensityFromZAxisTilting(self, Simulation, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ smearIntensityFromZAxisTilting( (Simulation)arg1) -> None """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 720


class SimulationParameters(__Boost_Python.instance):
    # no doc
    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    me_framework = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    me_if_approx = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default

    me_lattice_type = property(lambda self: object(), lambda self, v: None, lambda self: None)  # default


    BA = 1
    DA = 0
    DWBA = 0
    EFramework = None # (!) real value is ''
    EInterferenceApproximation = None # (!) real value is ''
    ELatticeType = None # (!) real value is ''
    ISGISAXSMOR = 3
    LATTICE = 1
    LMA = 1
    NONE = 0
    PARA1D = 2
    PARA1DFINITE = 3
    SSCA = 2
    __instance_size__ = 32


class StochasticParameter_t(__Boost_Python.instance):
    # no doc
    def clone(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (StochasticParameter_t)arg1) -> StochasticParameter_t
        
        clone( (StochasticParameter_t)arg1) -> None
        """
        pass

    def getAverage(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getAverage( (StochasticParameter_t)arg1) -> float """
        pass

    def getCurrent(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getCurrent( (StochasticParameter_t)arg1) -> float """
        pass

    def getFWHM(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getFWHM( (StochasticParameter_t)arg1) -> float
        
        getFWHM( (StochasticParameter_t)arg1) -> float
        """
        pass

    def getRandom(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRandom( (StochasticParameter_t)arg1) -> float
        
        getRandom( (StochasticParameter_t)arg1) -> float
        """
        pass

    def probabilityDensity(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        probabilityDensity( (StochasticParameter_t)arg1, (float)value) -> float
        
        probabilityDensity( (StochasticParameter_t)arg1, (float)arg2) -> None
        """
        pass

    def setToAverage(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToAverage( (StochasticParameter_t)arg1) -> None
        
        setToAverage( (StochasticParameter_t)arg1) -> None
        """
        pass

    def setToRandom(self, StochasticParameter_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToRandom( (StochasticParameter_t)arg1) -> None
        
        setToRandom( (StochasticParameter_t)arg1) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)average) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 48


class StochasticDoubleGate(StochasticParameter_t):
    # no doc
    def clone(self, StochasticDoubleGate, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (StochasticDoubleGate)arg1) -> StochasticDoubleGate
        
        clone( (StochasticDoubleGate)arg1) -> StochasticDoubleGate
        """
        pass

    def getFWHM(self, StochasticDoubleGate, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getFWHM( (StochasticDoubleGate)arg1) -> float
        
        getFWHM( (StochasticDoubleGate)arg1) -> float
        """
        pass

    def getRandom(self, StochasticDoubleGate, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRandom( (StochasticDoubleGate)arg1) -> float
        
        getRandom( (StochasticDoubleGate)arg1) -> float
        """
        pass

    def getStdDev(self, StochasticDoubleGate, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getStdDev( (StochasticDoubleGate)arg1) -> float """
        pass

    def probabilityDensity(self, StochasticDoubleGate, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        probabilityDensity( (StochasticDoubleGate)arg1, (float)value) -> float
        
        probabilityDensity( (StochasticDoubleGate)arg1, (float)value) -> float
        """
        pass

    def setToAverage(self, StochasticDoubleGate, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToAverage( (StochasticDoubleGate)arg1) -> None
        
        setToAverage( (StochasticDoubleGate)arg1) -> None
        """
        pass

    def setToRandom(self, StochasticDoubleGate, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToRandom( (StochasticDoubleGate)arg1) -> None
        
        setToRandom( (StochasticDoubleGate)arg1) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)min, (float)max) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 64


class StochasticDoubleGaussian(StochasticParameter_t):
    # no doc
    def clone(self, StochasticDoubleGaussian, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (StochasticDoubleGaussian)arg1) -> StochasticDoubleGaussian
        
        clone( (StochasticDoubleGaussian)arg1) -> StochasticDoubleGaussian
        """
        pass

    def getFWHM(self, StochasticDoubleGaussian, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getFWHM( (StochasticDoubleGaussian)arg1) -> float
        
        getFWHM( (StochasticDoubleGaussian)arg1) -> float
        """
        pass

    def getRandom(self, StochasticDoubleGaussian, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRandom( (StochasticDoubleGaussian)arg1) -> float
        
        getRandom( (StochasticDoubleGaussian)arg1) -> float
        """
        pass

    def getStdDev(self, StochasticDoubleGaussian, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getStdDev( (StochasticDoubleGaussian)arg1) -> float """
        pass

    def probabilityDensity(self, StochasticDoubleGaussian, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        probabilityDensity( (StochasticDoubleGaussian)arg1, (float)value) -> float
        
        probabilityDensity( (StochasticDoubleGaussian)arg1, (float)value) -> float
        """
        pass

    def setToAverage(self, StochasticDoubleGaussian, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToAverage( (StochasticDoubleGaussian)arg1) -> None
        
        setToAverage( (StochasticDoubleGaussian)arg1) -> None
        """
        pass

    def setToRandom(self, StochasticDoubleGaussian, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToRandom( (StochasticDoubleGaussian)arg1) -> None
        
        setToRandom( (StochasticDoubleGaussian)arg1) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1, (float)average, (float)std_dev) -> None """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 56


class StochasticSampledParameter(StochasticParameter_t):
    # no doc
    def clone(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        clone( (StochasticSampledParameter)arg1) -> StochasticSampledParameter
        
        clone( (StochasticSampledParameter)arg1) -> StochasticSampledParameter
        """
        pass

    def getBinValue(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getBinValue( (StochasticSampledParameter)arg1, (int)ibin) -> float """
        pass

    def getFWHM(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getFWHM( (StochasticSampledParameter)arg1) -> float
        
        getFWHM( (StochasticSampledParameter)arg1) -> float
        """
        pass

    def getNbins(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getNbins( (StochasticSampledParameter)arg1) -> int """
        pass

    def getNormalizedProbability(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ getNormalizedProbability( (StochasticSampledParameter)arg1, (int)ibin) -> float """
        pass

    def getRandom(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        getRandom( (StochasticSampledParameter)arg1) -> float
        
        getRandom( (StochasticSampledParameter)arg1) -> float
        """
        pass

    def probabilityBinDensity(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ probabilityBinDensity( (StochasticSampledParameter)arg1, (int)ibin) -> float """
        pass

    def probabilityDensity(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        probabilityDensity( (StochasticSampledParameter)arg1, (float)value) -> float
        
        probabilityDensity( (StochasticSampledParameter)arg1, (float)value) -> float
        """
        pass

    def setToAverage(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToAverage( (StochasticSampledParameter)arg1) -> None
        
        setToAverage( (StochasticSampledParameter)arg1) -> None
        """
        pass

    def setToRandom(self, StochasticSampledParameter, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        setToRandom( (StochasticSampledParameter)arg1) -> None
        
        setToRandom( (StochasticSampledParameter)arg1) -> None
        """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """
        __init__( (object)arg1, (StochasticParameter_t)par, (int)nbins, (float)xmin, (float)xmax) -> None
        
        __init__( (object)arg1, (StochasticParameter_t)par, (int)nbins [, (int)nfwhm=3]) -> None
        """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    __instance_size__ = 80


class vdouble1d_t(__Boost_Python.instance):
    # no doc
    def append(self, vdouble1d_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ append( (vdouble1d_t)arg1, (object)arg2) -> None """
        pass

    def extend(self, vdouble1d_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ extend( (vdouble1d_t)arg1, (object)arg2) -> None """
        pass

    def __contains__(self, vdouble1d_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __contains__( (vdouble1d_t)arg1, (object)arg2) -> bool """
        pass

    def __delitem__(self, vdouble1d_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __delitem__( (vdouble1d_t)arg1, (object)arg2) -> None """
        pass

    def __getitem__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __getitem__( (object)arg1, (object)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __iter__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iter__( (object)arg1) -> object """
        pass

    def __len__(self, vdouble1d_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __len__( (vdouble1d_t)arg1) -> int """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    def __setitem__(self, vdouble1d_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __setitem__( (vdouble1d_t)arg1, (object)arg2, (object)arg3) -> None """
        pass

    __instance_size__ = 40


class vector_IFormFactorPtr_t(__Boost_Python.instance):
    # no doc
    def append(self, vector_IFormFactorPtr_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ append( (vector_IFormFactorPtr_t)arg1, (object)arg2) -> None """
        pass

    def extend(self, vector_IFormFactorPtr_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ extend( (vector_IFormFactorPtr_t)arg1, (object)arg2) -> None """
        pass

    def __contains__(self, vector_IFormFactorPtr_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __contains__( (vector_IFormFactorPtr_t)arg1, (object)arg2) -> bool """
        pass

    def __delitem__(self, vector_IFormFactorPtr_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __delitem__( (vector_IFormFactorPtr_t)arg1, (object)arg2) -> None """
        pass

    def __getitem__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __getitem__( (object)arg1, (object)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __iter__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iter__( (object)arg1) -> object """
        pass

    def __len__(self, vector_IFormFactorPtr_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __len__( (vector_IFormFactorPtr_t)arg1) -> int """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    def __setitem__(self, vector_IFormFactorPtr_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __setitem__( (vector_IFormFactorPtr_t)arg1, (object)arg2, (object)arg3) -> None """
        pass

    __instance_size__ = 40


class vector_integer_t(__Boost_Python.instance):
    # no doc
    def append(self, vector_integer_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ append( (vector_integer_t)arg1, (object)arg2) -> None """
        pass

    def extend(self, vector_integer_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ extend( (vector_integer_t)arg1, (object)arg2) -> None """
        pass

    def __contains__(self, vector_integer_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __contains__( (vector_integer_t)arg1, (object)arg2) -> bool """
        pass

    def __delitem__(self, vector_integer_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __delitem__( (vector_integer_t)arg1, (object)arg2) -> None """
        pass

    def __getitem__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __getitem__( (object)arg1, (object)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __iter__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iter__( (object)arg1) -> object """
        pass

    def __len__(self, vector_integer_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __len__( (vector_integer_t)arg1) -> int """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    def __setitem__(self, vector_integer_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __setitem__( (vector_integer_t)arg1, (object)arg2, (object)arg3) -> None """
        pass

    __instance_size__ = 40


class vector_kvector_t(__Boost_Python.instance):
    # no doc
    def append(self, vector_kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ append( (vector_kvector_t)arg1, (object)arg2) -> None """
        pass

    def extend(self, vector_kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ extend( (vector_kvector_t)arg1, (object)arg2) -> None """
        pass

    def __contains__(self, vector_kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __contains__( (vector_kvector_t)arg1, (object)arg2) -> bool """
        pass

    def __delitem__(self, vector_kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __delitem__( (vector_kvector_t)arg1, (object)arg2) -> None """
        pass

    def __getitem__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __getitem__( (object)arg1, (object)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __iter__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iter__( (object)arg1) -> object """
        pass

    def __len__(self, vector_kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __len__( (vector_kvector_t)arg1) -> int """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    def __setitem__(self, vector_kvector_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __setitem__( (vector_kvector_t)arg1, (object)arg2, (object)arg3) -> None """
        pass

    __instance_size__ = 40


class vector_longinteger_t(__Boost_Python.instance):
    # no doc
    def append(self, vector_longinteger_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ append( (vector_longinteger_t)arg1, (object)arg2) -> None """
        pass

    def extend(self, vector_longinteger_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ extend( (vector_longinteger_t)arg1, (object)arg2) -> None """
        pass

    def __contains__(self, vector_longinteger_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __contains__( (vector_longinteger_t)arg1, (object)arg2) -> bool """
        pass

    def __delitem__(self, vector_longinteger_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __delitem__( (vector_longinteger_t)arg1, (object)arg2) -> None """
        pass

    def __getitem__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __getitem__( (object)arg1, (object)arg2) -> object """
        pass

    def __init__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __init__( (object)arg1) -> None """
        pass

    def __iter__(self, p_object, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __iter__( (object)arg1) -> object """
        pass

    def __len__(self, vector_longinteger_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __len__( (vector_longinteger_t)arg1) -> int """
        pass

    def __reduce__(self, *args, **kwargs): # real signature unknown
        pass

    def __setitem__(self, vector_longinteger_t, *args, **kwargs): # real signature unknown; NOTE: unreliably restored from __doc__ 
        """ __setitem__( (vector_longinteger_t)arg1, (object)arg2, (object)arg3) -> None """
        pass

    __instance_size__ = 40



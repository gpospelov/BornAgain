# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

import _libBornAgainBase

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


import weakref

class SwigPyIterator(object):
    r"""Proxy of C++ swig::SwigPyIterator class."""

    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _libBornAgainBase.delete_SwigPyIterator

    def value(self):
        r"""value(SwigPyIterator self) -> PyObject *"""
        return _libBornAgainBase.SwigPyIterator_value(self)

    def incr(self, n=1):
        r"""incr(SwigPyIterator self, size_t n=1) -> SwigPyIterator"""
        return _libBornAgainBase.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        r"""decr(SwigPyIterator self, size_t n=1) -> SwigPyIterator"""
        return _libBornAgainBase.SwigPyIterator_decr(self, n)

    def distance(self, x):
        r"""distance(SwigPyIterator self, SwigPyIterator x) -> ptrdiff_t"""
        return _libBornAgainBase.SwigPyIterator_distance(self, x)

    def equal(self, x):
        r"""equal(SwigPyIterator self, SwigPyIterator x) -> bool"""
        return _libBornAgainBase.SwigPyIterator_equal(self, x)

    def copy(self):
        r"""copy(SwigPyIterator self) -> SwigPyIterator"""
        return _libBornAgainBase.SwigPyIterator_copy(self)

    def next(self):
        r"""next(SwigPyIterator self) -> PyObject *"""
        return _libBornAgainBase.SwigPyIterator_next(self)

    def __next__(self):
        r"""__next__(SwigPyIterator self) -> PyObject *"""
        return _libBornAgainBase.SwigPyIterator___next__(self)

    def previous(self):
        r"""previous(SwigPyIterator self) -> PyObject *"""
        return _libBornAgainBase.SwigPyIterator_previous(self)

    def advance(self, n):
        r"""advance(SwigPyIterator self, ptrdiff_t n) -> SwigPyIterator"""
        return _libBornAgainBase.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        r"""__eq__(SwigPyIterator self, SwigPyIterator x) -> bool"""
        return _libBornAgainBase.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        r"""__ne__(SwigPyIterator self, SwigPyIterator x) -> bool"""
        return _libBornAgainBase.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        r"""__iadd__(SwigPyIterator self, ptrdiff_t n) -> SwigPyIterator"""
        return _libBornAgainBase.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        r"""__isub__(SwigPyIterator self, ptrdiff_t n) -> SwigPyIterator"""
        return _libBornAgainBase.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        r"""__add__(SwigPyIterator self, ptrdiff_t n) -> SwigPyIterator"""
        return _libBornAgainBase.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        r"""
        __sub__(SwigPyIterator self, ptrdiff_t n) -> SwigPyIterator
        __sub__(SwigPyIterator self, SwigPyIterator x) -> ptrdiff_t
        """
        return _libBornAgainBase.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self

# Register SwigPyIterator in _libBornAgainBase:
_libBornAgainBase.SwigPyIterator_swigregister(SwigPyIterator)

SHARED_PTR_DISOWN = _libBornAgainBase.SHARED_PTR_DISOWN

class ICloneable(object):
    r"""


    Interface for polymorphic classes that should not be copied, except by explicit cloning.

    Child classes of  ICloneable must provide clone().

    C++ includes: ICloneable.h

    """

    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _libBornAgainBase.delete_ICloneable

    def clone(self):
        r"""
        clone(ICloneable self) -> ICloneable
        virtual ICloneable* ICloneable::clone() const =0

        """
        return _libBornAgainBase.ICloneable_clone(self)

    def transferToCPP(self):
        r"""
        transferToCPP(ICloneable self)
        virtual void ICloneable::transferToCPP()

        Used for Python overriding of clone (see swig/tweaks.py) 

        """
        return self.__disown__()

# Register ICloneable in _libBornAgainBase:
_libBornAgainBase.ICloneable_swigregister(ICloneable)


def mul_I(z):
    r"""
    mul_I(complex_t z) -> complex_t
    complex_t mul_I(complex_t z)

    Returns product I*z, where I is the imaginary unit. 

    """
    return _libBornAgainBase.mul_I(z)

def exp_I(z):
    r"""
    exp_I(complex_t z) -> complex_t
    complex_t exp_I(complex_t z)

    Returns exp(I*z), where I is the imaginary unit. 

    """
    return _libBornAgainBase.exp_I(z)

def rad2deg(angle):
    r"""
    rad2deg(double angle) -> double
    double Units::rad2deg(double angle)

    """
    return _libBornAgainBase.rad2deg(angle)

def deg2rad(angle):
    r"""
    deg2rad(double angle) -> double
    double Units::deg2rad(double angle)

    """
    return _libBornAgainBase.deg2rad(angle)

cvar = _libBornAgainBase.cvar
I = cvar.I
nanometer = cvar.nanometer
angstrom = cvar.angstrom
micrometer = cvar.micrometer
millimeter = cvar.millimeter
meter = cvar.meter
nm = cvar.nm
nm2 = cvar.nm2
barn = cvar.barn
radian = cvar.radian
milliradian = cvar.milliradian
degree = cvar.degree
steradian = cvar.steradian
rad = cvar.rad
mrad = cvar.mrad
sr = cvar.sr
deg = cvar.deg
tesla = cvar.tesla
gauss = cvar.gauss

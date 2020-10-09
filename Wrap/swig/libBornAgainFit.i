// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainFit.i
//! @brief     SWIG interface file for libBornAgainFit
//!
//!            Configuration is done in Fit/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainFit"

%feature("autodoc");

%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_shared_ptr.i"

%include "warnings.i"

%include "auto/Wrap/doxygenFit.i"

%rename(minimize_cpp) Fit::Minimizer::minimize;
%rename(add_cpp) Fit::Parameters::add;

%feature("director") PyCallback;         // used in extendFit.i

%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector< std::vector<double> >;
%template(vector_integer_t) std::vector<int >;
%template(vector_longinteger_t) std::vector<unsigned long int >;
%template(vector_complex_t) std::vector< std::complex<double> >;
%template(vector_string_t) std::vector<std::string>;

#define SWIG_FILE_WITH_INIT

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
%}

%include "numpy.i"
%init %{
import_array();
%}

#ifndef BORNAGAIN_PYTHON
#define BORNAGAIN_PYTHON
#endif

%{
#include "Fit/Tools/RealLimits.h"
#include "Fit/Tools/AttLimits.h"
#include "Fit/Kernel/Parameter.h"
#include "Fit/Kernel/Parameters.h"
#include "Fit/Minimizer/IMinimizer.h"
#include "Fit/Minimizer/MinimizerCatalog.h"
#include "Fit/Minimizer/MinimizerFactory.h"

#include "Fit/Kernel/PyCallback.h"
#include "Fit/Kernel/MinimizerResult.h"
#include "Fit/Kernel/Minimizer.h"
%}

// The following goes verbatim from libBornAgainFit.i to libBornAgainFit_wrap.cxx.
// Note that the order matters, as base classes must be included before derived classes.

%include "Fit/Tools/RealLimits.h"
%include "Fit/Tools/AttLimits.h"
%include "Fit/Kernel/Parameter.h"
%include "Fit/Kernel/Parameters.h"
%include "Fit/Kernel/PyCallback.h"
%include "Fit/Kernel/MinimizerResult.h"
%include "Fit/Kernel/Minimizer.h"
%include "Fit/Minimizer/IMinimizer.h"
%include "Fit/Minimizer/MinimizerCatalog.h"
%include "Fit/Minimizer/MinimizerFactory.h"

%pythoncode %{
class ParametersIterator(object):

    def __init__(self, parameters):
        self.parameters = parameters
        self.index = -1

    def __iter__(self):
        return self

    def next(self):
        self.index += 1
        if self.index < self.parameters.size():
            return self.parameters[self.index]
        else:
            raise StopIteration

    def __next__(self):
        return self.next()
%}

// Parameters accessors
namespace Fit {

%extend Parameters {
    const Parameter& __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    const Parameter& __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode %{
def __iter__(self):
    return ParametersIterator(self)
%}
};

}

// --- Parameter x.value attribute
namespace Fit {

%extend Parameter{
%pythoncode %{
value = property(value, setValue)
error = property(error, setError)


%}
};

}


// --- Setting up Minimizer callback ---

%pythoncode %{
class CallableWrapper(PyCallback):
    def __init__(self, f, callable_type):
        super(CallableWrapper, self).__init__(callable_type)
        self.f_ = f
    def call_scalar(self, obj):
        return self.f_(obj)
    def call_residuals(self, obj):
        return self.f_(obj)

%}

namespace Fit {

%extend Minimizer {
%pythoncode %{
    def minimize(self, callback, pars):
        if not callable(callback):
            raise Exception("Not a Python callable")

        # single call to callback to check return type
        result = callback(pars)

        if isinstance(result, float):
            wrp = CallableWrapper(callback, PyCallback.SCALAR)
            return self.minimize_cpp(wrp, pars)
        elif hasattr(result, '__len__'):
            wrp = CallableWrapper(callback, PyCallback.RESIDUAL)
            return self.minimize_cpp(wrp, pars)
        else:
            raise Exception("Wrong callable type")

%}
};

%extend Parameters {
%pythoncode %{
    def add(self, name, value=None, vary=True, min=-float('inf'), max=float('inf'), step=0.0):
        par = None
        if isinstance(name, Parameter):
            par = name
        else:
            limits = AttLimits.limitless()
            if min != -float('inf') and max != float('inf'):
                limits = AttLimits.limited(min, max)
            elif min != -float('inf') and max==float('inf'):
                limits = AttLimits.lowerLimited(min)
            elif min == -float('inf') and max != float('inf'):
                limits = AttLimits.upperLimited(max)
            if not vary:
                limits = AttLimits.fixed()
            par = Parameter(name, value, limits, step)

        self.add_cpp(par)

%}
};
}

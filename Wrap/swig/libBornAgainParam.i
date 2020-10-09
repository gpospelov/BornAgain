// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainParam.i
//! @brief     SWIG interface file for libBornAgainParam
//!
//!            Configuration is done in Param/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainParam"

%feature("autodoc");

/**/
%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_shared_ptr.i"

%include "../../auto/Wrap/doxygenParam.i"

%include "warnings.i"

%include "ignoreBase.i"

%feature("director") IParameterized;     // needed by ISampleBuilder
%feature("director") INode;              // needed by ISample

%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector<std::vector<double>>;
%template(vector_integer_t) std::vector<int>;
%template(vinteger2d_t) std::vector<std::vector<int>>;
%template(vector_longinteger_t) std::vector<unsigned long int>;
%template(vector_complex_t) std::vector< std::complex<double>>;
%template(vector_string_t) std::vector<std::string>;
%template(map_string_double_t) std::map<std::string, double>;
%template(pvacuum_double_t) std::pair<double, double>;
%template(vector_pvacuum_double_t) std::vector<std::pair<double, double>>;
%nodefaultctor ParameterPool;

#define SWIG_FILE_WITH_INIT

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
%}

%include "numpy.i"
%init %{
    import_array();
%}

#define GCC_DIAG_OFF(x)
#define GCC_DIAG_ON(x)

#ifndef BORNAGAIN_PYTHON
#define BORNAGAIN_PYTHON
#endif

%{
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Param/Base/IParameterized.h"

#include "Param/Node/INode.h"
#include "Param/Node/INodeVisitor.h"

#include "Param/Distrib/Distributions.h"
#include "Param/Distrib/ParameterDistribution.h"
#include "Param/Varia/ParameterSample.h"
#include "Param/Distrib/RangedDistributions.h"

%}

%import(module="libBornAgainBase") "Base/Types/Complex.h"
%import(module="libBornAgainBase") "Base/Types/ICloneable.h"
%import(module="libBornAgainBase") "Base/Vector/BasicVector3D.h"
%import(module="libBornAgainBase") "Base/Vector/Vectors3D.h"
%include "fromBase.i"

%ignore IParameterized::addParametersToExternalPool(const std::string&, ParameterPool*, int) const;
%ignore IParameterized::addParametersToExternalPool(const std::string&, ParameterPool*) const;
%ignore RangedDistribution;

%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;

%include "Param/Base/IParameter.h"
%template(IParameterReal) IParameter<double>; // needed to avoid warning 401?

%include "Param/Base/RealParameter.h"
%include "Param/Base/ParameterPool.h"
%include "Param/Base/IParameterized.h"

%include "Param/Node/INode.h"
%include "Param/Node/INodeVisitor.h"

%include "Param/Distrib/Distributions.h"
%include "Param/Distrib/Distributions.h"
%include "Param/Distrib/ParameterDistribution.h"
%include "Param/Distrib/RangedDistributions.h"

%include "Param/Varia/ParameterSample.h"
%template(ParameterSampleVector) std::vector<ParameterSample>;

%include "extendParam.i"

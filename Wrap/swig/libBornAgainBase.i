// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainBase.i
//! @brief     SWIG interface file for libBornAgainBase
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainBase"

%feature("autodoc");

/**/
%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_shared_ptr.i"

%include "../../auto/Wrap/doxygenBase.i"

%include "warnings.i"
%include "ignores.i"
%include "renameBase.i"
%include "directors.i"

%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector<std::vector<double>>;

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
#include "Base/Types/Complex.h"
#include "Base/Types/ICloneable.h"
#include "Base/Const/Units.h"
#include "Base/Utils/ThreadInfo.h"

#include "Base/Vector/BasicVector3D.h"
#include "Base/Vector/Vectors3D.h"

#include "Base/Utils/MathFunctions.h"

#include "Base/Axis/Bin.h"
#include "Base/Axis/ConstKBinAxis.h"
#include "Base/Axis/CustomBinAxis.h"
#include "Base/Axis/FixedBinAxis.h"
#include "Base/Axis/VariableBinAxis.h"

#include "Base/Pixel/IPixel.h"

%}

%include "Base/Types/ICloneable.h"
%include "Base/Types/Complex.h"
%include "Base/Const/Units.h"

%include "Base/Utils/MathFunctions.h"
%include "Base/Utils/ThreadInfo.h"

%include "Base/Vector/BasicVector3D.h"
%include "Base/Vector/Vectors3D.h"

%include "Base/Axis/Bin.h"
%include "Base/Axis/IAxis.h"
%include "Base/Axis/VariableBinAxis.h"
%include "Base/Axis/ConstKBinAxis.h"
%include "Base/Axis/CustomBinAxis.h"
%include "Base/Axis/FixedBinAxis.h"

%include "Base/Pixel/IPixel.h"

%include "fromBase.i"

%include "extendBase.i"

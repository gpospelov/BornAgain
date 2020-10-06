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

#include "Base/Vector/BasicVector3D.h"
#include "Base/Vector/Vectors3D.h"
#include "Base/Vector/WavevectorInfo.h"

#include "Base/Utils/MathFunctions.h"
%}

%include "Base/Types/ICloneable.h"
%include "Base/Types/Complex.h"
%include "Base/Const/Units.h"
%include "Base/Utils/MathFunctions.h"

%include "Base/Vector/BasicVector3D.h"
%include "fromBase.i"

%include "Base/Vector/Vectors3D.h"
%include "Base/Vector/WavevectorInfo.h"

%include "extendBase.i"

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.cpp
//! @brief     Implements PyEmbeddedTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.h"
#include "Tests/Functional/Python/PyEmbedded/TestCases.h"

PyEmbeddedTestFactory::PyEmbeddedTestFactory()
{
    registerItem("SysPath", create_new<SysPath>);
    registerItem("ImportNumpy", create_new<ImportNumpy>);
    registerItem("FunctionCall", create_new<FunctionCall>);
    registerItem("MethodCall", create_new<MethodCall>);
    registerItem("CompiledFunction", create_new<CompiledFunction>);
    registerItem("ObjectExtract", create_new<ObjectExtract>);
    registerItem("EmbeddedMultiLayer", create_new<EmbeddedMultiLayer>);
    registerItem("ExportToPythonAndBack", create_new<ExportToPythonAndBack>);
    registerItem("ModuleFunctionsList", create_new<ModuleFunctionsList>);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/PythonScriptSampleBuilder.h
//! @brief     Defines class PythonScriptSampleBuilder
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYTHONSCRIPTSAMPLEBUILDER_H
#define PYTHONSCRIPTSAMPLEBUILDER_H


#include "ISampleBuilder.h"

#include <QFileInfo>

class BA_CORE_API_ PythonScriptSampleBuilder : public ISampleBuilder
{
public:
    PythonScriptSampleBuilder(QString script_path);
    virtual ~PythonScriptSampleBuilder();

    virtual ISample *buildSample() const;
private:
    QFileInfo m_script_path;
    static const char *m_class_name;
    static const char *m_const_function_name;
};

#endif // PYTHONSCRIPTSAMPLEBUILDER_H

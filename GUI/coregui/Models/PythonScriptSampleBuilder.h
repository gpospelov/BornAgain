#ifndef PYTHONSCRIPTSAMPLEBUILDER_H
#define PYTHONSCRIPTSAMPLEBUILDER_H

#include "ISampleBuilder.h"

#include <QDir>

class PythonScriptSampleBuilder : public ISampleBuilder
{
public:
    PythonScriptSampleBuilder(QDir script_path);
    virtual ~PythonScriptSampleBuilder();

    virtual ISample *buildSample() const;
};

#endif // PYTHONSCRIPTSAMPLEBUILDER_H

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

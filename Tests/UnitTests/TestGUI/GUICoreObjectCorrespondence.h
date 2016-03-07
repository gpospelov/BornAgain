#ifndef GUICOREOBJECTCORRESPONDENCE_H
#define GUICOREOBJECTCORRESPONDENCE_H

#include "SessionItem.h"
#include "IParameterized.h"

#include <vector>
#include <string>
#include <QString>

#include <QtTest>

inline void GUICoreObjectCorrespondence(const SessionItem& gui_object,
                                 const IParameterized& core_object)
{
    // First check if names correspond:
    QCOMPARE( gui_object.displayName(), QString::fromStdString(core_object.getName()) );

    // Now check every parameter name:
    std::vector<std::string> core_parameter_names
        = core_object.getParameterPool()->getParameterNames();
    for (auto name : core_parameter_names) {
        QString gui_name = QString::fromStdString(name);
        std::string message = "Parameter not found: " + name;
        QVERIFY2( gui_object.isRegisteredTag(gui_name), message.c_str() );
    }
}

#endif // GUICOREOBJECTCORRESPONDENCE_H

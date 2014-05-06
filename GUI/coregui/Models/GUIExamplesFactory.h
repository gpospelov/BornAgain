#ifndef GUIEXAMPLESFACTORY_H
#define GUIEXAMPLESFACTORY_H

#include <QMap>
#include <QString>

class ParameterizedItem;
class SessionModel;

//! Class that generates GUI model from
class GUIExamplesFactory
{
public:

    static bool isValidExampleName(const QString &name);

    static ParameterizedItem *createItems(const QString &name, SessionModel *model);


private:
    static QMap<QString, QString> m_name_to_registry;
    //!< correspondance of GUI example name and name from StandardSamples registry
};


#endif


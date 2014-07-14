#ifndef GROUPPROPERTYREGISTRY_H
#define GROUPPROPERTYREGISTRY_H

#include <QMap>
#include <QString>

class ParameterizedItem;

class GroupPropertyRegistry
{
public:
    GroupPropertyRegistry();
    ~GroupPropertyRegistry();

private:
    static GroupPropertyRegistry *m_instance;

    typedef QMap<QString, ParameterizedItem *(*)()> ObjectMap_t;
};


#endif

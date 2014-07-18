#ifndef GROUPPROPERTYREGISTRY_H
#define GROUPPROPERTYREGISTRY_H

#include <QMap>
#include <QString>

class FancyGroupProperty;
class SelectableGroupProperty;
class FixedGroupProperty;
class ParameterizedItem;

//! The GroupPropertyRegistry constructs FancyGroupProperty or SelectableGroupProperty
//! according to the given name of the group.
class GroupPropertyRegistry
{
public:
    //! correspondance of group name to ParameterizedItem's types to labels
    typedef QMap<QString, QMap<QString, QString> > SelectableGroupMap_t;

    static FancyGroupProperty *createGroupProperty(const QString &group_name);

private:
//    static SelectableGroupProperty *createSelectableGroupProperty(const QString &group_name, ParameterizedItem *parent = 0);
//    static FixedGroupProperty *createFixedGroupProperty(const QString &group_name, ParameterizedItem *parent = 0);

    static SelectableGroupMap_t m_selectable_group_map;
    //!< Contains correspondance of selectable group names to they content,
    //!< namely item type and item label
};


#endif

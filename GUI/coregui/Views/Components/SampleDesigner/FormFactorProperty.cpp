#include "FormFactorProperty.h"
#include "FormFactorItems.h"

namespace {
template<typename T> ParameterizedItem *createInstance() { return new T; }

QMap<QString, ParameterizedItem *(*)()> initializeFormFactorMap() {
    QMap<QString, ParameterizedItem *(*)()> result;
    result[QString("Cylinder")] = &createInstance<CylinderItem>;
    result[QString("FullSphere")] = &createInstance<FullSphereItem>;
    return result;
}
}


QMap<QString, ParameterizedItem *(*)()> FormFactorProperty::m_ff_map =
        initializeFormFactorMap();

FormFactorProperty::FormFactorProperty(QString ff_name)
    : m_ff_name("Undefined")
{
    if (m_ff_map.contains(ff_name)) {
        m_ff_name = ff_name;
    }
}

int FormFactorProperty::index() const
{
    return toIndex(m_ff_name);
}

int FormFactorProperty::toIndex(const QString value) const
{
    QStringList name_list = getFormFactorNames();
    for (int i = 0; i < name_list.size(); ++i) {
        if (value == name_list[i]) {
            return i;
        }
    }
    return -1;
}

QString FormFactorProperty::toString(const int index) const
{
    QStringList name_list = getFormFactorNames();
    if (index<0 || index>=name_list.size()) {
        return QString();
    }
    return name_list[index];
}

ParameterizedItem *FormFactorProperty::createFormFactorItem(QString name)
{
    if (!m_ff_map.contains(name)) return 0;
    return m_ff_map[name]();
}

#include "FormFactorProperty.h"

FormFactorProperty::FormFactorProperty(QString ff_name)
    : m_ff_name("Undefined")
{
    initializeFormFactorList();
    if (m_ff_names.contains(ff_name)) {
        m_ff_name = ff_name;
    }
}

int FormFactorProperty::index() const
{
    return toIndex(m_ff_name);
}

int FormFactorProperty::toIndex(const QString value) const
{
    for (int i = 0; i < m_ff_names.size(); ++i) {
        if (value == m_ff_names[i]) {
            return i;
        }
    }
    return -1;
}

QString FormFactorProperty::toString(const int index) const
{
    if (index<0 || index>=m_ff_names.size()) {
        return QString();
    }
    return m_ff_names[index];
}

void FormFactorProperty::initializeFormFactorList()
{
    m_ff_names.clear();
    m_ff_names << "Cylinder" << "FullSphere";
}

#include "imode.h"

IMode::IMode(QObject *parent) : m_isEnabled(true)
{
    (void)parent;
}

void IMode::setEnabled(bool enabled)
{
    if (m_isEnabled == enabled) return;
    m_isEnabled = enabled;
    emit enabledStateChanged(m_isEnabled);
}

bool IMode::isEnabled() const
{
    return m_isEnabled;
}

#ifndef HOSTOSINFO_H
#define HOSTOSINFO_H

#include <QString>

namespace Utils {

#define QTC_WIN_EXE_SUFFIX ".exe"

enum OsType { OsTypeWindows, OsTypeLinux, OsTypeMac, OsTypeOtherUnix, OsTypeOther };

class OsSpecificAspects
{
public:
    OsSpecificAspects(OsType osType) : m_osType(osType) { }

    QString withExecutableSuffix(const QString &executable) const {
        QString finalName = executable;
        if (m_osType == OsTypeWindows)
            finalName += QLatin1String(QTC_WIN_EXE_SUFFIX);
        return finalName;
    }

    Qt::CaseSensitivity fileNameCaseSensitivity() const {
        return m_osType == OsTypeWindows ? Qt::CaseInsensitive : Qt::CaseSensitive;
    }

    QChar pathListSeparator() const {
        return QLatin1Char(m_osType == OsTypeWindows ? ';' : ':');
    }

    Qt::KeyboardModifier controlModifier() const {
        return m_osType == OsTypeMac ? Qt::MetaModifier : Qt::ControlModifier;
    }

private:
    const OsType m_osType;
};


class HostOsInfo
{
public:

    static inline OsType hostOs();

    enum HostArchitecture { HostArchitectureX86, HostArchitectureAMD64, HostArchitectureItanium,
                            HostArchitectureArm, HostArchitectureUnknown };
    static HostArchitecture hostArchitecture();

    static bool isWindowsHost() { return hostOs() == OsTypeWindows; }
    static bool isLinuxHost() { return hostOs() == OsTypeLinux; }
    static bool isMacHost() { return hostOs() == OsTypeMac; }
    static inline bool isAnyUnixHost();

    static QString withExecutableSuffix(const QString &executable)
    {
        return hostOsAspects().withExecutableSuffix(executable);
    }

    static Qt::CaseSensitivity fileNameCaseSensitivity()
    {
        return hostOsAspects().fileNameCaseSensitivity();
    }

    static QChar pathListSeparator()
    {
        return hostOsAspects().pathListSeparator();
    }

    static Qt::KeyboardModifier controlModifier()
    {
        return hostOsAspects().controlModifier();
    }

private:
    static OsSpecificAspects hostOsAspects() { return OsSpecificAspects(hostOs()); }
};


OsType HostOsInfo::hostOs()
{
#if defined(Q_OS_WIN)
    return OsTypeWindows;
#elif defined(Q_OS_LINUX)
    return OsTypeLinux;
#elif defined(Q_OS_MAC)
    return OsTypeMac;
#elif defined(Q_OS_UNIX)
    return OsTypeOtherUnix;
#else
    return OsTypeOther;
#endif
}

bool HostOsInfo::isAnyUnixHost()
{
#ifdef Q_OS_UNIX
    return true;
#else
    return false;
#endif
}

} // namespace Utils

#endif // HOSTOSINFO_H


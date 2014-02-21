#include "stringutils.h"
#include "hostosinfo.h"
#include <QFileInfo>
#include <QDir>

namespace Utils
{

QString withTildeHomePath(const QString &path)
{
    if (Utils::HostOsInfo::isWindowsHost())
        return path;

    static const QString homePath = QDir::homePath();

    QFileInfo fi(QDir::cleanPath(path));
    QString outPath = fi.absoluteFilePath();
    if (outPath.startsWith(homePath))
        outPath = QLatin1Char('~') + outPath.mid(homePath.size());
    else
        outPath = path;
    return outPath;
}


}

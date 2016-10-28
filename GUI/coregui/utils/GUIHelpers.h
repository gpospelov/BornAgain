//* ************************************************************************* //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/GUIHelpers.h
//! @brief     Defines class GUIHelpers functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
//* ************************************************************************* //

#ifndef GUIHELPERS_H
#define GUIHELPERS_H

#include "WinDllMacros.h"
#include <QStringList>
#include <QWidget>
#include <memory>
#include <sstream>

class JobItem;
class RealDataItem;

namespace GUIHelpers
{
class BA_CORE_API_ Error : public std::exception
{
public:
    explicit Error(const QString& message) throw()
        : message(message) {}
    virtual ~Error() throw() {}

    virtual const char* what() const throw() { return message.toLatin1().data(); }

private:
    QString message;
};

BA_CORE_API_ void information(QWidget* parent, const QString& title,
        const QString& text, const QString& detailedText=QString());
BA_CORE_API_ void warning(QWidget* parent, const QString& title,
        const QString& text, const QString& detailedText=QString());
BA_CORE_API_ bool question(QWidget* parent, const QString& title,
        const QString& text, const QString& detailedText=QString(),
        const QString& yesText="&Yes",
        const QString& noText="&No");
BA_CORE_API_ bool okToDelete(QWidget* parent, const QString& title,
        const QString& text, const QString& detailedText=QString());

BA_CORE_API_ int getVariantType(const QVariant& variant);

BA_CORE_API_ QString getBornAgainVersionString();

BA_CORE_API_ QString getValidFileName(const QString& proposed_name);

BA_CORE_API_ QString fileDir(const QString& fileName);

BA_CORE_API_ bool parseVersion(
    const QString& version, int& major_num, int& minor_num, int& patch_num);

BA_CORE_API_ bool isVersionMatchMinimal(const QString& version, const QString& minimal_version);

BA_CORE_API_ QString currentDateTime();

BA_CORE_API_ QStringList fromStdStrings(const std::vector<std::string>& container);

BA_CORE_API_ QVector<double> fromStdVector(const std::vector<double>& data);

template<class T, class... Ts> std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

BA_CORE_API_ QString createUuid();

BA_CORE_API_ bool isTheSame(const QStringList& lhs, const QStringList& rhs);

} // namespace GUIHelpers

inline std::ostream&  operator <<(std::ostream& stream,const QString& str)
{
   stream << str.toStdString();
   return stream;
}



#endif // GUIHELPERS_H

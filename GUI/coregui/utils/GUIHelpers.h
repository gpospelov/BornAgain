// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIHelpers.h
//! @brief     Defines class GUIHelpers functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIHELPERS_H
#define GUIHELPERS_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>
#include <exception>
#include <memory>

class QVariant;

namespace GUIHelpers
{
class BA_CORE_API_ Error : public std::exception
{
public:
    explicit Error(const QString &message) throw()
        : message(message) {}
    virtual ~Error() throw() {}

    virtual const char *what() const throw() { return message.toLatin1().data(); }

private:
    QString message;
};

BA_CORE_API_ void information(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());
BA_CORE_API_ void warning(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());
BA_CORE_API_ bool question(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString(),
        const QString &yesText=QObject::tr("&Yes"),
        const QString &noText=QObject::tr("&No"));
BA_CORE_API_ bool okToDelete(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());

BA_CORE_API_ int getVariantType(const QVariant &variant);

BA_CORE_API_ QString getBornAgainVersionString();

BA_CORE_API_ QString getValidFileName(const QString &proposed_name);

template<class T, class... Ts> std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

} // namespace GUIHelpers

#endif // GUIHELPERS_H


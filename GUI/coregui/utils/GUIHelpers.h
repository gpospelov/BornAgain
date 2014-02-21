// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      utils/GUIHelpers.h
//! @brief     Defines GUI helper functions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIHELPERS_H
#define GUIHELPERS_H

#include <QWidget>
#include <QString>

#include <exception>

namespace GUIHelpers
{
class Error : public std::exception
{
public:
    explicit Error(const QString &message) throw()
        : message(message.toUtf8()) {}
    ~Error() throw() {}

    const char *what() const throw() { return message; }

private:
    const char *message;
};

void information(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());
void warning(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());
bool question(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString(),
        const QString &yesText=QObject::tr("&Yes"),
        const QString &noText=QObject::tr("&No"));
bool okToDelete(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());
};

#endif // GUIHELPERS_H


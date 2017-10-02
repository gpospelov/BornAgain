// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/PyImportAssistant.h
//! @brief     Implements class PyImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PYIMPORTASSISTANT_H
#define PYIMPORTASSISTANT_H

#include "WinDllMacros.h"
#include <QObject>

class MainWindow;

//! Assists in importing Python object to GUI models.

class BA_CORE_API_ PyImportAssistant : public QObject
{
    Q_OBJECT
public:
    PyImportAssistant(MainWindow* mainwin);

    void exec();

private:
    QString fileNameToOpen();
    void saveImportDir(const QString& fileName);
    QString readFile(const QString& fileName);

    MainWindow* m_mainWindow;
};


#endif // PYIMPORTASSISTANT_H

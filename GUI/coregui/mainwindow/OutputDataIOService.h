// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOService.h
//! @brief     Defines class OutputDataIOService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAIOSERVICE_H
#define OUTPUTDATAIOSERVICE_H

#include "WinDllMacros.h"
#include <QObject>

class ApplicationModels;

//! Provide read/write of heavy data files in a separate thread.
//!
//! Listens all models and keep tracks of changes in IntensityDataItem. Provides logic to
//! not to re-save already saved data.

class BA_CORE_API_ OutputDataIOService : public QObject
{
    Q_OBJECT
public:
    explicit OutputDataIOService(ApplicationModels* models, QObject* parent = 0);

    void setApplicationModels(ApplicationModels* models);

private:
    ApplicationModels* m_applicationModels;
};

#endif // OUTPUTDATAIOSERVICE_H

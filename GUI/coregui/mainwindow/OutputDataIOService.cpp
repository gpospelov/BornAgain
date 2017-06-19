// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOService.h
//! @brief     Implements class OutputDataIOService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataIOService.h"

OutputDataIOService::OutputDataIOService(ApplicationModels* models, QObject* parent)
    : QObject(parent)
    , m_applicationModels(nullptr)
{
    setApplicationModels(models);
}

void OutputDataIOService::setApplicationModels(ApplicationModels* models)
{

}


// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/SaveProjectionsAssistant.cpp
//! @brief     Implements class SaveProjectionsAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SaveProjectionsAssistant.h"
#include "ProjectUtils.h"
#include <QFileDialog>
#include <QDebug>

void SaveProjectionsAssistant::saveProjections(IntensityDataItem* item)
{
    QString defaultName = ProjectUtils::userExportDir() + QString("/untitled.txt");
    QString fileName =QFileDialog::getSaveFileName(0, "Save projections data", defaultName);

    qDebug() << "Aaa" << fileName;
}

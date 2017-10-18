// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitLogFlags.cpp
//! @brief     Implements class FitLogFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitLogFlags.h"
#include <QMap>

namespace {

QMap<FitLogFlags::MessageType, Qt::GlobalColor> messageTypeToColorMap()
{
    QMap<FitLogFlags::MessageType, Qt::GlobalColor> result;
    result[FitLogFlags::DEFAULT] = Qt::black;
    result[FitLogFlags::SUCCESS] = Qt::darkBlue;
    result[FitLogFlags::HIGHLIGHT] = Qt::darkGreen;
    result[FitLogFlags::WARNING] = Qt::darkYellow;
    result[FitLogFlags::ERROR] = Qt::darkRed;
    return result;
}

}

Qt::GlobalColor FitLogFlags::color(MessageType messageType)
{
    static auto typeToColor = messageTypeToColorMap();

    if (typeToColor.find(messageType) == typeToColor.end())
        return Qt::red;

    return typeToColor[messageType];
}

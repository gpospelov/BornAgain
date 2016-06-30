// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/SavePlotAssistant.h
//! @brief     Declares class SavePlotAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAVEPLOTASSISTANT_H
#define SAVEPLOTASSISTANT_H

#include "WinDllMacros.h"
#include <QString>
#include <QVector>

class QCustomPlot;
class IntensityDataItem;

//! Assistant class which contains all logic for saving IntensityData to various formats
//! from IntensityDataPlotWidget.

class BA_CORE_API_ SavePlotAssistant
{
public:
    class Format {
    public:
        Format(){}
        Format(const QString &file_extention, const QString &filter);
        QString m_file_extention;
        QString m_filter;
    };

    void savePlot(const QString &dirname, QCustomPlot *plot, IntensityDataItem *item);

private:
    void saveToFile(const QString &dirname, QCustomPlot *plot, IntensityDataItem *item);
    QString getFilterString() const;
    QString composeFileName(const QString &fileName, const QString &filterName) const;
    bool isValidExtension(const QString &fileName) const;
    QString getExtensionFromFilterName(const QString &filterName) const;
    bool isPngFile(const QString &fileName) const;
    bool isJpgFile(const QString &fileName) const;
    bool isPdfFile(const QString &fileName) const;
    static QVector<Format> m_formats;
};


#endif

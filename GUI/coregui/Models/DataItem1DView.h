// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItem1DView.h
//! @brief     Defines class DataItem1DView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATAITEM1DVIEW_H
#define DATAITEM1DVIEW_H

#include "DataItemView.h"

class AmplitudeAxisItem;
class BasicAxisItem;
class InstrumentItem;
template<class T> class OutputData;

//! View model for 1D DataItem. Can represent several items
//! at once. In current implementation the first of carried
//! items determines axes' limits.

class BA_CORE_API_ DataItem1DView : public DataItemView
{
public:
    static const QString P_TITLE;
    static const QString P_XAXIS;
    static const QString P_YAXIS;

    DataItem1DView();

    //! Number of bins in data
    int getNbins() const;

    //! returns lower and upper zoom ranges of x-axis
    double getLowerX() const;
    double getUpperX() const;

    //! returns min and max range of x-axis as given by IntensityData
    double getXmin() const;
    double getXmax() const;

    //! returns lower and upper zoom ranges of y-axis
    double getLowerY() const;
    double getUpperY() const;

    //! returns min and max range of y-axis as given by IntensityData
    double getYmin() const;
    double getYmax() const;

    bool isLog() const;
    QString getXaxisTitle() const;
    QString getYaxisTitle() const;

    QPair<double, double> dataRange() const;

    const BasicAxisItem* xAxisItem() const;
    BasicAxisItem* xAxisItem();
    const AmplitudeAxisItem* yAxisItem() const;

    void resetView();

    void setXaxisTitle(QString xtitle);
    void setYaxisTitle(QString ytitle);
    void setAxesRangeToData();
    void updateAxesUnits(const InstrumentItem* instrument);

    //! Returns data view to default state (no dimensional units, default axes' names)
    void resetToDefault();

public slots:
    void setLowerX(double xmin);
    void setUpperX(double xmax);
    void setLowerY(double ymin);
    void setUpperY(double ymax);
    void setLog(bool log_flag);

private:
    void updateAxesZoomLevel();
};

#endif // DATAITEM1DVIEW_H

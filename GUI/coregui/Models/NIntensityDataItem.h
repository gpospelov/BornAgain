// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NIntensityDataItem.h
//! @brief     Defines class NIntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NINTENSITYDATAITEM_H
#define NINTENSITYDATAITEM_H

#include "ParameterizedItem.h"
#include "OutputData.h"


class BA_CORE_API_ NIntensityDataItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_XAXIS_MIN;
    static const QString P_XAXIS_MAX;
    static const QString P_YAXIS_MIN;
    static const QString P_YAXIS_MAX;
    static const QString P_ZAXIS_MIN;
    static const QString P_ZAXIS_MAX;
    static const QString P_GRADIENT;
    static const QString P_IS_LOGZ;
    static const QString P_IS_INTERPOLATED;
    static const QString P_XAXIS_TITLE;
    static const QString P_YAXIS_TITLE;
    static const QString P_AXES_UNITS;
    static const QString P_PROPERTY_PANEL_FLAG;

    explicit NIntensityDataItem(ParameterizedItem *parent=0);
    ~NIntensityDataItem();

    OutputData<double> *getOutputData() { return m_data; }
    void setOutputData(OutputData<double> *data);

    double getXaxisMin() const;
    double getXaxisMax() const;
    double getYaxisMin() const;
    double getYaxisMax() const;
    double getZaxisMin() const;
    double getZaxisMax() const;
    QString getGradient() const;
    bool isLogz() const;
    bool isInterpolated() const;
    QString getXaxisTitle() const;
    QString getYaxisTitle() const;
    QString getAxesUnits() const;
    bool axesInRadians() const;

signals:
    void intensityModified();

public slots:
    void setXaxisMin(double xmin);
    void setXaxisMax(double xmax);
    void setYaxisMin(double ymin);
    void setYaxisMax(double ymax);
    void setZaxisRange(double zmin, double zmax);
    void setZaxisMin(double zmin);
    void setZaxisMax(double zmax);
    void setLogz(bool logz);
    void setInterpolated(bool interp);
    void setXaxisTitle(QString xtitle);
    void setYaxisTitle(QString ytitle);
    void setAxesUnits(const QString &units);

private:
    OutputData<double> *m_data; //!< simulation results

};

#endif // NINTENSITYDATAITEM_H


/*

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/OutputDataItem.h
//! @brief     Defines class OutputDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTADTAITEM_H
#define OUTPUTADTAITEM_H

#include <QObject>
#include <QString>
#include "OutputData.h"
#include "IntensityDataIOFactory.h"

class QXmlStreamWriter;
class QXmlStreamReader;

//! Holds graphical settings for the representation of OutputData in a view
class BA_CORE_API_ OutputDataItem : public QObject
{
    Q_OBJECT
public:
    OutputDataItem();
    virtual ~OutputDataItem();

    QString getName() const { return m_name;}

    double getXaxisMin() const { return m_xaxis_min; }

    double getXaxisMax() const { return m_xaxis_max; }

    double getYaxisMin() const { return m_yaxis_min; }

    double getYaxisMax() const { return m_yaxis_max; }

    double getZaxisMin() const { return m_zaxis_min; }

    double getZaxisMax() const { return m_zaxis_max; }

    bool isLogz() const { return m_is_logz; }

    bool isInterpolated() const { return m_is_interpolated; }

    void writeTo(QXmlStreamWriter *writer);
    void readFrom(QXmlStreamReader *reader);

    OutputData<double> *getOutputData() { return m_data; }

    void setOutputData(OutputData<double> *data);

    QString getXaxisTitle() const { return m_xaxis_title;}

    QString getYaxisTitle() const { return m_yaxis_title;}

    QString getAxesUnits() const { return m_axes_units; }

    bool axesInRadians() const;

signals:
    void modified();
    void intensityModified();

public slots:
    void setName(QString name);
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
    QString m_name;
    double m_xaxis_min;     //!< left bound of xaxis in a view
    double m_xaxis_max;     //!< right bounf of xaxis in a view
    double m_yaxis_min;     //!< left bound of yaxis in a view
    double m_yaxis_max;     //!< right bound of yaxis in a view
    double m_zaxis_min;     //!< left bound of zaxis in a view
    double m_zaxis_max;     //!< right bound of zaxis in a view
    bool m_is_logz;         //!< true if in logarithmic scale
    bool m_is_interpolated; //!< true if data in interpolated
    QString m_xaxis_title;
    QString m_yaxis_title;
    QString m_axes_units;
};


#endif


*/

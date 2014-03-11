#ifndef OUTPUTADTAITEM_H
#define OUTPUTADTAITEM_H

#include <QString>
#include "OutputData.h"

class QXmlStreamWriter;
class QXmlStreamReader;

//! Holds graphical settings for the representation of OutputData in a view
class OutputDataItem
{
public:
    OutputDataItem();
    virtual ~OutputDataItem(){}

    QString getName() const { return m_name;}
    void setName(QString name) { m_name = name; }

    double getXaxisMin() const { return m_xaxis_min; }
    void setXaxisMin(double xmin) { m_xaxis_min = xmin; }

    double getXaxisMax() const { return m_xaxis_max; }
    void setXaxisMax(double xmax) { m_xaxis_max = xmax; }

    double getYaxisMin() const { return m_yaxis_min; }
    void setYaxisMin(double ymin) { m_yaxis_min = ymin; }

    double getYaxisMax() const { return m_yaxis_max; }
    void setYaxisMax(double ymax) { m_yaxis_max = ymax; }

    double getZaxisMin() const { return m_zaxis_min; }
    void setZaxisMin(double zmin) { m_zaxis_min = zmin; }

    double getZaxisMax() const { return m_zaxis_max; }
    void setZaxisMax(double zmax) { m_zaxis_max = zmax; }

    bool isLogz() const { return m_is_logz; }
    void setLogz(bool logz) { m_is_logz = logz; }

    bool isInterpolated() const { return m_is_interpolated; }
    void setInterpolated(bool interp) { m_is_interpolated = interp; }

    void writeTo(QXmlStreamWriter *writer);
    void readFrom(QXmlStreamReader *reader);

private:
    const OutputData<double> *m_data; //!< simulation results
    QString m_name;
    double m_xaxis_min;     //!< left bound of xaxis in a view
    double m_xaxis_max;     //!< right bounf of xaxis in a view
    double m_yaxis_min;     //!< left bound of yaxis in a view
    double m_yaxis_max;     //!< right bound of yaxis in a view
    double m_zaxis_min;     //!< left bound of zaxis in a view
    double m_zaxis_max;     //!< right bound of zaxis in a view
    bool m_is_logz;         //!< true if in logarithmic scale
    bool m_is_interpolated; //!< true if data in interpolated

};


#endif


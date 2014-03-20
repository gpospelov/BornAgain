#ifndef OUTPUTADTAITEM_H
#define OUTPUTADTAITEM_H

#include <QObject>
#include <QString>
#include "OutputData.h"

class QXmlStreamWriter;
class QXmlStreamReader;

//! Holds graphical settings for the representation of OutputData in a view
class OutputDataItem : public QObject
{
    Q_OBJECT
public:
    OutputDataItem();
    virtual ~OutputDataItem(){}

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

signals:
    void modified();

public slots:
    void setName(QString name) { m_name = name; emit modified();}
    void setXaxisMin(double xmin) { m_xaxis_min = xmin; emit modified();}
    void setXaxisMax(double xmax) { m_xaxis_max = xmax; emit modified();}
    void setYaxisMin(double ymin) { m_yaxis_min = ymin; emit modified();}
    void setYaxisMax(double ymax) { m_yaxis_max = ymax; emit modified();}
    void setZaxisMin(double zmin) { m_zaxis_min = zmin; emit modified();}
    void setZaxisMax(double zmax) { m_zaxis_max = zmax; emit modified();}
    void setLogz(bool logz) { m_is_logz = logz; emit modified();}
    void setInterpolated(bool interp) { m_is_interpolated = interp; emit modified();}

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

};


#endif


#ifndef OUTPUTADTAITEM_H
#define OUTPUTADTAITEM_H

#include <QObject>
#include <QString>
#include "OutputData.h"
#include "IntensityDataIOFactory.h"

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

    QString getXaxisTitle() const { return m_xaxis_title;}

    QString getYaxisTitle() const { return m_yaxis_title;}


signals:
    void modified();

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

};


#endif


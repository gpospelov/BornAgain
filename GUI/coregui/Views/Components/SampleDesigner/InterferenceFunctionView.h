#ifndef INTERFERENCEFUNCTIONVIEW_H
#define INTERFERENCEFUNCTIONVIEW_H

#include "ConnectableView.h"


//! graphical representation of interference function
class InterferenceFunctionView : public ConnectableView
{
    Q_OBJECT
public:
    enum { Type = DesignerHelper::InterferenceFunctionType };

    InterferenceFunctionView(QGraphicsItem *parent = 0);

    virtual void accept(ISampleViewVisitor *visitor) { visitor->visit(this); }

    int type() const { return Type; }
};


//! graphical representation of 1D para crystal interference function
class InterferenceFunction1DParaCrystalView : public InterferenceFunctionView
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double peak_distance READ getPeakDistance WRITE setPeakDistance )
    Q_PROPERTY(double width READ getWidth WRITE setWidth )
    Q_PROPERTY(double corr_length READ getCorrLength WRITE setCorrLength )
public:
    enum { Type = DesignerHelper::InterferenceFunction1DParaType };

    InterferenceFunction1DParaCrystalView(QGraphicsItem *parent = 0);

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(ISampleViewVisitor *visitor) { visitor->visit(this); }

    int type() const { return Type; }

    double getPeakDistance() const { return m_peak_distance; }
    double getWidth() const { return m_width; }
    double getCorrLength() const { return m_corr_length; }

public slots:
    void setPeakDistance(double peak_distance) { m_peak_distance = peak_distance; }
    void setWidth(double width) { m_width = width; }
    void setCorrLength(double corr_length) { m_corr_length = corr_length; }
private:
    double m_peak_distance;
    double m_width;
    double m_corr_length;
};


#endif // INTERFERENCEFUNCTIONVIEW_H

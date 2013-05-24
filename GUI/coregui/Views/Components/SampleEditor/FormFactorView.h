#ifndef FORMFACTORVIEW_H
#define FORMFACTORVIEW_H

#include "Units.h"
#include "ISampleView.h"
#include <QGraphicsItem>
#include <iostream>


//! graphical representation of form factor
class FormFactorView : public ISampleRectView
{
public:
    FormFactorView(QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


//! graphical representation of FormFactorFullSphere
class FormFactorFullSphereView : public FormFactorView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double radius READ getRadius WRITE setRadius )
public:
    FormFactorFullSphereView(QGraphicsItem *parent = 0)
        : FormFactorView(parent)
        , m_radius(10.0*Units::nanometer) {
        setName("FormFactorFullSphere");
        setLabel("Form factor\nfull sphere");
    }

    double getRadius() const { return m_radius; }

public slots:
    void setRadius(double radius) { m_radius = radius; }
private:
    double m_radius;
};


//! graphical representation of FormFactorPyramid
class FormFactorPyramidView : public FormFactorView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double height READ getHeight WRITE setHeight )
    Q_PROPERTY(double half_side READ getHalfSide WRITE setHalfSide )
    Q_PROPERTY(double alpha READ getAlpha WRITE setAlpha )
public:
    FormFactorPyramidView(QGraphicsItem *parent = 0)
        : FormFactorView(parent)
        , m_height(5.0*Units::nanometer)
        , m_half_side(5.0*Units::nanometer)
        , m_alpha(54.73)
    {
        setName("FormFactorPyramid");
        setLabel("Form factor\npyramid");
    }
    double getHeight() const { return m_height; }
    double getHalfSide() const { return m_half_side; }
    double getAlpha() const { return m_alpha; }
public slots:
    void setHeight(double height) { m_height = height; }
    void setHalfSide(double half_side) { m_half_side = half_side; }
    void setAlpha(double alpha) { m_alpha = alpha; }

private:
    double m_height;
    double m_half_side;
    double m_alpha;
};


#endif // FORMFACTORVIEW_H

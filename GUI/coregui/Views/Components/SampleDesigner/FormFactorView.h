#ifndef FORMFACTORVIEW_H
#define FORMFACTORVIEW_H

#include "Units.h"
#include "ISampleView.h"
#include "MaterialBrowser.h"
#include "FormFactors.h"
#include <QGraphicsItem>
#include <iostream>



//! graphical representation of form factor
class FormFactorView : public ISampleRectView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::FormFactorType };
    int type() const { return Type; }

    FormFactorView(QGraphicsItem *parent = 0);

    double getWeight() const { return m_weight; }
    MaterialProperty getMaterialProperty() const { return m_materialProperty; }

public slots:
    void setWeight(double weight) { m_weight = weight; }
    void setMaterialProperty(const MaterialProperty &materialProperty)
    {
        m_materialProperty = materialProperty;
        setColor(materialProperty.getColor());
        update();
    }

private:
    double m_weight; //! weight of formfactor to be used with ParticleDecoration
    MaterialProperty m_materialProperty;
};


//! graphical representation of FormFactorFullSphere
class FormFactorFullSphereView : public FormFactorView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double weight READ getWeight WRITE setWeight )
    Q_PROPERTY(MaterialProperty material READ getMaterialProperty WRITE setMaterialProperty )
    Q_PROPERTY(double radius READ getRadius WRITE setRadius )
public:
    enum { Type = DesignerHelper::FormFactorFullSphereType };
    int type() const { return Type; }

    FormFactorFullSphereView(QGraphicsItem *parent = 0)
        : FormFactorView(parent)
        , m_ff(new FormFactorFullSphere(10.0*Units::nanometer)) {
        setName("FormFactorFullSphere");
        setLabel("Form factor\nfull sphere");        
    }
    ~FormFactorFullSphereView() { delete m_ff; }

    void setFormFactor(FormFactorFullSphere *ff) { delete m_ff; m_ff = ff; }
    const FormFactorFullSphere *getFormFactor() const { return m_ff; }

    double getRadius() const { return m_ff->getRadius(); }

public slots:
    void setRadius(double radius) { m_ff->setRadius(radius); }

private:
    FormFactorFullSphere *m_ff;
};


//! graphical representation of FormFactorPyramid
class FormFactorPyramidView : public FormFactorView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double weight READ getWeight WRITE setWeight )
    Q_PROPERTY(MaterialProperty material READ getMaterialProperty WRITE setMaterialProperty )
    Q_PROPERTY(double height READ getHeight WRITE setHeight )
    Q_PROPERTY(double half_side READ getHalfSide WRITE setHalfSide )
    Q_PROPERTY(double alpha READ getAlpha WRITE setAlpha )
public:
    enum { Type = DesignerHelper::FormFactorPyramidType };
    int type() const { return Type; }

    FormFactorPyramidView(QGraphicsItem *parent = 0)
        : FormFactorView(parent)
        , m_ff(new FormFactorPyramid(5.0*Units::nanometer, 5.0*Units::nanometer, 54.73))
    {
        setName("FormFactorPyramid");
        setLabel("Form factor\npyramid");
    }
    ~FormFactorPyramidView() { delete m_ff; }

    void setFormFactor(FormFactorPyramid *ff) { delete m_ff; m_ff = ff; }
    const FormFactorPyramid *getFormFactor() const { return m_ff; }

    double getHeight() const { return m_ff->getHeight(); }
    double getHalfSide() const { return m_ff->getHalfSide(); }
    double getAlpha() const { return m_ff->getAlpha(); }

public slots:
    void setHeight(double height) { m_ff->setHeight(height); }
    void setHalfSide(double half_side) { m_ff->setHalfSide(half_side); }
    void setAlpha(double alpha) { m_ff->setAlpha(alpha); }

private:
    FormFactorPyramid *m_ff;
};


//! graphical representation of FormFactorFullSphere
class FormFactorCylinderView : public FormFactorView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double weight READ getWeight WRITE setWeight )
    Q_PROPERTY(MaterialProperty material READ getMaterialProperty WRITE setMaterialProperty )
    Q_PROPERTY(double height READ getHeight WRITE setHeight )
    Q_PROPERTY(double radius READ getRadius WRITE setRadius )
public:
    enum { Type = DesignerHelper::FormFactorCylinderType };
    int type() const { return Type; }

    FormFactorCylinderView(QGraphicsItem *parent = 0)
        : FormFactorView(parent)
        , m_ff(new FormFactorCylinder(5.0*Units::nanometer, 5.0*Units::nanometer))
    {
        setName("FormFactorCylinder");
        setLabel("Form factor\ncylinder");
    }
    ~FormFactorCylinderView(){ delete m_ff; }

    void setFormFactor(FormFactorCylinder *ff) { delete m_ff; m_ff = ff; }
    const FormFactorCylinder *getFormFactor() const { return m_ff; }

    double getHeight() const { return m_ff->getHeight(); }
    double getRadius() const { return m_ff->getRadius(); }

public slots:
    void setHeight(double height) { m_ff->setHeight(height); }
    void setRadius(double radius) { m_ff->setRadius(radius); }

private:
    FormFactorCylinder *m_ff;
};


//! graphical representation of FormFactorPyramid
class FormFactorPrism3View : public FormFactorView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double weight READ getWeight WRITE setWeight )
    Q_PROPERTY(MaterialProperty material READ getMaterialProperty WRITE setMaterialProperty )
    Q_PROPERTY(double height READ getHeight WRITE setHeight )
    Q_PROPERTY(double half_side READ getHalfSide WRITE setHalfSide )
public:
    enum { Type = DesignerHelper::FormFactorPrism3Type };
    int type() const { return Type; }

    FormFactorPrism3View(QGraphicsItem *parent = 0)
        : FormFactorView(parent)
        , m_ff(new FormFactorPrism3(5.0*Units::nanometer, 5.0*Units::nanometer))
    {
        setName("FormFactorPrism3");
        setLabel("Form factor\nprism3");
    }
    ~FormFactorPrism3View() { delete m_ff; }

    void setFormFactor(FormFactorPrism3 *ff) { delete m_ff; m_ff = ff; }
    const FormFactorPrism3 *getFormFactor() const { return m_ff; }

    double getHeight() const { return m_ff->getHeight(); }
    double getHalfSide() const { return m_ff->getHalfSide(); }

public slots:
    void setHeight(double height) { m_ff->setHeight(height); }
    void setHalfSide(double half_side) { m_ff->setHalfSide(half_side); }

private:
    FormFactorPrism3 *m_ff;
};


#endif // FORMFACTORVIEW_H

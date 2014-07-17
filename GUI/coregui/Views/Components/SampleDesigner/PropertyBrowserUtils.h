#ifndef PROPERTYBROWSERUTILS_H
#define PROPERTYBROWSERUTILS_H

#include <QWidget>
#include "MaterialProperties.h"
#include "GroupProperty.h"
#include "ColorProperty.h"
#include "ScientificDoubleProperty.h"
#include "FancyGroupProperty.h"

class QLabel;
class QIcon;
class QComboBox;
class QLineEdit;
class QDoubleValidator;

//! The MaterialPropertyEdit class provides PropertyVariantFactory with editing
//! widget for MaterialProperty.
class MaterialPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    MaterialPropertyEdit(QWidget *parent = 0);

    void setMaterialProperty(const MaterialProperty &materialProperty);
    MaterialProperty getMaterialProperty() const {return m_materialProperty; }
signals:
    void materialPropertyChanged(const MaterialProperty &material);
private slots:
    void buttonClicked();
private:
    QLabel *m_textLabel;
    QLabel *m_pixmapLabel;
    MaterialProperty m_materialProperty;
};


//! The GroupPropertyEdit class provides PropertyVariantFactory with editing
//! widget for GroupProperty
class GroupPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    GroupPropertyEdit(QWidget *parent = 0);

    void setGroupProperty(const GroupProperty &groupProperty);
    GroupProperty getGroupProperty() const {
        return m_groupProperty;
    }

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void groupPropertyChanged(const GroupProperty &material);
private slots:
    void textChanged(QString text);
private:
    QComboBox *m_box;
    QLabel *m_label;
    GroupProperty m_groupProperty;
};



class FancyGroupPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    FancyGroupPropertyEdit(QWidget *parent = 0);

    void setFancyGroupProperty(FancyGroupProperty *groupProperty);
    FancyGroupProperty *getFancyGroupProperty() const {
        return m_groupProperty;
    }

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void fancyGroupPropertyChanged(FancyGroupProperty *group_property);
private slots:
    void textChanged(QString text);
    void indexChanged(int index);
private:
    QComboBox *m_box;
    FancyGroupProperty *m_groupProperty;
};



//! The ColorPropertyEdit class provides PropertyVariantFactory with editing
//! widget for ColorProperty
class ColorPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    ColorPropertyEdit(QWidget *parent = 0);

    void setColorProperty(const ColorProperty &colorProperty);
    ColorProperty getColorProperty() const {return m_colorProperty; }

    QString colorValueText(const QColor &c);

signals:
    void colorPropertyChanged(const ColorProperty &material_color);

private slots:
    void buttonClicked();
private:
    QLabel *m_textLabel;
    QLabel *m_pixmapLabel;
    ColorProperty m_colorProperty;
};


//! The ScientificDoublePropertyEdit class provides PropertyVariantFactory with editing
//! widget for ScientificDoubleProperty
class ScientificDoublePropertyEdit : public QWidget
{
    Q_OBJECT
public:
    ScientificDoublePropertyEdit(QWidget *parent = 0);

    void setScientificDoubleProperty(const ScientificDoubleProperty &doubleProperty);
    ScientificDoubleProperty getScientificDoubleProperty() const {
        return m_scientificDoubleProperty;
    }

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void scientificDoublePropertyChanged(const ScientificDoubleProperty &doubleProperty);
private slots:
    void onEditingFinished();
private:
    QLineEdit *m_lineEdit;
    QDoubleValidator *m_validator;
    ScientificDoubleProperty m_scientificDoubleProperty;
};

#endif // PROPERTYBROWSERUTILS_H

#ifndef PROPERTYBROWSERUTILS_H
#define PROPERTYBROWSERUTILS_H

#include "FormFactorProperty.h"
#include "MaterialProperties.h"
#include <QLabel>
#include <QIcon>
#include <QComboBox>

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

//! The FormFactorPropertyEdit class provides PropertyVariantFactory with editing
//! widget for MaterialProperty.
class FormFactorPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    FormFactorPropertyEdit(QWidget *parent = 0);

    void setFormFactorProperty(const FormFactorProperty &formFactorProperty);
    FormFactorProperty getFormFactorProperty() const {
        return m_formFactorProperty;
    }
signals:
    void formFactorPropertyChanged(const FormFactorProperty &material);
private slots:
    void textChanged(QString text);
private:
    QComboBox *m_box;
    FormFactorProperty m_formFactorProperty;
};

#endif // PROPERTYBROWSERUTILS_H

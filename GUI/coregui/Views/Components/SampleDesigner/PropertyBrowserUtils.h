#ifndef PROPERTYBROWSERUTILS_H
#define PROPERTYBROWSERUTILS_H

//#include "FormFactorProperty.h"
#include "MaterialProperties.h"
#include "GroupProperty.h"
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
    GroupProperty m_groupProperty;
};

#endif // PROPERTYBROWSERUTILS_H

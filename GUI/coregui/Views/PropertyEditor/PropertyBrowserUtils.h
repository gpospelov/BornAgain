// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/PropertyBrowserUtils.h
//! @brief     Defines class PropertyBrowserUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROPERTYBROWSERUTILS_H
#define PROPERTYBROWSERUTILS_H

#include <QWidget>
#include "MaterialProperty.h"
#include "ColorProperty.h"
#include "ScientificDoubleProperty.h"
#include "GroupProperty.h"
#include "ComboProperty.h"

class QLabel;
class QIcon;
class QComboBox;
class QLineEdit;
class QDoubleValidator;

//! The MaterialPropertyEdit class provides PropertyVariantFactory with editing
//! widget for MaterialProperty.
class BA_CORE_API_ MaterialPropertyEdit : public QWidget
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


class BA_CORE_API_ GroupPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    GroupPropertyEdit(QWidget *parent = 0);
    virtual ~GroupPropertyEdit();

    void setGroupProperty(GroupProperty_t groupProperty);
    GroupProperty_t getGroupProperty() const;

    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

signals:
    void groupPropertyChanged(const GroupProperty_t &group_property);
private slots:
    void indexChanged(int index);
private:
    void processFixedGroup();
    void processSelectableGroup();
    QComboBox *m_box;
    QLabel *m_label;
    GroupProperty_t m_groupProperty;
};

inline GroupProperty_t GroupPropertyEdit::getGroupProperty() const
{
    return m_groupProperty;
}


//! The ColorPropertyEdit class provides PropertyVariantFactory with editing
//! widget for ColorProperty
class BA_CORE_API_ ColorPropertyEdit : public QWidget
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
class BA_CORE_API_ ScientificDoublePropertyEdit : public QWidget
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

#include <QComboBox>

//! The ComboPropertyEdit class provides PropertyVariantFactory with editing
//! widget for ComboProperty
class BA_CORE_API_ ComboPropertyEdit : public QComboBox
{
    Q_OBJECT
public:
    ComboPropertyEdit(QWidget *parent = 0);

    void setComboProperty(const ComboProperty &combo_property);
    ComboProperty getComboProperty() const {return m_combo_property; }

    QString comboValueText();

signals:
    void comboPropertyChanged(const ComboProperty &combo_property);
private slots:
    void onCurrentIndexChanged(QString current_value);

private:
    ComboProperty m_combo_property;
};

#endif // PROPERTYBROWSERUTILS_H

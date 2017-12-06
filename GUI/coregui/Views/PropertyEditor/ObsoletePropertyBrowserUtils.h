// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ObsoletePropertyBrowserUtils.h
//! @brief     Defines class ObsoletePropertyBrowserUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEPROPERTYBROWSERUTILS_H
#define OBSOLETEPROPERTYBROWSERUTILS_H

#include <QWidget>
#include "ExternalProperty.h"
#include "ObsoleteColorProperty.h"
#include "ObsoleteScientificDoubleProperty.h"
#include "GroupProperty.h"
#include "ComboProperty.h"

class QLabel;
class QIcon;
class QComboBox;
class QLineEdit;
class QDoubleValidator;
class LostFocusFilter;

//! The MaterialPropertyEdit class provides PropertyVariantFactory with editing
//! widget for MaterialProperty.
class BA_CORE_API_ ObsoleteMaterialPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    ObsoleteMaterialPropertyEdit(QWidget *parent = 0);

    void setMaterialProperty(const ExternalProperty &materialProperty);
    ExternalProperty getMaterialProperty() const {return m_materialProperty; }
signals:
    void materialPropertyChanged(const ExternalProperty &material);
private slots:
    void buttonClicked();
private:
    QLabel *m_textLabel;
    QLabel *m_pixmapLabel;
    ExternalProperty m_materialProperty;
    LostFocusFilter* m_focusFilter;
};


class BA_CORE_API_ ObsoleteGroupPropertyEdit : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(GroupProperty_t group READ group WRITE setGroup USER true)

public:
    ObsoleteGroupPropertyEdit(QWidget *parent = 0);
    virtual ~ObsoleteGroupPropertyEdit();

    void setGroupProperty(GroupProperty_t groupProperty);
    GroupProperty_t getGroupProperty() const;

    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

    GroupProperty_t group() const;
    void setGroup(GroupProperty_t group);

signals:
    void groupPropertyChanged(const GroupProperty_t &group_property);

private slots:
    void indexChanged(int index);

private:
    void processGroup();
    QComboBox *m_box;
    QLabel *m_label;
    GroupProperty_t m_groupProperty;
};

inline GroupProperty_t ObsoleteGroupPropertyEdit::getGroupProperty() const
{
    return m_groupProperty;
}


//! The ColorPropertyEdit class provides PropertyVariantFactory with editing
//! widget for ColorProperty
class BA_CORE_API_ ObsoleteColorPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    ObsoleteColorPropertyEdit(QWidget *parent = 0);

    void setColorProperty(const ObsoleteColorProperty &colorProperty);
    ObsoleteColorProperty getColorProperty() const {return m_colorProperty; }

    QString colorValueText(const QColor &c);

signals:
    void colorPropertyChanged(const ObsoleteColorProperty &material_color);

private slots:
    void buttonClicked();
private:
    QLabel *m_textLabel;
    QLabel *m_pixmapLabel;
    ObsoleteColorProperty m_colorProperty;
};


//! The ScientificDoublePropertyEdit class provides PropertyVariantFactory with editing
//! widget for ScientificDoubleProperty
class BA_CORE_API_ ObsoleteScientificDoublePropertyEdit : public QWidget
{
    Q_OBJECT
public:
    ObsoleteScientificDoublePropertyEdit(QWidget *parent = 0);

    void setScientificDoubleProperty(const ObsoleteScientificDoubleProperty &doubleProperty);
    ObsoleteScientificDoubleProperty getScientificDoubleProperty() const {
        return m_scientificDoubleProperty;
    }

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void scientificDoublePropertyChanged(const ObsoleteScientificDoubleProperty &doubleProperty);
private slots:
    void onEditingFinished();
private:
    QLineEdit *m_lineEdit;
    QDoubleValidator *m_validator;
    ObsoleteScientificDoubleProperty m_scientificDoubleProperty;
};

#include <QComboBox>

//! The ComboPropertyEdit class provides PropertyVariantFactory with editing
//! widget for ComboProperty
class BA_CORE_API_ ObsoleteComboPropertyEdit : public QComboBox
{
    Q_OBJECT
public:
    ObsoleteComboPropertyEdit(QWidget *parent = 0);

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

#endif // OBSOLETEPROPERTYBROWSERUTILS_H

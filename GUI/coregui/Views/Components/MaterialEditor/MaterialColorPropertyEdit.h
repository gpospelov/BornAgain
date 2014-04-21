#ifndef MATERIALCOLORPROPERTYEDIT_H
#define MATERIALCOLORPROPERTYEDIT_H

#include "MaterialItem.h"
#include <QLabel>
#include <QIcon>
#include <QComboBox>


class MaterialColorPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    MaterialColorPropertyEdit(QWidget *parent = 0);

    void setMaterialColorProperty(const MaterialColorProperty &colorProperty);
    MaterialColorProperty getMaterialColorProperty() const {return m_colorProperty; }
signals:
    void materialColorPropertyChanged(const MaterialColorProperty &material_color);

private slots:
    void buttonClicked();
private:
    QLabel *m_textLabel;
    QLabel *m_pixmapLabel;
    MaterialColorProperty m_colorProperty;
};



#endif

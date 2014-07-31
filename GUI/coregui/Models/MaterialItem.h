#ifndef MATERIALITEM_H
#define MATERIALITEM_H


#include "ParameterizedItem.h"
#include <QColor>

class MaterialItem : public ParameterizedItem
{
    Q_OBJECT
public:

    static const QString P_MATERIAL_TYPE, P_COLOR, P_REFRACTIVE_INDEX, P_MAGNETIC_FIELD, P_IDENTIFIER;
    explicit MaterialItem(ParameterizedItem *parent=0);
    ~MaterialItem(){}
    void setMaterialType(int index);

    QString getIdentifier() const;

    QColor getColor() const;

    bool isHomogeneousMaterial() const;

    bool isHomogeneousMagneticMaterial() const;
};

#endif

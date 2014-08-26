#ifndef MATERIALITEM_H
#define MATERIALITEM_H


#include "ParameterizedItem.h"
#include <QColor>

class BA_CORE_API_ MaterialItem : public ParameterizedItem
{
    Q_OBJECT
public:

    static const QString P_MATERIAL_TYPE;
    static const QString P_COLOR;
    static const QString P_REFRACTIVE_INDEX;
    static const QString P_MAGNETIC_FIELD;
    static const QString P_IDENTIFIER;
    explicit MaterialItem(ParameterizedItem *parent=0);
    ~MaterialItem(){}
    void setMaterialType(int index);

    QString getIdentifier() const;

    QColor getColor() const;

    bool isHomogeneousMaterial() const;

    bool isHomogeneousMagneticMaterial() const;
};

#endif

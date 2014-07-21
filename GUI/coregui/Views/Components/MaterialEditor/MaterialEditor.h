#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H


#include <QObject>
#include "MaterialProperties.h"
class MaterialModel;

//! The MaterialEditor is the main class to access materials.
class MaterialEditor : public QObject
{
    Q_OBJECT
public:
    MaterialEditor(MaterialModel *materialModel);
    virtual ~MaterialEditor();

    static MaterialProperty getMaterialProperty(const QString &name);
    static MaterialProperty selectMaterialProperty();
    static MaterialProperty getDefaultMaterialProperty();

    static MaterialModel *getMaterialModel();

private:
    MaterialProperty this_selectMaterialProperty();
    MaterialProperty this_getMaterialProperty(const QString &name);
    MaterialProperty this_getDefaultMaterialProperty();
    MaterialModel *this_getMaterialModel();

    static MaterialEditor *m_instance;
    MaterialModel *m_materialModel;
};



#endif



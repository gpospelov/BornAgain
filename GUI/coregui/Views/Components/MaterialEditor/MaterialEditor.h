#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H


#include <QObject>
#include "MaterialProperty.h"
class MaterialModel;

//! The MaterialEditor is the main class to create, edit and access materials.
class MaterialEditor : public QObject
{
    Q_OBJECT
public:
    MaterialEditor(MaterialModel *model);
    virtual ~MaterialEditor();

    static MaterialProperty getMaterialProperty();
private:
    MaterialProperty this_getMaterialProperty();

    static MaterialEditor *m_instance;
    MaterialModel *m_materialModel;
};



#endif



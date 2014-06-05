#ifndef MATERIALEDITORWIDGET_H
#define MATERIALEDITORWIDGET_H

#include <QDialog>
#include "MaterialProperty.h"
class MaterialModel;
class MaterialPropertyBrowser;
class QStatusBar;
class QToolBar;

//! Main widget of MaterialEditor
class MaterialEditorWidget : public QDialog
{
    Q_OBJECT

public:

    explicit MaterialEditorWidget(MaterialModel *model, QWidget *parent = 0);
    virtual ~MaterialEditorWidget(){}

    void setModel(MaterialModel *model);

    MaterialProperty getSelectedMaterialProperty();

public slots:
    void addMaterial();
    void removeMaterial();
    void showMessage(const QString &message);
    void onSelectButton();
    void onCancelButton();

private:
    void setupActions();

    MaterialModel *m_materialModel;
    MaterialPropertyBrowser *m_propertyBrowser;
    QStatusBar *m_statusBar;
    QToolBar *m_toolBar;
    static int m_IndexOfUnnamed;
};



#endif

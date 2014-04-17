#ifndef MATERIALEDITORWIDGET_H
#define MATERIALEDITORWIDGET_H

#include <QWidget>
class MaterialModel;
class MaterialPropertyBrowser;
class QStatusBar;
class QToolBar;

//! Main widget of MaterialEditor
class MaterialEditorWidget : public QWidget
{
    Q_OBJECT

public:

    explicit MaterialEditorWidget(MaterialModel *model, QWidget *parent = 0);
    virtual ~MaterialEditorWidget(){}

    void setModel(MaterialModel *model);

public slots:
    void addMaterial();
    void removeMaterial();
    void showMessage(const QString &message);

private:
    void setupActions();

    MaterialModel *m_materialModel;
    MaterialPropertyBrowser *m_propertyBrowser;
    QStatusBar *m_statusBar;
    QToolBar *m_toolBar;
    static int m_IndexOfUnnamed;
};



#endif

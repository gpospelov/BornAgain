#ifndef MATERIALEDITORWIDGET_H
#define MATERIALEDITORWIDGET_H

#include <QWidget>
class MaterialModel;
class MaterialItem;
class QtTreePropertyBrowser;
class QtAbstractPropertyBrowser;
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtProperty;

class MaterialEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialEditorWidget(MaterialModel *model, QWidget *parent = 0);
    virtual ~MaterialEditorWidget(){}

    void setModel(MaterialModel *model);

private:
    void updateBrowser();
    void addMaterialProperties(const MaterialItem *material);
    void addSubProperties(QtProperty *property, const MaterialItem *material);

    MaterialModel *m_materialModel;
    QtTreePropertyBrowser *m_browser;
    QtVariantPropertyManager *m_variantManager;
    QtVariantEditorFactory *m_variantFactory;
};



#endif

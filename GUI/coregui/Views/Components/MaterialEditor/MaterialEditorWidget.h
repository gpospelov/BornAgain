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
class MaterialVariantManager;

class MaterialEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialEditorWidget(MaterialModel *model, QWidget *parent = 0);
    virtual ~MaterialEditorWidget(){}

    void setModel(MaterialModel *model);

private slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);

private:
    void updateBrowser();
    void addMaterialProperties(const MaterialItem *material);
    void addSubProperties(QtProperty *property, const MaterialItem *material);

    MaterialModel *m_materialModel;
    QtTreePropertyBrowser *m_browser;
    QtVariantPropertyManager *m_variantManager;
    QtVariantPropertyManager *m_readOnlyManager;
    QtVariantEditorFactory *m_variantFactory;
};



#endif

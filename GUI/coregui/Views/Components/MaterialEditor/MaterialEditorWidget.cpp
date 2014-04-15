#include "MaterialEditorWidget.h"
#include "MaterialModel.h"
#include "qttreepropertybrowser.h"
#include <QtVariantPropertyManager>
#include <QtProperty>

#include <QVBoxLayout>
#include <QDebug>


MaterialEditorWidget::MaterialEditorWidget(MaterialModel *model, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(0)
    , m_browser(0)
    , m_variantManager(0)

{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_browser = new QtTreePropertyBrowser(this);
    m_browser->setRootIsDecorated(false);

    m_variantManager = new QtVariantPropertyManager(this);

    m_variantFactory = new QtVariantEditorFactory(this);

    m_browser->setFactoryForManager(m_variantManager, m_variantFactory);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);


    setLayout(mainLayout);

    setModel(model);


}


void MaterialEditorWidget::setModel(MaterialModel *model)
{
    Q_ASSERT(model);
    if(model != m_materialModel) {
        m_materialModel = model;
        updateBrowser();
    }
}


void MaterialEditorWidget::updateBrowser()
{
    foreach(const MaterialItem *material, m_materialModel->materials()) {
        addMaterialProperties(material);
    }

}


void MaterialEditorWidget::addMaterialProperties(const MaterialItem *material)
{
    qDebug() << "MaterialEditorWidget::addMaterialProperties() " << material->getName();
    QtProperty *item_property = m_variantManager->addProperty(
                QtVariantPropertyManager::groupTypeId(), material->getName());

    Q_ASSERT(item_property);

    addSubProperties(item_property, material);
    m_browser->addProperty(item_property);

//    QtProperty *property = m_variantManager->addProperty(QVariant::String, tr("Name"));
//    property->setValue(material->getName());
//    addProperty(property, JobQueueXML::JobNameAttribute);

}


void MaterialEditorWidget::addSubProperties(QtProperty *material_property, const MaterialItem *material)
{
    Q_ASSERT(material_property);
    Q_ASSERT(material);
    QtVariantProperty *subProperty = m_variantManager->addProperty(QVariant::String, tr("End Time"));

    material_property->addSubProperty(subProperty);
}


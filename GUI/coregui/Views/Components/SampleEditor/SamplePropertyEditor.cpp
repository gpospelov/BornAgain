#include "SamplePropertyEditor.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"

#include <QtBoolPropertyManager>
#include <QtIntPropertyManager>
#include <QtStringPropertyManager>
#include <QtSizePropertyManager>
#include <QtRectPropertyManager>
#include <QtSizePolicyPropertyManager>
#include <QtEnumPropertyManager>
#include <QtGroupPropertyManager>

#include <QtCheckBoxFactory>
#include <QtSpinBoxFactory>
#include <QtSliderFactory>
#include <QtScrollBarFactory>
#include <QtLineEditFactory>
#include <QtEnumEditorFactory>
#include <QtProperty>

#include <QVBoxLayout>
#include <QVariant>
#include <iostream>

#include <QMetaObject>
#include <QMetaProperty>
#include <QVBoxLayout>
#include <QScrollArea>
#include "qtvariantproperty.h"
#include "qtgroupboxpropertybrowser.h"
#include "qttreepropertybrowser.h"
#include "qtpropertybrowser.h"



SamplePropertyEditor::SamplePropertyEditor(QWidget *parent)
//    : SamplePropertyEditorInterface(parent)
    : QWidget(parent)
    , m_variantManager(0)
    , m_propertyEditor(0)
{
    m_variantManager = new QtVariantPropertyManager(this);
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty*, QVariant)), SLOT(valueChanged(QtProperty*,QVariant)));

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);

    m_propertyEditor = new QtTreePropertyBrowser(this);
    m_propertyEditor->setFactoryForManager(m_variantManager, variantFactory);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_propertyEditor);
    setLayout(layout);


//    QtVariantProperty *property = m_variantManager->addProperty(QVariant::Double, tr("pos X"));
//    property->setValue(3.3);
//    QtBrowserItem *item = m_propertyEditor->addProperty(property);

}


void SamplePropertyEditor::valueChanged(QtProperty *property, const QVariant &value)
{
    std::cout << "SamplePropertyEditor::valueChange() " << std::endl;
    Q_UNUSED(property);
    Q_UNUSED(value);
    std::cout << "SamplePropertyEditor::valueChange() " << std::endl;
}


//void SamplePropertyEditor::attributeChanged(QtProperty *property,
//            const QString &attribute, const QVariant &val)
//{
//    std::cout << "SamplePropertyEditor::attributeChange() " << std::endl;

//}


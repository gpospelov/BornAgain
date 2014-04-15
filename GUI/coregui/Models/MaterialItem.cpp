#include "MaterialItem.h"
#include "RefractiveIndexProperty.h"
#include <QDynamicPropertyChangeEvent>
#include <QDebug>

QStringList MaterialItem::m_type_names = QStringList()
        << QString("Homogeneous Material")
        << QString("Homogeneous Magnetic Material");

MaterialItem::MaterialItem(const QString &name, MaterialType type)
    : m_name(name)
    , m_type(type)
    , m_color(Qt::red)
{

//    RefractiveIndexProperty rindex;
//    QVariant rindex_var;
//    rindex_var.setValue(rindex);
//    setProperty("Refractive index", rindex_var);

    updateProperties();
}


// emmits signal on property change
bool MaterialItem::event(QEvent * e )
{
    if(e->type() == QEvent::DynamicPropertyChange) {
        QDynamicPropertyChangeEvent *propertyEvent =
                dynamic_cast<QDynamicPropertyChangeEvent *>(e);
        Q_ASSERT(e);
        QByteArray byte_array = propertyEvent->propertyName();
        QString name(byte_array.constData());
        if (m_sub_items.contains(name)) {
            //updatePropertyItem(name);
        }
        qDebug() << "MaterialItem::event(QEvent * e ) property changed" << name;
        emit propertyChanged(name);
    }
    return QObject::event(e);
}



void MaterialItem::updateProperties()
{
    if(m_type == HomogeneousMaterial || m_type == HomogeneousMagneticMaterial) {
        addRefractiveIndexProperty();
    }

}


void MaterialItem::addRefractiveIndexProperty()
{
    setProperty("Refractive Rindex", QString("xxx"));
    RefractiveIndexItem *item = new RefractiveIndexItem();
    m_sub_items["Refractive Rindex"] = item;

    connect(item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyItemChanged(QString)));

}

void MaterialItem::onPropertyItemChanged(QString propertyName)
{
    qDebug() << "MaterialItem::onPropertyItemChanged() ";
}


void MaterialItem::removeRefractiveIndexProperty()
{


}





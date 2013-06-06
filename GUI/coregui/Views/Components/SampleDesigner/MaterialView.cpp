#include "MaterialView.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <iostream>

int MaterialView::m_nmaterial = 0;
QMap<QString, MaterialView *> MaterialView::m_materials = QMap<QString, MaterialView *>();

MaterialView::MaterialView(QGraphicsItem *parent)
    : ISampleView(parent)
    , m_refractive_index(1,0)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    m_rect = QRect(0, 0, DesignerHelper::getDefaultMaterialWidth(), DesignerHelper::getDefaultMaterialHeight());
    m_color = DesignerHelper::getDefaultMaterialColor();
    setToolTip(QString("%1\n\n%2").arg("HomogeneousMaterial")
               .arg("Drag and drop it on top of the layer or form factor."));
//    m_materials.app
    setName(proposeName());
}

MaterialView::~MaterialView()
{

}

QString MaterialView::proposeName()
{
    QString result = QString("%1%2").arg("material").arg(m_nmaterial);
    std::cout << "MaterialView::proposeName " << result.toStdString() << std::endl;
    m_nmaterial++;
    return result;
}


void MaterialView::registerName(const QString &name)
{
    std::cout << "MaterialView::registerName() ->" << std::endl;
//    QMap<QString, MaterialView *>::iterator pos = m_materials.find(name);
//    Q_ASSERT(pos==m_materials.end());

    for(QMap<QString, MaterialView *>::iterator it = m_materials.begin(); it!=m_materials.end(); ++it) {
        std::cout << it.key().toStdString() << " " << it.value() << std::endl;
    }
    m_materials.insert(name, this);
}


void MaterialView::setName(const QString &name)
{
    m_name = name;
    registerName(name);
}


void MaterialView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(m_color);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getMaterialGradient(m_color, m_rect ) );
    painter->drawEllipse(m_rect);
}


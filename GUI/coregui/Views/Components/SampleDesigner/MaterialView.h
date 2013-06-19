#ifndef MATERIALVIEW_H
#define MATERIALVIEW_H

#include "ISampleView.h"
#include <QMap>
#include "Types.h"

//! graphical representation of material
class MaterialView : public ISampleView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(complex_t refractive_index READ getRefractiveIndex WRITE setRefractiveIndex )
    Q_PROPERTY(QColor color READ getColor WRITE setColor )

public:
    enum { Type = DesignerHelper::MultiLayerType };
    MaterialView(QGraphicsItem *parent = 0);
    virtual ~MaterialView();

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(ISampleViewVisitor *visitor) const { visitor->visit(this); }

    virtual QRectF boundingRect() const { return m_rect; }
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString getName() const { return m_name; }
    QColor getColor() const { return m_color; }
    complex_t getRefractiveIndex() const { return m_refractive_index; }

public slots:
    void setName(const QString &name);
    void setRefractiveIndex(const complex_t &index);
    void setColor(const QColor &color);

private:
    QString proposeName();
    void registerName(const QString &name);

    QRect m_rect;
    QColor m_color;
    QString m_name;
    complex_t m_refractive_index;
    static int m_nmaterial;
    static QMap<QString, MaterialView *> m_materials;
};



inline void MaterialView::setColor(const QColor &color)
{
    if(color != m_color) {
        m_color = color;
        update();
    }
}

inline void MaterialView::setRefractiveIndex(const complex_t &refractive_index)
{
    m_refractive_index = refractive_index;
}


#endif // MATERIALVIEW_H

#ifndef INSTRUMENT_EDITOR_WIDGET_H
#define INSTRUMENT_EDITOR_WIDGET_H


#include <QWidget>
#include <QLabel>
#include <QMap>

class ParameterizedItem;
class QtProperty;
class QtVariantProperty;

class InstrumentEditorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentEditorWidget(QWidget *parent = 0);
    QSize sizeHint() const { return QSize(600, 600); }

    void setInstrumentItem(ParameterizedItem *instrument);

    struct SubItem {
        SubItem(ParameterizedItem *owner=0, QString name = QString())
            : m_owner(owner), m_name(name) {}
        ParameterizedItem *m_owner;
        QString m_name;
        friend bool operator <(const SubItem& left, const SubItem& right)
        {
            if(left.m_owner == right.m_owner)
                return left.m_name < right.m_name;
            return left.m_owner < right.m_owner;
        }
    };


private:
    void addProperty(QtVariantProperty *property, const QString &id);
    void updateExpandState();
    void addSubProperties(QtProperty *item_property, ParameterizedItem *item);

    QLabel *m_label;
    class QtVariantPropertyManager *m_variantManager;
    class QtAbstractPropertyBrowser *m_propertyBrowser;

//    QMap<QtProperty *, QString> propertyToId;
//    QMap<QString, QtVariantProperty *> idToProperty;
//    QMap<QString, bool> idToExpanded;

    QMap<QtProperty *, SubItem> m_property_to_subitem;
    QMap<ParameterizedItem *, QMap<QString, QtVariantProperty *> > m_material_to_property;


};

#endif

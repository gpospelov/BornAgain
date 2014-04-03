#ifndef SAMPLEPROPERTYEDITOR_H
#define SAMPLEPROPERTYEDITOR_H


#include <QWidget>
#include <QMap>

class SampleDesignerInterface;
class QItemSelectionModel;
class QItemSelection;
class QtVariantPropertyManager;
class QtTreePropertyBrowser;
class QtProperty;
class QtVariantProperty;
class QVariant;
class QtAbstractPropertyBrowser;
class ParameterizedItem;


//! property editor to modify property of the objectcurrently selected on the graphics scene
//! located in the bottom right corner of SampleView
class SamplePropertyEditor : public QWidget
{
    Q_OBJECT

public:
    SamplePropertyEditor(QItemSelectionModel *selection_model,
                         QWidget *parent = 0);
    virtual ~SamplePropertyEditor(){}

    QObject *getObject() const;

public slots:
    //! show property of currently selected object (triggered by graphics scene)
    void selectionChanged(const QItemSelection & selected,
                          const QItemSelection & deselected);

private slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);

private:
    //! assigns item to the property editor
    void setItem(ParameterizedItem *item);

    void addSubProperties(QtProperty *item_property,
                          const ParameterizedItem *item);

    ParameterizedItem *m_item; //! object to modify

    QItemSelectionModel *m_selection_model;

    QMap<const ParameterizedItem *, QtProperty *> m_item_to_property;
    QMap<QtProperty *, const ParameterizedItem *> m_property_to_item;

    QMap<QtProperty *, int>     m_property_to_index;
    QMap<const ParameterizedItem *, QMap<int, QtVariantProperty *> >
        m_item_to_index_to_property;

    QMap<QtProperty *, bool>    m_property_to_expanded;

    QList<QtProperty *>         m_top_level_properties;

    QtAbstractPropertyBrowser    *m_browser;
    QtVariantPropertyManager *m_manager;
    QtVariantPropertyManager *m_read_only_manager;

    void addItemProperties(const ParameterizedItem *item);
    void updateItemProperties(const ParameterizedItem *item);
    bool isSubValue(int value, int subValue) const;
};


#endif // SAMPLEPROPERTYEDITOR_H

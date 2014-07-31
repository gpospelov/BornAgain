#ifndef SAMPLEPROPERTYEDITOR_H
#define SAMPLEPROPERTYEDITOR_H


#include <QWidget>
#include <QMap>
#include <QString>

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
    struct ItemIndexPair {
        ItemIndexPair(ParameterizedItem *item=0, int index=0)
            : m_item(item), m_index(index) {}
        ParameterizedItem *m_item;
        int m_index;
    };

public slots:
    //! show property of currently selected object (triggered by graphics scene)
    void selectionChanged(const QItemSelection & selected,
                          const QItemSelection & deselected);

private slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);
    void updateSubItems(const QString &name);
    void onPropertyChanged(const QString &property_name);

private:
    //! assigns item to the property editor
    void setItem(ParameterizedItem *item);

    //! clear editor
    void clearEditor();

    ParameterizedItem *m_item; //! object to modify

    QItemSelectionModel *m_selection_model;

    QMap<QtProperty *, ItemIndexPair>     m_property_to_item_index_pair;
    QMap<const ParameterizedItem *, QMap<int, QtVariantProperty *> >
        m_item_to_index_to_property;

    QMap<const ParameterizedItem *, QMap<QString, QtVariantProperty *> >
        m_item_to_propertyname_to_qtvariantproperty;


    QtAbstractPropertyBrowser    *m_browser;
    QtVariantPropertyManager *m_manager;
    QtVariantPropertyManager *m_read_only_manager;

    void addItemProperties(const ParameterizedItem *item);
    void addSubProperties(QtProperty *item_property,
                          const ParameterizedItem *item);
};


#endif // SAMPLEPROPERTYEDITOR_H

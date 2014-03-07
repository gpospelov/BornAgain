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
    //! assigns objects to the property editor
    void setObject(QObject *object);

    QObject *m_object; //! object to modify

    QItemSelectionModel *m_selection_model;

//    QMap<const QMetaObject *, QtProperty *> m_classToProperty;
//    QMap<QtProperty *, const QMetaObject *> m_propertyToClass;

    QMap<const ParameterizedItem *, QtProperty *> m_itemToProperty;
    QMap<QtProperty *, const ParameterizedItem *> m_propertyToItem;
    QMap<const ParameterizedItem *, QMap<QString, QtVariantProperty *> >
            m_itemToStringToProperty;

    QMap<QtProperty *, int>     m_propertyToIndex;
//    QMap<const QMetaObject *, QMap<int, QtVariantProperty *> > m_classToIndexToProperty;

    QMap<QtProperty *, bool>    m_propertyToExpanded;

    QList<QtProperty *>         m_topLevelProperties;

    QtAbstractPropertyBrowser    *m_browser;
    QtVariantPropertyManager *m_manager;
    QtVariantPropertyManager *m_readOnlyManager;

//    void addClassProperties(const QMetaObject *metaObject);
    void addItemProperties(const ParameterizedItem *item);
//    void updateClassProperties(const QMetaObject *metaObject, bool recursive);
    void updateItemProperties(const ParameterizedItem *item);
//    void saveExpandedState();
//    void restoreExpandedState();
//    int enumToInt(const QMetaEnum &metaEnum, int enumValue) const;
//    int intToEnum(const QMetaEnum &metaEnum, int intValue) const;
//    int flagToInt(const QMetaEnum &metaEnum, int flagValue) const;
//    int intToFlag(const QMetaEnum &metaEnum, int intValue) const;
    bool isSubValue(int value, int subValue) const;
//    bool isPowerOf2(int value) const;

};


#endif // SAMPLEPROPERTYEDITOR_H

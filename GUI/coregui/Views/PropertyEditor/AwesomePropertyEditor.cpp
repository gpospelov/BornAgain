// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/AwesomePropertyEditor.cpp
//! @brief     Implements class AwesomePropertyEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AwesomePropertyEditor.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "ParameterizedItem.h"
#include "tooltipdatabase.h"
#include "GUIHelpers.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include <QEvent>
#include <QAbstractSpinBox>
#include <QtProperty>
#include <QMetaProperty>
#include <QDebug>
#include <QVBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <cmath>


class AwesomePropertyEditorPrivate
{
public:
    struct ItemPropertyPair {
        ItemPropertyPair(ParameterizedItem *item=0, QString property_name = QString())
            : m_item(item), m_name(property_name) {}
        ParameterizedItem *m_item;
        QString m_name;
        friend bool operator<(const ItemPropertyPair& left, const ItemPropertyPair& right)
        {
            if(left.m_item == right.m_item)
                return left.m_name < right.m_name;
            return left.m_item < right.m_item;
        }
        friend bool operator==(const ItemPropertyPair& left, const ItemPropertyPair& right)
        {
            return (left.m_item == right.m_item) && (left.m_name < right.m_name);
        }
        void clear() { m_name.clear(); m_item = 0; }
    };

    AwesomePropertyEditorPrivate(QWidget *parent, AwesomePropertyEditor::EBrowserType browser_type);
    ~AwesomePropertyEditorPrivate();

    QtAbstractPropertyBrowser *m_browser;
    QtVariantPropertyManager  *m_manager;
    QtVariantPropertyManager  *m_read_only_manager;
    AwesomePropertyEditor::EBrowserType m_browser_type;
    PropertyVariantFactory *m_propertyFactory;
    QMap<QtProperty *, ItemPropertyPair> m_qtproperty_to_itempropertypair;
    QMap<ParameterizedItem *, QMap<QString, QtVariantProperty *> > m_item_to_property_to_qtvariant;
    QMap<QString, QtVariantProperty *> m_groupname_to_qtvariant;
    QMap<QtVariantProperty *, QList<QtVariantProperty *> > m_qtvariant_to_dependend;
    QMap<ParameterizedItem *, QMap<QString, AwesomePropertyEditor::EInsertMode > > m_item_subitem_insert_mode;
    ItemPropertyPair m_current_item_property_pair;
};

AwesomePropertyEditorPrivate::AwesomePropertyEditorPrivate(QWidget *parent, AwesomePropertyEditor::EBrowserType browser_type)
    : m_browser(0)
    , m_manager(0)
    , m_read_only_manager(0)
    , m_browser_type(browser_type)
    , m_propertyFactory(new PropertyVariantFactory())
{
    if(m_browser_type == AwesomePropertyEditor::BROWSER_TREE_TYPE) {
        QtTreePropertyBrowser *browser = new QtTreePropertyBrowser(parent);
        browser->setResizeMode(QtTreePropertyBrowser::Interactive);
        browser->setRootIsDecorated(false);
        m_browser = browser;
    }
    else if(m_browser_type == AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE) {
        m_browser = new QtGroupBoxPropertyBrowser(parent);
    }
    else if(m_browser_type == AwesomePropertyEditor::BROWSER_BUTTON_TYPE) {
        m_browser = new QtButtonPropertyBrowser(parent);
    }
    else {
        throw GUIHelpers::Error("UniversalPropertyEditor::UniversalPropertyEditor() -> Error. Unknown browser type.");
    }
    m_read_only_manager = new PropertyVariantManager(parent);

    m_manager = new PropertyVariantManager(parent);
//    QtVariantEditorFactory *factory = new PropertyVariantFactory();
    m_browser->setFactoryForManager(m_manager, m_propertyFactory);

}

inline AwesomePropertyEditorPrivate::~AwesomePropertyEditorPrivate()
{
    delete m_propertyFactory;
}


AwesomePropertyEditor::AwesomePropertyEditor(QWidget *parent, EBrowserType browser_type)
    : QWidget(parent)
    , m_d(new AwesomePropertyEditorPrivate(this, browser_type))
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("AwesomePropertyEditor"));

    m_d->m_browser->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
//    m_d->m_browser->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_d->m_browser);

    connect(m_d->m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));
}

AwesomePropertyEditor::~AwesomePropertyEditor()
{
    delete m_d;
}

void AwesomePropertyEditor::setItem(ParameterizedItem *item, const QString &group_name)
{
    qDebug() << "AwesomePropertyEditor::setItem(ParameterizedItem *item)";
    clearEditor();
    if(item) addItemProperties(item, group_name);
}

//! adds given ParameterizedItem's property to the group
void AwesomePropertyEditor::addItemProperty(ParameterizedItem *item, const QString &property_name, const QString &group_name, AwesomePropertyEditor::EInsertMode subitem_insert_policy)
{
    Q_ASSERT(item);
    qDebug() << " AwesomePropertyEditor::addItemProperty() " << item << property_name << group_name << subitem_insert_policy;
    QtVariantProperty *groupVariantProperty(0);
    if(!group_name.isEmpty()) {
        if(m_d->m_groupname_to_qtvariant.contains(group_name)) {
            groupVariantProperty = m_d->m_groupname_to_qtvariant[group_name];
        } else {
            groupVariantProperty = m_d->m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), group_name);
            m_d->m_groupname_to_qtvariant[group_name] = groupVariantProperty;
            m_d->m_browser->addProperty(groupVariantProperty);
        }
    }
    insertItemProperty(item, property_name, groupVariantProperty, INSERT_AS_CHILD, subitem_insert_policy);
}

//! adds all ParameterizedItem properties to the group
void AwesomePropertyEditor::addItemProperties(ParameterizedItem *item, const QString &group_name, AwesomePropertyEditor::EInsertMode subitem_insert_policy)
{
    Q_ASSERT(item);
    qDebug() << "AwesomePropertyEditor::addItemProperties() group_name:" << group_name;
    QtVariantProperty *groupVariantProperty(0);
    if(!group_name.isEmpty()) {
        if(m_d->m_groupname_to_qtvariant.contains(group_name)) {
            groupVariantProperty = m_d->m_groupname_to_qtvariant[group_name];
            qDebug() << "AwesomePropertyEditor::addItemProperties() 1.1";
        } else {
            groupVariantProperty = m_d->m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), group_name);
            m_d->m_groupname_to_qtvariant[group_name] = groupVariantProperty;
            m_d->m_browser->addProperty(groupVariantProperty);
            qDebug() << "AwesomePropertyEditor::addItemProperties() 1.2" << groupVariantProperty;
        }
    }
    insertItemProperties(item, groupVariantProperty, INSERT_AS_CHILD, subitem_insert_policy);
}

//! clears the editor from all properties and connections
void AwesomePropertyEditor::clearEditor()
{
    qDebug() << "AwesomePropertyEditor::clearEditor()";
    disconnect(m_d->m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));
    disconnect();

    m_d->m_browser->clear();

    QMap<QtProperty *, AwesomePropertyEditorPrivate::ItemPropertyPair>::iterator it = m_d->m_qtproperty_to_itempropertypair.begin();
    while(it!=m_d->m_qtproperty_to_itempropertypair.end()) {
        delete it.key();
        it++;
    }

    m_d->m_qtproperty_to_itempropertypair.clear();
    m_d->m_item_to_property_to_qtvariant.clear();
    m_d->m_groupname_to_qtvariant.clear();
    m_d->m_qtvariant_to_dependend.clear();
    m_d->m_item_subitem_insert_mode.clear();

    connect(m_d->m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));

}

//! updates corresponding property of ParameterizedItem on editor change
void AwesomePropertyEditor::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    qDebug() << "AwesomePropertyEditor::slotValueChanged() BROWSER_ID:" << m_d->m_browser_type << "property:" << property->propertyName() << "value:" << value;

    if (!m_d->m_qtproperty_to_itempropertypair.contains(property)) {
        qDebug() << "    AwesomePropertyEditor::slotValueChanged()    -> No such property";
        return;
    }


    AwesomePropertyEditorPrivate::ItemPropertyPair itemPropertyPair = m_d->m_qtproperty_to_itempropertypair[property];
    qDebug() << "    AwesomePropertyEditor::slotValueChanged()-> itemPropertyPair" << itemPropertyPair.m_item << itemPropertyPair.m_name;


//    disconnect(itemPropertyPair.m_item, SIGNAL(propertyChanged(QString)),
//           this, SLOT(onPropertyChanged(QString)));

    // FIXME Find more elegant solution
    m_d->m_current_item_property_pair = itemPropertyPair;
    itemPropertyPair.m_item->setRegisteredProperty(itemPropertyPair.m_name, value);
//    itemPropertyPair.m_item->setProperty(itemPropertyPair.m_name.toUtf8().data(), value);
    m_d->m_current_item_property_pair.clear();

//    connect(itemPropertyPair.m_item, SIGNAL(propertyChanged(QString)),
//           this, SLOT(onPropertyChanged(QString)));

}

//! updates editors on ParameterizedItem's propertyChanged
void AwesomePropertyEditor::onPropertyChanged(const QString &property_name)
{
    ParameterizedItem *item = qobject_cast<ParameterizedItem *>(sender());
    qDebug() << "AwesomePropertyEditor::onPropertyChanged(const QString &property_name) BROWSER_ID:" << m_d->m_browser_type << "item->modelType(), property_name" << item->modelType() << property_name;

    QtVariantProperty *variant_property = m_d->m_item_to_property_to_qtvariant[item][property_name];
    if(variant_property) {
        QVariant property_value = item->property(property_name.toUtf8().data());

        disconnect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        disconnect(item, SIGNAL(subItemChanged(QString)),
                this, SLOT(onSubItemChanged(QString)));

        qDebug() << "       AwesomePropertyEditor::onPropertyChanged(const QString &property_name) -> Setting variant_property";
        variant_property->setValue(property_value);
        const PropertyAttribute &prop_attribute = item->getPropertyAttribute(property_name);
        if(prop_attribute.isDisabled()) {
            variant_property->setEnabled(false);
        } else {
            variant_property->setEnabled(true);
        }


        connect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)), Qt::UniqueConnection);
        connect(item, SIGNAL(subItemChanged(QString)),
                this, SLOT(onSubItemChanged(QString)), Qt::UniqueConnection);

    }
}

void AwesomePropertyEditor::onSubItemChanged(const QString &property_name)
{
    ParameterizedItem *item = qobject_cast<ParameterizedItem *>(sender());
    qDebug() << "AwesomePropertyEditor::onSubItemChanged(const QString &property_name) BROWSER_ID:" << m_d->m_browser_type << "item->modelType(), property_name" << item->modelType() << property_name;

    if(m_d->m_current_item_property_pair.m_item == item && m_d->m_current_item_property_pair.m_name == property_name) {
        return;
    }

    QtVariantProperty *variant_property = m_d->m_item_to_property_to_qtvariant[item][property_name];
    if(variant_property) {
        QVariant property_value = item->property(property_name.toUtf8().data());

        disconnect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        disconnect(item, SIGNAL(subItemChanged(QString)),
                this, SLOT(onSubItemChanged(QString)));

        variant_property->setValue(property_value);
        const PropertyAttribute &prop_attribute = item->getPropertyAttribute(property_name);
        if(prop_attribute.isDisabled()) {
            variant_property->setEnabled(false);
        } else {
            variant_property->setEnabled(true);
        }

        removeQtVariantProperties(m_d->m_qtvariant_to_dependend[variant_property]);

        insertItemProperties( item->getSubItems()[property_name], variant_property, m_d->m_item_subitem_insert_mode[item][property_name]);


        connect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        connect(item, SIGNAL(subItemChanged(QString)),
                this, SLOT(onSubItemChanged(QString)));
    }
}

//! Inserts all properties of given ParameterizedItem
void AwesomePropertyEditor::insertItemProperties(ParameterizedItem *item, QtVariantProperty *parent_qtproperty, EInsertMode insert_mode, EInsertMode subitem_insert_mode)
{
    Q_ASSERT(item);
    qDebug() << "AwesomePropertyEditor::insertItemProperties() item" << item << "parent_qtproperty" << parent_qtproperty << insert_mode << subitem_insert_mode;
    QList<QByteArray> property_names = item->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        insertItemProperty(item, prop_name, parent_qtproperty, insert_mode, subitem_insert_mode);
    }

}

//! Creates QtVariantProperty for given ParameterizedItem property name, inserts it into proper place, creates all signals, fills correspondance maps
void AwesomePropertyEditor::insertItemProperty(ParameterizedItem *item, const QString &property_name, QtVariantProperty *parent_qtproperty, EInsertMode insert_mode, EInsertMode subitem_insert_mode)
{
    Q_ASSERT(item);
    qDebug() << "AwesomePropertyEditor::insertItemProperty()" << item << property_name << parent_qtproperty << insert_mode << subitem_insert_mode;
    if(insert_mode == SKIP) return;

    QtVariantProperty *qtVariantItem = createQtVariantProperty(item, property_name);
    qDebug() << "     AwesomePropertyEditor::insertItemProperty(): qtVariantItem" << qtVariantItem;
    if(!qtVariantItem) return;

    insertQtVariantProperty(qtVariantItem, parent_qtproperty, insert_mode);

    // Processing SubProperty
    if(subitem_insert_mode != SKIP && item->getSubItems().contains(property_name)) {
        ParameterizedItem *subitem = item->getSubItems()[property_name];
        if (subitem) {
            insertItemProperties(subitem, qtVariantItem, subitem_insert_mode, subitem_insert_mode);
        }
    }

    // registering given property
    AwesomePropertyEditorPrivate::ItemPropertyPair itemPropertyPair(item, property_name);
    m_d->m_qtproperty_to_itempropertypair[qtVariantItem] = itemPropertyPair;
    m_d->m_item_to_property_to_qtvariant[item][property_name] = qtVariantItem;

    m_d->m_qtvariant_to_dependend[parent_qtproperty].append(qtVariantItem);
    m_d->m_item_subitem_insert_mode[item][property_name] = subitem_insert_mode;

    connect(item, SIGNAL(propertyChanged(QString)),
           this, SLOT(onPropertyChanged(QString)), Qt::UniqueConnection);
    connect(item, SIGNAL(subItemChanged(QString)),
            this, SLOT(onSubItemChanged(QString)), Qt::UniqueConnection);
}

//! creates QtVariantProperty for given ParameterizedItem's property
QtVariantProperty *AwesomePropertyEditor::createQtVariantProperty(ParameterizedItem *item, const QString &property_name)
{
    qDebug() << " ";
    qDebug() << "QtVariantProperty *AwesomePropertyEditor::createQtVariantProperty(ParameterizedItem *item, const QString &property_name) item" << item << property_name;
    QtVariantProperty *result(0);

    const PropertyAttribute &prop_attribute = item->getPropertyAttribute(property_name);
    if(prop_attribute.isHidden()) return 0;

    QVariant prop_value = item->getRegisteredProperty(property_name);//item->property(property_name.toUtf8().data());
    if (!prop_value.isValid()) return nullptr;
    Q_ASSERT(prop_value.isValid());
    int type = GUIHelpers::getVariantType(prop_value);

    QtVariantPropertyManager *manager = m_d->m_manager;
    if(prop_attribute.isReadOnly()) manager = m_d->m_read_only_manager;

    if(!manager->isPropertyTypeSupported(type)) {
        throw GUIHelpers::Error("AwesomePropertyEditor::createQtVariantProperty() -> Error. Not supported property type "+property_name);
    }

    if(prop_attribute.getLabel().isEmpty()) {
        result = manager->addProperty(type, property_name);
    } else {
        result = manager->addProperty(type, prop_attribute.getLabel());
    }

    if(type == QVariant::Double) {
        //result->setAttribute(QLatin1String("decimals"), prop_attribute.getDecimals());
        AttLimits limits = prop_attribute.getLimits();
        if(limits.hasLowerLimit()) result->setAttribute(QLatin1String("minimum"), limits.getLowerLimit());
        if(limits.hasUpperLimit()) result->setAttribute(QLatin1String("maximum"), limits.getUpperLimit());
        result->setAttribute(QLatin1String("decimals"), prop_attribute.getDecimals());
        result->setAttribute(QLatin1String("singleStep"), 1./std::pow(10.,prop_attribute.getDecimals()-1));
    }
    else if(type == QVariant::Int) {
        AttLimits limits = prop_attribute.getLimits();
        if(limits.hasLowerLimit()) result->setAttribute(QLatin1String("minimum"), int(limits.getLowerLimit()));
        if(limits.hasUpperLimit()) result->setAttribute(QLatin1String("maximum"), int(limits.getUpperLimit()));
    }

    QString toolTip = prop_attribute.getToolTip();
    if(toolTip.isEmpty()) {
        toolTip = ToolTipDataBase::getSampleViewToolTip(item->modelType(), property_name);
    }
    if(!toolTip.isEmpty()) result->setToolTip(toolTip);

    if(prop_attribute.isDisabled()) {
        result->setEnabled(false);
    }

    result->setValue(prop_value);

    qDebug() << "       QtVariantProperty *AwesomePropertyEditor::createQtVariantProperty(ParameterizedItem *item, const QString &property_name) result" << result;

    return result;
}

//! inserts QtVariantProperty in proper place of the browser
//! FIXME Hercules, clean this Augean stable one day.
void AwesomePropertyEditor::insertQtVariantProperty(QtVariantProperty *qtVariantItem, QtVariantProperty *parent_qtproperty, AwesomePropertyEditor::EInsertMode insert_mode)
{
    qDebug() << "AwesomePropertyEditor::insertQtVariantProperty qtVariantItem:" << qtVariantItem << " parent_property" << parent_qtproperty << insert_mode;

    if(parent_qtproperty) {
        if(insert_mode == INSERT_AS_CHILD) {
            parent_qtproperty->addSubProperty(qtVariantItem);
            qDebug() << "      AwesomePropertyEditor::insertQtVariantProperty() -> adding " << qtVariantItem << " as subproperty of" << parent_qtproperty;
        }
        else if(insert_mode == INSERT_AFTER) {
            if(m_d->m_browser->items(parent_qtproperty).size() == 1) {
                // inserting qtVariantItem after parent property, so we need to know parent of parent
                QList<QtBrowserItem *> associated = m_d->m_browser->items(parent_qtproperty);
                if(associated.size()) {
                    QtBrowserItem *parent_browser_item = associated.at(0)->parent();
                    if(parent_browser_item) {
                        QtProperty *new_parent = parent_browser_item->property();
                        //new_parent->insertSubProperty(qtVariantItem, parent_qtproperty);
                        //new_parent->insertSubProperty(qtVariantItem, new_parent->subProperties().back());
                        if(m_d->m_qtvariant_to_dependend[parent_qtproperty].size()) {
                            if(!new_parent->subProperties().contains(m_d->m_qtvariant_to_dependend[parent_qtproperty].back())) throw 1;
                            new_parent->insertSubProperty(qtVariantItem, m_d->m_qtvariant_to_dependend[parent_qtproperty].back());
                        } else {
//                      new_parent->insertSubProperty(qtVariantItem, new_parent->subProperties().back());
                        new_parent->insertSubProperty(qtVariantItem, parent_qtproperty);
                        }
                    } else {
                        //QtBrowserItem *browserItem = m_d->m_browser->insertProperty(qtVariantItem, parent_qtproperty);
                        QtBrowserItem *browserItem = m_d->m_browser->addProperty(qtVariantItem);
                        if(!browserItem) {
                            throw GUIHelpers::Error("AwesomePropertyEditor::insertQtVariantProperty() -> Failed while inserting property");
                        }
                    }
                } else {
                    throw GUIHelpers::Error("AwesomePropertyEditor::insertQtVariantProperty() -> Unexpected place");
                }
            } else {
                // our parent property is already at the top, so need to add into the browser
                QtBrowserItem *browserItem = m_d->m_browser->insertProperty(qtVariantItem, parent_qtproperty);
                if(!browserItem) {
                    throw GUIHelpers::Error("AwesomePropertyEditor::insertQtVariantProperty() -> Failed while inserting property");
                }
            }
        }
        else {
            throw GUIHelpers::Error("AwesomePropertyEditor::insertQtVariantProperty() -> Error. Unknown insert mode");
        }
    } else {
        m_d->m_browser->addProperty(qtVariantItem);
    }

    // hack to change behaviour of ComboBoxes and SpinBoxes produced by QtGroupBoxPropertyBrowser
    // with the goal to react on mouse wheel event only when there is keyboard focus
    if(m_d->m_browser_type == BROWSER_GROUPBOX_TYPE) {
        QList<QAbstractSpinBox*> spinboxes = m_d->m_browser->findChildren<QAbstractSpinBox *>();
        QList<QComboBox*> comboboxes = m_d->m_browser->findChildren<QComboBox *>();
        foreach(QAbstractSpinBox *w, spinboxes) {
            w->removeEventFilter(this);
            w->installEventFilter(this);
            w->setFocusPolicy(Qt::StrongFocus);
        }
        foreach(QComboBox *w, comboboxes) {
            w->removeEventFilter(this);
            w->installEventFilter(this);
        }
    }
}

//! removes list of QtVariantProperties from the browser and from all maps
void AwesomePropertyEditor::removeQtVariantProperties(QList<QtVariantProperty *> &list_of_properties)
{
    qDebug() << "AwesomePropertyEditor::removeQtVarintProperties(QList<QtVariantProperty> &list_of_properties)";

    foreach(QtVariantProperty *child, list_of_properties) {
        m_d->m_browser->removeProperty(child);
        delete child;
        QMap<QtProperty *, AwesomePropertyEditorPrivate::ItemPropertyPair >::iterator it = m_d->m_qtproperty_to_itempropertypair.find(child);
        if(it != m_d->m_qtproperty_to_itempropertypair.end()) {
            AwesomePropertyEditorPrivate::ItemPropertyPair itemPair = it.value();
            m_d->m_item_to_property_to_qtvariant.remove(itemPair.m_item);
            m_d->m_qtproperty_to_itempropertypair.erase(it);
        }
    }

    list_of_properties.clear();
}

//! event filter to install on combo boxes and spin boxes of QtGroupBoxPropertyBrowser to not
//! to react on wheel events during scrolling of InstrumentComponentWidget
bool AwesomePropertyEditor::eventFilter(QObject *obj, QEvent *event)
{
    if(QAbstractSpinBox* spinBox = qobject_cast<QAbstractSpinBox*>(obj)) {

        if(event->type() == QEvent::Wheel) {
            if(spinBox->focusPolicy() == Qt::WheelFocus) {
                event->accept();
                return false;
            } else {
                event->ignore();
                return true;
            }
        }
        else if(event->type() == QEvent::FocusIn) {
            spinBox->setFocusPolicy(Qt::WheelFocus);
        }
        else if(event->type() == QEvent::FocusOut) {
            spinBox->setFocusPolicy(Qt::StrongFocus);
        }
    }
    else if(qobject_cast<QComboBox*>(obj)) {
        if(event->type() == QEvent::Wheel) {
            event->ignore();
            return true;
        } else {
            event->accept();
            return false;
        }
    }
    return QObject::eventFilter(obj, event);
}

QGroupBox *AwesomePropertyEditor::getGroupBox()
{
    const QObjectList list = children();
    foreach(QObject *obj, list) {
        return dynamic_cast<QGroupBox *>(obj);
    }
    return 0;
}

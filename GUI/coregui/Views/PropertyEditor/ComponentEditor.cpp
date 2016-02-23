// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditor.cpp
//! @brief     Implements class ComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "ComponentEditor.h"
#include "ComponentEditorPrivate.h"
#include "qtpropertybrowser.h"
#include "PropertyVariantManager.h"
#include "GUIHelpers.h"
#include "ParameterizedItem.h"
#include "SessionModel.h"

#include <QVBoxLayout>
#include <QVariant>
#include <QDebug>


ComponentEditor::ComponentEditor(QWidget *parent)
    : QWidget(parent)
    , m_d(new ComponentEditorPrivate(this))
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("ComponentEditor"));

    m_d->m_browser->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_d->m_browser);

    connectManager();
}

void ComponentEditor::addItem(ParameterizedItem *item)
{
    qDebug() << "ComponentEditor::addItem(ParameterizedItem *item)" << item->modelType();
    Q_ASSERT(item);

    connectModel(item->model());

    QtVariantProperty *qtVariantProperty = createQtVariantProperty(item);

    if(qtVariantProperty) {
        m_d->m_browser->addProperty(qtVariantProperty);
        m_d->m_qtproperty_to_item[qtVariantProperty] = item;
//        m_d->m_index_to_qtvariantproperty[item->model()->indexOfItem(item)] = qtVariantProperty;
        m_d->m_item_to_qtvariantproperty[item] = qtVariantProperty;

    }


}

void ComponentEditor::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    if(topLeft != bottomRight) return;

    SessionModel *model = qobject_cast<SessionModel *>(sender());


//    const SessionModel *model = dynamic_cast<const SessionModel*>(topLeft.model());
//    qDebug() << "OOO" << model->itemForIndex(topLeft) << model->itemForIndex(bottomRight);

    qDebug() << "ComponentEditor::onDataChanged" << topLeft << bottomRight << roles;
//    QMap<QModelIndex, QtVariantProperty *>::iterator it = m_d->m_index_to_qtvariantproperty.begin();
//    while(it!=m_d->m_index_to_qtvariantproperty.end()) {
//        qDebug() << it.key() << it.value();
//        ++it;
//    }

    ParameterizedItem *item = model->itemForIndex(topLeft);
    Q_ASSERT(item);

    if(m_d->m_item_to_qtvariantproperty.contains(item)) {
        QtVariantProperty *variant_property = m_d->m_item_to_qtvariantproperty[item];

        disconnectManager();
        variant_property->setValue(item->value());
        connectManager();

    }

}

void ComponentEditor::onQtPropertyChanged(QtProperty *property, const QVariant &value)
{
    qDebug() << "ComponentEditor::onQtPropertyChanged" << property << value;

    if(m_d->m_qtproperty_to_item.contains(property)) {
        ParameterizedItem *item = m_d->m_qtproperty_to_item[property];
        disconnectModel(item->model());
        item->setValue(value);
        connectModel(item->model());
    }
}


//! creates QtVariantProperty for given ParameterizedItem's property
QtVariantProperty *ComponentEditor::createQtVariantProperty(ParameterizedItem *item)
{
    QtVariantProperty *result(0);

    QString property_name = item->itemName();
    QVariant prop_value = item->value();
    qDebug() << "QtVariantProperty *ComponentEditor::createQtVariantProperty(ParameterizedItem) item" << item << property_name << prop_value;

    if (!prop_value.isValid()) return nullptr;
    int type = GUIHelpers::getVariantType(prop_value);

    QtVariantPropertyManager *manager = m_d->m_manager;

    if(!manager->isPropertyTypeSupported(type)) {
        throw GUIHelpers::Error("ComponentEditor::createQtVariantProperty() -> Error. Not supported property type "+property_name);
    }

    result = manager->addProperty(type, property_name);
    result->setValue(prop_value);

    return result;
}

void ComponentEditor::disconnectModel(SessionModel *model)
{
    disconnect(model,
            SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this,
            SLOT(onDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));

}

void ComponentEditor::connectModel(SessionModel *model)
{
    connect(model,
            SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this,
            SLOT(onDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            Qt::UniqueConnection);

}

void ComponentEditor::disconnectManager()
{
    disconnect(m_d->m_manager,
               SIGNAL(valueChanged(QtProperty *, const QVariant &)),
               this,
               SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)));
}

void ComponentEditor::connectManager()
{
    connect(m_d->m_manager,
            SIGNAL(valueChanged(QtProperty *, const QVariant &)),
            this,
            SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)),
            Qt::UniqueConnection);
}

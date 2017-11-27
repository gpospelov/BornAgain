// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ObsoletePropertyVariantFactory.h
//! @brief     Defines class ObsoletePropertyVariantFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROPERTYVARIANTFACTORY_H
#define PROPERTYVARIANTFACTORY_H

//! collection of classes extending QtPropertyBrowser functionality

#include "GroupProperty.h"
#include <QtVariantEditorFactory>

class ObsoleteMaterialPropertyEdit;
class MaterialProperty;
class ObsoleteColorPropertyEdit;
class ColorProperty;
class ObsoleteScientificDoublePropertyEdit;
class ObsoleteScientificDoubleProperty;
class ObsoleteGroupPropertyEdit;
class ObsoleteComboPropertyEdit;
class ComboProperty;

//! The PropertyVariantFactory class provides and manages user defined
//! QVariant based properties.
class BA_CORE_API_ ObsoletePropertyVariantFactory : public QtVariantEditorFactory
{
    Q_OBJECT
public:
    ObsoletePropertyVariantFactory(QObject *parent = 0)
        : QtVariantEditorFactory(parent)
            { }

    virtual ~ObsoletePropertyVariantFactory();
protected:
    virtual void connectPropertyManager(QtVariantPropertyManager *manager);
    using QtVariantEditorFactory::createEditor;
    virtual QWidget *createEditor(QtVariantPropertyManager *manager,
                                  QtProperty *property, QWidget *parent);
    virtual void disconnectPropertyManager(QtVariantPropertyManager *manager);
private slots:
    void slotPropertyChanged(QtProperty *property, const QVariant &value);
    void slotSetValue(const MaterialProperty &value);
    void slotSetValue(const ColorProperty &value);
    void slotSetValue(const ObsoleteScientificDoubleProperty &value);
    void slotSetValue(const GroupProperty_t &value);
    void slotSetValue(const ComboProperty &value);
    void slotEditorDestroyed(QObject *object);
    void slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &);

private:
    QMap<QtProperty *, QList<ObsoleteMaterialPropertyEdit *> >
        m_property_to_material_editors;
    QMap<ObsoleteMaterialPropertyEdit *, QtProperty *>
        m_material_editor_to_property;

    QMap<QtProperty *, QList<ObsoleteColorPropertyEdit *> >
        m_property_to_color_editors;
    QMap<ObsoleteColorPropertyEdit *, QtProperty *>
        m_color_editor_to_property;

    QMap<QtProperty *, QList<ObsoleteScientificDoublePropertyEdit *> >
        m_property_to_scdouble_editors;
    QMap<ObsoleteScientificDoublePropertyEdit *, QtProperty *>
        m_scdouble_editor_to_property;

    QMap<QtProperty *, QList<ObsoleteGroupPropertyEdit *> >
        m_property_to_fancygroup_editors;
    QMap<ObsoleteGroupPropertyEdit *, QtProperty *>
        m_fancygroup_editor_to_property;

    QMap<QtProperty *, QList<ObsoleteComboPropertyEdit *> >
        m_property_to_combo_editors;
    QMap<ObsoleteComboPropertyEdit *, QtProperty *>
        m_combo_editor_to_property;

};

#endif // PROPERTYVARIANTFACTORY_H

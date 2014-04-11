#ifndef FORMFACTORPROPERTY_H
#define FORMFACTORPROPERTY_H

#include "ParameterizedItem.h"

#include <QString>
#include <QStringList>
#include <QMap>
#include <QMetaType>


//! The MaterialProperty defines material property (name,color) to be used
//! in LayerView, FormFactorView together with SamplePropertyEditor
class FormFactorProperty
{
public:
    FormFactorProperty(QString ff_name=QString());
    virtual ~FormFactorProperty(){}
    QString getFormFactorName() const { return m_ff_name; }

    void setName(const QString &name) { m_ff_name = name; }
    bool operator!=(const FormFactorProperty &other) {
        return getFormFactorName() != other.getFormFactorName();
    }
    bool isDefined() { return m_ff_name != QStringLiteral("Undefined"); }

    static QStringList getFormFactorNames() {
        return m_ff_map.keys();
    }

    int index() const;
    int toIndex(const QString value) const;
    QString toString(const int index) const;

    static ParameterizedItem *createFormFactorItem(QString name);

private:
    static QMap<QString, ParameterizedItem *(*)()> m_ff_map;
    QString m_ff_name;
};

Q_DECLARE_METATYPE(FormFactorProperty)

#endif // FORMFACTORPROPERTY_H

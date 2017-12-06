// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/UnitTests/GUI/test_utils.h
//! @brief     Defines auxiliary test functions in a namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TEST_UTILS
#define TEST_UTILS

#include <QString>
#include "SessionXML.h"
#include "PropertyItem.h"
#include <QXmlStreamWriter>
#include "verify_throw_macro.h"

namespace TestUtils
{

//! Creates directory in current working directory. If such directory already exists,
//! it will be removed with all its content.
void create_dir(const QString& dir_name);


//! Converts property to XML string
template <typename T>
QString propertyToXML(const T& property)
{
    QString result;
    QXmlStreamWriter writer(&result);
    SessionXML::writeVariant(&writer, property.variant(), /*role*/0);
    return result;
}

//! Converts XML string to property
template <typename T>
T propertyFromXML(const QString& buffer) {
    std::unique_ptr<PropertyItem> item(new PropertyItem);
    QXmlStreamReader reader(buffer);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ParameterTag) {
                SessionXML::readProperty(&reader, item.get());
            }
        }
    }

    return item->value().value<T>();
}

}

#endif // TEST_UTILS

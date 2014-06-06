#include "tooltipdatabase.h"
#include "GUIHelpers.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

ToolTipDataBase *ToolTipDataBase::m_instance = 0;
QMap<QString, QString > ToolTipDataBase::m_nameToTip = QMap();


ToolTipDataBase::ToolTipDataBase(QObject *parent)
    : QObject(parent)
{
    Q_ASSERT(!m_instance);
    m_instance = this;

    initDataBase();
}


ToolTipDataBase::~ToolTipDataBase()
{
    m_instance = 0;
}

void ToolTipDataBase::initDataBase()
{
    qDebug() << "ToolTipDataBase::initDataBase() ";

    QFile file(":/mainwindow/tooltips.xml");
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamReader reader(&file);

    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::StartElement: {
            const QStringRef tag = reader.name();
            if (tag == ToolTipsXML::modelTag) {
                continue;
            }
            if (tag == ToolTipsXML::categoryTag) {
                // <category name="SampleView">
                const QXmlStreamAttributes attributes = reader.attributes();
                const QString categoryName = attributes.value(ToolTipsXML::nameAttribute).toString();
                qDebug() << categoryName;
                continue;
            }
            if (tag == ToolTipsXML::classTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                const QString className = attributes.value(ToolTipsXML::nameAttribute).toString();
                qDebug() << className;

                continue;
            }
            if (tag == ToolTipsXML::propertyTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                const QString propertyName = attributes.value(ToolTipsXML::nameAttribute).toString();
                qDebug() << propertyName;

                continue;
            }
            if (tag == ToolTipsXML::tooltipTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                //const QString propertyName = attributes.value(ToolTipsXML::nameAttribute).toString();
                reader.readNext();
                qDebug() << reader.text();

                continue;
            }
            break;
        }
        case QXmlStreamReader::EndElement: {
           break;
        }
        default: break;
        }
    }

    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
    Q_ASSERT(0);
}

#include "tooltipdatabase.h"
#include "GUIHelpers.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

ToolTipDataBase *ToolTipDataBase::m_instance = 0;
QMap<QString, QString > ToolTipDataBase::m_tagToToolTip = QMap<QString, QString >();


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


QString ToolTipDataBase::getSampleViewToolTip(const QString &className, const QString &propertyName)
{
    Q_ASSERT(m_instance);
    return m_instance->this_getToolTip(ToolTipsXML::sampleViewContext, className, propertyName);
}


void ToolTipDataBase::initDataBase()
{
    qDebug() << "ToolTipDataBase::initDataBase() ";

    QFile file(":/mainwindow/tooltips.xml");
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamReader reader(&file);

    QString contextName, className, propertyName;
    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::StartElement: {
            const QStringRef tag = reader.name();
            if (tag == ToolTipsXML::modelTag) {
                continue;
            }
            if (tag == ToolTipsXML::contextTag) {
                // <category name="SampleView">
                const QXmlStreamAttributes attributes = reader.attributes();
                contextName = attributes.value(ToolTipsXML::nameAttribute).toString();
                //qDebug() << categoryName;
                continue;
            }
            if (tag == ToolTipsXML::classTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                className = attributes.value(ToolTipsXML::nameAttribute).toString();
                //qDebug() << className;

                continue;
            }
            if (tag == ToolTipsXML::propertyTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                propertyName = attributes.value(ToolTipsXML::nameAttribute).toString();
                //qDebug() << propertyName;

                continue;
            }
            if (tag == ToolTipsXML::tooltipTag) {
                //const QXmlStreamAttributes attributes = reader.attributes();
                //const QString propertyName = attributes.value(ToolTipsXML::nameAttribute).toString();
                reader.readNext();
                QString toolTip = reader.text().toString();
                //qDebug() << reader.text();
                addToolTip(contextName, className, propertyName, toolTip);



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
}


QString ToolTipDataBase::getTag(const QString &contextName, const QString &className, const QString &propertyName)
{
    return QString("/%1/%2/%3").arg(contextName, className, propertyName);
}


void ToolTipDataBase::addToolTip(const QString &contextName, const QString &className, const QString &propertyName, const QString &tooltip)
{
    if(!tooltip.isEmpty()) {
        QString formattedToolTip = QString("<FONT COLOR=black>"); // to have automatic line wrap
        formattedToolTip += tooltip;
        formattedToolTip += QString("</FONT>");
        m_tagToToolTip[getTag(contextName, className, propertyName)] = formattedToolTip;
    }
}


QString ToolTipDataBase::this_getToolTip(const QString &contextName, const QString &className, const QString &propertyName)
{
    return m_tagToToolTip[getTag(contextName, className, propertyName)];
}


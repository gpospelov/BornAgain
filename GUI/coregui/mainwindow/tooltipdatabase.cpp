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

QString ToolTipDataBase::getWidgetboxToolTip(const QString &propertyName)
{
    Q_ASSERT(m_instance);
    return m_instance->this_getToolTip(ToolTipsXML::widgetboxContext, ToolTipsXML::widgetboxContext, propertyName);
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
                const QXmlStreamAttributes attributes = reader.attributes();
                contextName = attributes.value(ToolTipsXML::nameAttribute).toString();
                continue;
            }
            if (tag == ToolTipsXML::categoryTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                className = attributes.value(ToolTipsXML::nameAttribute).toString();
                continue;
            }
            if (tag == ToolTipsXML::propertyTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                propertyName = attributes.value(ToolTipsXML::nameAttribute).toString();
                continue;
            }
            if (tag == ToolTipsXML::tooltipTag) {
                reader.readNext();
                QString toolTip = reader.text().toString();
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


QString ToolTipDataBase::getTag(const QString &contextName, const QString &categoryName, const QString &propertyName)
{
    return QString("/%1/%2/%3").arg(contextName, categoryName, propertyName);
}


void ToolTipDataBase::addToolTip(const QString &contextName, const QString &categoryName, const QString &propertyName, const QString &tooltip)
{
    if(!tooltip.isEmpty()) {
        QString formattedToolTip = QString("<FONT COLOR=black>"); // to have automatic line wrap
        formattedToolTip += tooltip;
        formattedToolTip += QString("</FONT>");
        m_tagToToolTip[getTag(contextName, categoryName, propertyName)] = formattedToolTip;
    }
}


QString ToolTipDataBase::this_getToolTip(const QString &contextName, const QString &className, const QString &propertyName)
{
    return m_tagToToolTip[getTag(contextName, className, propertyName)];
}


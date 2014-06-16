#ifndef TOOLTIP_DATABASE
#define TOOLTIP_DATABASE


#include <QObject>
#include <QMap>

namespace ToolTipsXML {
const QString modelTag = "ToolTipsData";
const QString contextTag = "context";
const QString classTag = "class";
const QString propertyTag = "property";
const QString tooltipTag = "tooltip";
const QString whatsthisTag = "whatsthis";
const QString nameAttribute = "name";
const QString sampleViewContext = "SampleView";
}


//! The MaterialEditor is the main class to access materials.
class ToolTipDataBase : public QObject
{
    Q_OBJECT
public:
    ToolTipDataBase(QObject *parent=0);
    virtual ~ToolTipDataBase();

    static QString getSampleViewToolTip(const QString &className, const QString &propertyName);

private:
    void initDataBase();
    QString getTag(const QString &contextName, const QString &className, const QString &propertyName);
    void addToolTip(const QString &contextName, const QString &className, const QString &propertyName, const QString &tooltip);
    QString this_getToolTip(const QString &contextName, const QString &className, const QString &propertyName);

    static ToolTipDataBase *m_instance;

    static QMap<QString, QString > m_tagToToolTip;
};



#endif


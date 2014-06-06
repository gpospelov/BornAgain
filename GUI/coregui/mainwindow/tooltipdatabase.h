#ifndef TOOLTIP_DATABASE
#define TOOLTIP_DATABASE


#include <QObject>
#include <QMap>

namespace ToolTipsXML {
const QString modelTag = "ToolTipsData";
const QString categoryTag = "category";
const QString classTag = "class";
const QString propertyTag = "property";
const QString tooltipTag = "tooltip";
const QString whatsthisTag = "whatsthis";
const QString nameAttribute = "name";
}


//! The MaterialEditor is the main class to access materials.
class ToolTipDataBase : public QObject
{
    Q_OBJECT
public:
    ToolTipDataBase(QObject *parent=0);
    virtual ~ToolTipDataBase();

private:
    void initDataBase();
    void addToolTip(const QString &category, const QString &item, const QString &text);

    static ToolTipDataBase *m_instance;

    static QMap<QString, QString > m_nameToTip;
};



#endif


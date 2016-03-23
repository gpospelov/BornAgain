// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/tooltipdatabase.h
//! @brief     Defines class ToolTipDataBase
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TOOLTIP_DATABASE
#define TOOLTIP_DATABASE

#include "WinDllMacros.h"
#include <QObject>
#include <QMap>

namespace ToolTipsXML {
const QString modelTag = "ToolTipsData";
const QString contextTag = "context";
const QString categoryTag = "category";
const QString propertyTag = "property";
const QString tooltipTag = "tooltip";
const QString whatsthisTag = "whatsthis";
const QString nameAttribute = "name";
const QString sampleViewContext = "SampleView";
const QString titleProperty = "Title";
const QString descriptionProperty = "Description";
}


//! The MaterialEditor is the main class to access materials.
class BA_CORE_API_ ToolTipDataBase : public QObject
{
    Q_OBJECT
public:
    ToolTipDataBase(QObject *parent=0);
    virtual ~ToolTipDataBase();

    static QString getSampleViewToolTip(const QString &className, const QString &propertyName);
    static QString getSampleViewWidgetboxToolTip(const QString &className);
    static QString getSampleViewDesignerToolTip(const QString &className);

private:
    void initDataBase();
    QString getTag(const QString &contextName, const QString &categoryName, const QString &propertyName);
    void addToolTip(const QString &contextName, const QString &categoryName, const QString &propertyName, const QString &tooltip);
    QString this_getToolTip(const QString &contextName, const QString &categoryName, const QString &propertyName);

    static ToolTipDataBase *m_instance;

    static QMap<QString, QString > m_tagToToolTip;
};



#endif


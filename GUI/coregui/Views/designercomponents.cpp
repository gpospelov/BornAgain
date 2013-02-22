#include "designercomponents.h"


#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerWidgetBoxInterface>
//#include <QDesignerWidgetBoxInterface>
//#include <QDesignerFormEditorInterface>


DesignerWidgetBoxInterface *DesignerComponents::createWidgetBox(QWidget *parent)
{
    return new DesignerWidgetBoxInterface(parent);
}

DesignerPropertyEditorInterface *DesignerComponents::createPropertyEditor(QWidget *parent)
{
    return new DesignerPropertyEditorInterface(parent);
}

DesignerSampleInspectorInterface *DesignerComponents::createSampleInspector(QWidget *parent)
{
    return new DesignerSampleInspectorInterface(parent);
}

DesignerSampleWorkspaceInterface *DesignerComponents::createSampleWorkspace(QWidget *parent)
{
    return new DesignerSampleWorkspaceInterface(parent);
}


//QDesignerWidgetBoxInterface *DesignerComponents::createDesignerWidgetBox(QDesignerFormEditorInterface *core, QWidget *parent)
//{
//    qdesigner_internal::WidgetBox *widgetBox = new qdesigner_internal::WidgetBox(core, parent);

//    const QDesignerLanguageExtension *lang = qt_extension<QDesignerLanguageExtension*>(core->extensionManager(), core);

//    do {
//        if (lang) {
//            const QString languageWidgetBox = lang->widgetBoxContents();
//            if (!languageWidgetBox.isEmpty()) {
//                widgetBox->loadContents(lang->widgetBoxContents());
//                break;
//            }
//        }

//        widgetBox->setFileName(QStringLiteral(":/qt-project.org/widgetbox/widgetbox.xml"));
//        widgetBox->load();
//    } while (false);

//    const QString userWidgetBoxFile = widgetBoxFileName(QT_VERSION, lang);

//    widgetBox->setFileName(userWidgetBoxFile);
//    if (!QFileInfo(userWidgetBoxFile).exists()) {
//        // check previous version, that is, are we running the new version for the first time
//        // If so, try to copy the old widget box file
//        if (const int minv = qtMinorVersion(QT_VERSION)) {
//            int oldVersion = QT_VERSION;
//            setMinorVersion(minv - 1, &oldVersion);
//            const QString oldWidgetBoxFile = widgetBoxFileName(oldVersion, lang);
//            if (QFileInfo(oldWidgetBoxFile).exists())
//                QFile::copy(oldWidgetBoxFile, userWidgetBoxFile);
//        }
//    }
//    widgetBox->load();

//    return widgetBox;
//}



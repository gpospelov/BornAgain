#include "SampleWidgetBox.h"
#include "widgetbox.h"
#include "styledbar.h"
#include <QVBoxLayout>

#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif


SampleWidgetBox::SampleWidgetBox(SampleDesignerInterface *core, QWidget *parent)
    : QWidget(parent)
    , m_core(core)
    , m_widgetBox(0)
{
    //Manhattan::StyledBar *bar = new Manhattan::StyledBar(this);

    m_widgetBox = new qdesigner_internal::WidgetBox(core, this);
    m_widgetBox->setFileName(QStringLiteral(":/widgetbox/widgetbox.xml"));
    m_widgetBox->load();
    m_widgetBox->setWindowTitle(QLatin1String("Widget Box"));
    m_widgetBox->setObjectName(QLatin1String("WidgetBox"));


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
//    layout->addWidget(bar);
    layout->addWidget(m_widgetBox);
    setLayout(layout);

}

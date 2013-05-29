#include "SampleTreeInspector.h"
#include "styledbar.h"
#include <QVBoxLayout>

SampleTreeInspector::SampleTreeInspector(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Object Inspector"));
    setObjectName(QLatin1String("ObjectInspector"));

//    Manhattan::StyledBar *bar = new Manhattan::StyledBar(this);

//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->setMargin(0);
//    layout->setSpacing(0);
//    layout->addWidget(bar);
//    layout->addWidget(new QWidget(this));
//    setLayout(layout);

    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}


#include "InstrumentSelectorWidget.h"
#include <QListView>
#include <QVBoxLayout>
#include <QPushButton>

InstrumentSelectorWidget::InstrumentSelectorWidget(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
{
    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);


    QVBoxLayout *mainLayout = new QVBoxLayout;

    QPushButton *addInstrumentButton = new QPushButton();

    m_listView = new QListView(this);

    mainLayout->addSpacing(5);
    mainLayout->addWidget(addInstrumentButton);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_listView);
    mainLayout->addStretch();

    setLayout(mainLayout);


}



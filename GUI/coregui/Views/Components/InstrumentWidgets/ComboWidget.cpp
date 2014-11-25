#include "ComboWidget.h"
#include "GUIHelpers.h"
#include <QBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QDebug>

ComboWidget::ComboWidget(QString title, QGridLayout *layout, QWidget *parent)
    : QWidget(parent)

{

    QGroupBox *groupBox = new QGroupBox("GroupBox");


    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);
}

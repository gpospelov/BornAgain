#include "TestView.h"

TestView::TestView(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


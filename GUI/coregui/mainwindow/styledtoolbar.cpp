#include "styledtoolbar.h"
#include <QIcon>
#include <QStyle>


StyledToolBar::StyledToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);
    setMinimumSize(128, 25);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setContentsMargins(0,0,0,0);

}

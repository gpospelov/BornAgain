// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolBar.cpp
//! @brief     Implements class MaskEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorToolBar.h"
#include <QStyle>
#include <QVariant>
#include <QToolButton>
#include <QLabel>

MaskEditorToolBar::MaskEditorToolBar(QWidget *parent)
    : QToolBar(parent)
{
    // const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    // setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setIconSize(QSize(32, 32));

    setProperty("_q_custom_style_disabled", QVariant(true));

    add_selection_group();
}


void MaskEditorToolBar::add_selection_group()
{
    QToolButton *selectionButton = new QToolButton(this);
    selectionButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_arrow.svg"));
    selectionButton->setToolTip("Select/modify mode");
    addWidget(selectionButton);

    QToolButton *panButton = new QToolButton(this);
    panButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_hand.svg"));
    panButton->setToolTip("Pan/zoom mode");
    addWidget(panButton);

    QToolButton *refreshButton = new QToolButton(this);
    refreshButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_refresh.svg"));
    refreshButton->setToolTip("Pan/zoom mode");
    addWidget(refreshButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    QToolButton *maskTrueButton = new QToolButton(this);
    maskTrueButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_masktrue.svg"));
    maskTrueButton->setToolTip("Pan/zoom mode");
    addWidget(maskTrueButton);

    QToolButton *maskFalseButton = new QToolButton(this);
    maskFalseButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_maskfalse.svg"));
    maskFalseButton->setToolTip("Pan/zoom mode");
    addWidget(maskFalseButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    QToolButton *rectangleButton = new QToolButton(this);
    rectangleButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_rectangle.svg"));
    rectangleButton->setToolTip("Pan/zoom mode");
    addWidget(rectangleButton);

    QToolButton *polygonButton = new QToolButton(this);
    polygonButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_polygon.svg"));
    polygonButton->setToolTip("Pan/zoom mode");
    addWidget(polygonButton);

    QToolButton *verticalLineButton = new QToolButton(this);
    verticalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_horizontalline.svg"));
    verticalLineButton->setToolTip("Pan/zoom mode");
    addWidget(verticalLineButton);

    QToolButton *horizontalLineButton = new QToolButton(this);
    horizontalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_verticalline.svg"));
    horizontalLineButton->setToolTip("Pan/zoom mode");
    addWidget(horizontalLineButton);


    QToolButton *ellipseButton = new QToolButton(this);
    ellipseButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_ellipse.svg"));
    ellipseButton->setToolTip("Pan/zoom mode");
    addWidget(ellipseButton);

    QToolButton *maskAllButton = new QToolButton(this);
    maskAllButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_maskall.svg"));
    maskAllButton->setToolTip("Pan/zoom mode");
    addWidget(maskAllButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    QToolButton *bringToFrontButton = new QToolButton(this);
    bringToFrontButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_bringtofront.svg"));
    bringToFrontButton->setToolTip("Pan/zoom mode");
    addWidget(bringToFrontButton);

    QToolButton *sendToBackButton = new QToolButton(this);
    sendToBackButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_sendtoback.svg"));
    sendToBackButton->setToolTip("Pan/zoom mode");
    addWidget(sendToBackButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    QToolButton *propertyPanelButton = new QToolButton(this);
    propertyPanelButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_toolpanel.svg"));
    propertyPanelButton->setToolTip("Pan/zoom mode");
    propertyPanelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addWidget(propertyPanelButton);


}


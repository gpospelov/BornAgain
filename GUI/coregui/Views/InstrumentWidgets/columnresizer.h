/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: LGPL v2.1 or later (see COPYING)
 */
#ifndef COLUMNRESIZER_H
#define COLUMNRESIZER_H

#include <QFormLayout>

#include <QtCore/QObject>
#include <QtCore/QList>

class QEvent;
class QGridLayout;
class QLayout;
class QWidget;

class ColumnResizerPrivate;

//! The ColumnResizer class provides vertically aligned widgets from diferent layouts
//! http://agateau.com/2011/clean-up-your-layouts-with-columnresizer/
//! https://github.com/agateau/columnresizer
class ColumnResizer : public QObject
{
    Q_OBJECT
public:
    ColumnResizer(QObject* parent = 0);
    virtual ~ColumnResizer();

    void addWidget(QWidget* widget);
    void addWidgetsFromLayout(QLayout*, int column);
    void addWidgetsFromGridLayout(QGridLayout*, int column);
    void addWidgetsFromFormLayout(QFormLayout*, QFormLayout::ItemRole role);

    void dropWidgetsFromGridLayout(QGridLayout *layout);

private slots:
    void updateWidth();

protected:
    void removeWidget(QWidget* widget);
    virtual bool eventFilter(QObject*, QEvent* event);

private:
    ColumnResizerPrivate* const d;
};

#endif /* COLUMNRESIZER_H */

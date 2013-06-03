#ifndef MATERIALBROWSER_H
#define MATERIALBROWSER_H

#include <QObject>

//! main class to access materials
class MaterialBrowser : public QObject
{
    Q_OBJECT
public:
    MaterialBrowser(QWidget *parent = 0);
    virtual ~MaterialBrowser();

    static MaterialBrowser *instance();

private:
    static MaterialBrowser *m_instance;
};

#endif // MATERIALBROWSER_H

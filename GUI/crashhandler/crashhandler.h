#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#include <QObject>

class CrashHandler : public QObject
{
    Q_OBJECT
public:
    explicit CrashHandler(QObject *parent = 0);
    virtual ~CrashHandler();
};

#endif // CRASHHANDLER_H

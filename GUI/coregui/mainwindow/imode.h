#ifndef IMODE_H
#define IMODE_H

#include <QObject>
#include <QIcon>

class IMode : public QObject
{
    Q_OBJECT

public:
    IMode(QObject *parent = 0);

    QString displayName() const { return m_displayName; }
    QIcon icon() const { return m_icon; }

    int id() const { return m_id; }
    bool isEnabled() const;

    void setEnabled(bool enabled);
    void setDisplayName(const QString &displayName) { m_displayName = displayName; }
    void setIcon(const QIcon &icon) { m_icon = icon; }
    void setId(int id) { m_id = id; }

signals:
    void enabledStateChanged(bool enabled);

private:
    QString m_displayName;
    QIcon m_icon;
    int m_id;
    bool m_isEnabled;
};


#endif // IMODE_H

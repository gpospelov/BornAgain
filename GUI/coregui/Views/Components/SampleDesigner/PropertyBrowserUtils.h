#ifndef PROPERTYBROWSERUTILS_H
#define PROPERTYBROWSERUTILS_H

#include <QLineEdit>
#include <QLabel>
#include "MaterialBrowser.h"

#include <QIcon>

//!
class MaterialPropertyEdit : public QWidget
{
    Q_OBJECT
public:
    MaterialPropertyEdit(QWidget *parent = 0);
//    void setFilePath(const QString &filePath) { if (theLineEdit->text() != filePath) theLineEdit->setText(filePath); }
//    QString filePath() const { return theLineEdit->text(); }
//    void setFilter(const QString &filter) { theFilter = filter; }
//    QString filter() const { return theFilter; }

    void setMaterialProperty(const MaterialProperty &materialProperty) { m_materialProperty = materialProperty; }
    MaterialProperty getMaterialProperty() const {return m_materialProperty; }
signals:
//    void filePathChanged(const QString &filePath);
    void materialPropertyChanged(const MaterialProperty &material);
protected:
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
private slots:
    void buttonClicked();
private:
    QLineEdit *theLineEdit;
    QString theFilter;
    QLabel *m_label;
    MaterialProperty m_materialProperty;
};




#endif // PROPERTYBROWSERUTILS_H

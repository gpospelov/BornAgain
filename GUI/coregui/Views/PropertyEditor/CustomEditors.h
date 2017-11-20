// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/CustomEditors.h
//! @brief     Defines CustomEditors classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef CUSTOMEDITORS_H
#define CUSTOMEDITORS_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QVariant>

class QLabel;
class LostFocusFilter;
class QComboBox;

//! Base class for all custom variants editors.

class BA_CORE_API_ CustomEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CustomEditor(QWidget* parent = nullptr) : QWidget(parent) {}

    QVariant editorData() { return m_data; }

public slots:
    virtual void setData(const QVariant& data);

signals:
    //! Signal emit then user changed the data through the editor
    void dataChanged(const QVariant& data);

protected:
    void setDataIntern(const QVariant& data);
    QVariant m_data;
};

//! Editor for MaterialProperty variant.

class BA_CORE_API_ MaterialPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit MaterialPropertyEditor(QWidget* parent = nullptr);

public slots:
    void setData(const QVariant& data);

private slots:
    void buttonClicked();

private:
    QLabel* m_textLabel;
    QLabel* m_pixmapLabel;
    LostFocusFilter* m_focusFilter;
};

//! Editor for GroupProperty variant.

class BA_CORE_API_ GroupPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit GroupPropertyEditor(QWidget *parent = nullptr);

public slots:
    void setData(const QVariant& data);

private slots:
    void onIndexChanged(int index);

private:
    void setConnected(bool isConnected);

    QComboBox* m_box;
};

//! Editor for ComboProperty variant.

class BA_CORE_API_ ComboPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit ComboPropertyEditor(QWidget *parent = nullptr);

public slots:
    void setData(const QVariant& data);

private slots:
    void onIndexChanged(int index);

private:
    void setConnected(bool isConnected);

    QComboBox* m_box;
};

#endif  //  CUSTOMEDITORS_H

//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/AxesItems.h
//! @brief     Defines various axis items
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_AXESITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_AXESITEMS_H

#include "GUI/coregui/Models/SessionItem.h"
#include <memory>

class IAxis;

class BA_CORE_API_ BasicAxisItem : public SessionItem {
public:
    static const QString P_IS_VISIBLE;
    static const QString P_NBINS;
    static const QString P_MIN_DEG;
    static const QString P_MAX_DEG;
    static const QString P_TITLE;
    static const QString P_TITLE_IS_VISIBLE;

    explicit BasicAxisItem(const QString& type = "BasicAxis");
    virtual ~BasicAxisItem();

    int binCount() const;
    void setBinCount(int value);

    double lowerBound() const;
    void setLowerBound(double value);

    double upperBound() const;
    void setUpperBound(double value);

    QString title() const;
    void setTitle(const QString& title);

    virtual std::unique_ptr<IAxis> createAxis(double scale) const;

protected:
    void register_basic_properties();
};

class BA_CORE_API_ AmplitudeAxisItem : public BasicAxisItem {
public:
    static const QString P_IS_LOGSCALE;
    static const QString P_LOCK_MIN_MAX;
    AmplitudeAxisItem();

    bool isLogScale() const;
    void setLogScale(bool value);

private:
    void setMinMaxEditor(const QString& editorType);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_AXESITEMS_H

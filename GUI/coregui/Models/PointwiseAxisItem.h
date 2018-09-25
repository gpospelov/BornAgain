// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/PointwiseAxisItem.h
//! @brief     Defines pointwise axis item
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef POINTWISEAXISITEM_H
#define POINTWISEAXISITEM_H

#include "AxesItems.h"
#include "SaveLoadInterface.h"

class IAxis;
class PointwiseAxis;

//! Item for non-uniform axis with specified coordinates.
class BA_CORE_API_ PointwiseAxisItem : public BasicAxisItem, public SaveLoadInterface
{
public:
    static const QString P_FILE_NAME;

    explicit PointwiseAxisItem();
    ~PointwiseAxisItem() override;

    bool containsNonXMLData() const override;
    QDateTime lastModified() const override;
    QString fileName() const override;

    void setAxis(const IAxis* axis);
    const IAxis* getAxis();
    std::unique_ptr<IAxis> createAxis(double scale) const override;

private:
    bool load(const QString& projectDir) override;
    bool save(const QString& projectDir) override;
    void setLastModified(const QDateTime& dtime);

    std::unique_ptr<PointwiseAxis> m_axis;
    QDateTime m_last_modified;
};

#endif // POINTWISEAXISITEM_H

#ifndef TESTGUICOREOBJECTCORRESPONDENCE_H
#define TESTGUICOREOBJECTCORRESPONDENCE_H

#include "GUICoreObjectCorrespondence.h"
#include "FormFactors.h"
#include "FormFactorItems.h"

#include <QtTest>

class TestGUICoreObjectCorrespondence : public QObject {
    Q_OBJECT

private slots:
    void test_Cylinder();
};

inline void TestGUICoreObjectCorrespondence::test_Cylinder()
{
    CylinderItem gui_cylinder;
    FormFactorCylinder core_cylinder(1.0, 3.0);
    GUICoreObjectCorrespondence(gui_cylinder, core_cylinder);
}

#endif // TESTGUICOREOBJECTCORRESPONDENCE_H

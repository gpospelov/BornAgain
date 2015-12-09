#ifndef TESTGUICOREOBJECTCORRESPONDENCE_H
#define TESTGUICOREOBJECTCORRESPONDENCE_H

#include <QtTest>

class TestGUICoreObjectCorrespondence : public QObject {
    Q_OBJECT

private slots:
    void test_AnisoPyramid();
    void test_Box();
    void test_Cone();
    void test_Cone6();
    void test_Cuboctahedron();
    void test_Cylinder();
    void test_EllipsoidalCylinder();
    void test_FullSphere();
    void test_FullSpheroid();
    void test_HemiEllipsoid();
    void test_Prism3();
    void test_Prism6();
    void test_Pyramid();
    void test_Ripple1();
    void test_Ripple2();
    void test_Tetrahedron();
    void test_TruncatedCube();
    void test_TruncatedSphere();
    void test_TruncatedSpheroid();
};

#endif // TESTGUICOREOBJECTCORRESPONDENCE_H

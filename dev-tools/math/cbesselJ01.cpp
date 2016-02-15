//  original source of complex Bessel code, modified to get it running,
//  plus a short main routine for interactive use.
//  It's almost C code, just one detail makes it C++.
//  JWu jan16

//  cbessjy.cpp -- complex Bessel functions.
//  Algorithms and coefficient values from "Computation of Special
//  Functions", Zhang and Jin, John Wiley and Sons, 1996.
//
//  (C) 2003, C. Bond. All rights reserved.
//
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
static double eps = 2.2e-16;
static double complex cii = I;
static double complex cone = 1;
static double complex czero = 0;

int cbessj01(double complex z,double complex &cj0,double complex &cj1)
{
    double complex z1,z2,cr,cp,cs,cp0,cq0,cp1,cq1,ct1,ct2,cu;
    double a0,w0,w1;
    int k,kz;

    static double a[] = {
        -7.03125e-2,
         0.112152099609375,
        -0.5725014209747314,
         6.074042001273483,
        -1.100171402692467e2,
         3.038090510922384e3,
        -1.188384262567832e5,
         6.252951493434797e6,
        -4.259392165047669e8,
         3.646840080706556e10,
        -3.833534661393944e12,
         4.854014686852901e14,
        -7.286857349377656e16,
         1.279721941975975e19};
    static double b[] = {
         7.32421875e-2,
        -0.2271080017089844,
         1.727727502584457,
        -2.438052969955606e1,
         5.513358961220206e2,
        -1.825775547429318e4,
         8.328593040162893e5,
        -5.006958953198893e7,
         3.836255180230433e9,
        -3.649010818849833e11,
         4.218971570284096e13,
        -5.827244631566907e15,
         9.476288099260110e17,
        -1.792162323051699e20};
    static double a1[] = {
         0.1171875,
        -0.1441955566406250,
         0.6765925884246826,
        -6.883914268109947,
         1.215978918765359e2,
        -3.302272294480852e3,
         1.276412726461746e5,
        -6.656367718817688e6,
         4.502786003050393e8,
        -3.833857520742790e10,
         4.011838599133198e12,
        -5.060568503314727e14,
         7.572616461117958e16,
        -1.326257285320556e19};
    static double b1[] = {
        -0.1025390625,
         0.2775764465332031,
        -1.993531733751297,
         2.724882731126854e1,
        -6.038440767050702e2,
         1.971837591223663e4,
        -8.902978767070678e5,
         5.310411010968522e7,
        -4.043620325107754e9,
         3.827011346598605e11,
        -4.406481417852278e13,
         6.065091351222699e15,
        -9.833883876590679e17,
         1.855045211579828e20};

    a0 = cabs(z);
    z2 = z*z;
    z1 = z;
    if (a0 == 0.0) {
        cj0 = cone;
        cj1 = czero;
        return 0;
    }
    if (creal(z) < 0.0) z1 = -z;
    if (a0 <= 12.0) {
        cj0 = cone;
        cr = cone;
        for (k=1;k<=40;k++) {
            cr *= -0.25*z2/(double)(k*k);
            cj0 += cr;
            if (cabs(cr) < cabs(cj0)*eps) break;
        }
        cj1 = cone;
        cr = cone;
        for (k=1;k<=40;k++) {
            cr *= -0.25*z2/(k*(k+1.0));
            cj1 += cr;
            if (cabs(cr) < cabs(cj1)*eps) break;
        }
        cj1 *= 0.5*z1;
    }
    else {
        if (a0 >= 50.0) kz = 8;         // can be changed to 10
        else if (a0 >= 35.0) kz = 10;   //   "      "     "  12
        else kz = 12;                   //   "      "     "  14
        ct1 = z1 - M_PI_4;
        cp0 = cone;
        for (k=0;k<kz;k++) {
            cp0 += a[k]*cpow(z1,-2.0*k-2.0);
        }
        cq0 = -0.125/z1;
        for (k=0;k<kz;k++) {
            cq0 += b[k]*cpow(z1,-2.0*k-3.0);
        }
        cu = csqrt(M_2_PI/z1);
        cj0 = cu*(cp0*ccos(ct1)-cq0*csin(ct1));
        ct2 = z1 - 0.75*M_PI;
        cp1 = cone;
        for (k=0;k<kz;k++) {
            cp1 += a1[k]*cpow(z1,-2.0*k-2.0);
        }
        cq1 = 0.375/z1;
        for (k=0;k<kz;k++) {
            cq1 += b1[k]*cpow(z1,-2.0*k-3.0);
        }
        cj1 = cu*(cp1*ccos(ct2)-cq1*csin(ct2));
    }
    if (creal(z) < 0.0) {
        cj1 = -cj1;
    }
    return 0;
}


int main (int argc, char *argv[]) {
    if( argc!=4 ) {
        printf("Usage: cbessy <nu> <Re z> <Im z>\n");
        return -1;
    }
    int nu = atoi( argv[1] );
    double zr = atof( argv[2] );
    double zi = atof( argv[3] );
    double complex z = zr + I*zi;
    double complex cj0;
    double complex cj1;
    cbessj01(z, cj0, cj1);
    double complex res;
    if( nu==0 )
        res = cj0;
    else if( nu==1 )
        res = cj1;
    else {
        printf( "Only nu=0,1 are supported\n" );
        return -1;
    }
    printf( "    res = MathFunctions::crbond_bessel_J1(complex_t(%g,%g));\n"
            "    EXPECT_NEAR( res.real(), %24.17g, eps*std::abs(res) );\n"
            "    EXPECT_NEAR( res.imag(), %24.17g, eps*std::abs(res) );\n",
            zr, zi, creal(res), cimag(res) );
    return 0;
}

#include <complex>
using std::complex;
#include <iostream>
#include <cstdio>

typedef long double quad;

complex<double> eval( double a, double b, int mode, int& info )
{
    static double eps = 1e-8;
    quad aa = a;
    quad bb = b;
    complex<quad> ci( 0.L, 1.L );
    complex<quad> res;
    if( std::abs(b)<eps ) {
        if( std::abs(a)<eps ) {
            info = 5;
            res = 1;
        } else {
            info = 6;
            res = 2.L*(-1.L + (1.L-ci*aa)*std::exp(ci*aa))/aa/aa;
        }
    } else {
        if( std::abs(a-b)<eps ) {
            info = 3;
            res = ((1.L-std::exp(ci*(aa+bb)))/(aa+bb) + ci ) / bb;
        } else if( std::abs(a+b)<eps ) {
            info = 4;
            res = ( -ci - (1.L-std::exp(ci*(aa-bb)))/(aa-bb) ) / bb;
        } else {
            if ( mode==1 ) {
                info = 1;
                res = ( (1.L-std::exp(ci*(aa+bb)))/(aa+bb)
                      - (1.L-std::exp(ci*(aa-bb)))/(aa-bb) ) / bb;
            } else if ( mode==2 ) {
                info = 2;
                res = (-1.L + ( std::cos(bb) - ci*aa*std::sin(bb)/bb)*
                       std::exp(ci*aa)) * 2.L / (aa*aa-bb*bb);
            } else
                throw "unexpected mode";
        }
    }
    return (complex<double>)(res);
}


int line_test( double a_step, double b_step, double a_perp, double b_perp )
{
    static int Nj = 35;
    static int Ni = 15;
    int count = 0;
    for( int j=0; j<Nj; ++j ) {
        double pos = 1e-20*pow(10.,j*21./Nj);
        double a = a_step * pos;
        double b = b_step * pos;
        for( int i=0; i<Ni; ++i ){
            double del = 1e-20*pow(10.,i*21./Ni);
            double aa = a + a_perp * del;
            double bb = b + b_perp * del;
            int i1, i2;
            complex<double> e1 = eval(aa,bb,1,i1);
            complex<double> e2 = eval(aa,bb,2,i2);
            double dd = std::abs(e1 - e2) / ( std::abs(e1) + std::abs(e2) ) * 2;
            if( std::abs(dd)>1e-8 ) {
                ++count;
                printf( "%9.2g %9.2g %1i %11.4g %11.4g   %1i %11.4g  %11.4g   %11.4g\n",
                        aa, bb,
                        i1, 1-e1.real(), e1.imag(),
                        i2, 1-e2.real(), e2.imag(), dd );
            }
        }
    }
    printf( "#--> #problems = %i\n", count );
    return count;
}

int main (int argc, char *argv[])
{
    int totcount = 0;
    constexpr double r2 = sqrt(0.5);
    std::cout << "## line b=0 ##\n";
    totcount += line_test( 1., 0., 0., 1. );
    std::cout << "## line a=b ##\n";
    totcount += line_test( r2, r2, r2, -r2 );
    std::cout << "## line a=-b ##\n";
    totcount += line_test( r2, -r2, r2, r2 );
    std::cout << "## line a=0 ##\n";
    totcount += line_test( 0., 1., 1., 0. );
    std::cout << "## oblique line ##\n";
    constexpr double r3 = sqrt(1/3.);
    constexpr double c3 = sqrt(1-r3*r3);
    totcount += line_test( r3, c3, c3, -r3);
    printf( "#==> #Problems = %i\n", totcount );
}

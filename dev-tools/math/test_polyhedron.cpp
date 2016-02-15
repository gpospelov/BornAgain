// internal test program
// JWu 2016

#include <complex>
using std::complex;
#include <iostream>
#include <cstdio>
#include <vector>
using std::vector;

typedef complex<double> cmplx;
class q_type {
public:
    q_type( double _abs, cmplx _ux, cmplx _uy, cmplx _uz ) : abs(_abs), uvec({_ux,_uy,_uz}) {};
    double abs;
    cmplx uvec[3];
};

cmplx face( const vector<double*>& VV )
{
//    for( auto V: VV )
//        for( int i=0; i<3; ++i )
//            std::cout << "corner" << i << ": " << V[i] << "\n";
    // compute n_k

    return cmplx(1.,0);
}

cmplx ff( const q_type q )
{
    double V[4][3] = {
        { 0., 0., 0. },
        { 1., 0., 0. },
        { 0., 1., 0. },
        { 0., 0., 1. } };
    cmplx res = 0;
    res += face( { V[0], V[1], V[2] } );
    res += face( { V[0], V[3], V[1] } );
    res += face( { V[0], V[2], V[3] } );
    res += face( { V[1], V[3], V[2] } );
    return res;
}

int main (int argc, char *argv[])
{
    q_type q( 0., 1., 0., 0. );
    std::cout << "volume: " << ff(q) << "\n";
}

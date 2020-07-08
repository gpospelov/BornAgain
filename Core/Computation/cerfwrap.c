#include "cerfwrap.h"
#include <cerf.h>

#  if !defined(CMPLX) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7\
)) && !(defined(__ICC) || defined(__INTEL_COMPILER))
#    define CMPLX(a,b) __builtin_complex((double) (a), (double) (b))
#  endif

#  ifdef CMPLX // C11
#    define C(a,b) CMPLX(a,b)
#  else
#    define C(a,b) ((a) + I*(b))
#  endif

void wrap_cerfcx(double zx, double zy, double* vx, double* vy)
{
    const double _Complex arg = C(zx,zy);
    const double _Complex val = cerfcx(arg);
    *vx = creal(val);
    *vy = cimag(val);
}

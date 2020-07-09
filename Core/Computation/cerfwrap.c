#include "cerfwrap.h"
#include <cerf.h>
#include <string.h>

void wrap_cerfcx(void* z, void* ret)
{
    double _Complex val = cerfcx(*(double _Complex*)(z));
    memcpy(ret, &val, 2*sizeof(double));
}

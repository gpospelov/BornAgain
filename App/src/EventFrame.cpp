#include "EventFrame.h"

EventFrame::EventFrame()
{
    clear();
}

void EventFrame::clear()
{
    nframe = 0;
    alpha_i = 0;
    phi_i = 0;

    nphi_f = 0;
    phi_f_min = 0;
    phi_f_max = 0;

    nalpha_f = 0;
    alpha_f_min = 0;
    alpha_f_max = 0;

    malpha = 0;
    mphi = 0;
    npR = 0;

    valpha_f.clear();
    vphi_f.clear();
    vi.clear();
}

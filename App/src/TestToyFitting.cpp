#include "TestToyFitting.h"
#include "TCanvas.h"
#include "TF2.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
#include "TList.h"


TestToyFitting::TestToyFitting()
    : IFunctionalTest("TestToyFitting")
    , m_xmin(-10.0)
    , m_xmax(10.0)
    , m_ymin(-10.0)
    , m_ymax(10.0)
    , m_nbinx(50)
    , m_nbiny(50)
{

}


void TestToyFitting::execute()
{
    gStyle->SetPalette(1);

    SincXSincY *fobj_sinc = new SincXSincY();
    SincXSincYNoisy *fobj_sinc_noisy = new SincXSincYNoisy();

    TF2 *func_sim = new TF2("funcexp", fobj_sinc, m_xmin, m_xmax, m_ymin, m_ymax, 4, "SincXSincY");
    TF2 *func_exp = new TF2("funcsim", fobj_sinc_noisy, m_xmin, m_xmax, m_ymin, m_ymax, 4, "SincXSincYNoisy");

    TH2D *h2_exp = new TH2D("h2_exp","h2_exp", m_nbinx, m_xmin, m_xmax, m_nbiny, m_ymin, m_ymax);
    func_exp->SetParameters(0.1, 1.0, 0.0, 0.0 );
    fill_histogram(h2_exp, func_exp);

    TH2D *h2_sim = new TH2D("h2_sim","h2_sim",m_nbinx, m_xmin, m_xmax, m_nbiny, m_ymin, m_ymax);
    func_sim->SetParameters(0.0, 1.0, 0.0, 0.0 );
    fill_histogram(h2_sim, func_sim);


    // experimental histogram
    TCanvas *c1 = new TCanvas("toyfit_expdata","toyfit_expdata", 1024, 768);
    c1->cd();
    gPad->SetBottomMargin(0.12);
    gPad->SetRightMargin(0.15);

    beautify_histogram(h2_exp);
    h2_exp->SetTitle("Experimental data");
    h2_exp->SetMinimum(-0.15);
    h2_exp->SetMaximum(1.2);

    h2_exp->Draw("surf3 z");
    beautify_palette(h2_exp);
    c1->SaveAs("toyfit_expdata.eps");

    // model histogram
    TCanvas *c2 = new TCanvas("toyfit_simdata","toyfit_simdata", 1024, 768);
    c2->cd();
    gPad->SetBottomMargin(0.12);
    gPad->SetRightMargin(0.15);

    beautify_histogram(h2_sim);
    h2_sim->SetTitle("Model");
    h2_sim->Draw("surf3 z");
    h2_sim->SetMinimum(-0.15);
    h2_sim->SetMaximum(1.2);
    beautify_palette(h2_sim);
    c2->SaveAs("toyfit_simdata.eps");

    // chi2_p23
    func_exp->SetParameters(0.5, 1.0, 0.0, 0.0 );
    func_sim->SetParameters(0.0, 1.0, 0.0, 0.0 );
    TH2D *h2_p23 = new TH2D("h2_p23","h2_p23", 50, -10.0, 10.0, 50, -10.0, 10.0);
    fill_chi23(h2_p23, func_exp, func_sim);

    TCanvas *c3 = new TCanvas("toyfit_chi2_p23", "toyfit_chi2_p23", 1024, 768);
    c3->cd();
    gPad->SetLeftMargin(0.12);
    gPad->SetTopMargin(0.05);

    beautify_histogram(h2_p23);
    h2_p23->SetTitle("");
    h2_p23->Draw("surf1");
    h2_p23->GetZaxis()->SetTitle("#chi^{2}");
    h2_p23->GetZaxis()->SetTitleOffset(1.2);
    h2_p23->GetXaxis()->SetTitle("p2");
    h2_p23->GetYaxis()->SetTitle("p3");
    //beautify_palette(h2_sim);
    c3->SaveAs("toyfit_chi2_p23.eps");

    // chi2_p12
    func_exp->SetParameters(0.5, 1.0, 0.0, 0.0 );
    func_sim->SetParameters(0.0, 1.0, 0.0, 0.0 );
    TH2D *h2_p12 = new TH2D("h2_p12","h2_p12", 50, 0.0, 2., 50, -10.0, 10.0);
    fill_chi12(h2_p12, func_exp, func_sim);

    TCanvas *c4 = new TCanvas("toyfit_chi2_p12", "toyfit_chi2_p12", 1024, 768);
    c4->cd();
    gPad->SetLeftMargin(0.12);
    gPad->SetTopMargin(0.05);

    beautify_histogram(h2_p12);
    h2_p12->SetTitle("");
    h2_p12->Draw("surf1");
    h2_p12->GetZaxis()->SetTitle("#chi^{2}");
    h2_p12->GetZaxis()->SetTitleOffset(1.3);
    h2_p12->GetXaxis()->SetTitle("p1");
    h2_p12->GetYaxis()->SetTitle("p2");
    c4->SaveAs("toyfit_chi2_p12.eps");


}



void TestToyFitting::fill_chi12(TH2D *hist, TF2 *func_exp, TF2 *func_sim)
{
    TH2D h2_exp("h2_exp_tmp","h2_exp_tmp", m_nbinx, m_xmin, m_xmax, m_nbiny, m_ymin, m_ymax);
    fill_histogram(&h2_exp, func_exp);

    for(int ix = 1; ix<=hist->GetNbinsX(); ix++) {
        double p1 = hist->GetXaxis()->GetBinCenter(ix);
        func_sim->SetParameter(1, p1);
        for(int iy = 1; iy<=hist->GetNbinsY(); iy++) {

            double p2 = hist->GetYaxis()->GetBinCenter(iy);

            func_sim->SetParameter(2, p2);

            TH2D h2_sim("h2_sim_tmp","h2_sim_tmp", m_nbinx, m_xmin, m_xmax, m_nbiny, m_ymin, m_ymax);
            fill_histogram(&h2_sim, func_sim);

            double value = get_chi2(&h2_exp, &h2_sim);
            std::cout << "ix " << ix << " iy:" << iy << " value:" << value << std::endl;

            hist->SetBinContent(hist->GetBin(ix,iy), value);

        }
    }
}


void TestToyFitting::fill_chi23(TH2D *hist, TF2 *func_exp, TF2 *func_sim)
{
    TH2D h2_exp("h2_exp_tmp","h2_exp_tmp", m_nbinx, m_xmin, m_xmax, m_nbiny, m_ymin, m_ymax);
    fill_histogram(&h2_exp, func_exp);

    for(int ix = 1; ix<=hist->GetNbinsX(); ix++) {
        double p2 = hist->GetXaxis()->GetBinCenter(ix);
        func_sim->SetParameter(2, p2);
        for(int iy = 1; iy<=hist->GetNbinsY(); iy++) {

            double p3 = hist->GetYaxis()->GetBinCenter(iy);

            func_sim->SetParameter(3, p3);

            TH2D h2_sim("h2_sim_tmp","h2_sim_tmp", m_nbinx, m_xmin, m_xmax, m_nbiny, m_ymin, m_ymax);
            fill_histogram(&h2_sim, func_sim);

            double value = get_chi2(&h2_exp, &h2_sim);
            std::cout << "ix " << ix << " iy:" << iy << " value:" << value << std::endl;

            hist->SetBinContent(hist->GetBin(ix,iy), value);

        }
    }
}


double TestToyFitting::get_chi2(TH2D *hist_exp, TH2D *hist_sim)
{
    double chi2(0);
    int ntot(0);
    for(int ix = 1; ix<=hist_exp->GetNbinsX(); ix++) {
        for(int iy = 1; iy<=hist_exp->GetNbinsY(); iy++) {
            double value_exp = hist_exp->GetBinContent(hist_exp->GetBin(ix,iy));
            double value_sim = hist_sim->GetBinContent(hist_sim->GetBin(ix,iy));
            chi2 += (value_exp-value_sim)*(value_exp-value_sim)/(0.01*0.01);
            ntot++;
        }
    }
    chi2 /= double(ntot);
    std::cout << "chi2 " << chi2 << std::endl;

    return chi2;
}


void TestToyFitting::beautify_histogram(TH2D *hist)
{
    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetXaxis()->SetTitle("X");
    hist->GetXaxis()->SetTitleOffset(1.4);
    hist->GetXaxis()->SetLabelSize(0.035);

    hist->GetYaxis()->SetTitle("Y");
    hist->GetYaxis()->SetTitleOffset(1.4);
    hist->GetYaxis()->SetLabelSize(0.035);

    hist->GetZaxis()->SetTitle("I");
    //hist->GetZaxis()->SetTitleOffset(1.4);
}


void TestToyFitting::beautify_palette(TH2D *hist)
{
    gPad->Update();
    TPaletteAxis *palette = (TPaletteAxis*)hist->GetListOfFunctions()->FindObject("palette");
    palette->SetX1NDC(0.90);
    palette->SetX2NDC(0.94);
    palette->SetY1NDC(0.1);
    palette->SetY2NDC(0.9);
    gPad->Modified();
    gPad->Update();
}


void TestToyFitting::fill_histogram(TH2D *hist, TF2 *func)
{
    for(int ix = 1; ix<=hist->GetNbinsX(); ix++) {
        for(int iy = 1; iy<=hist->GetNbinsY(); iy++) {
            double x = hist->GetXaxis()->GetBinCenter(ix);
            double y = hist->GetYaxis()->GetBinCenter(iy);
            hist->SetBinContent(hist->GetBin(ix,iy), func->Eval(x, y));

        }
    }
}

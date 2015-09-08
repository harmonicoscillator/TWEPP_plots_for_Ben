#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLine.h>
#include <TROOT.h>
#include <TStyle.h>
#include "tdrstyle.C"
#include <TLatex.h>

const int NThresholds=10;//12;
const Double_t L1_THRESHOLD[NThresholds] = {0.,10.,20.,30.,40.,50.,100.,140.,160.,170.};//,180.,190.};
const Int_t COLORS[NThresholds] = {1, 1, kBlue,kRed,kOrange,kRed+2,1,6,kBlue,kRed};//,kOrange,kRed+2 };

void makePrettyTurnOn(){

  setTDRStyle();

  TFile *inFile = TFile::Open("Hydjet502MC_CentralityCalibration.root");
  TGraphAsymmErrors *asymm[NThresholds];//[2];
  TLine *line[NThresholds];
  for(int i = 1; i < NThresholds; i++)
  {
    asymm[i] = (TGraphAsymmErrors*)inFile->Get(Form("asymm_cen_%d_cen",(int)L1_THRESHOLD[i]));
    asymm[i]->SetMarkerColor(COLORS[i]);
    asymm[i]->SetLineColor(COLORS[i]);
    line[i]=new TLine(L1_THRESHOLD[i],0.,L1_THRESHOLD[i],1.);
    line[i]->SetLineWidth(2);
    line[i]->SetLineStyle(2);
    line[i]->SetLineColor(COLORS[i]);
  }

  const int nBins = 100;
  const double maxPt = 100;

  TH1D *hEmpty = new TH1D("hEmpty",";Offline centrality (%); Efficiency",nBins,0.,maxPt);

  TCanvas *c1 = new TCanvas("c1","c1",720,600);
  //c1->SetRightMargin(0.5);
  TPad *pad1 = new TPad("pad1","",0,0,1,1);
  TPad *pad2 = new TPad("pad2","",0,0,1,1);
  pad1->SetRightMargin(1.2/7.2);
  pad2->SetRightMargin(1.2/7.2);
  //pad2->SetFillStyle(4000);
  pad2->SetFillColorAlpha(kWhite,0);
  pad1->Draw();
  pad1->cd();
  hEmpty->SetMinimum(0);
  hEmpty->SetMaximum(1.15);

  hEmpty->Draw();
  pad1->Update();

  pad2->Draw();
  pad2->cd();
  TH1D *hEmpty2 = new TH1D("hEmpty2","",nBins,0.,2*maxPt);
  hEmpty2->SetMinimum(0);
  hEmpty2->SetMaximum(1.15);
  hEmpty2->GetXaxis()->SetLabelSize(0);
  hEmpty2->Draw("][sames");  

  TLatex *tex = new TLatex(5, 1.05 , "CMS Simulation Preliminary");
  tex->SetTextFont(42);
  tex->SetTextSize(0.05);
  tex->Draw();

  for(int i = 1; i < NThresholds; i++){
    asymm[i]->Draw("p");
  }

  TLegend *leg = new TLegend(0.848,0.330,0.995,0.75,"L1 Threshold");
  //TLegend *leg = new TLegend(0.3689777,0.305074,0.6927732,0.7257928);
  //leg->SetTextAlign(13);
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  //leg->AddEntry((TObject*)0, "L1 Centrality Threshold", "");
  //leg->AddEntry((TObject*)0, "Threshold", "");

  for(int i = 1; i < NThresholds; i++){
    leg->AddEntry(asymm[i],Form("%d%%",(int)L1_THRESHOLD[i]/2),"lp");
    line[i]->Draw();
  }

  // TLine *endLine=new TLine(200,0.,200,1.);
  // endLine->SetLineWidth(1);
  // endLine->SetLineStyle(1);
  // endLine->SetLineColor(kBlack);
  // endLine->Draw();

  leg->Draw();
  //pad1->cd();
  //hEmpty->Draw();

  c1->SaveAs("Plots/TurnOnCurveCentrality.pdf");
  c1->SaveAs("Plots/TurnOnCurveCentrality.gif");

}

int main()
{
  makePrettyTurnOn();
  return 0;
}

#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TFileCollection.h"
#include "TString.h"

int juntos2(){

    TH1D *MVA_BDT_rejBvsS__1 = new TH1D("MVA_BDT_rejBvsS__1","Background rejection vs signal efficiency",31,0.4,0.7);
   
   MVA_BDT_rejBvsS__1->SetBinContent(1,0.9984246);
   MVA_BDT_rejBvsS__1->SetBinContent(2,0.9983505);
   MVA_BDT_rejBvsS__1->SetBinContent(3,0.9982658);
   MVA_BDT_rejBvsS__1->SetBinContent(4,0.998145);
   MVA_BDT_rejBvsS__1->SetBinContent(5,0.9980064);
   MVA_BDT_rejBvsS__1->SetBinContent(6,0.9978091);
   MVA_BDT_rejBvsS__1->SetBinContent(7,0.9976331);
   MVA_BDT_rejBvsS__1->SetBinContent(8,0.9974754);
   MVA_BDT_rejBvsS__1->SetBinContent(9,0.9972173);
   MVA_BDT_rejBvsS__1->SetBinContent(10,0.9968354);
   MVA_BDT_rejBvsS__1->SetBinContent(11,0.996592);
   MVA_BDT_rejBvsS__1->SetBinContent(12,0.996335);
   MVA_BDT_rejBvsS__1->SetBinContent(13,0.9959834);
   MVA_BDT_rejBvsS__1->SetBinContent(14,0.9955602);
   MVA_BDT_rejBvsS__1->SetBinContent(15,0.995154);
   MVA_BDT_rejBvsS__1->SetBinContent(16,0.994811);
   MVA_BDT_rejBvsS__1->SetBinContent(17,0.9943921);
   MVA_BDT_rejBvsS__1->SetBinContent(18,0.9939873);
   MVA_BDT_rejBvsS__1->SetBinContent(19,0.993454);
   MVA_BDT_rejBvsS__1->SetBinContent(20,0.9930439);
   MVA_BDT_rejBvsS__1->SetBinContent(21,0.9923412);
   MVA_BDT_rejBvsS__1->SetBinContent(22,0.9918225);
   MVA_BDT_rejBvsS__1->SetBinContent(23,0.9909709);
   MVA_BDT_rejBvsS__1->SetBinContent(24,0.9901157);
   MVA_BDT_rejBvsS__1->SetBinContent(25,0.9893979);
   MVA_BDT_rejBvsS__1->SetBinContent(26,0.9885085);
   MVA_BDT_rejBvsS__1->SetBinContent(27,0.9878146);
   MVA_BDT_rejBvsS__1->SetBinContent(28,0.9863445);
   MVA_BDT_rejBvsS__1->SetBinContent(29,0.9850814);
   MVA_BDT_rejBvsS__1->SetBinContent(30,0.9842517);
   MVA_BDT_rejBvsS__1->SetBinContent(31,0.9828197);
   
   MVA_BDT_rejBvsS__1->SetEntries(31);MVA_BDT_rejBvsS__1->SetLineColor(1);MVA_BDT_rejBvsS__1->SetLineWidth(3);MVA_BDT_rejBvsS__1->GetXaxis()->SetTitle("Signal eff");MVA_BDT_rejBvsS__1->GetXaxis()->SetLabelFont(42);MVA_BDT_rejBvsS__1->GetXaxis()->SetTitleOffset(1);MVA_BDT_rejBvsS__1->GetXaxis()->SetTitleFont(42);MVA_BDT_rejBvsS__1->GetYaxis()->SetTitle("Backgr rejection (1-eff)");MVA_BDT_rejBvsS__1->GetYaxis()->SetLabelFont(42);MVA_BDT_rejBvsS__1->GetYaxis()->SetTitleFont(42);MVA_BDT_rejBvsS__1->GetZaxis()->SetLabelFont(42);MVA_BDT_rejBvsS__1->GetZaxis()->SetTitleOffset(1);MVA_BDT_rejBvsS__1->GetZaxis()->SetTitleFont(42);MVA_BDT_rejBvsS__1->Draw("C");
   
    TH1D *MVA_BDTB_rejBvsS__2 = new TH1D("MVA_BDTB_rejBvsS__2","MVA_BDTB",31,0.4,0.7);

   MVA_BDTB_rejBvsS__2->SetBinContent(1,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(2,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(3,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(4,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(5,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(6,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(7,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(8,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(9,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(10,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(11,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(12,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(13,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(14,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(15,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(16,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(17,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(18,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(19,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(20,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(21,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(22,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(23,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(24,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(25,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(26,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(27,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(28,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(29,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(30,0.9246422);
   MVA_BDTB_rejBvsS__2->SetBinContent(31,0.9246422);

   MVA_BDTB_rejBvsS__2->SetEntries(31);
   MVA_BDTB_rejBvsS__2->SetLineColor(2);
   MVA_BDTB_rejBvsS__2->SetLineWidth(3);
   MVA_BDTB_rejBvsS__2->GetXaxis()->SetTitle("Signal eff");
   MVA_BDTB_rejBvsS__2->GetXaxis()->SetLabelFont(42);
   MVA_BDTB_rejBvsS__2->GetXaxis()->SetTitleOffset(1);
   MVA_BDTB_rejBvsS__2->GetXaxis()->SetTitleFont(42);
   MVA_BDTB_rejBvsS__2->GetYaxis()->SetTitle("Backgr rejection (1-eff)");
   MVA_BDTB_rejBvsS__2->GetYaxis()->SetLabelFont(42);
   MVA_BDTB_rejBvsS__2->GetYaxis()->SetTitleFont(42);
   MVA_BDTB_rejBvsS__2->GetZaxis()->SetLabelFont(42);
   MVA_BDTB_rejBvsS__2->GetZaxis()->SetTitleOffset(1);
   MVA_BDTB_rejBvsS__2->GetZaxis()->SetTitleFont(42);
   MVA_BDTB_rejBvsS__2->Draw("sameC");
    
   TH1D *MVA_BDTD_rejBvsS__3 = new TH1D("MVA_BDTD_rejBvsS__3","MVA_BDTD",31,0.4,0.7);

   MVA_BDTD_rejBvsS__3->SetBinContent(1,0.9960838);
   MVA_BDTD_rejBvsS__3->SetBinContent(2,0.9956558);
   MVA_BDTD_rejBvsS__3->SetBinContent(3,0.9954019);
   MVA_BDTD_rejBvsS__3->SetBinContent(4,0.9951001);
   MVA_BDTD_rejBvsS__3->SetBinContent(5,0.994779);
   MVA_BDTD_rejBvsS__3->SetBinContent(6,0.9946129);
   MVA_BDTD_rejBvsS__3->SetBinContent(7,0.9941799);
   MVA_BDTD_rejBvsS__3->SetBinContent(8,0.9937832);
   MVA_BDTD_rejBvsS__3->SetBinContent(9,0.9933027);
   MVA_BDTD_rejBvsS__3->SetBinContent(10,0.9927514);
   MVA_BDTD_rejBvsS__3->SetBinContent(11,0.9922258);
   MVA_BDTD_rejBvsS__3->SetBinContent(12,0.9917081);
   MVA_BDTD_rejBvsS__3->SetBinContent(13,0.9910908);
   MVA_BDTD_rejBvsS__3->SetBinContent(14,0.9901866);
   MVA_BDTD_rejBvsS__3->SetBinContent(15,0.9897424);
   MVA_BDTD_rejBvsS__3->SetBinContent(16,0.9885641);
   MVA_BDTD_rejBvsS__3->SetBinContent(17,0.9879531);
   MVA_BDTD_rejBvsS__3->SetBinContent(18,0.987217);
   MVA_BDTD_rejBvsS__3->SetBinContent(19,0.9863753);
   MVA_BDTD_rejBvsS__3->SetBinContent(20,0.9855336);
   MVA_BDTD_rejBvsS__3->SetBinContent(21,0.9845722);
   MVA_BDTD_rejBvsS__3->SetBinContent(22,0.9837919);
   MVA_BDTD_rejBvsS__3->SetBinContent(23,0.9832676);
   MVA_BDTD_rejBvsS__3->SetBinContent(24,0.9820695);
   MVA_BDTD_rejBvsS__3->SetBinContent(25,0.9807835);
   MVA_BDTD_rejBvsS__3->SetBinContent(26,0.9797322);
   MVA_BDTD_rejBvsS__3->SetBinContent(27,0.9783262);
   MVA_BDTD_rejBvsS__3->SetBinContent(28,0.9770579);
   MVA_BDTD_rejBvsS__3->SetBinContent(29,0.9751666);
   MVA_BDTD_rejBvsS__3->SetBinContent(30,0.9743516);
   MVA_BDTD_rejBvsS__3->SetBinContent(31,0.9724324);

   MVA_BDTD_rejBvsS__3->SetEntries(31);
   MVA_BDTD_rejBvsS__3->SetLineColor(3);
   MVA_BDTD_rejBvsS__3->SetLineWidth(3);
   MVA_BDTD_rejBvsS__3->GetXaxis()->SetTitle("Signal eff");
   MVA_BDTD_rejBvsS__3->GetXaxis()->SetLabelFont(42);
   MVA_BDTD_rejBvsS__3->GetXaxis()->SetTitleOffset(1);
   MVA_BDTD_rejBvsS__3->GetXaxis()->SetTitleFont(42);
   MVA_BDTD_rejBvsS__3->GetYaxis()->SetTitle("Backgr rejection (1-eff)");
   MVA_BDTD_rejBvsS__3->GetYaxis()->SetLabelFont(42);
   MVA_BDTD_rejBvsS__3->GetYaxis()->SetTitleFont(42);
   MVA_BDTD_rejBvsS__3->GetZaxis()->SetLabelFont(42);
   MVA_BDTD_rejBvsS__3->GetZaxis()->SetTitleOffset(1);
   MVA_BDTD_rejBvsS__3->GetZaxis()->SetTitleFont(42);
   MVA_BDTD_rejBvsS__3->Draw("SameC");
    
   TH1D *MVA_BDTF_rejBvsS__4 = new TH1D("MVA_BDTF_rejBvsS__4","MVA_BDTF",31,0.4,0.7);

   MVA_BDTF_rejBvsS__4->SetBinContent(1,0.9952733);
   MVA_BDTF_rejBvsS__4->SetBinContent(2,0.9950571);
   MVA_BDTF_rejBvsS__4->SetBinContent(3,0.9948026);
   MVA_BDTF_rejBvsS__4->SetBinContent(4,0.9943844);
   MVA_BDTF_rejBvsS__4->SetBinContent(5,0.9940913);
   MVA_BDTF_rejBvsS__4->SetBinContent(6,0.9937589);
   MVA_BDTF_rejBvsS__4->SetBinContent(7,0.9934118);
   MVA_BDTF_rejBvsS__4->SetBinContent(8,0.9928914);
   MVA_BDTF_rejBvsS__4->SetBinContent(9,0.9924832);
   MVA_BDTF_rejBvsS__4->SetBinContent(10,0.9921518);
   MVA_BDTF_rejBvsS__4->SetBinContent(11,0.9916771);
   MVA_BDTF_rejBvsS__4->SetBinContent(12,0.9912588);
   MVA_BDTF_rejBvsS__4->SetBinContent(13,0.9904878);
   MVA_BDTF_rejBvsS__4->SetBinContent(14,0.9897564);
   MVA_BDTF_rejBvsS__4->SetBinContent(15,0.9892182);
   MVA_BDTF_rejBvsS__4->SetBinContent(16,0.9884338);
   MVA_BDTF_rejBvsS__4->SetBinContent(17,0.9876981);
   MVA_BDTF_rejBvsS__4->SetBinContent(18,0.9870347);
   MVA_BDTF_rejBvsS__4->SetBinContent(19,0.9864673);
   MVA_BDTF_rejBvsS__4->SetBinContent(20,0.9858498);
   MVA_BDTF_rejBvsS__4->SetBinContent(21,0.9851663);
   MVA_BDTF_rejBvsS__4->SetBinContent(22,0.9844597);
   MVA_BDTF_rejBvsS__4->SetBinContent(23,0.9838933);
   MVA_BDTF_rejBvsS__4->SetBinContent(24,0.9826932);
   MVA_BDTF_rejBvsS__4->SetBinContent(25,0.9817895);
   MVA_BDTF_rejBvsS__4->SetBinContent(26,0.9805639);
   MVA_BDTF_rejBvsS__4->SetBinContent(27,0.978874);
   MVA_BDTF_rejBvsS__4->SetBinContent(28,0.9773759);
   MVA_BDTF_rejBvsS__4->SetBinContent(29,0.9761688);
   MVA_BDTF_rejBvsS__4->SetBinContent(30,0.9748044);
   MVA_BDTF_rejBvsS__4->SetBinContent(31,0.972573);
   
   MVA_BDTF_rejBvsS__4->SetEntries(31);
   MVA_BDTF_rejBvsS__4->SetLineColor(4);
   MVA_BDTF_rejBvsS__4->SetLineWidth(3);
   MVA_BDTF_rejBvsS__4->GetXaxis()->SetTitle("Signal eff");
   MVA_BDTF_rejBvsS__4->GetXaxis()->SetLabelFont(42);
   MVA_BDTF_rejBvsS__4->GetXaxis()->SetTitleOffset(1);
   MVA_BDTF_rejBvsS__4->GetXaxis()->SetTitleFont(42);
   MVA_BDTF_rejBvsS__4->GetYaxis()->SetTitle("Backgr rejection (1-eff)");
   MVA_BDTF_rejBvsS__4->GetYaxis()->SetLabelFont(42);
   MVA_BDTF_rejBvsS__4->GetYaxis()->SetTitleFont(42);
   MVA_BDTF_rejBvsS__4->GetZaxis()->SetLabelFont(42);
   MVA_BDTF_rejBvsS__4->GetZaxis()->SetTitleOffset(1);
   MVA_BDTF_rejBvsS__4->GetZaxis()->SetTitleFont(42);
   MVA_BDTF_rejBvsS__4->Draw("sameC");
    
   TH1D *MVA_BDTG_rejBvsS__7 = new TH1D("MVA_BDTG_rejBvsS__7","MVA_BDTG",31,0,1);

   MVA_BDTG_rejBvsS__7->SetBinContent(1,0.996985);
   MVA_BDTG_rejBvsS__7->SetBinContent(2,0.99676);
   MVA_BDTG_rejBvsS__7->SetBinContent(3,0.9965366);
   MVA_BDTG_rejBvsS__7->SetBinContent(4,0.9962407);
   MVA_BDTG_rejBvsS__7->SetBinContent(5,0.995861);
   MVA_BDTG_rejBvsS__7->SetBinContent(6,0.9954883);
   MVA_BDTG_rejBvsS__7->SetBinContent(7,0.9952332);
   MVA_BDTG_rejBvsS__7->SetBinContent(8,0.9949246);
   MVA_BDTG_rejBvsS__7->SetBinContent(9,0.9946642);
   MVA_BDTG_rejBvsS__7->SetBinContent(10,0.99433);
   MVA_BDTG_rejBvsS__7->SetBinContent(11,0.9938862);
   MVA_BDTG_rejBvsS__7->SetBinContent(12,0.9933535);
   MVA_BDTG_rejBvsS__7->SetBinContent(13,0.9929001);
   MVA_BDTG_rejBvsS__7->SetBinContent(14,0.9924809);
   MVA_BDTG_rejBvsS__7->SetBinContent(15,0.9920633);
   MVA_BDTG_rejBvsS__7->SetBinContent(16,0.9913619);
   MVA_BDTG_rejBvsS__7->SetBinContent(17,0.9907254);
   MVA_BDTG_rejBvsS__7->SetBinContent(18,0.990298);
   MVA_BDTG_rejBvsS__7->SetBinContent(19,0.9896825);
   MVA_BDTG_rejBvsS__7->SetBinContent(20,0.9893115);
   MVA_BDTG_rejBvsS__7->SetBinContent(21,0.9885659);
   MVA_BDTG_rejBvsS__7->SetBinContent(22,0.9874976);
   MVA_BDTG_rejBvsS__7->SetBinContent(23,0.986509);
   MVA_BDTG_rejBvsS__7->SetBinContent(24,0.9857665);
   MVA_BDTG_rejBvsS__7->SetBinContent(25,0.9847238);
   MVA_BDTG_rejBvsS__7->SetBinContent(26,0.9840461);
   MVA_BDTG_rejBvsS__7->SetBinContent(27,0.9832651);
   MVA_BDTG_rejBvsS__7->SetBinContent(28,0.9824303);
   MVA_BDTG_rejBvsS__7->SetBinContent(29,0.9815292);
   MVA_BDTG_rejBvsS__7->SetBinContent(30,0.9802149);
   MVA_BDTG_rejBvsS__7->SetBinContent(31,0.9788723);

   MVA_BDTG_rejBvsS__7->SetEntries(31);
   MVA_BDTG_rejBvsS__7->SetLineColor(5);
   MVA_BDTG_rejBvsS__7->SetLineWidth(3);
   MVA_BDTG_rejBvsS__7->GetXaxis()->SetTitle("Signal eff");
   MVA_BDTG_rejBvsS__7->GetXaxis()->SetLabelFont(42);
   MVA_BDTG_rejBvsS__7->GetXaxis()->SetTitleOffset(1);
   MVA_BDTG_rejBvsS__7->GetXaxis()->SetTitleFont(42);
   MVA_BDTG_rejBvsS__7->GetYaxis()->SetTitle("Backgr rejection (1-eff)");
   MVA_BDTG_rejBvsS__7->GetYaxis()->SetLabelFont(42);
   MVA_BDTG_rejBvsS__7->GetYaxis()->SetTitleFont(42);
   MVA_BDTG_rejBvsS__7->GetZaxis()->SetLabelFont(42);
   MVA_BDTG_rejBvsS__7->GetZaxis()->SetTitleOffset(1);
   MVA_BDTG_rejBvsS__7->GetZaxis()->SetTitleFont(42);
   MVA_BDTG_rejBvsS__7->Draw("sameC");


    gPad->SetGrid();

    MVA_BDT_rejBvsS__1->SetStats(0);

    TLegend *legend = new TLegend(0.1,0.35,0.4,0.1);
    legend->SetHeader("Legend", "C");
    legend->AddEntry(MVA_BDT_rejBvsS__1, "BDT", "l");
    legend->AddEntry(MVA_BDTB_rejBvsS__2, "BDTB", "l");
    legend->AddEntry(MVA_BDTD_rejBvsS__3, "BDTD", "l");
    legend->AddEntry(MVA_BDTF_rejBvsS__4, "BDTF", "l");
    legend->AddEntry(MVA_BDTG_rejBvsS__7, "BDTG", "l");
    legend->Draw();

    return 0;
}

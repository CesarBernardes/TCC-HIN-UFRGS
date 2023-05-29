///To run it do: root -l -b -q macro_HBT_AllCentralities.C

//to reject a range in the fit -- in principle did not reject any range
Double_t reject_range_min = 0.0;
Double_t reject_range_max = 0.00001;

//Exponential function + long range
Double_t func1_exp(Double_t* x, Double_t* par){
Double_t v = 0;
if(reject_range_min<x[0] && x[0]<reject_range_max){TF1::RejectPoint();}
else{v= par[0]*(1 + par[1]*exp(-par[2]*x[0]/0.1973))*(1+par[3]*x[0]);}
return v;
}

//Gaussian function + long range
Double_t func2_gauss(Double_t* x, Double_t* par){
Double_t v = 0;
if(reject_range_min<x[0] && x[0]<reject_range_max){TF1::RejectPoint();}
else{v= par[0]*(1 + par[1]*exp(-pow(par[2]*x[0]/0.1973,2.)))*(1+par[3]*x[0]);}
return v;
}

//Customize Histograms
void func_hist_custom_qinv(TH1D *h){
   h->GetXaxis()->SetTitle("q_{inv} [GeV]");
   h->GetYaxis()->SetTitle("Number of pairs / bin");
   h->GetXaxis()->SetTitleOffset(1.15);
   h->GetYaxis()->SetTitleOffset(1.15);
   h->SetLineColor(1);
   h->SetMarkerColor(1);
   h->SetLineWidth(2);
}

void func_hist_custom_sr(TH1D *h){
   h->GetXaxis()->SetTitle("q_{inv} [GeV]");
   h->GetYaxis()->SetTitle("Single Ratio");
   h->GetXaxis()->SetTitleOffset(1.15);
   h->GetYaxis()->SetTitleOffset(1.15);
   h->SetLineColor(2);
   h->SetMarkerColor(2);
   h->SetLineWidth(2);
}

//Set fit functions
void set_fit_func_exp(TF1 *f){
   f->SetParameters(1.0,1.0,4.0,0.0); //initialize parameters
   f->SetParName(0,"Const");
   f->SetParLimits(0,0.0,2.0);//The specified limits will be used in a fit operation when the option "B" is specified (Bounds). To fix a parameter, use TF1::FixParameter.
   f->SetParName(1,"#lambda");
   f->SetParLimits(1,0.0,2.0);
   f->SetParName(2,"R (fm)");
   f->SetParName(3,"#delta");
   f->SetLineColor(kBlue); 
   f->SetLineWidth(2);
}

void set_fit_func_gauss(TF1 *f){
   f->SetParameters(1.0,1.0,4.0,0.0); //initialize parameters
   f->SetParName(0,"Const");
   f->SetParLimits(0,0.0,2.0);//The specified limits will be used in a fit operation when the option "B" is specified (Bounds). To fix a parameter, use TF1::FixParameter.
   f->SetParName(1,"#lambda");
   f->SetParLimits(1,0.0,2.0);
   f->SetParName(2,"R (fm)");
   f->SetParName(3,"#delta");
   f->SetLineColor(kMagenta);
   f->SetLineWidth(2);
   f->SetLineStyle(2);
}

//Main function
void macro_HBT_AllCentralities(){

auto fileName = "/Users/cesarbernardes/Dropbox/Ubuntu_1204/AltasEnergias/ProfessorUFRGS/OrientacaoDeAlunos/Tools/CMSOpenData/cms_open_data_work_hin10/CMSSW_3_9_2_patch5/src/HiForest/HiForestProducer/HiForestAOD_DATA_HBT_withMixing_500k.root"; //access tree here: 
auto outFileName = "HBT_histos_AllCentralities.root"; //output file saving the histograms, fit functions, etc...
TFile *f = TFile::Open(fileName);
TFile *output = new TFile(outFileName,"recreate");

auto treeName = "demo/HBT";
auto t_1 = f->Get<TTree>(treeName);

///From paper Fig1 of "https://arxiv.org/pdf/1107.4800.pdf" correspondence of HFsumET and Centrality:  
///0-5% (centrality)-> 3380-5000GeV (HFSumET), 5-10%->2770-3380GeV, 10-15%-> 2280-2770GeV, 15-20%-> 1850-2280GeV,  20-25%-> 1500-1850GeV,  25-30%-> 1210-1500GeV,  30-35%-> 900-1210GeV,  35-60%-> 240-900GeV,  60-100%->  0.0-240GeV 
///When doing the analysis you can merge some of the bins, for example: 10-20% --> 1850-2770GeV (since the mixing was done following this binning)

//interval for normalization of qinv distributions
Double_t qinv_min = 0.4001;
Double_t qinv_max = 0.9999;

//Fit range
Double_t fit_qinv_min = 0.02;
Double_t fit_qinv_max = 0.50;

//Histo nBins and range
Int_t histNbins=50;
Float_t histLowerRange=0;
Float_t histUpperRange=1; //maximum is 1, since saved only till this value in the tree to save space

const unsigned int nCentBins =9;
TH1D * h_qinv_sig_SS[nCentBins];
TH1D * h_qinv_sig_SS_Corr[nCentBins];
TH1D * h_qinv_bkg_OS[nCentBins];
TH1D * h_qinv_bkg_OS_Corr[nCentBins];
TH1D * h_sr_SS_Over_OS[nCentBins];
TF1  *f_exp_sr_SS_Over_OS[nCentBins];
TF1  *f_gauss_sr_SS_Over_OS[nCentBins];

TString cent_bins[nCentBins]={"0-5%","5-10%","10-15%","15-20%","20-25%","25-30%","30-35%","35-60%","60-100%"};
TCut hFsumEtcut[nCentBins]={"HFsumET>3380 && HFsumET<5000","HFsumET>2770 && HFsumET<3380","HFsumET>2280 && HFsumET<2770","HFsumET>1850 && HFsumET<2280","HFsumET>1500 && HFsumET<1850","HFsumET>1210 && HFsumET<1500","HFsumET>900 && HFsumET<1210","HFsumET>240 && HFsumET<900","HFsumET>0 && HFsumET<240"};
TCut hFsumEtcut_coulombWSS[nCentBins]={"coulombWSS*(HFsumET>3380 && HFsumET<5000)","coulombWSS*(HFsumET>2770 && HFsumET<3380)","coulombWSS*(HFsumET>2280 && HFsumET<2770)","coulombWSS*(HFsumET>1850 && HFsumET<2280)","coulombWSS*(HFsumET>1500 && HFsumET<1850)","coulombWSS*(HFsumET>1210 && HFsumET<1500)","coulombWSS*(HFsumET>900 && HFsumET<1210)","coulombWSS*(HFsumET>240 && HFsumET<900)","coulombWSS*(HFsumET>0 && HFsumET<240)"};
TCut hFsumEtcut_coulombWOS[nCentBins]={"coulombWOS*(HFsumET>3380 && HFsumET<5000)","coulombWOS*(HFsumET>2770 && HFsumET<3380)","coulombWOS*(HFsumET>2280 && HFsumET<2770)","coulombWOS*(HFsumET>1850 && HFsumET<2280)","coulombWOS*(HFsumET>1500 && HFsumET<1850)","coulombWOS*(HFsumET>1210 && HFsumET<1500)","coulombWOS*(HFsumET>900 && HFsumET<1210)","coulombWOS*(HFsumET>240 && HFsumET<900)","coulombWOS*(HFsumET>0 && HFsumET<240)"};

std::string histName_sig_SS[nCentBins]={"hqinvSigSS_0to5","hqinvSigSS_5to10","hqinvSigSS_10to15","hqinvSigSS_15to20","hqinvSigSS_20to25","hqinvSigSS_25to30","hqinvSigSS_30to35","hqinvSigSS_35to60","hqinvSigSS_60to100"};
std::string histName_bkg_OS[nCentBins]={"hqinvBkgOS_0to5","hqinvBkgOS_5to10","hqinvBkgOS_10to15","hqinvBkgOS_15to20","hqinvBkgOS_20to25","hqinvBkgOS_25to30","hqinvBkgOS_30to35","hqinvBkgOS_35to60","hqinvBkgOS_60to100"};
std::string histName_sig_SS_Corr[nCentBins]={"hqinvSigSS_Corr_0to5","hqinvSigSS_Corr_5to10","hqinvSigSS_Corr_10to15","hqinvSigSS_Corr_15to20","hqinvSigSS_Corr_20to25","hqinvSigSS_Corr_25to30","hqinvSigSS_Corr_30to35","hqinvSigSS_Corr_35to60","hqinvSigSS_Corr_60to100"};
std::string histName_bkg_OS_Corr[nCentBins]={"hqinvBkgOS_Corr_0to5","hqinvBkgOS_Corr_5to10","hqinvBkgOS_Corr_10to15","hqinvBkgOS_Corr_15to20","hqinvBkgOS_Corr_20to25","hqinvBkgOS_Corr_25to30","hqinvBkgOS_Corr_30to35","hqinvBkgOS_Corr_35to60","hqinvBkgOS_Corr_60to100"};

TString histTitle_sig_SS[nCentBins]={"Single ratio SS/OS, 0-5%","Single ratio SS/OS, 5-10%","Single ratio SS/OS, 10-15%","Single ratio SS/OS, 15-20%","Single ratio SS/OS, 20-25%","Single ratio SS/OS, 25-30%","Single ratio SS/OS, 30-35%","Single ratio SS/OS, 35-60%","Single ratio SS/OS, 60-100%"};
TString histTitle_bkg_OS[nCentBins]={"q_{inv} SameEvt OS tracks, 0-5%","q_{inv} SameEvt OS tracks, 5-10%","q_{inv} SameEvt OS tracks, 10-15%","q_{inv} SameEvt OS tracks, 15-20%","q_{inv} SameEvt OS tracks, 20-25%","q_{inv} SameEvt OS tracks, 25-30%","q_{inv} SameEvt OS tracks, 30-35%","q_{inv} SameEvt OS tracks, 35-60%","q_{inv} SameEvt OS tracks, 60-100%"};
TString histTitle_sig_SS_Corr[nCentBins]={"q_{inv} SameEvt SS_Corr tracks, 0-5%","q_{inv} SameEvt SS_Corr tracks, 5-10%","q_{inv} SameEvt SS_Corr tracks, 10-15%","q_{inv} SameEvt SS_Corr tracks, 15-20%","q_{inv} SameEvt SS_Corr tracks, 20-25%","q_{inv} SameEvt SS_Corr tracks, 25-30%","q_{inv} SameEvt SS_Corr tracks, 30-35%","q_{inv} SameEvt SS_Corr tracks, 35-60%","q_{inv} SameEvt SS_Corr tracks, 60-100%"};
TString histTitle_bkg_OS_Corr[nCentBins]={"q_{inv} SameEvt OS_Corr tracks, 0-5%","q_{inv} SameEvt OS_Corr tracks, 5-10%","q_{inv} SameEvt OS_Corr tracks, 10-15%","q_{inv} SameEvt OS_Corr tracks, 15-20%","q_{inv} SameEvt OS_Corr tracks, 20-25%","q_{inv} SameEvt OS_Corr tracks, 25-30%","q_{inv} SameEvt OS_Corr tracks, 30-35%","q_{inv} SameEvt OS_Corr tracks, 35-60%","q_{inv} SameEvt OS_Corr tracks, 60-100%"};

std::string histName_sr_SS_Over_OS[nCentBins]={"hsrSSoverOS_0to5","hsrSSoverOS_5to10","hsrSSoverOS_10to15","hsrSSoverOS_15to20","hsrSSoverOS_20to25","hsrSSoverOS_25to30","hsrSSoverOS_30to35","hsrSSoverOS_35to60","hsrSSoverOS_60to100"};
TString histTitle_sr_SS_Over_OS[nCentBins]={"Single ratio SS/OS, 0-5%","Single ratio SS/OS, 5-10%","Single ratio SS/OS, 10-15%","Single ratio SS/OS, 15-20%","Single ratio SS/OS, 20-25%","Single ratio SS/OS, 25-30%","Single ratio SS/OS, 30-35%","Single ratio SS/OS, 35-60%","Single ratio SS/OS, 60-100%"};

TString funcExpName_sr_SS_Over_OS[nCentBins]={"fExpSrSSoverOS_0to5","fExpSrSSoverOS_5to10","fExpSrSSoverOS_10to15","fExpSrSSoverOS_15to20","fExpSrSSoverOS_20to25","fExpSrSSoverOS_25to30","fExpSrSSoverOS_30to35","fExpSrSSoverOS_35to60","fExpSrSSoverOS_60to100"};
TString funcGaussName_sr_SS_Over_OS[nCentBins]={"fGaussSrSSoverOS_0to5","fGaussSrSSoverOS_5to10","fGaussSrSSoverOS_10to15","fGaussSrSSoverOS_15to20","fGaussSrSSoverOS_20to25","fGaussSrSSoverOS_25to30","fGaussSrSSoverOS_30to35","fGaussSrSSoverOS_35to60","fGaussSrSSoverOS_60to100"};


///Canvas will be updated on-the-fly
//auto c = new TCanvas("c", "c", 500, 500);
//c->cd();

//Loop in all centrality bins - do everything: create histos, single ratios and fits
for(unsigned int i_centbin=0; i_centbin<nCentBins; i_centbin++){

   h_qinv_sig_SS[i_centbin] = new TH1D((TString)histName_sig_SS[i_centbin],histTitle_sig_SS[i_centbin],histNbins,histLowerRange,histUpperRange);	
   h_qinv_sig_SS_Corr[i_centbin] = new TH1D((TString)histName_sig_SS_Corr[i_centbin],histTitle_sig_SS_Corr[i_centbin],histNbins,histLowerRange,histUpperRange);
   h_qinv_bkg_OS[i_centbin] = new TH1D((TString)histName_bkg_OS[i_centbin],histTitle_bkg_OS[i_centbin],histNbins,histLowerRange,histUpperRange);
   h_qinv_bkg_OS_Corr[i_centbin] = new TH1D((TString)histName_bkg_OS_Corr[i_centbin],histTitle_bkg_OS_Corr[i_centbin],histNbins,histLowerRange,histUpperRange);
   h_sr_SS_Over_OS[i_centbin] = new TH1D((TString)histName_sr_SS_Over_OS[i_centbin],histTitle_sr_SS_Over_OS[i_centbin],histNbins,histLowerRange,histUpperRange);
   f_exp_sr_SS_Over_OS[i_centbin] = new TF1(funcExpName_sr_SS_Over_OS[i_centbin],func1_exp,fit_qinv_min,fit_qinv_max,4);
   f_gauss_sr_SS_Over_OS[i_centbin] = new TF1(funcGaussName_sr_SS_Over_OS[i_centbin],func2_gauss,fit_qinv_min,fit_qinv_max,4);

   ///qinv distributions 
   t_1->Draw(Form("qinvSigSS>>%s",histName_sig_SS[i_centbin].c_str()),hFsumEtcut[i_centbin],"goff");
   func_hist_custom_qinv(h_qinv_sig_SS[i_centbin]);
   h_qinv_sig_SS[i_centbin]->Write();
   //c->Update(); 

   t_1->Draw(Form("qinvSigSS>>%s",histName_sig_SS_Corr[i_centbin].c_str()),hFsumEtcut_coulombWSS[i_centbin],"goff");
   func_hist_custom_qinv(h_qinv_sig_SS_Corr[i_centbin]);
   h_qinv_sig_SS_Corr[i_centbin]->Write();
   //c->Update();

   t_1->Draw(Form("qinvSigOS>>%s",histName_bkg_OS[i_centbin].c_str()),hFsumEtcut[i_centbin],"goff"); //I use "qinvSigOS" but this was not a proper name saved in the tree...should be BkgOS
   func_hist_custom_qinv(h_qinv_bkg_OS[i_centbin]);
   h_qinv_bkg_OS[i_centbin]->Write();
   //c->Update();

   t_1->Draw(Form("qinvSigOS>>%s",histName_bkg_OS_Corr[i_centbin].c_str()),hFsumEtcut_coulombWOS[i_centbin],"goff"); //I use "qinvSigOS" but this was not a proper name saved in the tree...should be BkgOS
   func_hist_custom_qinv(h_qinv_bkg_OS_Corr[i_centbin]);
   h_qinv_bkg_OS_Corr[i_centbin]->Write();
   //c->Update();

   ///single ratios
   Int_t bin_for_normInt_min = h_qinv_sig_SS_Corr[i_centbin]->GetXaxis()->FindBin(qinv_min); //interval for normalization of qinv distributions
   Int_t bin_for_normInt_max = h_qinv_sig_SS_Corr[i_centbin]->GetXaxis()->FindBin(qinv_max);
   Double_t int_num_controlRegion = h_qinv_sig_SS_Corr[i_centbin]->Integral(bin_for_normInt_min,bin_for_normInt_max);
   Double_t int_den_controlRegion = h_qinv_bkg_OS_Corr[i_centbin]->Integral(bin_for_normInt_min,bin_for_normInt_max);
   //h_qinv_sig_SS_Corr[i_centbin]->Sumw2();
   //h_qinv_bkg_OS_Corr[i_centbin]->Sumw2();
   h_sr_SS_Over_OS[i_centbin]->Divide(h_qinv_sig_SS_Corr[i_centbin],h_qinv_bkg_OS_Corr[i_centbin],int_num_controlRegion,int_den_controlRegion); //see definition here: https://root.cern.ch/doc/master/classTH1.html#a4ef2329285beb6091515b836e160bd9f
   func_hist_custom_sr(h_sr_SS_Over_OS[i_centbin]);
   h_sr_SS_Over_OS[i_centbin]->Write();
   //c->Update();

   ///fitting
   //Exponential
   set_fit_func_exp(f_exp_sr_SS_Over_OS[i_centbin]);
   TFitResultPtr res_exp_sr_SSoverOS;
   ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
   h_sr_SS_Over_OS[i_centbin]->Fit(f_exp_sr_SS_Over_OS[i_centbin], "S R Q N");//See option here: https://root.cern.ch/root/htmldoc/guides/users-guide/FittingHistograms.html#the-fit-method
   h_sr_SS_Over_OS[i_centbin]->Fit(f_exp_sr_SS_Over_OS[i_centbin], "S R Q N");
   res_exp_sr_SSoverOS = h_sr_SS_Over_OS[i_centbin]->Fit(f_exp_sr_SS_Over_OS[i_centbin], "S R M");
   f_exp_sr_SS_Over_OS[i_centbin]->Write();
   //c->Update();
   //Gaussian
   set_fit_func_gauss(f_gauss_sr_SS_Over_OS[i_centbin]);
   TFitResultPtr res_gauss_sr_SSoverOS;
   ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
   h_sr_SS_Over_OS[i_centbin]->Fit(f_gauss_sr_SS_Over_OS[i_centbin], "S R Q N");
   h_sr_SS_Over_OS[i_centbin]->Fit(f_gauss_sr_SS_Over_OS[i_centbin], "S R Q N");
   res_gauss_sr_SSoverOS = h_sr_SS_Over_OS[i_centbin]->Fit(f_gauss_sr_SS_Over_OS[i_centbin], "S R M");
   f_gauss_sr_SS_Over_OS[i_centbin]->Write();
   //c->Update();
}//end for loop in centrality bins	

}	

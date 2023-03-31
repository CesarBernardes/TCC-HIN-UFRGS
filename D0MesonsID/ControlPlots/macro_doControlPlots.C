///To run it, please, do: root -l -b -q 'macro_doControlPlots.C("RootFileFullPath/RootFileName.root")'
///Example: root -l -b -q 'macro_doControlPlots.C("/Users/cesarbernardes/RootTreesD0mesons/tree_skim_MC_prompt.root")'


///Let's use RDataFrame :-) 
///Reference here: https://root.cern.ch/doc/v614/classROOT_1_1RDataFrame.html
///RDataFrame tutorials: https://root.cern.ch/doc/master/group__tutorial__dataframe.html

///Auxiliar functions

//Function to select signal D0 candidates
std::vector<float> func_select_signal( ROOT::VecOps::RVec<Float_t> vec_ori, ROOT::VecOps::RVec<Float_t> vec_dgen ){
   std::vector<float> v;
   for (int i = 0; i < vec_ori.size(); i++){
      if (vec_dgen[i]==23333 || vec_dgen[i]==23344) v.push_back(vec_ori[i]);
   }
   return v;
}

//Function to select fake D0 mesons (background)
std::vector<float> func_select_fake( ROOT::VecOps::RVec<Float_t> vec_ori, ROOT::VecOps::RVec<Float_t> vec_dgen ){
   std::vector<float> v;
   for (int i = 0; i < vec_ori.size(); i++){
      if (vec_dgen[i]!=23333 && vec_dgen[i]!=23344) v.push_back(vec_ori[i]);
   }
   return v;
}

//Function to customize Legend of the histograms
void legendStyle(TLegend* tl, TH1D* h_all, TH1D* h_fake, TH1D* h_sig){
   tl->AddEntry(h_all,"All","l");
   tl->AddEntry(h_fake,"Fake","l");
   tl->AddEntry(h_sig,"True","l");
   tl->SetFillStyle(0);
   tl->SetBorderSize(0);
   tl->SetTextSize(0.045);
   tl->SetTextFont(42);
}

///Main function
void macro_doControlPlots(std::string filename = "/Users/cesarbernardes/D0_MC_SkimmedTrees/tree_skim_MC_prompt.root"){


auto fileName = filename;
auto treeName = "Dfinder/ntDkpi";

// We read the tree from the file and create a RDataFrame object called "d"
ROOT::RDataFrame d(treeName, fileName);

///Section 1 *** Event Variables ***///

// Book histograms

///common y-axis label
auto yaxis_label1 = "Number of Events / Bin";

auto h_centrality = d.Define("cent","centrality/2.0")
	             .Histo1D(TH1D("Centrality","Centrality",100,0,100),"cent"); //for centrality variable
h_centrality->GetYaxis()->SetTitle(yaxis_label1);
h_centrality->GetXaxis()->SetTitle("Centrality (%)");
h_centrality->SetLineColor(2);
h_centrality->SetLineWidth(2);

auto h_PVz = d.Histo1D(TH1D("PVz","Z Position of Primary Vertex",100,-25,25),"PVz"); //for primary vertex Z position
h_PVz->GetYaxis()->SetTitle(yaxis_label1);
h_PVz->GetXaxis()->SetTitle("PV Z Position (cm)");
h_PVz->SetLineColor(2);
h_PVz->SetLineWidth(2);

auto h_PVx = d.Histo1D(TH1D("PVx","X Position of Primary Vertex",100,0,0.07),"PVx"); //for primary vertex X position
h_PVx->GetYaxis()->SetTitle(yaxis_label1);
h_PVx->GetXaxis()->SetTitle("PV X Position (cm)");
h_PVx->SetLineColor(2);
h_PVx->SetLineWidth(2);

auto h_PVy = d.Histo1D(TH1D("PVy","Y Position of Primary Vertex",100,0,0.07),"PVy"); //for primary vertex Y position
h_PVy->GetYaxis()->SetTitle(yaxis_label1);
h_PVy->GetXaxis()->SetTitle("PV Y Position (cm)");
h_PVy->SetLineColor(2);
h_PVy->SetLineWidth(2);

auto h_PVpos = d.Histo3D(TH3D("PV3DPos","3D Position of Primary Vertex",50,-0.07,0.07,50,-0.07,0.07,50,-25,25),"PVx","PVy","PVz"); //for particle primary vertex 3D position
h_PVpos->GetZaxis()->SetTitle("PV Z Position (cm)");
h_PVpos->GetZaxis()->SetTitleOffset(1.3);
h_PVpos->GetYaxis()->SetTitle("PV Y Position (cm)");
h_PVpos->GetYaxis()->SetTitleOffset(2.5);
h_PVpos->GetXaxis()->SetTitle("PV X Position (cm)");
h_PVpos->GetXaxis()->SetTitleOffset(1.8);

// Draw and save histograms

TCanvas tc_globalObservables("tc_globalObservables","GlobalObservables",1000,1000);
tc_globalObservables.Divide(2,2,0.01,0.01);
TGaxis::SetMaxDigits(4);
tc_globalObservables.cd(1);
gPad->SetTickx(1);
gPad->SetTicky(1);
h_centrality->Draw();
tc_globalObservables.cd(2);
gPad->SetTickx(1);
gPad->SetTicky(1);
h_PVz->GetYaxis()->SetLabelOffset(0.01);
h_PVz->Draw();
tc_globalObservables.cd(3);
gPad->SetTickx(1);
gPad->SetTicky(1);
h_PVx->Draw();
tc_globalObservables.cd(4);
gPad->SetTickx(1);
gPad->SetTicky(1);
h_PVy->GetYaxis()->SetLabelOffset(0.01);
h_PVy->Draw();
tc_globalObservables.Print("hist_globalObservables.pdf");


TCanvas tc_PVpos("tc_PVpos","PVPosition3D",500,500);
tc_PVpos.cd(1);
h_PVpos->Draw("BOX2");
tc_PVpos.Print("hist_3D_PVposition.pdf");


///Section 2 *** D0 mesons and its daughters variables ***///

// Book histograms

auto d_select = d.Define("DPt_true","func_select_signal(DPt,DGen)") //pT
                 .Define("DPt_fake","func_select_fake(DPt,DGen)")  //pT
		 .Define("DRapidity_true","func_select_signal(DRapidity,DGen)") //Rapidity
		 .Define("DRapidity_fake","func_select_fake(DRapidity,DGen)") //Rapidity
		 .Define("DPhi_true","func_select_signal(DPhi,DGen)") //Phi
	         .Define("DPhi_fake","func_select_fake(DPhi,DGen)") //Phi		 
		 .Define("DMass_true","func_select_signal(DMass,DGen)") //Mass
                 .Define("DMass_fake","func_select_fake(DMass,DGen)") //Mass
                 .Define("D3DDecayLength_true","func_select_signal(D3DDecayLength,DGen)") //Decay Length 3D
                 .Define("D3DDecayLength_fake","func_select_fake(D3DDecayLength,DGen)") //Decay Length 3D
                 .Define("DVtxProb_true","func_select_signal(DVtxProb,DGen)") // SV Chi2 Probability
                 .Define("DVtxProb_fake","func_select_fake(DVtxProb,DGen)") // SV Chi2 Probability  
                 .Define("D2DPointingAngle_true","func_select_signal(D2DPointingAngle,DGen)") // 2D Projection of Pointing Angle
                 .Define("D2DPointingAngle_fake","func_select_fake(D2DPointingAngle,DGen)") // 2D Projection of Pointing Angle
                 .Define("DTtrk1Pt_true","func_select_signal(DTtrk1Pt,DGen)") // 1st Daughter Transverse Momentum
                 .Define("DTtrk1Pt_fake","func_select_fake(DTtrk1Pt,DGen)") // 1st Daughter Transverse Momentum
                 .Define("DTrk1PtErr_true","func_select_signal(DTrk1PtErr,DGen)") // 1st Daughter Transverse Momentum Uncertainty
                 .Define("DTrk1PtErr_fake","func_select_fake(DTrk1PtErr,DGen)") // 1st Daughter Transverse Momentum Uncertainty
                 .Define("DTrk1Eta_true","func_select_signal(DTrk1Eta,DGen)") // 1st Daughter Pseudo-rapidity
                 .Define("DTrk1Eta_fake","func_select_fake(DTrk1Eta,DGen)") // 1st Daughter Pseudo-rapidity
                 .Define("DTrk1Chi2n_true","func_select_signal(DTrk1Chi2n,DGen)") // 1st Daughter Normalized Chi2 of the Trajectory Fit
                 .Define("DTrk1Chi2n_fake","func_select_fake(DTrk1Chi2n,DGen)") // 1st Daughter Normalized Chi2 of the Trajectory Fit
                 .Define("DzDCASignificanceDaugther1_true","func_select_signal(DzDCASignificanceDaugther1,DGen)") // 1st Daughter Significance of the Impact Parameter in Z Axis
                 .Define("DzDCASignificanceDaugther1_fake","func_select_fake(DzDCASignificanceDaugther1,DGen)") // 1st Daughter Significance of the Impact Parameter in Z Axis
                 .Define("DxyDCASignificanceDaugther1_true","func_select_signal(DxyDCASignificanceDaugther1,DGen)") // 1st Daughter Significance of the Impact Parameter in XY Plane
                 .Define("DxyDCASignificanceDaugther1_fake","func_select_fake(DxyDCASignificanceDaugther1,DGen)") // 1st Daughter Significance of the Impact Parameter in XY Plane
                 .Define("D2DDecayLength_true","func_select_signal(D2DDecayLength, DGen)") //Projection of "D3DDecayLenghth" in xy plane
                 .Define("D2DDecayLength_fake","func_select_fake(D2DDecayLength, DGen)") //Projection of "D3DDecayLenghth" in xy plane
                 .Define("DDca_true","func_select_signal(DDca,DGen)") //D0 mesons distance of closest approach (DCA)
                 .Define("DDca_fake","func_select_fake(DDca,DGen)") //D0 mesons distance of closest approach (DCA)
                 .Define("D3DPointingAngle_true","func_select_signal(D3DPointingAngle,DGen)") //DCA in 3D
                 .Define("D3DPointingAngle_fake","func_select_fake(D3DPointingAngle,DGen)") //DCA in 3D
                 .Define("DTrk2Pt_true", "func_select_signal(DTrk2Pt,DGen)") // 2nd Daughter Transverse Momentum
                 .Define("DTrk2Pt_fake", "func_select_fake(DTrk2Pt,DGen)") // 2nd Daughter Transverse Momentum
                 .Define("DTrk2PtErr_true","func_select_signal(DTrk2PtErr,DGen)") // 2nd Daughter Transverse Momentum Uncertainty
                 .Define("DTrk2PtErr_fake","func_select_fake(DTrk2PtErr,DGen)") // 2nd Daughter Transverse Momentum Uncertainty
                 .Define("DTrk2Eta_true","func_select_signal(DTrk2Eta,DGen)") // 2nd Daugther Pseudo-rapidity
                 .Define("DTrk2Eta_fake","func_select_fake(DTrk2Eta,DGen)") // 2nd Daugther Pseudo-rapidity
                 .Define("DTrk2Chi2n_true", "func_select_signal(DTrk2Chi2n,DGen)") // 2nd Daughter Normalized Chi2 of the Trajectory Fit
                 .Define("DTrk2Chi2n_fake", "func_select_fake(DTrk2Chi2n,DGen)") // 2nd Daughter Normalized Chi2 of the Trajectory Fit
                 .Define("DzDCASignificanceDaugther2_true","func_select_signal(DzDCASignificanceDaugther2,DGen)") // 2nd Daughter Significance of the Impact Parameter in Z Axis
                 .Define("DzDCASignificanceDaugther2_fake","func_select_fake(DzDCASignificanceDaugther2,DGen)") // 2nd Daughter Significance of the Impact Parameter in Z Axis
                 .Define("DxyDCASignificanceDaugther2_true", "func_select_signal(DxyDCASignificanceDaugther2,DGen)") // 2nd Daughter Significance of the Impact Parameter in XY Plane
                 .Define("DxyDCASignificanceDaugther2_fake", "func_select_fake(DxyDCASignificanceDaugther2,DGen)"); // 2nd Daughter Significance of the Impact Parameter in XY Plane
                 
                 
                 
                 
                 

const unsigned int N_variables = 22; //Sequence: DPt, DRapidity, DPhi, DMass, D3DDecayLength, DVtxProb, D2DPointingAngle, DTtrk1Pt, DTrk1PtErr, DTrk1Eta, DTrk1Chi2n, DzDCASignificanceDaugther1, DxyDCASignificanceDaugther1, D2DDecayLength, DDca, D3DPointingAngle, DTrk2Pt, DTrk2PtErr, DTrk2Eta, DTrk2Chi2n, DzDCASignificanceDaugther2, DxyDCASignificanceDaugther2, ...

std::string variable_name_all[N_variables]={"DPt","DRapidity","DPhi","DMass","D3DDecayLength","DVtxProb","D2DPointingAngle","DTtrk1Pt","DTrk1PtErr","DTrk1Eta","DTrk1Chi2n","DzDCASignificanceDaugther1","DxyDCASignificanceDaugther1","D2DDecayLength", "DDca", "D3DPointingAngle", "DTrk2Pt", "DTrk2PtErr", "DTrk2Eta", "DTrk2Chi2n", "DzDCASignificanceDaugther2", "DxyDCASignificanceDaugther2"}; //variables' name
std::string variable_name_true[N_variables]={"DPt_true","DRapidity_true","DPhi_true","DMass_true","D3DDecayLength_true","DVtxProb_true","D2DPointingAngle_true","DTtrk1Pt_true","DTrk1PtErr_true","DTrk1Eta_true","DTrk1Chi2n_true","DzDCASignificanceDaugther1_true","DxyDCASignificanceDaugther1_true","D2DDecayLength_true", "DDca_true", "D3DPointingAngle_true", "DTrk2Pt_true", "DTrk2PtErr_true", "DTrk2Eta_true", "DTrk2Chi2n_true", "DzDCASignificanceDaugther2_true", "DxyDCASignificanceDaugther2_true"};
std::string variable_name_fake[N_variables]={"DPt_fake","DRapidity_fake","DPhi_fake","DMass_fake","D3DDecayLength_fake","DVtxProb_fake","D2DPointingAngle_fake","DTtrk1Pt_fake","DTrk1PtErr_fake","DTrk1Eta_fake","DTrk1Chi2n_fake","DzDCASignificanceDaugther1_fake","DxyDCASignificanceDaugther1_fake","D2DDecayLength_fake", "DDca_fake", "D3DPointingAngle_fake", "DTrk2Pt_fake", "DTrk2PtErr_fake", "DTrk2Eta_fake", "DTrk2Chi2n_fake", "DzDCASignificanceDaugther2_fake", "DxyDCASignificanceDaugther2_fake"};
TString hist_name_all[N_variables]={"DPt_all","DRapidity_all","DPhi_all","DMass_all","D3DDecayLength_all","DVtxProb_all","D2DPointingAngle_all","DTtrk1Pt_all","DTrk1PtErr_all","DTrk1Eta_all","DTrk1Chi2n_all","DzDCASignificanceDaugther1_all","DxyDCASignificanceDaugther1_all","D2DDecayLength_all", "DDca_all", "D3DPointingAngle_all", "DTrk2Pt_all", "DTrk2PtErr_all", "DTrk2Eta_all", "DTrk2Chi2n_all", "DzDCASignificanceDaugther2_all", "DxyDCASignificanceDaugther2_all"}; //histograms' name
TString hist_name_true[N_variables]={"DPt_true","DRapidity_true","DPhi_true","DMass_true","D3DDecayLength_true","DVtxProb_true","D2DPointingAngle_true","DTtrk1Pt_true","DTrk1PtErr_true","DTrk1Eta_true","DTrk1Chi2n_true","DzDCASignificanceDaugther1_true","DxyDCASignificanceDaugther1_true","D2DDecayLength_true", "DDca_true", "D3DPointingAngle_true", "DTrk2Pt_true", "DTrk2PtErr_true", "DTrk2Eta_true", "DTrk2Chi2n_true", "DzDCASignificanceDaugther2_true", "DxyDCASignificanceDaugther2_true"};
TString hist_name_fake[N_variables]={"DPt_fake","DRapidity_fake","DPhi_fake","DMass_fake","D3DDecayLength_fake","DVtxProb_fake","D2DPointingAngle_fake","DTtrk1Pt_fake","DTrk1PtErr_fake","DTrk1Eta_fake","DTrk1Chi2n_fake","DzDCASignificanceDaugther1_fake","DxyDCASignificanceDaugther1_fake","D2DDecayLength_fake", "DDca_fake", "D3DPointingAngle_fake", "DTrk2Pt_fake", "DTrk2PtErr_fake", "DTrk2Eta_fake", "DTrk2Chi2n_fake", "DzDCASignificanceDaugther2_fake", "DxyDCASignificanceDaugther2_fake"};
TString hist_title_all[N_variables]={"p_{T} of D^{0} Mesons Candidates","Rapidity (y) of D^{0} Mesons","Azimuthal Angle (#phi) of D^{0} Mesons","Invariant Mass (M_{inv}) of D^{0} Mesons","Distance from Primary Vertex to Secondary Vertex of D^{0} Mesons","Chi2 Probability of the Secondary Vertex of D^{0} Mesons","Superficial Angle Between p of D^{0} Mesons and the Segment PVSV","1st Daughters of D^{0} Mesons Transverse Momentum","1st Daughters of D^{0} Mesons Transverse Momentum Uncertainty","1st Daughters of D^{0} Mesons Pseudo-rapidity","1st Daughters of D^{0} Mesons Normalized Chi2 of the Trajectory Fit","1st Daughters of D^{0} Mesons Significance of the Impact Parameter in Z Axis","1st Daughters of D^{0} Mesons Significance of the Impact Parameter in XY Plane","Distance from Primary Vertex to Secondary Vertex of D^{0} Mesons projected in XY plane","D^{0} Mesons distance of closest approach (DCA)","Angle between the D{0} momentum and the line connecting the PV And SV","2nd Daughters of D^{0} Mesons Transverse Momentum","2nd Daughters of D^{0} Mesons Transverse Momentum Uncertainty","2nd Daughters of D^{0} Mesons Pseudo-rapidity","2nd Daughters of D^{0} Mesons Normalized Chi2 of the Trajectory Fit","2nd Daughters of D^{0} Mesons Significance of the Impact Parameter in Z Axis","2nd Daughters of D^{0} Mesons Significance of the Impact Parameter in XY Plane"}; //histograms' title
TString hist_title_true[N_variables]={"p_{T} of true D^{0} Mesons","Rapidity (y) of true D^{0} Mesons","Azimuthal Angle (#phi) of true D^{0} Mesons","Invariant Mass (M_{inv}) of true D^{0} Mesons","Distance from Primary Vertex to Secondary Vertex of true D^{0} Mesons","Chi2 Probability of the Secondary Vertex of true D^{0} Mesons","Superficial Angle Between p of the true D^{0} Mesons and the Segment PVSV","1st Daughters of true D^{0} Mesons Transverse Momentum","1st Daughters of true D^{0} Mesons Transverse Momentum Uncertainty","1st Daughters of true D^{0} Mesons Pseudo-rapidity","1st Daughters of true D^{0} Mesons Normalized Chi2 of the Trajectory Fit","1st Daughters of true D^{0} Mesons Significance of the Impact Parameter in Z Axis","1st Daughters of true D^{0} Mesons Significance of the Impact Parameter in XY Plane","Distance from Primary Vertex to Secondary Vertex of true D^{0} Mesons projected in XY plane","True D^{0} Mesons distance of closest approach (DCA)","Angle between the true D{0} momentum and the line connecting the PV And SV","2nd Daughters of true D^{0} Mesons Transverse Momentum","2nd Daughters of true D^{0} Mesons Transverse Momentum Uncertainty","2nd Daughters of true D^{0} Mesons Pseudo-rapidity","2nd Daughters of true D^{0} Mesons Normalized Chi2 of the Trajectory Fit","2nd Daughters of true D^{0} Mesons Significance of the Impact Parameter in Z Axis","2nd Daughters of true D^{0} Mesons Significance of the Impact Parameter in XY Plane"};
TString hist_title_fake[N_variables]={"p_{T} of fake D^{0} Mesons (background)","Rapidity (y) of fake D^{0} Mesons (background)","Azimuthal Angle (#phi) of fake D^{0} Mesons","Invariant Mass (M_{inv}) of fake D^{0} Mesons (background)","Distance from Primary Vertex to Secondary Vertex of fake D^{0} Mesons (background)","Chi2 Probability of the Secondary Vertex of fake D^{0} Mesons (background)"," Superficial Angle Between p of the fake D^{0} Mesons (background) and the Segment PVSV","1st Daughters of fake D^{0} Mesons (background) Transverse Momentum","1st Daughters of fake D^{0} Mesons (background) Transverse Momentum Uncertainty","1st Daughters of fake D^{0} Mesons (background) Pseudo-rapidity","1st Daughters of fake D^{0} Mesons (background) Normalized Chi2 of the Trajectory Fit","1st Daughters of fake D^{0} Mesons (background) Significance of the Impact Parameter in Z Axis","1st Daughters of fake D^{0} Mesons (background) Significance of the Impact Parameter in XY Plane","Distance from Primary Vertex to Secondary Vertex of fake D^{0} Mesons projected in XY plane","Fake D^{0} Mesons distance of closest approach (DCA)","Angle between the fake D{0} momentum and the line connecting the PV And SV","2nd Daughters of fake D^{0} Mesons Transverse Momentum","2nd Daughters of fake D^{0} Mesons Transverse Momentum Uncertainty","2nd Daughters of fake D^{0} Mesons Pseudo-rapidity","2nd Daughters of fake D^{0} Mesons Normalized Chi2 of the Trajectory Fit","2nd Daughters of fake D^{0} Mesons Significance of the Impact Parameter in Z Axis","2nd Daughters of fake D^{0} Mesons Significance of the Impact Parameter in XY Plane"};
const float hist_Nbins[N_variables]= {20, 50, 25, 50, 100, 20, 20, 40, 100, 100, 100, 70, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}; //Number of bins for All, True, and Fake D0 candidates histograms
const float hist_Xrange_min[N_variables]= {3, -2.5, -4.6, 1.60, 0, 0, 0, 0.5, 0, -1.8, 0, -540, -100, 0, 0, 0, 0, 0, -1.8, 0, -300, -250}; //Minimum value of the x-axis range for All, True, and Fake D0 candidates histograms
const float hist_Xrange_max[N_variables]= {5, 2.5, 4.6, 2.10, 20, 1, 1, 4, 0.2, 1.8, 10, 125, 100, 20, 20, 1, 4, 0.14, 1.8, 10, 800, 250}; //Maximum value of the x-axis range for All, True, and Fake D0 candidates histograms
TString hist_XaxisTitle[N_variables]={"p_{T} (GeV/c)","Rapidity","#phi","M_{inv} (GeV/c^{2})","Decay Length (#mum)","Probability","#alpha (rad)","p_{T} (GeV/c)","p_{T} Uncertainty (GeV/c)","Pseudo-rapidity","#chi^{2}/ndf","Significance","Significance","Decay Length (#mum)","DCA (cm)","#alpha (rad)","p_{T} (GeV/c)","p_{T} Uncertainty (GeV/c)","Pseudo-rapidity","#chi^{2}/ndf","Significance","Significance"}; //Title of x-axis for All, True, and Fake D0 candidates histograms
const float hist_Yrange_min[N_variables]={0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9}; //Minimum of the y-axis range for All, True, and Fake D0 candidates histograms
const float hist_Yrange_max[N_variables]={10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000}; //Maximum of the y-axis range for All, True, and Fake D0 candidates histograms
const float histNorm_Yrange_min[N_variables]={0.0,0.0,0.0,0.0,0.00001,0.0,0.0,0.0,0.00001,0.0,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001}; //Minimum of the y-axis range for All, True, and Fake D0 candidates Normalized histograms
const float histNorm_Yrange_max[N_variables]={0.4,0.1,0.1,0.25,0.4,0.3,0.6,0.1,0.2,0.2,0.06,0.4,0.4,0.4,0.4,0.1,0.05,0.15,0.05,0.4,0.4,0.2}; //Maximum of the y-axis range for All, True, and Fake D0 candidates Normalized histograms
TString fig_name[N_variables]={"hist_DPt.png","hist_DRapidity.png","hist_DPhi.png","hist_DMass.png","hist_D3DDecayLength.png","hist_DVtxProb.png","hist_D2DPointingAngle.png","hist_DTtrk1Pt.png","hist_DTrk1PtErr.png","hist_DTrk1Eta.png","hist_DTrk1Chi2n.png","hist_DzDCASignificanceDaugther1.png","hist_DxyDCASignificanceDaugther1.png","hist_D2DDecayLength.png", "hist_DDca.png", "hist_D3DPointingAngle.png", "hist_DTrk2Pt.png", "hist_DTrk2PtErr.png", "hist_DTrk2Eta.png","hist_DTrk2Chi2n.png","hist_DzDCASignificanceDaugther2.png","hist_DxyDCASignificanceDaugther2.png"}; //Name of the figure file with the histograms saved
auto yaxis_label2 = "Total Number of Particles / Bin"; //common y-axis label
auto yaxis_label3 = "Normalized Distributions";

//Book histograms using RDataFrame, plot and save the figure in a PDF format
TCanvas tc("tc","tc",1000,500); //ROOT TCanvas to plot the variables - it will be updated on-the-fly after saving the PDF with the plot
tc.Divide(2,1,0.02,0.02);
for (unsigned int i=0; i<N_variables; i++){

   //Book histograms	
   auto h_all = d_select.Histo1D(TH1D(hist_name_all[i],hist_title_all[i],hist_Nbins[i],hist_Xrange_min[i],hist_Xrange_max[i]),variable_name_all[i]);
   h_all->GetYaxis()->SetTitle(yaxis_label2);
   h_all->GetYaxis()->SetTitleOffset(1.4);
   h_all->GetXaxis()->SetTitle(hist_XaxisTitle[i]);
   h_all->SetLineColor(1);
   h_all->SetMarkerColor(1);
   h_all->SetLineWidth(2);
   h_all->GetYaxis()->SetRangeUser(hist_Yrange_min[i], hist_Yrange_max[i]);

   auto h_true = d_select.Histo1D(TH1D(hist_name_true[i],hist_title_true[i],hist_Nbins[i],hist_Xrange_min[i],hist_Xrange_max[i]),variable_name_true[i]);
   h_true->GetYaxis()->SetTitle(yaxis_label2);
   h_true->GetXaxis()->SetTitle(hist_XaxisTitle[i]);
   h_true->SetLineColor(4);
   h_true->SetMarkerColor(4);
   h_true->SetLineWidth(2);

   auto h_fake = d_select.Histo1D(TH1D(hist_name_fake[i],hist_title_fake[i],hist_Nbins[i],hist_Xrange_min[i],hist_Xrange_max[i]),variable_name_fake[i]);
   h_fake->GetYaxis()->SetTitle(yaxis_label2);
   h_fake->GetXaxis()->SetTitle(hist_XaxisTitle[i]);
   h_fake->SetLineColor(2);
   h_fake->SetMarkerColor(2);
   h_fake->SetLineStyle(2);
   h_fake->SetLineWidth(2);

   //Draw and save histograms - use two situations: 
   // 1) With all entries in y-axis (better to see total number of candidates in each case); 
   // 2) Normalized in y-axis by its integral (better to visualize the shape of the distributions)
   
   //First, case "1)"...
   tc.cd(1);
   if (i == 4 || i == 10) {
      gPad->SetLogx(); //use log scale in x-axis for wanted varibles
   } else {
      gPad->SetLogx(0);
   }
   gPad->SetLogy(); //use log scale in y-axis
   gPad->SetTickx(1); 
   gPad->SetTicky(1);
   h_all->Draw();
   gPad->Update();     
   TPaveStats *st_all = (TPaveStats*)h_all->FindObject("stats"); //To adjust the position of the Statistics box
   st_all->SetY1NDC(0.75);
   st_all->SetY2NDC(0.90);
   st_all->SetX1NDC(0.80);
   st_all->SetX2NDC(1.00);
   h_fake->Draw("sameS"); //draw in the same canvas and with statistcs box
   gPad->Update();
   TPaveStats *st_fake = (TPaveStats*)h_fake->FindObject("stats"); //To adjust the position of the Statistics box
   st_fake->SetY1NDC(0.60);
   st_fake->SetY2NDC(0.75);
   st_fake->SetX1NDC(0.80);
   st_fake->SetX2NDC(1.00);
   h_true->Draw("sameS");  //draw in the same canvas and with statistcs box
   gPad->Update();
   TPaveStats *st_true = (TPaveStats*)h_true->FindObject("stats"); //To adjust the position of the Statistics box
   st_true->SetY1NDC(0.45);
   st_true->SetY2NDC(0.60);
   st_true->SetX1NDC(0.80);
   st_true->SetX2NDC(1.00);
   TLegend *leg = new TLegend(0.6,0.68,0.85,0.9); //Create a legend for the plots
   legendStyle(leg, h_all.GetPtr(), h_fake.GetPtr(), h_true.GetPtr()); //call function to customize style of TCanvas
   leg->Draw();
   //...and then, case "2)"
   tc.cd(2);
   gPad->SetTickx(1);
   gPad->SetTicky(1);
   TH1D *h_clone_all = (TH1D *)h_all->Clone("h_clone_all"); //clone the histogram "h_all" in order to not messup the original one
   h_clone_all->GetYaxis()->SetTitle(yaxis_label3);
   h_clone_all->SetStats(0);
   h_clone_all->GetYaxis()->SetTitleOffset(1.5);
   h_clone_all->Scale(1./(h_clone_all->Integral())); //Normalize it by multiplying the distribution by 1./integral
   h_clone_all->Draw("h");
   h_clone_all->GetYaxis()->SetRangeUser(histNorm_Yrange_min[i], histNorm_Yrange_max[i]);
   TH1D *h_clone_fake = (TH1D *)h_fake->Clone("h_clone_fake"); //clone the histogram "h_fake" in order to not messup the original one
   h_clone_fake->Scale(1./(h_clone_fake->Integral())); //Normalize it by multiplying the distribution by 1./integral
   h_clone_fake->SetStats(0);
   h_clone_fake->Draw("hsame");
   TH1D *h_clone_true = (TH1D *)h_true->Clone("h_clone_true"); //clone the histogram "h_true" in order to not messup the original one
   h_clone_true->Scale(1./(h_clone_true->Integral()));
   h_clone_true->SetStats(0);
   h_clone_true->Draw("hsame");
   TLegend *leg_norm = new TLegend(0.7,0.68,0.95,0.9); //Create a legend for the plots
   legendStyle(leg_norm, h_clone_all, h_clone_fake, h_clone_true);  //call function to customize style of TCanvas
   leg_norm->Draw();
   if (i == 4 || i == 10) {
      gPad->SetLogx(); //use log scale in x-axis for wanted varibles
   } else {
      gPad->SetLogx(0);
   }
   if (i == 4 || i == 8 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 19 || i == 20 || i == 21) {
      gPad->SetLogy(); //use log scale in y-axis for wanted variables
   } else {
      gPad->SetLogy(0);
   }
   tc.Print(fig_name[i]); //save Canvas in a PDF file...we can change format if needed PNG, JPG, ..etc...
}


//Just to check the branches in the input trees
//Open the root file and list the columns of the tree
/*
TString fName = (TString) filename;
TFile f1(fName);
auto t = f1.Get<TTree>(treeName); //get root tree
std::cout << "These are the columns of the tree:" << std::endl;
for (auto branch : *t->GetListOfBranches()) {
   std::cout << "Branch: " << branch->GetName() << std::endl;	
}
f1.Close();
*/


}


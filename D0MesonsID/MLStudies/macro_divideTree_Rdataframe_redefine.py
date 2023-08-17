###To run it do: << pyroot macro_divideTree_Rdataframe.py >> 

import ROOT

# We prepare an input tree to run on
fileName = "/home/guilherme/testes/treeMC.root"
treeName = "Dfinder/ntDkpi"
outFileNameTrain = "treeMCprompt.root"
outFileNameTest = "treeMCtest.root"

# We read the tree from the file and create a RDataFrame
d = ROOT.RDataFrame(treeName, fileName) 

# Auxiliar functions to Redefine variables as vector<float> instead of ROOT::VecOps::RVec<Float_t> default format from RDataframe
getVector_code ='''
std::vector<float> getVectorFloat_Aux(ROOT::VecOps::RVec<Float_t> vec_){
   std::vector<float> v;
   for(int i=0; i<vec_.size(); i++){
      v.push_back(vec_[i]);
   }
   return v;
}
'''
ROOT.gInterpreter.Declare(getVector_code)

##select first 500k entries 
d_train = d.Range(500000) \
           .Redefine("DPt","getVectorFloat_Aux(DPt)") \
           .Redefine("DRapidity","getVectorFloat_Aux(DRapidity)") \
           .Redefine("DMass","getVectorFloat_Aux(DMass)") \
           .Redefine("DPhi","getVectorFloat_Aux(DPhi)") \
           .Redefine("D2DDecayLength","getVectorFloat_Aux(D2DDecayLength)") \
           .Redefine("DD0Err","getVectorFloat_Aux(DD0Err)") \
           .Redefine("D3DDecayLength","getVectorFloat_Aux(D3DDecayLength)") \
           .Redefine("DDxyzErr","getVectorFloat_Aux(DDxyzErr)") \
           .Redefine("D3DDecayLengthSignificance","getVectorFloat_Aux(D3DDecayLengthSignificance)") \
           .Redefine("D2DDecayLengthSignificance","getVectorFloat_Aux(D2DDecayLengthSignificance)") \
           .Redefine("DVtxProb","getVectorFloat_Aux(DVtxProb)") \
           .Redefine("D3DPointingAngle","getVectorFloat_Aux(D3DPointingAngle)") \
           .Redefine("D2DPointingAngle","getVectorFloat_Aux(D2DPointingAngle)") \
           .Redefine("DDca","getVectorFloat_Aux(DDca)") \
           .Redefine("DImpactParameter3D","getVectorFloat_Aux(DImpactParameter3D)") \
           .Redefine("DImpactParameter3Derror","getVectorFloat_Aux(DImpactParameter3Derror)") \
           .Redefine("DTtrk1Pt","getVectorFloat_Aux(DTtrk1Pt)") \
           .Redefine("DTrk2Pt","getVectorFloat_Aux(DTrk2Pt)") \
           .Redefine("DTrk1PtErr","getVectorFloat_Aux(DTrk1PtErr)") \
           .Redefine("DTrk2PtErr","getVectorFloat_Aux(DTrk2PtErr)") \
           .Redefine("DTrk1Eta","getVectorFloat_Aux(DTrk1Eta)") \
           .Redefine("DTrk2Eta","getVectorFloat_Aux(DTrk2Eta)") \
           .Redefine("DxyDCASignificanceDaugther1","getVectorFloat_Aux(DxyDCASignificanceDaugther1)") \
           .Redefine("DxyDCASignificanceDaugther2","getVectorFloat_Aux(DxyDCASignificanceDaugther2)") \
           .Redefine("DzDCASignificanceDaugther1","getVectorFloat_Aux(DzDCASignificanceDaugther1)") \
           .Redefine("DzDCASignificanceDaugther2","getVectorFloat_Aux(DzDCASignificanceDaugther2)") \
           .Redefine("DTrk1Chi2n","getVectorFloat_Aux(DTrk1Chi2n)") \
           .Redefine("DTrk2Chi2n","getVectorFloat_Aux(DTrk2Chi2n)") \
           .Redefine("DGen","getVectorFloat_Aux(DGen)") \
           .Redefine("DGenIndex","getVectorFloat_Aux(DGenIndex)") \
           .Redefine("DGennDa","getVectorFloat_Aux(DGennDa)") \
           .Redefine("DGenpt","getVectorFloat_Aux(DGenpt)") \
           .Redefine("DGenphi","getVectorFloat_Aux(DGenphi)") \
           .Redefine("DGeny","getVectorFloat_Aux(DGeny)") \

##from 500001 till the end of dataset, which has around 1M events
d_test = d.Range(500001,0) \
          .Redefine("DPt","getVectorFloat_Aux(DPt)") \
          .Redefine("DRapidity","getVectorFloat_Aux(DRapidity)") \
          .Redefine("DMass","getVectorFloat_Aux(DMass)") \
          .Redefine("DPhi","getVectorFloat_Aux(DPhi)") \
          .Redefine("D2DDecayLength","getVectorFloat_Aux(D2DDecayLength)") \
          .Redefine("DD0Err","getVectorFloat_Aux(DD0Err)") \
          .Redefine("D3DDecayLength","getVectorFloat_Aux(D3DDecayLength)") \
          .Redefine("DDxyzErr","getVectorFloat_Aux(DDxyzErr)") \
          .Redefine("D3DDecayLengthSignificance","getVectorFloat_Aux(D3DDecayLengthSignificance)") \
          .Redefine("D2DDecayLengthSignificance","getVectorFloat_Aux(D2DDecayLengthSignificance)") \
          .Redefine("DVtxProb","getVectorFloat_Aux(DVtxProb)") \
          .Redefine("D3DPointingAngle","getVectorFloat_Aux(D3DPointingAngle)") \
          .Redefine("D2DPointingAngle","getVectorFloat_Aux(D2DPointingAngle)") \
          .Redefine("DDca","getVectorFloat_Aux(DDca)") \
          .Redefine("DImpactParameter3D","getVectorFloat_Aux(DImpactParameter3D)") \
          .Redefine("DImpactParameter3Derror","getVectorFloat_Aux(DImpactParameter3Derror)") \
          .Redefine("DTtrk1Pt","getVectorFloat_Aux(DTtrk1Pt)") \
          .Redefine("DTrk2Pt","getVectorFloat_Aux(DTrk2Pt)") \
          .Redefine("DTrk1PtErr","getVectorFloat_Aux(DTrk1PtErr)") \
          .Redefine("DTrk2PtErr","getVectorFloat_Aux(DTrk2PtErr)") \
          .Redefine("DTrk1Eta","getVectorFloat_Aux(DTrk1Eta)") \
          .Redefine("DTrk2Eta","getVectorFloat_Aux(DTrk2Eta)") \
          .Redefine("DxyDCASignificanceDaugther1","getVectorFloat_Aux(DxyDCASignificanceDaugther1)") \
          .Redefine("DxyDCASignificanceDaugther2","getVectorFloat_Aux(DxyDCASignificanceDaugther2)") \
          .Redefine("DzDCASignificanceDaugther1","getVectorFloat_Aux(DzDCASignificanceDaugther1)") \
          .Redefine("DzDCASignificanceDaugther2","getVectorFloat_Aux(DzDCASignificanceDaugther2)") \
          .Redefine("DTrk1Chi2n","getVectorFloat_Aux(DTrk1Chi2n)") \
          .Redefine("DTrk2Chi2n","getVectorFloat_Aux(DTrk2Chi2n)") \
          .Redefine("DGen","getVectorFloat_Aux(DGen)") \
          .Redefine("DGenIndex","getVectorFloat_Aux(DGenIndex)") \
          .Redefine("DGennDa","getVectorFloat_Aux(DGennDa)") \
          .Redefine("DGenpt","getVectorFloat_Aux(DGenpt)") \
          .Redefine("DGenphi","getVectorFloat_Aux(DGenphi)") \
          .Redefine("DGeny","getVectorFloat_Aux(DGeny)") \

d_train.Snapshot(treeName, outFileNameTrain, {"centrality","PVx","PVy","PVz","DPt","DRapidity","DMass","DPhi","D2DDecayLength","DD0Err","D3DDecayLength","DDxyzErr","D3DDecayLengthSignificance","D2DDecayLengthSignificance","DVtxProb","D3DPointingAngle","D2DPointingAngle","DDca","DImpactParameter3D","DImpactParameter3Derror","DTtrk1Pt","DTrk2Pt","DTrk1PtErr","DTrk2PtErr","DTrk1Eta","DTrk2Eta","DxyDCASignificanceDaugther1","DxyDCASignificanceDaugther2","DzDCASignificanceDaugther1","DzDCASignificanceDaugther2","DTrk1Chi2n","DTrk2Chi2n","DGen","DGenIndex","DGennDa","DGenpt","DGenphi","DGeny"})

d_test.Snapshot(treeName, outFileNameTest, {"centrality","PVx","PVy","PVz","DPt","DRapidity","DMass","DPhi","D2DDecayLength","DD0Err","D3DDecayLength","DDxyzErr","D3DDecayLengthSignificance","D2DDecayLengthSignificance","DVtxProb","D3DPointingAngle","D2DPointingAngle","DDca","DImpactParameter3D","DImpactParameter3Derror","DTtrk1Pt","DTrk2Pt","DTrk1PtErr","DTrk2PtErr","DTrk1Eta","DTrk2Eta","DxyDCASignificanceDaugther1","DxyDCASignificanceDaugther2","DzDCASignificanceDaugther1","DzDCASignificanceDaugther2","DTrk1Chi2n","DTrk2Chi2n","DGen","DGenIndex","DGennDa","DGenpt","DGenphi","DGeny"})

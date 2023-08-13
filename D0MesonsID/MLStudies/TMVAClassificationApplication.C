#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

// RUN: root -l -b -q TMVAClassificationApplication.C\(\"BDT\"\) >& OutPut.txt &

void TMVAClassificationApplication( TString myMethodList = "" )
{
        
    //---------------------------------------------------------------
    // This loads the library
    TMVA::Tools::Instance();
    // Default MVA methods to be trained + tested
    std::map<std::string,int> Use;
    // Cut optimisation
    Use["Cuts"]            = 1;
    Use["CutsD"]           = 1;
    Use["CutsPCA"]         = 0;
    Use["CutsGA"]          = 0;
    Use["CutsSA"]          = 0;
    //
    // 1-dimensional likelihood ("naive Bayes estimator")
    Use["Likelihood"]      = 1;
    Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
    Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
    Use["LikelihoodKDE"]   = 0;
    Use["LikelihoodMIX"]   = 0;
    //
    // Mutidimensional likelihood and Nearest-Neighbour methods
    Use["PDERS"]           = 1;
    Use["PDERSD"]          = 0;
    Use["PDERSPCA"]        = 0;
    Use["PDEFoam"]         = 1;
    Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
    Use["KNN"]             = 1; // k-nearest neighbour method
    //
    // Linear Discriminant Analysis
    Use["LD"]              = 1; // Linear Discriminant identical to Fisher
    Use["Fisher"]          = 0;
    Use["FisherG"]         = 0;
    Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
    Use["HMatrix"]         = 0;
    //
    // Function Discriminant analysis
    Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
    Use["FDA_SA"]          = 0;
    Use["FDA_MC"]          = 0;
    Use["FDA_MT"]          = 0;
    Use["FDA_GAMT"]        = 0;
    Use["FDA_MCMT"]        = 0;
    //
    // Neural Networks (all are feed-forward Multilayer Perceptrons)
    Use["MLP"]             = 0; // Recommended ANN
    Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
    Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
    Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
    Use["TMlpANN"]         = 0; // ROOT's own ANN
    //
    // Support Vector Machine
    Use["SVM"]             = 1;
    //
    // Boosted Decision Trees
    Use["BDT"]             = 1; // uses Adaptive Boost
    Use["BDTG"]            = 0; // uses Gradient Boost
    Use["BDTB"]            = 0; // uses Bagging
    Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
    //
    // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
    Use["RuleFit"]         = 1;
    // ---------------------------------------------------------------
    Use["Plugin"]          = 0;
    Use["Category"]        = 0;
    Use["SVM_Gauss"]       = 0;
    Use["SVM_Poly"]        = 0;
    Use["SVM_Lin"]         = 0;
    std::cout << std::endl;
    std::cout << "==> Start TMVAClassificationApplication" << std::endl;

    // Select methods (don't look at this code - not of interest)
    if (myMethodList != "") {
        for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
        std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
        for (UInt_t i=0; i<mlist.size(); i++) {
            std::string regMethod(mlist[i]);
            if (Use.find(regMethod) == Use.end()) {
                std::cout << "Method \"" << regMethod
                        << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
                for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
                std::cout << it->first << " ";
                }
                std::cout << std::endl;
                return;
            }
            Use[regMethod] = 1;
        }
    }

    // --------------------------------------------------------------------------------------------------
    // Create the Reader object
    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    // Create a set of variables and declare them to the reader
    // - the variable names MUST corresponds in name and type to those given in the weight file(s) used

    Float_t D3DDecayLength, D2DPointingAngle, D3DPointingAngle, D3DDecayLengthSignificance,  DTrk1PtErr, DTrk2PtErr, DVtxProb, DTtrk1Pt, DTrk2Pt,  DTrk1Eta, DTrk2Eta, DxyDCASignificanceDaugther1, DxyDCASignificanceDaugther2, DzDCASignificanceDaugther1, DzDCASignificanceDaugther2;
    reader->AddVariable("D3DDecayLength", &D3DDecayLength);
    reader->AddVariable("D2DPointingAngle", &D2DPointingAngle);
    reader->AddVariable("D3DPointingAngle", &D3DPointingAngle);
    reader->AddVariable("D3DDecayLengthSignificance", &D3DDecayLengthSignificance);
    //reader->AddVariable("DTrk1Chi2n", &DTrk1Chi2n);
    reader->AddVariable("DTrk1PtErr", &DTrk1PtErr);
    reader->AddVariable("DTrk2PtErr", &DTrk2PtErr);
    //reader->AddVariable("DTrk2Chi2n", &DTrk2Chi2n);
    reader->AddVariable("DVtxProb", &DVtxProb);
    
    //reader->AddVariable("DDca", &DDca);
    reader->AddVariable("DTtrk1Pt", &DTtrk1Pt);
    reader->AddVariable("DTrk2Pt", &DTrk2Pt);
    reader->AddVariable("DTrk1Eta", &DTrk1Eta);
    reader->AddVariable("DTrk2Eta", &DTrk2Eta);
    reader->AddVariable("DxyDCASignificanceDaugther1", &DxyDCASignificanceDaugther1);
    reader->AddVariable("DxyDCASignificanceDaugther2", &DxyDCASignificanceDaugther2);
    reader->AddVariable("DzDCASignificanceDaugther1", &DzDCASignificanceDaugther1);
    reader->AddVariable("DzDCASignificanceDaugther2", &DzDCASignificanceDaugther2);

    // Book the MVA methods
    ///TString dir    = "/home/allanfgodoi/Desktop/";

    TString dir    = "/home/guilherme/testes/TCC-HIN-UFRGS/D0MesonsID/MLStudies/dataset_15/weights/";

    TString prefix = "TMVAClassification";

    // Book method(s)
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
        if (it->second) {
            TString methodName = TString(it->first) + TString(" method");
            TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
            reader->BookMVA( methodName, weightfile );
        }
    }

    // Book output histograms
    UInt_t nbin = 100;
    TH1F *histBdt(0);
    if (Use["BDT"])           histBdt     = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -0.8, 0.8 );

    // Prepare input tree (this must be replaced by your data source)
    // in this example, there is a toy tree with signal and one with background events
    // we'll later on use only the "signal" events for the test in this example.
    //
    TFile *input(0);
    //TString fname = "/home/allanfgodoi/Desktop/tree_skim_MC_promptTest.root";

    TString fname = "/home/guilherme/testes/TCC-HIN-UFRGS/D0MesonsID/MLStudies/treeMCprompt.root";

    if (!gSystem->AccessPathName( fname ))
        input = TFile::Open( fname ); // check if file in local directory exists
    else
        input = TFile::Open( "http://root.cern.ch/files/tmva_class_example.root" ); // if not: download from ROOT server
    if (!input) {
        std::cout << "ERROR: could not open data file" << std::endl;
        exit(1);
    }
    std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

    // Event loop
    // Prepare the event tree
    // - Here the variable names have to corresponds to your tree
    // - You can use the same variables as above which is slightly faster,
    //   but of course you can use different ones and copy the values inside the event loop
    //
    std::cout << "--- Select signal+background sample" << std::endl;
    TTree* theTree = (TTree*)input->Get("Dfinder/ntDkpi");

    std::vector<float> * vec_D3DDecayLength = 0;
    std::vector<float> * vec_D2DPointingAngle = 0;
    std::vector<float> * vec_D3DPointingAngle = 0; 
    std::vector<float> * vec_D3DDecayLengthSignificance = 0;
    
    
    //std::vector<float> * vec_DTrk1Chi2n = 0;
    std::vector<float> * vec_DTrk1PtErr = 0;
    //std::vector<float> * vec_DTrk2Chi2n = 0;
    std::vector<float> * vec_DVtxProb = 0;
    
    //std::vector<float> * vec_DDca = 0;
    std::vector<float> * vec_DTtrk1Pt = 0;
    std::vector<float> * vec_DTrk2Pt = 0;
    std::vector<float> * vec_DTrk2PtErr = 0;
    std::vector<float> * vec_DTrk1Eta = 0;
    std::vector<float> * vec_DTrk2Eta = 0;
    std::vector<float> * vec_DxyDCASignificanceDaugther1 = 0;
    std::vector<float> * vec_DxyDCASignificanceDaugther2 = 0;
    std::vector<float> * vec_DzDCASignificanceDaugther1 = 0;
    std::vector<float> * vec_DzDCASignificanceDaugther2 = 0;
    //std::vector<float> * vec_DMass = 0;
    theTree->SetBranchAddress("D3DDecayLength", &vec_D3DDecayLength);

    theTree->SetBranchAddress("D2DPointingAngle", &vec_D2DPointingAngle);
    theTree->SetBranchAddress("D3DPointingAngle", &vec_D3DPointingAngle);
    theTree->SetBranchAddress("D3DDecayLengthSignificance", &vec_D3DDecayLengthSignificance);
    theTree->SetBranchAddress("DTrk1PtErr", &vec_DTrk1PtErr);
    theTree->SetBranchAddress("DTrk2PtErr", &vec_DTrk2PtErr);
    theTree->SetBranchAddress("DVtxProb", &vec_DVtxProb);
    theTree->SetBranchAddress("DTtrk1Pt", &vec_DTtrk1Pt);
    theTree->SetBranchAddress("DTrk2Pt", &vec_DTrk2Pt);
    theTree->SetBranchAddress("DTrk1Eta", &vec_DTrk1Eta);
    theTree->SetBranchAddress("DTrk2Eta", &vec_DTrk2Eta);
    theTree->SetBranchAddress("DxyDCASignificanceDaugther1", &vec_DxyDCASignificanceDaugther1);
    theTree->SetBranchAddress("DxyDCASignificanceDaugther2", &vec_DxyDCASignificanceDaugther2);
    theTree->SetBranchAddress("DzDCASignificanceDaugther1", &vec_DzDCASignificanceDaugther1);
    theTree->SetBranchAddress("DzDCASignificanceDaugther2", &vec_DzDCASignificanceDaugther2);

    //theTree->SetBranchAddress("DMass", &vec_DMass);


    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();
    //this is a loop in the events (each collision)
    std::vector<float> aux_vec_all_trainingVariables;
    for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

        if (ievt%100000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

        theTree->GetEntry(ievt);

	//this is a loop in the D0 meson candidates in a given event
	//NB.: here it can include signal and background 
        for(int iD0=0; iD0<vec_D3DDecayLength->size(); iD0++){

           //use same sequence of variables as in the weight file
           
           if (!TMath::IsNaN((*vec_D3DDecayLength)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_D3DDecayLength)[iD0]);
           if (!TMath::IsNaN((*vec_D2DPointingAngle)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_D2DPointingAngle)[iD0]);
           if (!TMath::IsNaN((*vec_D3DPointingAngle)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_D3DPointingAngle)[iD0]);
           if (!TMath::IsNaN((*vec_D3DDecayLengthSignificance)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_D3DDecayLengthSignificance)[iD0]);
           if (!TMath::IsNaN((*vec_DTrk1PtErr)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DTrk1PtErr)[iD0]);
           if (!TMath::IsNaN((*vec_DTrk2PtErr)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DTrk2PtErr)[iD0]);
           if (!TMath::IsNaN((*vec_DVtxProb)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DVtxProb)[iD0]);
           if (!TMath::IsNaN((*vec_DTtrk1Pt)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DTtrk1Pt)[iD0]);
           if (!TMath::IsNaN((*vec_DTrk2Pt)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DTrk2Pt)[iD0]);
           if (!TMath::IsNaN((*vec_DTrk1Eta)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DTrk1Eta)[iD0]);
           if (!TMath::IsNaN((*vec_DTrk2Eta)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DTrk2Eta)[iD0]);
           if (!TMath::IsNaN((*vec_DxyDCASignificanceDaugther1)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DxyDCASignificanceDaugther1)[iD0]);
           if (!TMath::IsNaN((*vec_DxyDCASignificanceDaugther2)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DxyDCASignificanceDaugther2)[iD0]);
           if (!TMath::IsNaN((*vec_DzDCASignificanceDaugther1)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DzDCASignificanceDaugther1)[iD0]);
           if (!TMath::IsNaN((*vec_DzDCASignificanceDaugther2)[iD0])) aux_vec_all_trainingVariables.push_back((*vec_DzDCASignificanceDaugther2)[iD0]);

           // Return the MVA outputs and fill into histograms
	   // See method here: https://root.cern.ch/root/html608/Reader_8cxx_source.html#l00486
           if (Use["BDT"]) histBdt->Fill(reader->EvaluateMVA(aux_vec_all_trainingVariables,"BDT method"));
           aux_vec_all_trainingVariables.clear(); //clean up the vector to fill next D0 meson information					  
	} 
    }

    // Get elapsed time
    sw.Stop();
    std::cout << "--- End of event loop: "; sw.Print();
    
    // Write histograms
    TFile *target  = new TFile( "TMVApp.root","RECREATE" );
    if (Use["BDT"          ])   histBdt    ->Write();
      
    target->Close();
    std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;
    delete reader;
    std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;
}

int main( int argc, char** argv ) {
    TString methodList;
    for (int i=1; i<argc; i++) {
        TString regMethod(argv[i]);
        if(regMethod=="-b" || regMethod=="--batch") continue;
        if (!methodList.IsNull()) methodList += TString(",");
        methodList += regMethod;
    }
    TMVAClassificationApplication(methodList);
    return 0;
}

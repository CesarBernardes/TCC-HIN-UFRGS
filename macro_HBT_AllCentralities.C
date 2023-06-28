/********************************************************************
 *                  	   Macro HBT All Centralitie	              *
 * 			Aluno:  Thierre F. Conceição
                       Orientador: Dr. Prof. César A. Bernardes     *
 *******************************************************************/
 ///To run it do: root -l -b -q macro_HBT_AllCentralities.C
 
 
/*******************************************************************			        
 *                               INCLUDES                          *  
 *******************************************************************/
#include <iostream>
#include <string>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1D.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TCut.h>
#include <TLegend.h>
#include <TLine.h>
#include "TPolyLine.h"
#include <TGraph.h>


//Intervalo para rejeitar em um ajuste - inicialmente nenhum intervalo é rejeitado
Double_t reject_range_min = 0.0;
Double_t reject_range_max = 0.00001;

//Função exponencial + alcance longo
Double_t func1_exp(Double_t* x, Double_t* par) {
    Double_t v = 0;
    if (reject_range_min < x[0] && x[0] < reject_range_max) {
        TF1::RejectPoint();
    } else {
        v = par[0] * (1 + par[1] * exp(-par[2] * x[0] / 0.1973)) * (1 + par[3] * x[0]);
    }
    return v;
}
//Função gaussiana + alcance longo
Double_t func2_gauss(Double_t* x, Double_t* par) {
    Double_t v = 0;
    if (reject_range_min < x[0] && x[0] < reject_range_max) {
        TF1::RejectPoint();
    } else {
        v = par[0] * (1 + par[1] * exp(-pow(par[2] * x[0] / 0.1973, 2.))) * (1 + par[3] * x[0]);
    }
    return v;
}

//Personalizar Histogramas
void func_hist_custom_qinv(TH1D *h){
   h->GetXaxis()->SetTitle("q_{inv} [GeV]");
   h->GetYaxis()->SetTitle("Number of pairs / bin");
   h->GetXaxis()->CenterTitle(); // Centraliza o título do eixo x
   h->GetYaxis()->CenterTitle(); // Centraliza o título do eixo y

}

void func_hist_custom_sr(TH1D *h){
   h->GetXaxis()->SetTitle("q_{inv} [GeV]");
   h->GetYaxis()->SetTitle("Single Ratio / (0.02 Gev)");
   h->SetLineColor(4); // Define a cor da linha para aul
   h->SetLineWidth(1); // Define a largura da linha para 2 pixels
   h->SetLineStyle(3); // Define o estilo da linha
   h->SetMarkerColor(kBlue); // Define a cor dos marcadores para aul
   h->SetMarkerSize(0.5); // Defina um valor menor que o padrão (geralmente 2)
   h->SetMarkerStyle(4); // Define o estilo dos marcadores para círculos  
   h->SetStats(0);
   
   h->GetXaxis()->CenterTitle(); // Centraliza o título do eixo x
   h->GetYaxis()->CenterTitle(); // Centraliza o título do eixo y

}


//Definir funções de ajuste
void set_fit_func_exp(TF1 *f){
   f->SetParameters(1.0,1.0,4.0,0.0);//Define os valores iniciais dos parâmetros do ajuste. Neste caso, os valores iniciais são 1.0, 1.0, 4.0 e 0.0.
   f->SetParName(0,"Const");
   f->SetParLimits(0,0.0,2.0);//Limites para o ajuste
   f->SetParName(1,"#lambda");
   f->SetParLimits(1,0.0,2.0);
   f->SetParName(2,"R (fm)");
   f->SetParName(3,"#delta");
   f->SetLineColor(kRed);
   f->SetLineWidth(2);
   f->SetLineStyle(1);
   
   
   //Legenda
   TLegend *legend7 = new TLegend(0.6, 0.67, 0.9, 0.83);
   legend7->AddEntry(f, "Fit: Exponential", "l");
   legend7->SetTextSize(0.02);
   legend7->SetBorderSize(0);
   legend7->SetFillColorAlpha(0, 0);
   legend7->Draw();
   
}

void set_fit_func_gauss(TF1 *f){
   f->SetParameters(1.0,1.0,4.0,0.0);//Inicialiar parâmetros
   f->SetParName(0,"Const");
   f->SetParLimits(0,0.0,2.0);//Limites para o ajuste
   f->SetParName(1,"#lambda");
   f->SetParLimits(1,0.0,2.0);
   f->SetParName(2,"R (fm)");
   f->SetParName(3,"#delta");
   f->SetLineColor(kBlack);
   f->SetLineWidth(1);
   f->SetLineStyle(1);

   //Legenda
   TLegend *legend2 = new TLegend(0.6, 0.64, 0.9, 0.74);
   legend2->AddEntry(f, "Fit: Gaussian", "l");
   // Definindo o tamanho da fonte da legenda  
   legend2->SetTextSize(0.02); 
   legend2->SetBorderSize(0);
   legend2->SetFillColorAlpha(0, 0);
   legend2->Draw();
 
 
}

//Função principal
void macro_HBT_AllCentralities(){
// Abrir arquivo ROOT e ler a Tree
auto fileName = "/home/user/root/HiForestAOD_DATA_HBT_withMixing_500k.root"; 

auto outFileName = "HBT_histos_AllCentralities.root"; //arquivo de saída salvando os histogramas, funções de ajuste, etc...

TFile *f = TFile::Open(fileName);//Abre o arquivo ROOT especificado pelo nome do arquivo e atribui o ponteiro TFile a f. Isso permite acessar o conteúdo do arquivo.

TFile *output = new TFile(outFileName,"recreate");//Cria um novo arquivo ROOT de saída com o nome especificado por outFileName. O modo "recreate" indica que se o arquivo já existir, ele será recriado, excluindo qualquer conteúdo anterior.

auto treeName = "demo/HBT";//Define o nome da árvore (tree) que será lida a partir do arquivo ROOT. Neste caso, o nome da árvore é "demo/HBT".

auto t_1 = f->Get<TTree>(treeName);//Obtém a árvore (tree) especificada pelo nome treeName a partir do arquivo ROOT f e atribui o ponteiro TTree a t_1. Isso permite acessar os dados da árvore para análise e processamento posterior.

/******************************************************/
//     Cria diretórios para salvar em formato PDF.
/******************************************************/
std::string folder_name="sig_SS_Corr";
gSystem->Exec(Form("mkdir %s",folder_name.c_str()));

std::string _name="bkg_OS_Corr";
gSystem->Exec(Form("mkdir %s",_name.c_str()));

std::string folder_ ="SS_Over_OS";
gSystem->Exec(Form("mkdir %s",folder_.c_str()));

std::string fol_ ="funcGaussName_sr_SS_Over_OS";
gSystem->Exec(Form("mkdir %s",fol_.c_str()));

std::string f_ ="funcExpName_sr_SS_Over_OS";
gSystem->Exec(Form("mkdir %s",f_.c_str()));

/********************************************************/
/*Essa é uma descrição dos intervalos de centrality e (soma da energia transversa do Forward Hadron) correspondentes, conforme apresentado na Figura 1 do artigo "https://arxiv.org/pdf/1107.4800.pdf". Aqui está a correspondência dos intervalos de centrality e HFsumET mencionados:

0-5% (centrality) -> 3380-5000GeV (HFsumET)
5-10% -> 2770-3380GeV
10-15% -> 2280-2770GeV
15-20% -> 1850-2280GeV
20-25% -> 1500-1850GeV
25-30% -> 1210-1500GeV
30-35% -> 900-1210GeV
35-60% -> 240-900GeV
60-100% -> 0.0-240GeV
Durante a análise, você pode mesclar alguns desses intervalos, por exemplo, 10-20% pode ser mesclado para 1850-2770GeV, já que a mistura foi feita seguindo essa divisão de intervalos. 

35-100% -> 0.0-900GeV

*/
/***********************************************************/

//interval for normalization of qinv distributions
Double_t qinv_min = 0.4001;
Double_t qinv_max = 0.9999;

//Fit range
Double_t fit_qinv_min = 0.02;
Double_t fit_qinv_max = 1.0;//Double_t fit_qinv_max = 0.50;

//Histo nBins and range
Int_t histNbins=50;// 
Float_t histLowerRange=0;
Float_t histUpperRange=1; //maximum is 1, since saved only till this value in the tree to save space

//Declaração de ponteiros para objetos do tipo TH1D e TF1	
const unsigned int nCentBins =10;
TH1D * h_qinv_sig_SS[nCentBins];
TH1D * h_qinv_sig_SS_Corr[nCentBins];
TH1D * h_qinv_bkg_OS[nCentBins];
TH1D * h_qinv_bkg_OS_Corr[nCentBins];
TH1D * h_sr_SS_Over_OS[nCentBins];
TF1  *f_exp_sr_SS_Over_OS[nCentBins];
TF1  *f_gauss_sr_SS_Over_OS[nCentBins];


//definem os intervalos de centrality e os cortes correspondentes na variável HFsumET (soma da energia na região de Forward Hadron Calorimeter).
TString cent_bins[nCentBins]={"0-5%","5-10%","10-15%","15-20%","20-25%","25-30%","30-35%","35-60%","60-100%","35-100%"};
TCut hFsumEtcut[nCentBins]={"HFsumET>3380 && HFsumET<5000","HFsumET>2770 && HFsumET<3380","HFsumET>2280 && HFsumET<2770","HFsumET>1850 && HFsumET<2280","HFsumET>1500 && HFsumET<1850","HFsumET>1210 && HFsumET<1500","HFsumET>900 && HFsumET<1210","HFsumET>240 && HFsumET<900","HFsumET>0 && HFsumET<240","HFsumET>0 && HFsumET<900"};


//Correção da interação Coulombiana
TCut hFsumEtcut_coulombWSS[nCentBins]={"coulombWSS*(HFsumET>3380 && HFsumET<5000)","coulombWSS*(HFsumET>2770 && HFsumET<3380)","coulombWSS*(HFsumET>2280 && HFsumET<2770)","coulombWSS*(HFsumET>1850 && HFsumET<2280)","coulombWSS*(HFsumET>1500 && HFsumET<1850)","coulombWSS*(HFsumET>1210 && HFsumET<1500)","coulombWSS*(HFsumET>900 && HFsumET<1210)","coulombWSS*(HFsumET>240 && HFsumET<900)","coulombWSS*(HFsumET>0 && HFsumET<240)","coulombWSS*(HFsumET>0 && HFsumET<900)"};
TCut hFsumEtcut_coulombWOS[nCentBins]={"coulombWOS*(HFsumET>3380 && HFsumET<5000)","coulombWOS*(HFsumET>2770 && HFsumET<3380)","coulombWOS*(HFsumET>2280 && HFsumET<2770)","coulombWOS*(HFsumET>1850 && HFsumET<2280)","coulombWOS*(HFsumET>1500 && HFsumET<1850)","coulombWOS*(HFsumET>1210 && HFsumET<1500)","coulombWOS*(HFsumET>900 && HFsumET<1210)","coulombWOS*(HFsumET>240 && HFsumET<900)","coulombWOS*(HFsumET>0 && HFsumET<240)","coulombWOS*(HFsumET>0 && HFsumET<900)"};

//Armazenam os nomes dos histogramas que serão criados para cada classe de centrality.
std::string histName_sig_SS[nCentBins]={"hqinvSigSS_0to5","hqinvSigSS_5to10","hqinvSigSS_10to15","hqinvSigSS_15to20","hqinvSigSS_20to25","hqinvSigSS_25to30","hqinvSigSS_30to35","hqinvSigSS_35to60","hqinvSigSS_60to100","hqinvSigSS_35to100"};
std::string histName_bkg_OS[nCentBins]={"hqinvBkgOS_0to5","hqinvBkgOS_5to10","hqinvBkgOS_10to15","hqinvBkgOS_15to20","hqinvBkgOS_20to25","hqinvBkgOS_25to30","hqinvBkgOS_30to35","hqinvBkgOS_35to60","hqinvBkgOS_60to100","hqinvBkgOS_35to100"};
std::string histName_sig_SS_Corr[nCentBins]={"hqinvSigSS_Corr_0to5","hqinvSigSS_Corr_5to10","hqinvSigSS_Corr_10to15","hqinvSigSS_Corr_15to20","hqinvSigSS_Corr_20to25","hqinvSigSS_Corr_25to30","hqinvSigSS_Corr_30to35","hqinvSigSS_Corr_35to60","hqinvSigSS_Corr_60to100","hqinvSigSS_Corr_35to100"};
std::string histName_bkg_OS_Corr[nCentBins]={"hqinvBkgOS_Corr_0to5","hqinvBkgOS_Corr_5to10","hqinvBkgOS_Corr_10to15","hqinvBkgOS_Corr_15to20","hqinvBkgOS_Corr_20to25","hqinvBkgOS_Corr_25to30","hqinvBkgOS_Corr_30to35","hqinvBkgOS_Corr_35to60","hqinvBkgOS_Corr_60to100","hqinvBkgOS_Corr_35to100"};


//Armazenam os títulos dos histogramas para cada classe de centrality.
TString histTitle_sig_SS[nCentBins]={"q_{inv} SameEvt SS tracks, 0-5%","q_{inv} SameEvt SS tracks, 5-10%","q_{inv} SameEvt SS tracks, 10-15%","q_{inv} SameEvt SS tracks, 15-20%","q_{inv} SameEvt SS tracks, 20-25%","q_{inv} SameEvt SS tracks, 25-30%","q_{inv} SameEvt SS tracks, 30-35%","q_{inv} SameEvt SS tracks, 35-60%","q_{inv} SameEvt SS tracks, 60-100%","q_{inv} SameEvt SS tracks, 35-100%"};

TString histTitle_bkg_OS[nCentBins]={"q_{inv} OpposiSig OS tracks, 0-5%","q_{inv} OpposiSig OS tracks, 5-10%","q_{inv} OpposiSig OS tracks, 10-15%","q_{inv} OpposiSig OS tracks, 15-20%","q_{inv} OpposiSig OS tracks, 20-25%","q_{inv} OpposiSig OS tracks, 25-30%","q_{inv} OpposiSig OS tracks, 30-35%","q_{inv} OpposiSig OS tracks, 35-60%","q_{inv} OpposiSig OS tracks, 60-100%","q_{inv} OpposiSig OS tracks, 35-100%"};

TString histTitle_sig_SS_Corr[nCentBins]={"q_{inv} SameEvt SS_Corr tracks, 0-5%","q_{inv} SameEvt SS_Corr tracks, 5-10%","q_{inv} SameEvt SS_Corr tracks, 10-15%","q_{inv} SameEvt SS_Corr tracks, 15-20%","q_{inv} SameEvt SS_Corr tracks, 20-25%","q_{inv} SameEvt SS_Corr tracks, 25-30%","q_{inv} SameEvt SS_Corr tracks, 30-35%","q_{inv} SameEvt SS_Corr tracks, 35-60%","q_{inv} SameEvt SS_Corr tracks, 60-100%","q_{inv} SameEvt SS_Corr tracks, 35-100%"};

TString histTitle_bkg_OS_Corr[nCentBins]={"q_{inv} OpposiSig OS_Corr tracks, 0-5%","q_{inv} OpposiSig OS_Corr tracks, 5-10%","q_{inv} OpposiSig OS_Corr tracks, 10-15%","q_{inv} OpposiSig OS_Corr tracks, 15-20%","q_{inv} OpposiSig OS_Corr tracks, 20-25%","q_{inv} OpposiSig OS_Corr tracks, 25-30%","q_{inv} OpposiSig OS_Corr tracks, 30-35%","q_{inv} OpposiSig OS_Corr tracks, 35-60%","q_{inv} OpposiSig OS_Corr tracks, 60-100%","q_{inv} OpposiSig OS_Corr tracks, 35-100%"};

std::string histName_sr_SS_Over_OS[nCentBins]={"hsrSSoverOS_0to5","hsrSSoverOS_5to10","hsrSSoverOS_10to15","hsrSSoverOS_15to20","hsrSSoverOS_20to25","hsrSSoverOS_25to30","hsrSSoverOS_30to35","hsrSSoverOS_35to60","hsrSSoverOS_60to100","hsrSSoverOS_35to100"};
TString histTitle_sr_SS_Over_OS[nCentBins]={"Centrality: 0-5%","Centrality: 5-10%","Centrality: 10-15%","Centrality: 15-20%","Centrality: 20-25%","Centrality: 25-30%","Centrality: 30-35%","Centrality: 35-60%","Centrality: 60-100%","Centrality: 35-100%"};


TString funcExpName_sr_SS_Over_OS[nCentBins]={"fExpSrSSoverOS_0to5","fExpSrSSoverOS_5to10","fExpSrSSoverOS_10to15","fExpSrSSoverOS_15to20","fExpSrSSoverOS_20to25","fExpSrSSoverOS_25to30","fExpSrSSoverOS_30to35","fExpSrSSoverOS_35to60","fExpSrSSoverOS_60to100","fExpSrSSoverOS_35to100"};
TString funcGaussName_sr_SS_Over_OS[nCentBins]={"fGaussSrSSoverOS_0to5","fGaussSrSSoverOS_5to10","fGaussSrSSoverOS_10to15","fGaussSrSSoverOS_15to20","fGaussSrSSoverOS_20to25","fGaussSrSSoverOS_25to30","fGaussSrSSoverOS_30to35","fGaussSrSSoverOS_35to60","fGaussSrSSoverOS_60to100","fGaussSrSSoverOS_35to100"};

///Canvas will be updated on-the-fly
auto c = new TCanvas("c", "c", 500, 500);
c->cd();

//Loop in all  bins - do everything: create histos, single ratios and fits
for(unsigned int i_centbin=0; i_centbin<nCentBins; i_centbin++){

//Estão sendo criados objetos histograma e funções ajuste para cada classe de centralidade

   h_qinv_sig_SS[i_centbin] = new TH1D((TString)histName_sig_SS[i_centbin],"",histNbins,histLowerRange,histUpperRange);
   h_qinv_sig_SS_Corr[i_centbin] = new TH1D((TString)histName_sig_SS_Corr[i_centbin],"",histNbins,histLowerRange,histUpperRange);
   
   h_qinv_bkg_OS[i_centbin] = new TH1D((TString)histName_bkg_OS[i_centbin],"",histNbins,histLowerRange,histUpperRange);
   h_qinv_bkg_OS_Corr[i_centbin] = new TH1D((TString)histName_bkg_OS_Corr[i_centbin],"",histNbins,histLowerRange,histUpperRange);
   
   h_sr_SS_Over_OS[i_centbin] = new TH1D((TString)histName_sr_SS_Over_OS[i_centbin],"",histNbins,histLowerRange,histUpperRange);
   
   f_exp_sr_SS_Over_OS[i_centbin] = new TF1(funcExpName_sr_SS_Over_OS[i_centbin],func1_exp,fit_qinv_min,fit_qinv_max,4);  
   f_gauss_sr_SS_Over_OS[i_centbin] = new
    TF1(funcGaussName_sr_SS_Over_OS[i_centbin],func2_gauss,fit_qinv_min,fit_qinv_max,4);
   

/****************Preenchimento dos histogramas*********************/
/***************************************************************** 
 *                     q_inv distributions                       *
 *****************************************************************/ 
   t_1->Draw(Form("qinvSigSS>>%s",histName_sig_SS[i_centbin].c_str()),hFsumEtcut[i_centbin],"goff");
   func_hist_custom_qinv(h_qinv_sig_SS[i_centbin]);
   h_qinv_sig_SS[i_centbin]->Write();
   h_qinv_sig_SS[i_centbin]->Draw();
   h_qinv_sig_SS[i_centbin]->SetLineColor(kRed);
   h_qinv_sig_SS[i_centbin]->SetLineWidth(2); 
   h_qinv_sig_SS[i_centbin]->SetLineStyle(7); // Define o estilo da linha
   h_qinv_sig_SS[i_centbin]->SetStats(0);
   //c->Update(); 

   t_1->Draw(Form("qinvSigSS>>%s",histName_sig_SS_Corr[i_centbin].c_str()),hFsumEtcut_coulombWSS[i_centbin],"goff");
   func_hist_custom_qinv(h_qinv_sig_SS_Corr[i_centbin]);
   h_qinv_sig_SS_Corr[i_centbin]->Write();
   h_qinv_sig_SS_Corr[i_centbin]->Draw("same");
   
      //Marcadores dos eixos  x e y
   c->SetTickx(); 
   c->SetTicky();
   
   h_qinv_sig_SS_Corr[i_centbin]->SetLineColor(kBlack);
   h_qinv_sig_SS_Corr[i_centbin]->SetLineWidth(2); 
   //h_qinv_sig_SS_Corr[i_centbin]->SetMarkerColor(kBlack);
   h_qinv_sig_SS_Corr[i_centbin]->SetStats(0);
   gPad->SetLogy(1);

   
   TLatex *text4 = new TLatex();
   text4->SetNDC();
   text4->SetTextColor(kBlack);
   text4->SetTextFont(42);
   text4->SetTextSize(0.02);
   text4->DrawLatex(0.15, 0.78, histTitle_sr_SS_Over_OS[i_centbin]);

   
   //Cria texto dentro do gráfico - lado superior esquerdo
   TLatex *text3 = new TLatex();
   text3->SetNDC();
   text3->SetTextColor(kBlack);
   text3->SetTextFont(62);  // Define a fonte do texto (opcional)
   text3->SetTextSize(0.025);  // Define o tamanho do texto (opcional)
   text3->DrawLatex(0.15, 0.82, "CMS Open Data PbPb #sqrt{s_{NN}} = 2.76 TeV");

   
   //Cria texto dentro do gráfico - lado superior esquerdo
   TLatex *text7 = new TLatex();
   text7->SetNDC();
   text7->SetTextColor(kBlack);
   text7->SetTextFont(62);  // Define a fonte do texto (opcional)
   text7->SetTextSize(0.02);  // Define o tamanho do texto (opcional)
   //text7->DrawLatex(0.52, 0.92, "q_{inv} Same Event: Same Sign(SS_{++,--})");
   text7->DrawLatex(0.53, 0.91, "Method: Pairs of opposite charges(SS_{++,--})");
   

   //Legenda
   TLegend *legend3 = new TLegend(0.6, 0.65, 0.9, 0.85);
   //legend3->AddEntry(h_qinv_sig_SS[i_centbin], "Without Coulomb correction", "l");
   legend3->AddEntry(h_qinv_sig_SS[i_centbin], "Uncorrected - Coulomb", "l");
   // Definindo o tamanho da fonte da legenda  
   legend3->SetTextSize(0.02); 
   legend3->SetBorderSize(0);
   legend3->SetFillColorAlpha(0, 0);
   legend3->Draw();
   
   
   //Legenda
   TLegend *legend4 = new TLegend(0.6, 0.62, 0.9, 0.78);
   legend4->AddEntry(h_qinv_sig_SS_Corr[i_centbin], "Corrected - Coulomb", "l");
   // Definindo o tamanho da fonte da legenda  
   legend4->SetTextSize(0.02); 
   legend4->SetBorderSize(0);
   legend4->SetFillColorAlpha(0, 0);
   legend4->Draw();
   

/****************************************************************/    
   c->SaveAs(Form("%s/%s_%s.pdf",folder_name.c_str(),histName_sig_SS[i_centbin].c_str(),histName_sig_SS_Corr[i_centbin].c_str()));
   c->Update();
   
/**************************************************************/

   t_1->Draw(Form("qinvSigOS>>%s",histName_bkg_OS[i_centbin].c_str()),hFsumEtcut[i_centbin],"goff"); //I use "qinvSigOS" but this was not a proper name saved in the tree...should be BkgOS
   func_hist_custom_qinv(h_qinv_bkg_OS[i_centbin]);
   h_qinv_bkg_OS[i_centbin]->Write();
   h_qinv_bkg_OS[i_centbin]->Draw();
   
   //Marcadores dos eixos  x e y
   c->SetTickx(); 
   c->SetTicky();
   
   h_qinv_bkg_OS[i_centbin]->SetLineColor(kRed);
   h_qinv_bkg_OS[i_centbin]->SetLineStyle(7); // Define o estilo da linha
   h_qinv_bkg_OS[i_centbin]->SetLineWidth(2); 
   h_qinv_bkg_OS[i_centbin]->SetStats(0);
   //c->Update();
  
   t_1->Draw(Form("qinvSigOS>>%s",histName_bkg_OS_Corr[i_centbin].c_str()),hFsumEtcut_coulombWOS[i_centbin],"goff"); //I use "qinvSigOS" but this was not a proper name saved in the tree...should be BkgOS
   func_hist_custom_qinv(h_qinv_bkg_OS_Corr[i_centbin]);
   h_qinv_bkg_OS_Corr[i_centbin]->Write();
   h_qinv_bkg_OS_Corr[i_centbin]->Draw("same");
   h_qinv_bkg_OS_Corr[i_centbin]->SetLineColor(kBlack);
   h_qinv_bkg_OS_Corr[i_centbin]->SetLineWidth(2); 
   //h_qinv_bkg_OS_Corr[i_centbin]->SetMarkerColor(2);
   h_qinv_bkg_OS_Corr[i_centbin]->SetStats(0);
   gPad->SetLogy(1);
   
   
   TLatex *text6 = new TLatex();
   text6->SetNDC();
   text6->SetTextColor(kBlack);
   text6->SetTextFont(42);
   text6->SetTextSize(0.02);
   text6->DrawLatex(0.15, 0.78,histTitle_sr_SS_Over_OS[i_centbin]);
   
   
  
    //Cria texto dentro do gráfico - lado superior esquerdo
   TLatex *text5 = new TLatex();
   text5->SetNDC();
   text5->SetTextColor(kBlack);
   text5->SetTextFont(62);  // Define a fonte do texto (opcional)
   text5->SetTextSize(0.025);  // Define o tamanho do texto (opcional)
   text5->DrawLatex(0.15, 0.82, "CMS Open Data PbPb #sqrt{s_{NN}} = 2.76 TeV");
   //text5->DrawLatex(0.15, 0.92, " q_{inv} Same Event(OS_{+-}) track");
   //text5->DrawLatex(0.55, 0.91, "Method: Opposite Sign(OS_{+-})");

   
   
     //Cria texto dentro do gráfico - lado superior esquerdo
   TLatex *text8 = new TLatex();
   text8->SetNDC();
   text8->SetTextColor(kBlack);
   text8->SetTextFont(62);  // Define a fonte do texto (opcional)
   text8->SetTextSize(0.02);  // Define o tamanho do texto (opcional)
   //text8->DrawLatex(0.55, 0.91, "Method: Opposite Sign(OS_{+-})");
   //text8->DrawLatex(0.52, 0.91, "Method: Pairs of opposite charges");
   text8->DrawLatex(0.53, 0.91, "Method: Pairs of opposite charges(OS_{+-})");   


    //Legenda
   TLegend *legend5 = new TLegend(0.6, 0.65, 0.9, 0.85);
   legend5->AddEntry(h_qinv_bkg_OS[i_centbin], "Uncorrected - Coulomb", "l");
   // Definindo o tamanho da fonte da legenda  
   legend5->SetTextSize(0.02); 
   legend5->SetBorderSize(0);
   legend5->SetFillColorAlpha(0, 0);
   legend5->Draw();
   
   
    //Legenda
   TLegend *legend6 = new TLegend(0.6, 0.62, 0.9, 0.78);
   legend6->AddEntry(h_qinv_bkg_OS_Corr[i_centbin], "Corrected - Coulomb", "l");
   // Definindo o tamanho da fonte da legenda  
   legend6->SetTextSize(0.02); 
   legend6->SetBorderSize(0);
   legend6->SetFillColorAlpha(0, 0);
   legend6->Draw();
   
  
   c->SaveAs(Form("%s/%s_%s.pdf",_name.c_str(),histName_bkg_OS[i_centbin].c_str(),histName_bkg_OS_Corr[i_centbin].c_str()));
   c->Update();   
    
   
   
/***************************************************************** 
 *                     SINGLE RATIO                              *
 *****************************************************************/   
   Int_t bin_for_normInt_min = h_qinv_sig_SS_Corr[i_centbin]->GetXaxis()->FindBin(qinv_min); //interval for normalization of qinv distributions
   Int_t bin_for_normInt_max = h_qinv_sig_SS_Corr[i_centbin]->GetXaxis()->FindBin(qinv_max);
   
   //Não entendi essa parte, posso apagar depois.
   Int_t bin_for_normInt_min_bkg = h_qinv_bkg_OS_Corr[i_centbin]->GetXaxis()->FindBin(qinv_min); //interval for normalization of qinv distributions
   Int_t bin_for_normInt_max_bkg = h_qinv_bkg_OS_Corr[i_centbin]->GetXaxis()->FindBin(qinv_max);
   
  
   Double_t int_num_controlRegion = h_qinv_sig_SS_Corr[i_centbin]->Integral(bin_for_normInt_min,bin_for_normInt_max); 
   Double_t int_den_controlRegion = h_qinv_bkg_OS_Corr[i_centbin]->Integral(bin_for_normInt_min,bin_for_normInt_max);
   
  //h_qinv_sig_SS_Corr[i_centbin]->Sumw2();
  //h_qinv_bkg_OS_Corr[i_centbin]->Sumw2();

   h_sr_SS_Over_OS[i_centbin]->Divide(h_qinv_sig_SS_Corr[i_centbin],h_qinv_bkg_OS_Corr[i_centbin],int_num_controlRegion,int_den_controlRegion); 
   
   func_hist_custom_sr(h_sr_SS_Over_OS[i_centbin]);
   h_sr_SS_Over_OS[i_centbin]->Write();
   // Desenhe o histograma no TCanvas
   h_sr_SS_Over_OS[i_centbin]->Draw();
   
   // Desativa a escala logarítmica no eixo y
   gPad->SetLogy(0);
   
/**********************************************************/   
   
   //Marcadores dos eixos  x e y
   c->SetTickx(); 
   c->SetTicky();

   //Legenda
   TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9);
   legend->AddEntry(h_sr_SS_Over_OS[i_centbin], "Data", "p");
   // Definindo o tamanho da fonte da legenda  
   legend->SetTextSize(0.02); 
   legend->SetBorderSize(0);
   legend->SetFillColorAlpha(0, 0);
   legend->Draw();
   
  
    //Cria texto dentro do gráfico - lado superior esquerdo
   TLatex *text = new TLatex();
   text->SetNDC();
   text->SetTextColor(kBlack);
   text->SetTextFont(62);  // Define a fonte do texto (opcional)
   text->SetTextSize(0.025);  // Define o tamanho do texto (opcional)
   text->DrawLatex(0.15, 0.82, "CMS Open Data PbPb #sqrt{s_{NN}} = 2.76 TeV");


   TLatex *text2 = new TLatex();
   text2->SetNDC();
   text2->SetTextColor(kBlack);
   text2->SetTextFont(42);
   text2->SetTextSize(0.02);
   text2->DrawLatex(0.15, 0.78, histTitle_sr_SS_Over_OS[i_centbin]);
   
   
   
    //Cria texto dentro do gráfico - lado superior esquerdo
   TLatex *text9 = new TLatex();
   text9->SetNDC();
   text9->SetTextColor(kBlack);
   text9->SetTextFont(62);  // Define a fonte do texto (opcional)
   text9->SetTextSize(0.02);  // Define o tamanho do texto (opcional)
   text9->DrawLatex(0.48, 0.91, "Method: Pairs of opposite charges(SS_{++,--}/OS_{+-})");


   //Cria uma linha reta em y = 1
   TLine *line = new TLine(c->GetUxmin(), 1, c->GetUxmax(), 1);
   line->SetLineColor(kBlack); // Define a cor da linha (opcional)
   line->SetLineStyle(2); // Define o estilo da linha (opcional)
   line->Draw();
/*************************************************************/   
   //Salve o TCanvas como um arquivo PDF
   c->SaveAs(Form("%s/%s.pdf",folder_.c_str(),histName_sr_SS_Over_OS[i_centbin].c_str()));
   // Atualize o TCanvas
   c->Update();
   
/*******************AJUSTES(Fitting)********************************/                         
/*******************************************************************/       
//Exponencial
/*******************************************************************/   
   set_fit_func_exp(f_exp_sr_SS_Over_OS[i_centbin]);
   TFitResultPtr res_exp_sr_SSoverOS;
   ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
   h_sr_SS_Over_OS[i_centbin]->Fit(f_exp_sr_SS_Over_OS[i_centbin], "S R Q N");
   h_sr_SS_Over_OS[i_centbin]->Fit(f_exp_sr_SS_Over_OS[i_centbin], "S R Q N");
   res_exp_sr_SSoverOS = h_sr_SS_Over_OS[i_centbin]->Fit(f_exp_sr_SS_Over_OS[i_centbin], "S R M");
   f_exp_sr_SS_Over_OS[i_centbin]->Write();
   f_exp_sr_SS_Over_OS[i_centbin]->Draw("same");
  
   // Salve o TCanvas como um arquivo PDF
    c->SaveAs(Form("%s/%s.pdf", f_.c_str(), f_exp_sr_SS_Over_OS[i_centbin]->GetName()));
   // Atualize o TCanvas
  c->Update();
/*******************************************************************/      
//Gaussian
/*******************************************************************/   
 
   set_fit_func_gauss(f_gauss_sr_SS_Over_OS[i_centbin]);
   TFitResultPtr res_gauss_sr_SSoverOS;
   ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
   h_sr_SS_Over_OS[i_centbin]->Fit(f_gauss_sr_SS_Over_OS[i_centbin], "S R Q N");
   h_sr_SS_Over_OS[i_centbin]->Fit(f_gauss_sr_SS_Over_OS[i_centbin], "S R Q N"); 
   res_gauss_sr_SSoverOS = h_sr_SS_Over_OS[i_centbin]->Fit(f_gauss_sr_SS_Over_OS[i_centbin], "S R M"); 
   f_gauss_sr_SS_Over_OS[i_centbin]->Write();
   f_gauss_sr_SS_Over_OS[i_centbin]->Draw("same");
   //Salve o TCanvas como um arquivo PDF
   c->SaveAs(Form("%s/%s.pdf", fol_.c_str(), f_gauss_sr_SS_Over_OS[i_centbin]->GetName()));
   // Atualize o TCanvas
   c->Update(); 
   

}//end for loop in centrality bins	

}



/***********************************************************************************   
DEfinicao de dividir dois argumentos: https://root.cern.ch/doc/master/classTH1.html#a4ef2329285beb6091515b836e160bd9f
************************************************************************************/

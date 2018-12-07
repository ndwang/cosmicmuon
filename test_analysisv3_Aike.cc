/*
This script is the framework for you to start your analysis. I have written enough for you to access
data from each event (Muon passing through/stopping in the detector) individually. With the data organized
this way, you can make decisions about individual events and apply them to the entire data set. Feel free
to make this analysis code as complex as you need it to be. Write functions so you can think about things
more abstractly, maybe make your detector layers into classes and give them attributes and functions.
*/



#include <string>
#include "TFile.h"
#include "TTree.h"
#include <TCanvas.h>
#include <fstream>
#include <map>
#include <queue>
#include <iostream>       // std::cout
#include <deque>          // std::deque
#include <list>
#include <cmath>
using namespace std;




void test_analysisv3_Aike(){
	//initialization
	TFile *f=new TFile("MuonData15.11-04.12.2018.root"); // Opens the root file
	TTree *tr=(TTree*)f->Get("tree"); // Pulls the tree from the file into memory so we can work with it
	TCanvas *result=new TCanvas("result","Up-Down");
	result->Clear();



	TH1F* h_u1 = new TH1F("h_u1","Up", 80,0,8);
	TH1F* h_d1 = new TH1F("h_d1","Down",80,0,8);
  TH1F* h_diff1 = new TH1F("h_diff1","Diff", 80,0,8);
	TH1F* h_u2 = new TH1F("h_u2","Up", 80,0,8);
	TH1F* h_d2 = new TH1F("h_d2","Down",80,0,8);
  TH1F* h_diff2 = new TH1F("h_diff2","Diff", 80,0,8);
	TH1F* h_u3 = new TH1F("h_u3","Up", 80,0,8);
	TH1F* h_d3 = new TH1F("h_d3","Down",80,0,8);
  TH1F* h_diff3 = new TH1F("h_diff3","Diff", 80,0,8);
	TH1F* h_u4 = new TH1F("h_u4","Up", 80,0,8);
	TH1F* h_d4 = new TH1F("h_d4","Down",80,0,8);
  TH1F* h_diff4 = new TH1F("h_diff4","Diff", 80,0,8);

//for (int event=0,event<tr->GetEntries();event++){

	// These floats correspond to each PMT. You'll use these to hold
	Short_t W01,W02,W03,W04,W05,W06,W07,W08,W09,W10,W11,W12,W13,W14;
	Short_t E01,E02,E03,E04,E05,E06,E07,E08,E09,E10,E11,E12,E13,E14;
	Short_t STDC_W03,STDC_W04,STDC_W05,STDC_W06,STDC_W07,STDC_W08,STDC_W09,STDC_W10,STDC_W11,STDC_W12;
	Short_t STDC_E03,STDC_E04,STDC_E05,STDC_E06,STDC_E07,STDC_E08,STDC_E09,STDC_E10,STDC_E11,STDC_E12;
	Short_t STDC_8_SUM;

/////////////////////////////////////////
// This section grabs the data from the branches in your root file
// and assigns them to a variable (change &a to the relevant PMT
// or however you prefer to refer to your inputs)
/////////////////////////////////////////
	tr->SetBranchAddress("ADC_1_0",&E03);
	tr->SetBranchAddress("ADC_1_1",&W03);
	tr->SetBranchAddress("ADC_1_2",&E04);
	tr->SetBranchAddress("ADC_1_3",&W04);
	tr->SetBranchAddress("ADC_1_4",&E05);
	tr->SetBranchAddress("ADC_1_5",&W05);
	tr->SetBranchAddress("ADC_1_6",&E06);
	tr->SetBranchAddress("ADC_1_7",&W06);
	tr->SetBranchAddress("ADC_1_8",&E07);
	tr->SetBranchAddress("ADC_1_9",&W07);
	tr->SetBranchAddress("ADC_1_10",&E08);
	tr->SetBranchAddress("ADC_1_11",&W08);
	tr->SetBranchAddress("ADC_2_0",&E09);
	tr->SetBranchAddress("ADC_2_1",&W09);
	tr->SetBranchAddress("ADC_2_2",&E10);
	tr->SetBranchAddress("ADC_2_3",&W10);
	tr->SetBranchAddress("ADC_2_4",&E11);
	tr->SetBranchAddress("ADC_2_5",&W11);
	tr->SetBranchAddress("ADC_2_6",&E12);
	tr->SetBranchAddress("ADC_2_7",&W12);
	//tr->SetBranchAddress("ADC_2_9",&E12);
	//tr->SetBranchAddress("ADC_2_8",&E11);
	//tr->SetBranchAddress("ADC_2_10",&E11);
	//tr->SetBranchAddress("ADC_2_11",&E12);

	tr->SetBranchAddress("STDC_8_0",&STDC_W03);
	tr->SetBranchAddress("STDC_8_1",&STDC_W04);
	tr->SetBranchAddress("STDC_8_2",&STDC_W05);
	tr->SetBranchAddress("STDC_8_3",&STDC_W06);
	tr->SetBranchAddress("STDC_8_4",&STDC_W07);
	tr->SetBranchAddress("STDC_8_5",&STDC_W08);
	tr->SetBranchAddress("STDC_8_6",&STDC_W09);
	tr->SetBranchAddress("STDC_8_7",&STDC_W10);
	tr->SetBranchAddress("STDC_8_8",&STDC_W11);
	tr->SetBranchAddress("STDC_8_9",&STDC_W12);
	// tr->SetBranchAddress("STDC_8_10",&STDC_E03);
	// tr->SetBranchAddress("STDC_8_11",&STDC_E04);
	// tr->SetBranchAddress("STDC_8_12",&STDC_E05);
	// tr->SetBranchAddress("STDC_8_13",&STDC_E06);
	// tr->SetBranchAddress("STDC_8_14",&STDC_E07);
	// tr->SetBranchAddress("STDC_8_15",&STDC_E08);
	// tr->SetBranchAddress("STDC_8_SUM",&STDC_8_SUM);
	//
	//
	// tr->SetBranchAddress("FTDC_9_0",&FTDC_9_0);
	// tr->SetBranchAddress("FTDC_9_1",&FTDC_9_1);
	// tr->SetBranchAddress("FTDC_9_2",&FTDC_9_2);
	// tr->SetBranchAddress("FTDC_9_3",&FTDC_9_3);
	// tr->SetBranchAddress("FTDC_9_4",&FTDC_9_4);
	// tr->SetBranchAddress("FTDC_9_5",&FTDC_9_5);
	// tr->SetBranchAddress("FTDC_9_6",&FTDC_9_6);
	// tr->SetBranchAddress("FTDC_9_7",&FTDC_9_7);


  cout<<tr->GetEntries()<<endl;
  for (int i=0;i<tr->GetEntries();i++){
    tr->GetEntry(i);

  //Indentify the last layer the muon passed through as layer_pass.
  //Muon decays between layer_pass and layer_pass+1
  //Discard events that dacays before the first layer or pass through the fifth layer
    Short_t Layer1=E03+E04+W03+W04;
    Short_t Layer2=E05+E06+W05+W06;
    Short_t Layer3=E07+E08+W07+W08;
    Short_t Layer4=E09+E10+W09+W10;
    Short_t Layer5=E11+E12+W11+W12;


    Short_t layer_pass = 0;

		//lower bound on muon energy to remove unphysical peak near 0
    if((W03 > 160 && E03 > 70) ||(W04 > 200 && E04 > 220)){
      layer_pass = 1;
    }
    if( ((W05 > 285 && E05 > 47) ||(W06 > 45 && E06 > 70))){
      if(layer_pass==1){
      layer_pass = 2;}
      else{layer_pass = 0;}
    }
    if(((W07 > 276 && E07 > 50) ||(W08 > 100 && E08 > 100))){
      if(layer_pass==2){
      layer_pass = 3;}
      else{layer_pass = 0;}
    }
    if( ((W09 > 224 && E09 > 68) ||(W10 > 73 && E10 > 81))){
      if(layer_pass==3){
      layer_pass = 4;}
      else{layer_pass = 0;}
    }
     if(((W11 > 45 && E11 > 45) ||(W12 > 88 && E12 > 36))){
      if(layer_pass==4){
      layer_pass = 5;}
      else{layer_pass = 0;}
    }


  //Indentify the layer of electron hits
  //Reject events with more than one hit or no hit
    int layer_hit=0;
    double uptime=0;
    double downtime=0;
    int countu = 0;
		int countd = 0;
    int hit_time[10]={STDC_W03,STDC_W04,STDC_W05,STDC_W06,STDC_W07,STDC_W08,STDC_W09,STDC_W10,STDC_W11,STDC_W12};
		//take average of up/down time
    for(int i = 1; i <= 4; ++i){
      if(i == layer_pass){
        for(int j = 2*i-1; j >= 0; j--){
					if (j==0 || j==1)
						continue;
          if(hit_time[j] < 4000 && hit_time[j] > 2){
            uptime += hit_time[j];
						countu++;
          }
        }
        for(int j = 2*i; j<=9; j++){
					if (j==0 || j==1)
						continue;
          if(hit_time[j] < 4000 && hit_time[j] > 2){
            downtime += hit_time[j];
						countd++;
          }
        }
      }
    }

		uptime /= countu;
		downtime /= countd;
		//uptime>100 && downtime<1 &&
    if( layer_pass != 5 && layer_pass != 0){
			switch (layer_pass) {
				case 1:	h_u1->Fill(2.0/1000*uptime);
				case 2: h_u2->Fill(2.0/1000*uptime);
				case 3: h_u3->Fill(2.0/1000*uptime);
				case 4: h_u4->Fill(2.0/1000*uptime);
			}
    }
		//downtime>100&&uptime<1  &&
		if( layer_pass != 5 && layer_pass != 0){
			switch (layer_pass) {
				case 1:	h_d1->Fill(2.0/1000*downtime);
				case 2: h_d2->Fill(2.0/1000*downtime);
				case 3: h_d3->Fill(2.0/1000*downtime);
				case 4: h_d4->Fill(2.0/1000*downtime);
			}
    }

  }

////////////////////////////////////////
//This section analyze and plot data
////////////////////////////////////////
	//rescale h_d
   // Double_t nu = h_u3->GetEntries();
   // Double_t nd = h_d3->GetEntries();
   // h_u3 -> Scale(nd/nu);
	 // nu = h_u2->GetEntries();
   // nd = h_d2->GetEntries();
   // h_u2 -> Scale(nd/nu);


	//fitting function for h_u and h_d
  TF1 *myfit = new TF1("myfit","[0]*exp(-x/[1])+[2]", 0, 8);
  myfit->SetParameter(0,100);
  myfit->SetParameter(1,2); //[1] estimates muon lifetime
  myfit->SetParameter(2,0);

	//fitting function for h_diff
	//[0]N,[1]life time,[2]A,[3]ang freq,[4]phase,[5]offset
  TF1 *myfitd = new TF1("myfitd","[0]*exp(-x/[1])*(1+[2]*cos([3]*x+[4]))+[5]", 4.0, 8.0);
  myfitd->SetParameter(0,100);
  myfitd->SetParameter(1,2);
  myfitd->SetParameter(2,10);
  myfitd->SetParameter(3,0.6);
	myfitd->SetParameter(4,0);
  myfitd->SetParameter(5,0);

	//plot three histograms
  // result->Divide(3,2);
	// //plot h_u with fitting
  // result->cd(1);
  // h_u2->Fit("myfit");
  // h_u2->Draw("E");
	// //plot h_d with fitting
  // result->cd(2);
  // h_d2->Fit("myfit");
  // h_d2->Draw("E");
	//
	// result->cd(4);
	// h_u3->Draw("E");
	// result->cd(5);
	// h_d3->Draw("E");
	//
	// h_diff2->Add(h_u2);
	// h_diff2->Add(h_d2,-1);
	// h_diff3->Add(h_u3);
	// h_diff3->Add(h_d3,-1);
	// result->cd(3);
	// h_diff2->Draw("E");
	// result->cd(6);
	// h_diff3->Draw("E");

	//plot hist_diff with oscillation fitting
  // result->cd(3);
//  TH1* hist_diff = (TH1*) h1->Clone("hist_diff");
	// h_diff->Add(h_u);
  // h_diff->Add(h_d, -1);
  // h_diff->Fit("myfitd","R");
  // h_diff->Draw("E");
	// gStyle->SetOptFit(1111);  //show more fitting information

	// result->cd(4);
	// TH1F* UpDown =new TH1F("h2","Up and Down", 80,0,8);
	// h_u->setMarkerColor("k");
	// UpDown->Add(h_u);
	// h_d->setMarkerColor("red");
	// UpDown->Add(h_d);
	// UpDown->Draw("E");

/////////////////////////////////
// Experimental TGraphError
/////////////////////////////////
TCanvas *testcanvas=new TCanvas("graph with customized error bars","Up-Down");
Double_t x[80];
Double_t y[80];
Double_t ex[80];
Double_t ey[80];

for (int i = 0; i < 80; i++){
	x[i] = i*0.1;
	y[i] = h_u3->GetBinContent(i) - h_d3->GetBinContent(i);
	ex[i] = 0;
	ey[i]= sqrt(h_u3->GetBinContent(i)) + sqrt(h_d3->GetBinContent(i));
}

gr = new TGraphErrors(80,x,y,ex,ey);
gr->Draw("ALP");




}

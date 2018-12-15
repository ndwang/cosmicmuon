/*
This script analyzes a cosmic muon dataset to determine the precession frequency
of muon and therefore the g factor. It first identifies decay events by
checking the detector layers it passes through, then determines the direction of
the decay (up/down). It records the decay time in two histograms for up/down.
The decay time histograms are then fitted to exponential decay to determine muon
lifetime. The script also calculates the difference between spin up/down, and
determines the precession frequency of muon. Together with magnetic field data,
we are able to calculate the g factor for muon.

@Author: Chad
				 Joy, Aike
				 Nora Sherman, Ningdong Wang
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


string FileName = "MuonData15.11-04.12.2018";
string RootFile =  FileName + ".root";
string csvFile = FileName + ".csv";


void THECODE(){
	//initialization
	TFile *f=new TFile(RootFile.c_str()); // Opens the root file
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

	// TH1D* x_cor = new TH1D("x_cor","x coordinate", 200,-3000,3000);
	// TH1D* y_cor = new TH1D("y_cor","y coordinate", 200,-3000,3000);

	// These floats correspond to each PMT. You'll use these to hold
	Short_t W01,W02,W03,W04,W05,W06,W07,W08,W09,W10,W11,W12,W13,W14;
	Short_t E01,E02,E03,E04,E05,E06,E07,E08,E09,E10,E11,E12,E13,E14;
	Short_t STDC_W03,STDC_W04,STDC_W05,STDC_W06,STDC_W07,STDC_W08,STDC_W09,STDC_W10,STDC_W11,STDC_W12;
	Short_t STDC_E03,STDC_E04,STDC_E05,STDC_E06,STDC_E07,STDC_E08,STDC_E09,STDC_E10,STDC_E11,STDC_E12;
	Short_t STDC_8_SUM;

//////////////////////////
// Read ADC normalization parameters from file
//////////////////////////
	string s;
	ifstream infile;
	double normalization[12][2];
	infile.open(csvFile.c_str());
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 2; j++){
			getline(infile,s);
			normalization[i][j] = stod(s,NULL);
		}
	}


/////////////////////////////////////////
// This section grabs the data from the branches in your root file
// and assigns them to a variable
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


	//determine the x,y location of muon
	//accept events in the middle
	if (layer_pass != 5 && layer_pass != 0){
		int ADC[16]  = {W03,W04,E03,E04,W05,W06,E05,E06,W07,W08,E07,E08,W09,W10,E09,E10};
		//normalize ADCs
		double left[2];
		double right[2];
		left[0] = (ADC[layer_pass*4-4]-normalization[layer_pass*4-4][0])*normalization[0][1]/(normalization[layer_pass*4-4][1]);
		left[1] = (ADC[layer_pass*4-3]-normalization[layer_pass*4-3][0])*normalization[0][1]/(normalization[layer_pass*4-3][1]);
		right[0] = (ADC[layer_pass*4-2]-normalization[layer_pass*4-2][0])*normalization[0][1]/(normalization[layer_pass*4-2][1]);
		right[1] = (ADC[layer_pass*4-1]-normalization[layer_pass*4-1][0])*normalization[0][1]/(normalization[layer_pass*4-1][1]);

		double x = left[0] + left[1] - right[0] - right[1];
		double y = left[0] - left[1] + right[0] - right[1];

		// if (left[0] > 300 || left[1] > 300 || right[0] > 300 || right[1] > 300){
		// 	x_cor->Fill(x);
		// 	y_cor->Fill(y);
		// }
		if (x > 400 || x < -200){continue;}
	}





  //Indentify the layer of electron hits
  //Reject events with more than one hit or no hit
    double uptime=-1;
    double downtime=-1;
    int countu = 0;
		int countd = 0;
    int hit_time[10]={STDC_W03,STDC_W04,STDC_W05,STDC_W06,STDC_W07,STDC_W08,STDC_W09,STDC_W10,STDC_W11,STDC_W12};
		//take average of up/down time
    // for(int i = 1; i <= 4; ++i){
    //   if(i == layer_pass){
    //     for(int j = 2*i-1; j >= 0; j--){
		// 			if (j==0 || j==1)
		// 				continue;
    //       if(hit_time[j] < 4000 && hit_time[j] > 2){
    //         uptime += hit_time[j];
		// 				countu++;
    //       }
    //     }
    //     for(int j = 2*i; j<=9; j++){
		// 			if (j==0 || j==1)
		// 				continue;
    //       if(hit_time[j] < 4000 && hit_time[j] > 2){
    //         downtime += hit_time[j];
		// 				countd++;
    //       }
    //     }
    //   }
    // }
		// uptime /= countu;
		// downtime /= countd;

		if (layer_pass != 5 && layer_pass != 0){
			for(int i = 1; i <= 4; ++i){
	      if(i == layer_pass){
	        for(int j = 2*i-1; j >= 2; j--){
	          if(50<hit_time[j] && hit_time[j] < 4000){
	            //count ++;
	            uptime = hit_time[j];
	            break;
	          }
	        }
	        for(int j = 2*i; j<=9; j++){
	          if(hit_time[j] < 4000 && 50<hit_time[j]){
	            //count ++;
	            downtime = hit_time[j];
	            break;
	          }
	        }
	      }
	    }
		}


		// cout << "uptime: " << uptime << endl;
		// cout << "downtime: " << downtime << endl;

    if(uptime>100 && downtime<1 && layer_pass != 5 && layer_pass != 0){
			switch (layer_pass) {
				case 1:	h_u1->Fill(2.0/1000*uptime);
				case 2: h_u2->Fill(2.0/1000*uptime);
				case 3: h_u3->Fill(2.0/1000*uptime);
				case 4: h_u4->Fill(2.0/1000*uptime);
			}
    }

		if(downtime>100&&uptime<1  && layer_pass != 5 && layer_pass != 0){
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
   Double_t nu = h_u2->GetEntries();
   Double_t nd = h_d2->GetEntries();
   h_u2 -> Scale(nd/nu);
	 nu = h_u3->GetEntries();
   nd = h_d3->GetEntries();
   h_u3 -> Scale(nd/nu);
	 nu = h_u4->GetEntries();
   nd = h_d4->GetEntries();
   h_u4 -> Scale(nd/nu);


	//fitting function for h_u and h_d
  TF1 *myfit = new TF1("myfit","[0]*exp(-x/[1])*(1+[2]*cos([3]*x+[4]))+[5]", 0, 8);
	myfit->SetParameter(0,100);
  myfit->SetParameter(1,2);
  myfit->SetParameter(2,10);
  myfit->SetParameter(3,4);
	myfit->SetParameter(4,0);
  myfit->SetParameter(5,0);

	//fitting function for h_diff
  TF1 *myfitd = new TF1("myfitd","[0]*exp(-x/[1])*cos([2]*x+[3])+[4]", 4, 8);
	myfitd->SetParameter(0,100);
  // myfitd->SetParameter(1,2);
	myfitd->FixParameter(1,2);
  myfitd->SetParameter(2,4);
	myfitd->SetParLimits(2,3,6);
	myfitd->SetParameter(3,0);
  myfitd->SetParameter(4,0);

	//plot three histograms
  result->Divide(3,4);
	//plot h_u1 with fitting
  result->cd(1);
  h_u1->Fit("myfit");
  h_u1->Draw("E");
	//plot h_d1 with fitting
  result->cd(2);
  h_d1->Fit("myfit");
  h_d1->Draw("E");
	//plot h_diff1 with fitting
	result->cd(3);
	h_diff1->Add(h_u1);
	h_diff1->Add(h_d1,-1);
	// h_diff1->Fit("myfitd");
	h_diff1->Draw("E");

	//plot h_u2 with fitting
  result->cd(4);
  h_u2->Fit("myfit");
  h_u2->Draw("E");
	//plot h_d2 with fitting
  result->cd(5);
  h_d2->Fit("myfit");
  h_d2->Draw("E");
	//plot h_diff2 with fitting
	result->cd(6);
	h_diff2->Add(h_u2);
	h_diff2->Add(h_d2,-1);
	h_diff2->Fit("myfitd");
	h_diff2->Draw("E");

	//plot h_u3 with fitting
  result->cd(7);
  h_u3->Fit("myfit");
  h_u3->Draw("E");
	//plot h_d3 with fitting
  result->cd(8);
  h_d3->Fit("myfit");
  h_d3->Draw("E");
	//plot h_diff3 with fitting
	result->cd(9);
	h_diff3->Add(h_u3);
	h_diff3->Add(h_d3,-1);
	h_diff3->Fit("myfitd");
	h_diff3->Draw("E");

	//plot h_u4 with fitting
  result->cd(10);
  h_u4->Fit("myfit");
  h_u4->Draw("E");
	//plot h_d4 with fitting
  result->cd(11);
  h_d4->Fit("myfit");
  h_d4->Draw("E");
	//plot h_diff4 with fitting
	result->cd(12);
	h_diff4->Add(h_u4);
	h_diff4->Add(h_d4,-1);
	h_diff4->Fit("myfitd");
	h_diff4->Draw("E");


	gStyle->SetOptFit(1111);  //show more fitting information


/////////////////////////////////
// Experimental TGraphError (customized error bars)
/////////////////////////////////
// TCanvas *testcanvas=new TCanvas("graph with customized error bars","Up-Down");
// Double_t x[80];
// Double_t y[80];
// Double_t ex[80];
// Double_t ey[80];
//
// for (int i = 0; i < 80; i++){
// 	x[i] = i*0.1;
// 	y[i] = h_u3->GetBinContent(i) - h_d3->GetBinContent(i);
// 	ex[i] = 0;
// 	ey[i]= sqrt(h_u3->GetBinContent(i)) + sqrt(h_d3->GetBinContent(i));
// }
//
// gr = new TGraphErrors(80,x,y,ex,ey);
// gr->Draw("ALP");

// result->Divide(1,2);
// result->cd(1);
// x_cor->Draw("");
// result->cd(2);
// y_cor->Draw("");
}

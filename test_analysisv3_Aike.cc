/*
This script is the framework for you to start your analysis. I have written enough for you to access
data from each event (Muon passing through/stopping in the detector) individually. With the data organized
this way, you can make decisions about individual events and apply them to the entire data set. Feel free
to make this analysis code as complex as you need it to be. Write functions so you can think about things
more abstractly, maybe make your detector layers into classes and give them attributes and functions.
*/



#include <iostream>
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
using namespace std;




void test_analysisv3_Aike(){
  //cout<<"i"<<endl;
	TFile *f=new TFile("MuonData15.11-04.12.2018.root"); // Opens the root file
	TTree *tr=(TTree*)f->Get("tree"); // Pulls the tree from the file into memory so we can work with it
	TCanvas *result=new TCanvas("result","Up-Down");
  TH1F* h_u = new TH1F("h_u","Up", 80,0,8);
	TH1F* h_d = new TH1F("h_d","Down",80,0,8);
  TH1F *h1 = new TH1F("h1","Diff", 80,0,8);

//for (int event=0,event<tr->GetEntries();event++){

	// These floats correspond to each PMT. You'll use these to hold
	Short_t W01,W02,W03,W04,W05,W06,W07,W08,W09,W10,W11,W12,W13,W14;
	Short_t E01,E02,E03,E04,E05,E06,E07,E08,E09,E10,E11,E12,E13,E14;
	Short_t STDC_W03,STDC_W04,STDC_W05,STDC_W06,STDC_W07,STDC_W08,STDC_W09,STDC_W10,STDC_W11,STDC_W12;
	Short_t STDC_E03,STDC_E04,STDC_E05,STDC_E06,STDC_E07,STDC_E08,STDC_E09,STDC_E10,STDC_E11,STDC_E12;
	Short_t STDC_8_SUM;

// This section grabs the data from the branches in your root file and assigns them to a variable (change &a to the relevant PMT, or however you prefer to refer to your inputs)

	tr->SetBranchAddress("ADC_1_0",&W03);
	tr->SetBranchAddress("ADC_1_1",&W04);
	tr->SetBranchAddress("ADC_1_2",&W05);
	tr->SetBranchAddress("ADC_1_3",&W06);
	tr->SetBranchAddress("ADC_1_4",&W07);
	tr->SetBranchAddress("ADC_1_5",&W08);
	tr->SetBranchAddress("ADC_1_6",&W09);
	tr->SetBranchAddress("ADC_1_7",&W10);
	tr->SetBranchAddress("ADC_1_8",&W11);
	tr->SetBranchAddress("ADC_1_9",&W12);
	//tr->SetBranchAddress("ADC_1_10",&E01);
	//tr->SetBranchAddress("ADC_1_11",&E02);
	tr->SetBranchAddress("ADC_2_0",&E03);
	tr->SetBranchAddress("ADC_2_1",&E04);
	tr->SetBranchAddress("ADC_2_2",&E05);
	tr->SetBranchAddress("ADC_2_3",&E06);
	tr->SetBranchAddress("ADC_2_4",&E07);
	tr->SetBranchAddress("ADC_2_5",&E08);
	tr->SetBranchAddress("ADC_2_6",&E09);
	tr->SetBranchAddress("ADC_2_7",&E10);
	tr->SetBranchAddress("ADC_2_8",&E11);
	tr->SetBranchAddress("ADC_2_9",&E12);
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
	/*tr->SetBranchAddress("STDC_8_10",&STDC_E03);
	tr->SetBranchAddress("STDC_8_11",&STDC_E04);
	tr->SetBranchAddress("STDC_8_12",&STDC_E05);
	tr->SetBranchAddress("STDC_8_13",&STDC_E06);
	tr->SetBranchAddress("STDC_8_14",&STDC_E07);
	tr->SetBranchAddress("STDC_8_15",&STDC_E08);
	tr->SetBranchAddress("STDC_8_SUM",&STDC_8_SUM);


	tr->SetBranchAddress("FTDC_9_0",&FTDC_9_0);
	tr->SetBranchAddress("FTDC_9_1",&FTDC_9_1);
	tr->SetBranchAddress("FTDC_9_2",&FTDC_9_2);
	tr->SetBranchAddress("FTDC_9_3",&FTDC_9_3);
	tr->SetBranchAddress("FTDC_9_4",&FTDC_9_4);
	tr->SetBranchAddress("FTDC_9_5",&FTDC_9_5);
	tr->SetBranchAddress("FTDC_9_6",&FTDC_9_6);
	tr->SetBranchAddress("FTDC_9_7",&FTDC_9_7);
*/

//cout<<"i"<<endl;
  cout<<tr->GetEntries()<<endl;
  int countm =0;
  for (int i=0;i<tr->GetEntries();i++){
    tr->GetEntry(i);
	//The following is test code for making sure we can read data
  //int countm =0;
  //cout<<"i"<<endl;

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
    if((W03 > 70 && E03 > 68) ||(W04 > 160 && E04 > 224)){
      layer_pass = 1;
    }
    if( ((W05 > 220 && E05 > 81) ||(W06 > 200 && E06 > 73))){
      if(layer_pass==1){
      layer_pass = 2;}
      else{layer_pass = 0;}
    }
    if(((W07 > 47 && E07 > 45) ||(W08 > 285 && E08 > 45))){
      if(layer_pass==2){
      layer_pass = 3;}
      else{layer_pass = 0;}
    }
    if( ((W09 > 70 && E09 > 36) ||(W10 > 45 && E10 > 88))){
      if(layer_pass==3){
      layer_pass = 4;}
      else{layer_pass = 0;}
    }
     if(((W11 > 50 && E11 > 17) ||(W12 > 276 && E12 > 120))){
      if(layer_pass==4){
      layer_pass = 5;}
      else{layer_pass = 0;}
    }
  /*
    if(Layer2 >= 310){
      layer_pass++;
      layer_pass = 2;
    }
    if(Layer3>=240){
      layer_pass++;
      layer_pass = 3;
    }
    if(Layer4>=70){
      layer_pass++;
      layer_pass = 4;
    }
    if(Layer5>=300){
      layer_pass++;
      layer_pass = 5;
    }*/
    //cout<<layer_pass<<endl;
    //if(layer_pass == 5 || layer_pass == 0){
    //  continue;
    //}
    //else{cout<<layer_pass<<endl;}


  //Indentify the layer of electron hits
  //Reject events with more than one hit or no hit
  //cout<<"okay"<<endl;
    int layer_hit=0;
    int uptime=-1;
    int downtime=-1;
    int count = 0;
    int hit_time[10]={STDC_W03,STDC_W04,STDC_W05,STDC_W06,STDC_W07,STDC_W08,STDC_W09,STDC_W10,STDC_W11,STDC_W12};
    for(int i = 1; i <= 4; ++i){
      if(i == layer_pass){
        for(int j = 2*i-1; j >= 0; j--){
          if(hit_time[j] < 4000){
            uptime = hit_time[j];
          }
        }
        for(int j = 2*i; j<=9; j++){
          if(hit_time[j] < 4000){
            downtime = hit_time[j];
          }
        }
      }
    }
    /*
    if(STDC_W03!=4095){
      //int flag = 0;
      count ++;
      time=STDC_W03;
      //cout<<i<<" "<<time<<endl;
      //cout<<time<<endl;
      //if(layer_hit = 0){
      //layer_hit = 1;}
      //flat = 1;
    }
    if(STDC_W04!=4095){
      count ++;
      time=STDC_W04;
      //cout<<i<<" "<<tim:e<<endl;
      //if(layer_hit = 0){
      //layer_hit = 1;}
    }
    if(STDC_W05!=4095){
      count ++;
      time=STDC_W05;
      //cout<<time<<endl;
      //if(layer_hit < 2){
      //layer_hit = 2;}
    }
    if(STDC_W06!=4095){
      count ++;//flag = 1;
      time=STDC_W06;
      //if(layer_hit < 2){
      //layer_hit = 2;}
    }
    if(STDC_W07!=4095){
      count ++;//flag = 1;
      time=STDC_W07;
      if(layer_hit < 3){
      layer_hit = 3;}
    }
    if(STDC_W08!=4095){
      count ++;
      //flag = 1;
      time=STDC_W08;
      layer_hit = 3;
    }
    if(STDC_W09!=4095){
      count ++;
      //flag = 1;
      time=STDC_W09;
      layer_hit = 4;
    }
    if(STDC_W10!=4095){
      count ++;//flag = 1;
      time=STDC_W10;
      layer_hit = 4;
    }

    if(STDC_W11!=4095){
      count ++;//flag = 1;
      time=STDC_W11;
      layer_hit = 5;
    }
    if(STDC_W12!=4095){
      count ++;//flag = 1;
      time=STDC_W12;
      layer_hit = 5;
    }
*/
    if(uptime>100&&downtime<0 && layer_pass != 5 && layer_pass != 0){
      h_u->Fill(2.0/1000*uptime);
    }

    if(downtime>100&&uptime<0  && layer_pass != 5 && layer_pass != 0){
      h_d->Fill(2.0/1000*downtime);
    }

  }
  Double_t nu = h_u->GetEntries();
  Double_t nd = h_d->GetEntries();
  h_d -> Scale(nu/nd);
  TF1 *myfit = new TF1("myfit","[0]*exp(-x/[1])+[2]", 0, 8);
  myfit->SetParameter(0,100);
  myfit->SetParameter(1,2);
  myfit->SetParameter(2,0);

  //cout<<"where?"<<endl;
	//[0]N,[1]tau,[2]A,[3]ang freq,[4]phase,[5]offset
  TF1 *myfitd = new TF1("myfitd","[0]*exp(-x/[1])*(1+[2]*cos([3]*x+[4]))+[5]", 4.0, 8.0);
  myfitd->SetParameter(0,100);
  myfitd->SetParameter(1,2);
  myfitd->SetParameter(2,10);
  myfitd->SetParameter(3,0.6);
	myfitd->SetParameter(4,0);
  myfitd->SetParameter(5,0);
 // cout<<"here?"<<endl;
  //TF1 *f1 = new TF1("f1","[0]*x*sin([1]*x)",-3,3);
  //cout<<countm<<endl;
  result->Divide(3,1);
  result->cd(1);
  h_u->Fit("myfit");
  h_u->Draw("E");
  //result->Update();
  //h_d->Draw("same");
  result->cd(2);
  //h_u->Add(h_d, 1);
  //h_d->SetLineColor(kRed);
  h_d->Fit("myfit");
  h_d->Draw("E");
  result->cd(3);
  //TH1* hist_diff = (TH1*) h_u->Clone("hist_diff");
  TH1* h_uc = (TH1*) h_u->Clone("h_uc");
  TH1* h_dc = (TH1*) h_d->Clone("h_dc");
  TF1 *fa1 = new TF1("fa1","-1",0,8);
  h_dc -> Add(fa1,6);
  h_uc -> Add(fa1,4);
  TH1* hist_diff = (TH1*) h_uc->Clone("hist_diff");
  hist_diff->Add(h_dc, -1);
  //hist_diff->Rebin(2);
  hist_diff->Fit("myfitd","R");
  hist_diff->Draw("E");

/*
	for (int i=0;i<tr->GetEntries();i++){          // This will loop over all of the recorded events in chronological order
		tr->GetEntry(i); // Sets the values of all of your variables for event number i
		if(W03>20){
			h1->Fill(W03);
		}
*/
		/*
		Now that we have the data for a particular event, you can start imposing conditions and processing data. Something like:

		float Layer3 = E03 + W03;    //Add the inputs from a layer together
		float Layer4 = E04 + W04;

		if (Layer3>50 && Layer4>50){  //If layer 3 and 4 are above noise
			TimeHist->Fill(STDC_E04); // Add a count to a histogram corresponting to the STDC value in layer 4
		}



		This example processing is only meant to give you an idea of the type of logic you'll use and the syntax involved.
		Your code will be more complex and meaningful... I hope.
}
		*/


	/*
	for (int i=0;i<tr->GetEntries();i++){
		tr->GetEntry(i);
		h1a->Fill(W03 - h1->GetMaximumBin());
	}
	*/
	//h1->Draw();




}

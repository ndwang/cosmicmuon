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
#include <fstream>
#include <map>
#include <queue>
#include <iostream>       // std::cout
#include <deque>          // std::deque
#include <list>
using namespace std;




void test_analysis(){

	TFile *f=new TFile("2018-07-10_MagRun_01.root"); // Opens the root file
	TTree *tr=(TTree*)f->Get("tree"); // Pulls the tree from the file into memory so we can work with it
	TCanvas *result=new TCanvas("result","Up-Down");
  TH1F *h_u = new TH1F("h_u","Up", 600,0,600);
	TH1F *h_d = new TH1F("h_d","Down", 600,0,600);
  TH1F *h_diff =new TH1F("h_diff","Difference between up and down", 600,0,600);
  //TH1F *h1a = new TH1F("h1a","STDC_SUM", 4000,0,4000);

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




//The following is test code for making sure we can read data
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

    if(Layer1 > = 280){
      layer_pass++
    }
    if(Layer2 > = 310){
      layer++;
    }
    if(Layer3>=240){
      layer++;
    }
    if(Layer4>=70){
      layer++;
    }
    if(Layer5>=300){
      layer++;
    }

    if(layer == 5 || layer == 0){
      break
    }

  //Indentify the layer of electron hits
  //Reject events with more than one hit or no hit 
   
    int layer_hit=0;
    int time=-1;
    //int flag = 0;
    int count = 0;

    if(STDC_E03!=4095){
      count ++;
      time=STDC_E03;
      layer_hit = 1;
    }
    if(STDC_E04!=4095){
      count ++;
      time=STDC_E04;
      layer_hit = 1;
    }
    if(STDC_E05!=4095){
      count ++;
      time=STDC_E05;
      layer_hit = 2;
    }
    if(STDC_E06!=4095){
      count ++;//flag = 1;
      time=STDC_E06;
      layer_hit = 2;
    }
    if(STDC_E07!=4095){
      count ++;//flag = 1;
      time=STDC_E07;
      layer_hit = 3;
    }
    if(STDC_E08!=4095){
      count ++;
      //flag = 1;
      time=STDC_E08;
      layer_hit = 3;
    }
    if(STDC_E09!=4095){
      count ++;
      //flag = 1;
      time=STDC_E09;
      layer_hit = 4;
    }
    if(STDC_E10!=4095){
      count ++;//flag = 1;
      time=STDC_E10;
      layer_hit = 4;
    }

    if(STDC_E11!=4095){
      count ++;//flag = 1;
      time=STDC_E09;
      layer_hit = 5;
    }
    if(STDC_E12!=4095){
      count ++;//flag = 1;
      time=STDC_E10;
      layer_hit = 5;
    }



    if(flag==1 && layer_hit >= layer_pass){
      h_u->Fill(time);
    }
    
    if(flag==1 && layer_hit < layer_pass){
      h_d->Fill(time);
    }

  }

  h_diff = h_u->Add(*h_d,-1);

  result->Divide(2,1);
  result->cd(1);
  h_u->Draw();
  h_d->Draw("same");
  result->cd(2);
  h_diff->Draw();
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
























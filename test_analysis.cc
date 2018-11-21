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
using namespace std;



void test_analysis(){

	TFile *f=new TFile("Real_Run.root"); // Opens the root file
	TTree *tr=(TTree*)f->Get("tree"); // Pulls the tree from the file into memory so we can work with it
	TH1F *h1 = new TH1F("h1","STDC_SUM", 4000,0,4000);
	TH1F *h1a = new TH1F("h1a","STDC_SUM", 4000,0,4000);

//for (int event=0,event<tr->GetEntries();event++){
	
	// These floats correspond to each PMT. You'll use these to hold 
	float W01,W02,W03,W04,W05,W06,W07,W08,W09,W10,W11,W12,W13,W14;
	float E01,E02,E03,E04,E05,E06,E07,E08,E09,E10,E11,E12,E13,E14;
	float STDC_W03,STDC_W04,STDC_W05,STDC_W06,STDC_W07,STDC_W08,STDC_W09,STDC_W10,STDC_W11,STDC_W12;
	float STDC_E03,STDC_E04,STDC_E05,STDC_E06,STDC_E07,STDC_E08,STDC_E09,STDC_E10,STDC_E11,STDC_E12;
	Short_t STDC_8_SUM;
	
// This section grabs the data from the branches in your root file and assigns them to a variable (change &a to the relevant PMT, or however you prefer to refer to your inputs)
/*
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
	tr->SetBranchAddress("ADC_1_10",&E01);
	tr->SetBranchAddress("ADC_1_11",&E02);
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
	tr->SetBranchAddress("ADC_2_10",&E11);
	tr->SetBranchAddress("ADC_2_11",&E12);
	*//*
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
	tr->SetBranchAddress("STDC_8_10",&STDC_E03);
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
	tr->SetBranchAddress("STDC_8_SUM",&STDC_8_SUM);

  
	for (int i=0;i<tr->GetEntries();i++){          // This will loop over all of the recorded events in chronological order
		tr->GetEntry(i); // Sets the values of all of your variables for event number i
		h1->Fill(STDC_8_SUM);
		
		
		/*
		Now that we have the data for a particular event, you can start imposing conditions and processing data. Something like:
		
		float Layer3 = E03 + W03;    //Add the inputs from a layer together
		float Layer4 = E04 + W04;
		
		if (Layer3>50 && Layer4>50){  //If layer 3 and 4 are above noise
			TimeHist->Fill(STDC_E04); // Add a count to a histogram corresponting to the STDC value in layer 4
		}
		
		
		
		This example processing is only meant to give you an idea of the type of logic you'll use and the syntax involved.
		Your code will be more complex and meaningful... I hope.
		
		*/

	}
	/*
	for (int i=0;i<tr->GetEntries();i++){
		tr->GetEntry(i);
		h1a->Fill(W03 - h1->GetMaximumBin());
	}
	*/
	h1->Draw();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include <fstream>
using namespace std;



void Lifetime(){

	TFile *f=new TFile("RealData1.root"); // Opens the root file	
	TTree *tr=(TTree*)f->Get("tree"); // Pulls the tree from the file into memory so we can work with it
	TCanvas *c1 = new TCanvas("c1","Fits",400,400);    //Makes a new window to draw our histogram
	TH1F *h1 = new TH1F("h1","STDC_SUM", 4000,0,8000); //Declares a histogram with 500 bins from 0 to 8000
	
	/// Try your fit function here using the format provided
	TF1 *fit = new TF1("fit", "([0]/2200)*exp(-x/2200) + ([1]/[2])*exp(-x/[2]) + [3]",20,5500); // Declaration is TF1("name","function",int x_start,int x_stop)

	Short_t STDC_8_SUM;
	
	tr->SetBranchAddress("STDC_8_SUM",&STDC_8_SUM);
  
	for (int i=0;i<tr->GetEntries();i++){          // This will loop over all of the recorded events in chronological order
		tr->GetEntry(i); // Sets the values of all of your variables for event number i
		if (STDC_8_SUM>0){h1->Fill(STDC_8_SUM);}
	}

	h1->Draw();
	h1->Fit("fit","R SAME q");
	
	//cout << "Negative lifetime = " << fit->GetParameter(3) << " ns"<<endl;
	/*
	ofstream myfile; // Creates and output file object
	myfile.open("lifetime_histo.csv");
	for (int bin = 0; bin<4000; bin++){
	myfile<< 2*bin << ","<< h1->GetBinContent(bin)<<endl;
	}
	myfile.close();
*/
}
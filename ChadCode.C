#include <fstream>
#include <iostream>
#include <string>
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"



using namespace std;

// Write the path to your file here in quotes eg. "/home/user/MuonDaq/run/"
string Path =  "/home/nw3/cosmicmuon";

// Write the name of your file here without .root extension eg. MuonData1
string FileName = "RealData1";

// These lines tack on the .root and .csv extensions for use in the function
string RootFile =  FileName + ".root";
string csvFile = FileName + ".csv";

void ChadCode(){

	TFile *f=new TFile(RootFile.c_str()); // Opens your root file
	TTree *tr=(TTree*)f->Get("tree"); 	// creates the TTree object and gets the data out of the root file
	TCanvas *c = new TCanvas("c","temp",100,100); // Creates a canvas (window) for us to draw a temporary histogram on
	TCanvas *c1 = new TCanvas("c1","Fits",1000,800); // Creates our permenant canvas that will display our output
	TPad *pad = new TPad("pad", "pad",0.15,0.11,0.85,0.79); // Creates pads on our canvas to draw histograms on
	TF1 *f1 = new TF1("fit","landau");  // Creates a fit object that will store the fit parameters
	c1->Divide(6,4); // Divides the canvas into 6 columns and 4 rows
	Short_t ADC; // This variable will store our data. Only one is needed because we aren't processing the data
	int p=1; // This will keep track of how many channels we have looped through (instead of module number and channel)

	ofstream myfile; // Creates and output file object
	myfile.open(csvFile.c_str()); // Opens a csv file to write to with your file name
	myfile<<"Name, x-Offset, MPV, Width"<<endl; // Header data for the top of the .csv


	// Loop over module and channel
	for(int Mod=1;Mod<=2;Mod++){
		for(int ch=0;ch<12;ch++){

			cout<<"ADC_"<<Mod<<"_"<<ch<<endl;
			tr->SetBranchAddress( Form( "ADC_%d_%d", Mod,ch ), &ADC ); // Set the address of our branch to the address of the variable we created earlier
			c->cd(0);	// Select which canvas and pad we will draw on
			tr->Draw(Form( "ADC_%d_%d",Mod,ch)); // Draws a histogram straight from the branch (same as in TBrowser)

			TH1F *htemp = (TH1F*)gPad->GetPrimitive("htemp"); // Grabs the histogram straight from the branch so we can work with it
			TH1F *h1 = new TH1F(Form( "ADC_%d_%d",Mod,ch),"ADC",512,0,1000); // Make a new histogram the same size as htemp

			Double_t offset=11+htemp->GetBinCenter(htemp->GetMaximumBin());  // Find the largest bin (zero value in our case) in the pre-made branch histogram and adds an additional offset to buffer agains second peaks

			for(int evNo=0;evNo<tr->GetEntries();evNo++){   // Use this line to loop over every event in your file (more accurate but takes longer)
			//for(int evNo=0;evNo<10;evNo++){   	// Use this line to loop over a few events (faster, less accurate)

				tr->GetEntry(evNo); // Grab the data from a particular event
				h1->Fill(ADC-offset); // Fill our histogram with that data
			}

			c1->cd(p); // Selects our permenant canvas and draws on pad number p
			p++; // Increment p by 1 so we don't keep drawing on the same pad
			if(p<22){  // The last few channels aren't used and fitting a channel without data causes problems, so I excluded channels over 21
				h1->Fit("fit","SAME q"); // Fit the data in the histogram with the TF1 we created earlier (landau)
				myfile<<"ADC_"<<Mod<<"_"<<ch<<", "<<offset<<", "<<f1->GetParameter(1)<<", "<<f1->GetParameter(2)<<endl;  // Save the fit parameters to the .csv
				}
			h1->DrawCopy(); // Draws a copy of the histogram that will remain static so we can reuse the same histogram for other channels
			delete h1;  // Delete the histogram
		}
	}
	delete c; // Delete the temporary canvas
}

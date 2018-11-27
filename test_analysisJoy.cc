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




void test_analysisJoy(){

        TFile *f=new TFile("2018-07-10_MagRun_01.root");//"MuonData15.11-04.12.2018.root");//"2018-07-10_MagRun_01.root"); // Opens the root file
	TTree *tr=(TTree*)f->Get("tree"); // Pulls the tree from the file into memory so we can work with it
	TCanvas *result=new TCanvas("result","Up-Down");
  TH1F *h_u = new TH1F("h_u","Up", 600,0,600);
	TH1F *h_d = new TH1F("h_d","Down", 600,0,600);
	TH1F *h_diff =new TH1F("h_diff","Difference between up and down", 600,0,600);

//for (int event=0,event<tr->GetEntries();event++){

	// These floats correspond to each PMT. You'll use these to hold
	Short_t W01,W02,W03,W04,W05,W06,W07,W08,W09,W10,W11,W12,W13,W14;
	Short_t E01,E02,E03,E04,E05,E06,E07,E08,E09,E10,E11,E12,E13,E14;
	Short_t STDC_03,STDC_04,STDC_05,STDC_06,STDC_07,STDC_08,STDC_09,STDC_10,STDC_11,STDC_12;


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

	tr->SetBranchAddress("STDC_8_0",&STDC_03);
	tr->SetBranchAddress("STDC_8_1",&STDC_04);
	tr->SetBranchAddress("STDC_8_2",&STDC_05);
	tr->SetBranchAddress("STDC_8_3",&STDC_06);
	tr->SetBranchAddress("STDC_8_4",&STDC_07);
	tr->SetBranchAddress("STDC_8_5",&STDC_08);
	tr->SetBranchAddress("STDC_8_6",&STDC_09);
	tr->SetBranchAddress("STDC_8_7",&STDC_10);
	tr->SetBranchAddress("STDC_8_8",&STDC_11);
	tr->SetBranchAddress("STDC_8_9",&STDC_12);

	/*
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
//for (int i=0;i<500000;i++){
	tr->GetEntry(i);
	Short_t Layer1=E03+E04+W03+W04;
	Short_t Layer2=E05+E06+W05+W06;
	Short_t Layer3=E07+E08+W07+W08;
	Short_t Layer4=E09+E10+W09+W10;
	Short_t Layer5=E11+E12+W11+W12;

	int lastLayer=0;


	if(Layer1<280){
		Layer1=0;
	}
	if(Layer2<310){
		Layer2=0;
	}
	if(Layer3<240){
		Layer3=0;
	}
	if(Layer4<70){
		Layer4=0;
	}
	if(Layer5<300){
		Layer5=0;
	}

if(Layer1){
	lastLayer=1;
}
if(Layer2){
	lastLayer=2;
}
if(Layer3){
	lastLayer=3;
}
if(Layer4){
	lastLayer=4;
}
if(Layer5){
	lastLayer=5;
}


	int flag;

	/// Layer 1 time logic
	int flag1=0;
	int time1=-1;

	if(flag1==0 && STDC_03!=4095){
		flag1=1;
		flag=1;
		time1=STDC_03;
	}

	if(flag1==0 && STDC_04!=4095){\
		flag1=1;
		flag=1;
		time1=STDC_04;
	}

///

/// Layer 2 time logic
int flag2=0;
int time2=-1;

if(flag2==0 && STDC_05!=4095){
	flag2=2;
	flag=2;
	time2=STDC_05;
}

if(flag2==0 && STDC_06!=4095){
	flag2=2;
	flag=2;
	time2=STDC_06;
}

///

/// Layer 3 time logic
int flag3=0;
int time3=-1;

if(flag3==0 && STDC_07!=4095){
	flag3=3;
	flag=3;
	time3=STDC_07;
}

if(flag3==0 && STDC_08!=4095){\
	flag3=3;
	flag=3;
	time3=STDC_08;
}

///

/// Layer 4 time logic
int flag4=0;
int time4=-1;

if(flag4==0 && STDC_09!=4095){
	flag4=4;
	flag=4;
	time4=STDC_09;
}

if(flag4==0 && STDC_10!=4095){\
	flag4=4;
	flag=4;
	time4=STDC_10;
}

///

/// Layer 5 time logic
int flag5=0;
int time5=-1;

if(flag5==0 && STDC_11!=4095){
	flag5=5;
	flag=5;
	time5=STDC_11;
}

if(flag5==0 && STDC_12!=4095){\
	flag5=5;
	flag=5;
	time5=STDC_12;
}

///


int decaytime=0;


if(flag1 && time1>10){
	decaytime=time1;
	//cout<<"Decay in layer 1 = "<<decaytime<<endl;
}

if(flag2 && time2>10){
	decaytime=time2;
	//cout<<"Decay in layer 2 = "<<decaytime<<endl;
}

if(flag3 && time3>10){
	decaytime=time3;
	//cout<<"Decay in layer 3 = "<<decaytime<<endl;;
}

if(flag4 && time4>10){
	decaytime=time4;
	//cout<<"Decay in layer 4 = "<<decaytime<<endl;
}

if(flag5 && time5>10){
	decaytime=time5;
	//cout<<"Decay in layer 5 = "<<decaytime<<endl;
}

/*
if(Layer1 && decaytime){
	cout<<"layer 1 = "<<Layer1<<endl;
}

if(Layer2 && decaytime){
	cout<<"layer 2 = "<<Layer2<<endl;
}

if(Layer3 && decaytime){
	cout<<"layer 3 = "<<Layer3<<endl;
}

if(Layer4 && decaytime){
	cout<<"layer 4 = "<<Layer4<<endl;
}

if(Layer5 && decaytime){
	cout<<"layer 5 = "<<Layer5<<endl;
}
*/

int up=0;
int down=0;
decaytime=decaytime*2;
//Gives it in nanoseconds

if(flag && lastLayer && decaytime>10 && flag <= lastLayer){
	up=1;
	//cout<<"Up decay"<<endl;
	h_u->Fill(decaytime);
}
if(flag && lastLayer && decaytime>10 && flag > lastLayer){
	down=1;
	//cout<<"Down decay"<<endl;
	h_d->Fill(decaytime);
}

//h_diff = h_u->Add(*h_d,-1);

//result->Divide(2,1);
//result->cd(1);

//result->cd(2);
//h_diff->Draw();

}

//h_u->Draw("AC*");
//h_d->Draw();
//h_d->Draw("AC*");

///

//h_u->GetBinCenter(600);
//h_u->GetBinContent();
h_u->SetMarkerColor(8); // green;
h_d->SetMarkerColor(4);  // blue
h_u->SetMarkerStyle(kFullCircle);
h_d->SetMarkerStyle(kFullCircle);

h_u->Draw("P");          //draw hist_2 first as it has a larger range
h_d->Draw("same P");
h_u->SetTitle("Up Down Funk");

h_diff = h_u;
h_diff->Add(h_d,-1);

//h_diff=h_u-h_d;
//TCanvas *Diff=new TCanvas("Diff","Up Minus Down");
h_diff->SetMarkerColor(13);
h_diff->Draw("P");



// leg_hist = new TLegend(0.5,0.6,0.79,0.79);
// leg_hist->SetHeader("Some histograms");
//leg_hist->AddEntry(hist_1,"First histo","l");
// leg_hist->AddEntry(hist_2,"Second histo","l");
//leg_hist->Draw();

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

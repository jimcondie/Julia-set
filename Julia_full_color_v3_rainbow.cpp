#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>


using namespace std;
const double PI=3.14159265359;
const double phase=100;
const double phase_diff=0;
const double freq=0.001;






//map x value into real part
double mapXIntoReal(int width, double minX, double maxX, double pixelX)
{
double domain=maxX-minX;

double realPart=domain/(width)*pixelX+minX;
return realPart;

}

//map y value into imaginary part
double mapYIntoImaginary(int height, double minY, double maxY, double pixelY)
{
double range=maxY-minY;

double imaginaryPart=range/(height)*pixelY+minY;
return imaginaryPart;

}

//function that calculates magnitudes
double mag(double Real, double Imaginary)
{
double mag=sqrt((Real*Real)+(Imaginary*Imaginary));
return mag;
}

//function that finds R value from C
double findRValue(double cReal, double cImaginary)
{
//find magnitude of C
double magOfC=mag(cReal, cImaginary);
//find R using formula
double rValue=(1+sqrt(1+4*magOfC))/2;
return rValue;
}


//find nth iterate of function
int iterateFunction(int maxiter, double cReal, double cImaginary, double zReal, double zImaginary)
{

	//find Radius value
	double rValue=findRValue(cReal, cImaginary);
	//cout<<"rValue "<<rValue<<endl;
	//R value and C remain fixed

	//initialize n at 0
	int n=0;

	//set initial f^0(z)
	double fReal=zReal;
	double fImaginary=zImaginary;


		while(n<maxiter)
		{

		//calculate f^n(z), at the same time reassign input parameters, fReal and fImaginary
		double fRealTemp=fReal*fReal-fImaginary*fImaginary+cReal;
		double fImaginaryTemp=2*fReal*fImaginary+cImaginary;

			//break if |f^n(z)|>R
			if(mag(fRealTemp,fImaginaryTemp) >rValue)
			break;

			else
			{
			fReal=fRealTemp;
			fImaginary=fImaginaryTemp;
			n++;
			}


		}

	//return value of n
	return n;
}

void colorPixel(int n, int maxiter, ofstream &ofile)
{

	bool is_in=false;
//if n==maxiter, this z point is in; set color black
	if(n>=maxiter)
	{
//write pixel to file
ofile<<0<<" "<<0<<" "<<0<<" ";
		is_in=true;
	}



	//color pixel based on rainbow
    if(is_in==false)
	{
    //made colors using this tutorial: https://krazydad.com/tutorials/makecolors.php
    double phase_frac=phase/360;
    double r_frequency=.004;
    double r_phase=phase_frac*0;

    double g_frequency=.004;
    double g_phase=phase_frac*2*PI;


    double b_frequency=0.004;
    double b_phase=2*phase_frac*2*PI;

    int amplitude=127;
    int center=128;

    double offset=phase_diff/360*2*PI;

    int r=cos(n*r_frequency+r_phase+offset)*amplitude+center;
    int g=cos(n*g_frequency+g_phase+offset)*amplitude+center;
    int b=cos(n*b_frequency+b_phase+offset)*amplitude+center;


	//write pixel to file
    ofile<<r<<" "<<g<<" "<<b<<" ";
	}


}





int main()
{

//input program parameters
ifstream ifile("juliaFrame.txt");

	if(!ifile)
	{
	cout<<"frame file not found"<<endl;
	cin.ignore();

	return 0;
	}

 int width,height, maxiter;
 double minX, minY, cReal, cImaginary, maxX, maxY;

//read in values
ifile>>width>>height>>maxiter>>cReal>>cImaginary>>minX>>maxX>>minY>>maxY;
ifile.close();


ofstream ofile("phase_"+to_string(phase)+" phase_diff_"+to_string(phase_diff)+" freq_"+to_string(freq)+" "+to_string(width)+" "+to_string(maxiter)+" "+to_string(cReal)+" "+to_string(cImaginary)+".ppm");


//PPM header
ofile<<"P3 " << endl << width << " " << height << endl;
ofile<<"256"<<endl;



for(int y=0; y<height; y++)
{
	for(int x=0; x<width; x++)
	{
		//cout<<"row: "<<y<<" col: "<<x<<endl;
	//map pixel to z
	double zReal=mapXIntoReal(width,minX,maxX,x);
	double zImaginary=mapYIntoImaginary(height,minY,maxY,y);

	//find n for z value
	int n=iterateFunction(maxiter, cReal, cImaginary, zReal, zImaginary);

	//write n to output
	colorPixel(n, maxiter,ofile);

	}
ofile<<endl;

}

ofile.close();

return 0;
}


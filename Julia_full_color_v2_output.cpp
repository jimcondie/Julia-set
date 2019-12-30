#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>


using namespace std;


//construct color pallete
struct color
{
	int r;
	int g;
	int b;


	void assignColor()
	{
	r=(rand() % (255+1));
	g=(rand() % (255+1));
	b=(rand() % (255+1));
	}

};


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

void colorPixel(int n, int maxiter,color *pallete, ofstream &ofile)
{

	bool is_in=false;
//if n==maxiter, this z point is in; set color black
	if(n>=maxiter)
	{
//write pixel to file
ofile<<0<<" "<<0<<" "<<0<<" ";

		is_in=true;
	}

//color pixel based on determined pallete
	if(is_in==false)
	{
	//write pixel to file
ofile<<(pallete+n)->r<<" "<<(pallete+n)->g<<" "<<(pallete+n)->b<<" ";

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

ofstream ofile(to_string(width)+" "+to_string(height)+" "+to_string(maxiter)+" "+to_string(cReal)+" "+to_string(cImaginary)+" "+to_string(minX)+" "+to_string(maxX)+" "+to_string(minY)+" "+to_string(maxY)+".ppm");


//PPM header
ofile<<"P3 " << endl << width << " " << height << endl;
ofile<<"256"<<endl;


//construct pallete
color* pallete=new color[maxiter];
	unsigned int seed=time(0);
	srand(seed);
	for(int i=0; i<maxiter; i++)
	{
		(pallete+i)->assignColor();
	}

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
	colorPixel(n, maxiter,pallete ,ofile);

	}
ofile<<endl;

}

ofile.close();

return 0;
}


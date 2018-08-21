#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

double mapToReal(int x, int imageWidth,double minR,double maxR){
double range=maxR-minR; 
//[0,width]
//0, maxR-minR] - val*range/width
//[minR,maxR]-last step+minR
return x*(range/imageWidth)+minR;

}

double mapToImaginary(int y, int imageHeight,double minI,double maxI){
double range=maxI-minI;
return y*(range/imageHeight)+minI;
}    

int findMandelbrot(double cr, double ci, int max_iters){
    int i=0;
    double zr=0.0,zi=0.0;
    while(i<max_iters && zr*zr+zi*zi<4.0){

        double temp=zr*zr-zi*zi+cr;
        zi=2.0*zr*zi+ci;
        zr=temp;
        i++;
    }
return i;
}

int main(){
// get the required input values from file
ifstream fin("input.txt");
int imageWidth, imageheight,maxN;
double minR, maxR, minI, maxI;
if(!fin){
    cout<<"input file error"<<endl;
cin.ignore();
return 0;
}
fin>>imageWidth>>imageheight>>maxN;
fin>>minR>>maxR>>minI>>maxI;
fin.close();

// open the output file, write the ppm header
ofstream fout("out_img.ppm");
fout<<"P3"<<endl;
fout<<imageWidth<<" "<<imageheight<<endl;
fout<<"256"<<endl;

// for every pixel
for(int y=0;y<imageheight;y++){
    for(int x=0;x<imageWidth;x++){
// find the real and imaginary values for c, corrrspondng
// to thet x,y pixel in the image
double cr=mapToReal(x,imageWidth,minR,maxR);
   double ci=mapToImaginary(y,imageheight,minI,maxI);
   //find th enumber of iterations in the Mandelbrot formula
   // using said c.
int n=findMandelbrot(cr,ci,maxN);

   //map the resulting number to an RGB value
int r= ((n*2)%256);
int g=((n*3)%256);
int b= (n%256);
   // output it to the image
   fout<<r<<" "<<g<<" "<<b<<" ";
    }
    fout<<endl;
}
fout.close();
cout<<"finished"<<endl;
return 0;
}

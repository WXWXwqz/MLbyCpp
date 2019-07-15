#ifndef DOUBLEMOON
#define DOUBLEMOON
#include <string>
using namespace std;
class DoubleMoon
{
    private:
    unsigned long N;
    int d;      
    int r;     
    int width;
    int angle;  //0~pi/2
    double**dat;
    public: 
    string filename2;
    string filename1;
    DoubleMoon(int N,int d,int r,int shift,int width,double angle,string name1,string name2);
    
};
#endif

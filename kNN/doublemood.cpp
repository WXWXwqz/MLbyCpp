#include "doublemood.h"
#include "math.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
//parameter
//N number of point
//d distance of two moon
//r radius of moon
//
DoubleMoon::DoubleMoon(int N,int d,int r,int shift,int width,double angle,string name1,string name2)
{
    char tmp[100];
    this->N=N;
    this->d=d;
    this->r=r;
    this->width =width;
    this->angle = angle;    
	getcwd(tmp,100);
    filename1=filename2 =tmp;
    filename1+=("/"+name1);
    filename2+=("/"+name2);
 
    ofstream storefile1(filename1);
    ofstream storefile2(filename2);
	// cout<<filename1<<endl;
    // cout<<filename2<<endl;

    std::cout<<"N="<<N<<std::endl;
    std::cout<<"d="<<d<<std::endl;
    std::cout<<"r="<<r<<std::endl;
    std::cout<<"width="<<width<<std::endl;
    std::cout<<"angle="<<angle<<std::endl;
    dat = (double **)malloc(sizeof(double*)*2*N);
    for(int i=0;i<N*2;i++)
    {
        int done=1;
        double dis=0;
        dat[i] = (double*)malloc(2*sizeof(double));
        do
        {
            dat[i][0] = (rand()%200*(r+width/2)+1)*0.01-(r+width/2);
            dat[i][1] = (rand()%200*(r+width/2)+1)*0.01-(r+width/2);
            dis = sqrt(dat[i][0]*dat[i][0]+dat[i][1]*dat[i][1]);
            if(dis<=(r+width/2)&&dis>=(r-width/2))
            { 
                done=0;
                if(dat[i][1]>=0)
                {
                    dat[i][1]-=d/2;
                    dat[i][0]-=shift/2;
                    storefile1<<dat[i][0]<<" "<<dat[i][1]<<std::endl;
                }
                else
                {
                    dat[i][1]+=d/2;
                    dat[i][0]+=shift/2;
                    storefile2<<dat[i][0]<<" "<<dat[i][1]<<std::endl;
                }   
                
            }
        }while(done);        
    }
    storefile1.close();
    storefile2.close();
    
}
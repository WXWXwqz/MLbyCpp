#ifndef  __kNN__H
#define  __kNN__H
using namespace std;
#include "iostream"
#include <vector>
#include <fstream>
#include <unistd.h>
template <typename T> 
class kNN
{
    public:
    int num;
    //kNN(vector<vector<T>>  inputdata);
    vector<vector<T>>   data;
    vector<vector<T>>  k_nearest_dat;
    kNN<T>();
    ~kNN<T>()
    {
          storefile1.close();
    }
    kNN<T>(vector<vector<T>>  inputdata);
    vector<vector<T>>  get_K_nearest(vector<T> aimdata,int k);
    T  get_class(vector<T> aimdata);
    vector<double> distance;    
    int maxidx;
    double max=0;
    int  get_Max( vector<double> data_in);
    private:
    double discal(vector<T> p1,vector<T> p2);
    char tmp[100];
    string filename ;
    ofstream storefile1;
};
template <typename T> 
kNN<T>::kNN()   
{
        //data=12;
        //data = inputdata;
        //cout<<data[0][0]<<endl;
      
 }
  template <typename T> 
T kNN<T>::get_class(vector<T> aimdata)   
{
    int k=7;
        vector<vector<T>>  k_near = get_K_nearest(aimdata,k);
        int class_true=0,class_fasle=0;
        for(int i =0;i<k_near.size();i++)
        {
            if(k_near[i][k_near[i].size()-1]>0)
            {
                    class_true++;
                    if(class_true>k/2)
                        return k_near[i][k_near[i].size()-1];
            }
            else
            {
                class_fasle++;
                  if(class_fasle>k/2)
                        return k_near[i][k_near[i].size()-1];
            }
        }
}
 template <typename T> 
kNN<T>::kNN(vector<vector<T>>  inputdata)   
{
       data=inputdata;
      
 
    getcwd(tmp,100);

    filename =tmp;
    filename=filename+"/"+"kdata.txt"; 
    storefile1=  ofstream(filename);
 }
template <typename T> 
vector<vector<T>>  kNN<T>::get_K_nearest(vector<T> aimdata,int k)
{
      //vector<double>  distance(10,0);
      max=0;
      k_nearest_dat.clear();
      distance.clear();
    for(int i=0;i<k;i++)
    {
        distance.push_back(0);       
    }
    for(int i=0;i<k;i++)
    {
        k_nearest_dat.push_back(data[i]);
        distance[i]=discal(k_nearest_dat[i],aimdata);
        if(distance[i]>max)
        {
            max=distance[i];
            maxidx=i;
        }
    }
  
    for (size_t i = k; i < data.size(); i++)
    {
        auto t=discal(data[i],aimdata);
        if(t<max)
        {
             k_nearest_dat[maxidx]=data[i];
            distance[maxidx]=t;
            maxidx=get_Max(distance);
            max=distance[maxidx];
        }
    }
        //    for(int i=0;i<k_nearest_dat.size();i++)
        //     {
        //         for(int j=0;j<k_nearest_dat[i].size();j++)
        //             cout<<k_nearest_dat[i][j]<<" *";
        //         cout<<endl;
        //     }


 //   cout<<"qaz"<<endl;


               /*for(int i=0;i<k_nearest_dat.size();i++)
            {
                for(int j=0;j<k_nearest_dat[i].size()-1;j++)
                    storefile1<<k_nearest_dat[i][j]<<"  ";
                storefile1<<endl;
            }*/
            /*
	for(int i=0;i<k_nearest_dat.size();i++)
	{
		//	cout<<"123";
		for(int j=0;j<k_nearest_dat[i].size();j++)
			cout<<k_nearest_dat[i][j];
		cout<<endl;
	}*/
  
    return k_nearest_dat;
    
}
template <typename T> 
double kNN<T>::discal(vector<T> p1,vector<T> p2)
{
    double tmp=0;
    for(int i=0;i<p1.size()-1;i++)
    {
        tmp+=(p1[i]-p2[i])*(p1[i]-p2[i]);
    }
    return tmp;
}  
template <typename T>
int kNN<T>::get_Max(vector <double> data_in)
{
        double tmp=0;
        int num;
        for (size_t i = 0; i < data_in.size(); i++)
        {
            if(tmp<data_in[i])
            {
                tmp=data_in[i];
                num=i;
            }
        }
        return num;
}
#endif

#include <iostream>
#include "doublemood.h"
#include <unistd.h>
#include <vector>
#include <kNN.h>
#include <fstream>
#include <sstream>   
using namespace std;
const std::string strCfgName = "logger_import_db.conf" ;   
void getData(string filename1,string filename2,vector<vector<double>>  &dat);
void generate_decision_board(double x1,double x2,double y1,double y2, string txtname,kNN<double> &knn);
int main(void)
{
	DoubleMoon dbmood(2000,4,10,10,6,3.1415*0,"moon1.txt","moon2.txt");
	DoubleMoon tstdbmood(20,6,10,10,6,3.1415*0,"tstmoon1.txt","tstmoon2.txt");
	vector<vector<double>>  traindat ;
	vector<vector<double>>  tstdat ;
 
	getData(dbmood.filename1,dbmood.filename2,traindat);
	getData(tstdbmood.filename1,tstdbmood.filename2,tstdat);
		kNN<double>  knn(traindat);
//	for(int i=0;i<tstdat.size();i++)
//	 	cout<<knn.get_class(tstdat[i])<<endl;
	 //	knn.get_K_nearest(tstdat[0],10);
generate_decision_board(-20,20,-15,15,"board.txt",knn);
	//cout<<tstdat[0][0]<<" "<<tstdat[0][1]<<endl;

}

void generate_decision_board(double x1,double x2,double y1,double y2, string txtname,kNN<double> &knn)
{
		vector<vector<double>> board;
		vector<double> xy;
		vector<double> boardxy;
		double  dif=1;
				char tmp[100];
		getcwd(tmp,100);
		string  filename;
    filename =tmp;
    filename+=("/"+txtname);    
    ofstream storefile(filename);
		xy.push_back(x1);
		xy.push_back(y1);
		xy.push_back(0);
		double last_class;
		for(double i=x1;i<x2;i+=0.1)
		{
			boardxy.clear();
			xy[0]=i;
			xy[1]=y1;
			last_class=knn.get_class(xy);
			for(double j=y1;j<y2;j+=dif)
			{
				xy[0]=i;
				xy[1]=j;
				cout<<"i="<<i<<"j="<<j<<"dif="<<dif<<endl;
				if(last_class!=knn.get_class(xy)||j>y2-dif)
				{
					j=j-dif;
					dif/=10;
					if(dif<=0.009||j>y2-dif)
					{
					   	dif=1;
							boardxy.push_back(i);
							boardxy.push_back(j);
							board.push_back(boardxy);
							storefile<<i<<" "<<j<<endl;							
							break;
					}
				}
			}

		}
		storefile.close();



}

vector <string> split(const string &s, const string &seperator){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;
  
  while(i != s.size()){
    //找到字符串中首个不等于分隔符的字母；
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
    	if(s[i] == seperator[x]){
     		++i;
 			flag = 0;
			break;
			}
    }
    
    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
			if(s[j] == seperator[x]){
				flag = 1;
				break;
			}
      if(flag == 0) 
				++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

//正例文件，反例文件
void getData(string filename1,string filename2,vector<vector<double>>  &dat)
{
	string tmp;
    ifstream storefile(filename1);
	//cout<<storefile<<endl;
	unsigned long cnt=0;
	if(storefile)
	{			
		while(getline(storefile,tmp))
		{
			cnt++;
			vector <double> dat1;
			auto tp=split(tmp," ");
			for(int i=0;i<tp.size();i++)
			{
				istringstream iss(tp[i]);  
				double num;  
    			iss >> num;
				dat1.push_back(num);
			}
			dat1.push_back(1);	
			dat.push_back(dat1);
			}
	}
	storefile.close();
	storefile.open(filename2);
	 if(storefile)
	{			
		while(getline(storefile,tmp))
		{
			cnt++;
			vector <double> dat1;
			auto tp=split(tmp," ");
			for(int i=0;i<tp.size();i++)
			{
				istringstream iss(tp[i]);  
				double num;  
    			iss >> num;
				dat1.push_back(num);
			}
			dat1.push_back(-1);	
			dat.push_back(dat1);
			}
	}
	cout<<"total num="<<cnt<<endl;
}
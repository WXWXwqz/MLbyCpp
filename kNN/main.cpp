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
int main(void)
{
	DoubleMoon dbmood(2000,4,10,10,6,3.1415*0,"moon1.txt","moon2.txt");
	DoubleMoon tstdbmood(20,8,10,10,6,3.1415*0,"tstmoon1.txt","tstmoon2.txt");
	vector<vector<double>>  traindat ;
	vector<vector<double>>  tstdat ;
 
	getData(dbmood.filename1,dbmood.filename2,traindat);
	getData(tstdbmood.filename1,tstdbmood.filename2,tstdat);
		kNN<double>  knn(traindat);
	for(int i=0;i<tstdat.size();i++)
	 	knn.get_K_nearest(tstdat[i],10);
	 //	knn.get_K_nearest(tstdat[0],10);

	cout<<tstdat[0][0]<<" "<<tstdat[0][1]<<endl;

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
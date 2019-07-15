#include <iostream>
#include "doublemood.h"
#include <unistd.h>
#include <MLP.h>
using namespace std;
const std::string strCfgName = "logger_import_db.conf" ;   
int main(void)
{
	DoubleMoon dbmood(2000,2,10,10,6,3.1415*0);
	MLP dbmood_mlp(2,10,1);
	vector<double> tst(2,1);
	vector<double> result;
	dbmood_mlp.predict(tst,result);
	cout<<result[0]<<endl;
}
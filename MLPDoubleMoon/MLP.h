#ifndef __MLP__H
#define __MLP__H
using namespace std;
#include "iostream"
#include <vector>


class MLP
{
    public:
    MLP(int input,int hidden,int output);
    int predict(vector <double> dat,vector <double> &result);
    int back_propagate(vector <double> dat,vector <double> label,double learn,double correct);    
    private:
    int sgn(double x);
    double sig(double x);
    double sigmod(double x);  
    double sigmod_derivate(double x);   
    int input_n;
    int hidden_n;
    int output_n;
    vector <double> input_cells; //输入层神经元
    vector <double> hidden_cells;
    vector <double> output_cells;
    vector <vector<double>> input_hidden_weights;
    vector <vector<double>> hidden_output_weights;

    vector <vector<double>> in_hid_wghcrr;
    vector <vector<double>> hid_out_wghcrr;

};
#endif
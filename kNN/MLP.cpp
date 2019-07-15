#include "MLP.h"
#include "math.h"
int MLP::sgn(double x)
{
   return x>0?1:-1;        
}
double MLP::sig(double x)
{
    return 1.0/(1+exp(x));
}
double MLP::sigmod(double x)
{
    return 1.0/(1.0+exp(x));
}
double MLP::sigmod_derivate(double x)
{
    return x*(1.0-x);
}
MLP::MLP(int input,int hidden,int output)
{
    this->input_n=input+1;//加上偏zhishu  
    this->hidden_n=hidden; 
    this->output_n=output;
    this->input_cells = vector<double>(input_n,1.0);
    this->hidden_cells = vector<double>(hidden_n,1.0);
    this->output_cells = vector<double>(output_n,1.0);
    this->input_hidden_weights=\
    vector<vector<double>>(input_n,vector<double>(hidden_n,1.0));
    this->hidden_output_weights=\
    vector<vector<double>>(hidden_n,vector<double>(output_n,1.0));
    
    this->in_hid_wghcrr=\
    vector<vector<double>>(input_n,vector<double>(hidden_n,1.0));
    this->hid_out_wghcrr=\
    vector<vector<double>>(hidden_n,vector<double>(output_n,1.0));
 
    for(int j=0;j<input_hidden_weights.size();j++)
    {
        for(int i=0;i<input_hidden_weights[j].size();i++)
        {
            // -0.2<=weights<=0.2
            input_hidden_weights[j][i]=(rand()%4000-2000)/10000.0;
            //cout<<input_hidden_weights[j][i]<<endl;
        }
    }
    for(int j=0;j<hidden_output_weights.size();j++)
    {
        for(int i=0;i<hidden_output_weights[j].size();i++)
        {
            // -0.2<=weights<=0.2
            hidden_output_weights[j][i]=(rand()%4000-2000)/10000.0;
         //   cout<<hidden_output_weights[j][i]<<endl;
         
        }
    }
}
int MLP::back_propagate(vector <double> dat,vector <double> label,double learn,double correct)
{
    double error;
    vector <double> result(1,0.0); 
    this->predict(dat,result);
    vector <double>output_deltas(output_n,0.0);
    for(int i=0;i<output_cells.size();i++)
    {
        error = label[i]-output_cells[i];
    }
    cout<<error<<endl;
}
int MLP::predict(vector <double> dat,vector <double> &result)
{
     if(dat.size()!=this->input_n-1)
     {
         cout<<"PREDICT ERROR"<<endl;
         cout<<dat.size()<<endl;
         cout<<this->input_n<<endl;
         return -1;
     } 
     for(int i=0;i<input_n-1;i++)
     {
        input_cells[i]=dat[i];   
       // cout<<"input_cells["<<i<<"]="<<input_cells[i]<<endl;     
     } 
     for(int i=0;i<hidden_n;i++)
     {
         double total=0;
         
         for(int j=0;j<input_n;j++)
         {
             total+=input_cells[j]*input_hidden_weights[j][i];              
         }
         //cout<<total<<endl;
         //cout<<sigmod(total)<<endl;
         hidden_cells[i]=sigmod(total);
        // cout<<"hidden_cells["<<i<<"]="<<hidden_cells[i]<<endl;
     }
     for(int i = 0; i < output_n; i++)
     {
         double total=0;
         for(int j=0;j<hidden_n;j++)
         {
             //cout<<hidden_output_weights[j][i]<<endl;
             total+=hidden_cells[j]*hidden_output_weights[j][i];             
         }
         output_cells[i]=sigmod(total);         
     }
     result = output_cells; 
    // cout<<"res="<<result[0]<<endl;
     return 0;
     
}
#include"SupportFunctions.h"


map<string,double> GetInitializeMatrix(string filePath)
{
    fstream f;
    f.open(filePath);
    string line = "";
    map<string, double> InitMatrix;
    while(getline(f,line))
    {
        string d = "";
        string state;
        double prob;
        for(auto i : line)
            if(i!=' ')
                d+=i;
            else{
                state = d;
                d="";
            }
        prob = stod(d);
        InitMatrix.insert(pair<string,double> (state,prob));
    }
    f.close();
    return InitMatrix;
}

map<string,map<string, double>> GetEmissionMatrix(string filePath)
{
    map<string,map<string, double>> Emis;
    fstream f;
    f.open(filePath);
    string line = "";
    while(getline(f,line)){
        
    }
    f.close();


    return Emis;    
}
map<string,map<string, double>> GetTransitionMatrix(string filePath)
{

}

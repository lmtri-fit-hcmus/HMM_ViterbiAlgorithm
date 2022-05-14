#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<cstring>
using namespace std;

map<string,double> GetInitializeMatrix(string filePath);
map<string,map<string, double>> GetEmissionMatrix(string filePath);
map<string,map<string, double>> GetTransitionMatrix(string filePath);
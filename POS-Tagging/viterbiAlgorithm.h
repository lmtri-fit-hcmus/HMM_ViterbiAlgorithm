#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

double GetEmissionProb(string Observation, int j, vector<vector<double>> Emission, vector<string> O);
void PrintPath(int maxIndex, vector<vector<int>> Path, vector<string> States);
vector<string> ViterbiAlgorithm(vector<string> Observations, vector<string> O, vector<string> States, vector<double> Pi, vector<vector<double>> Trans, vector<vector<double>> Emission);

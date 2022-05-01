#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

double GetProbality(string Observation, int j, vector<vector<double>> Emission, vector<string> O)
{
    for (int i = 0; i < O.size(); i++)
        if (O[i] == Observation)
        {
            return Emission[j][i];
        }
    return 0;
}

void PrintPath(int maxIndex, vector<vector<int>> Path, vector<string> States)
{
    int i = Path.size() - 2;
    int j = Path[Path.size() - 1][maxIndex];
    string res = States[maxIndex];
    while (i >= 0)
    {
        string tmp = States[j] + " ";
        res = tmp + res;
        j = Path[i][j];
        i--;
    }
    cout << "The steps of states are " << res;
}

void ViterbiAlgorithm(vector<string> Observations, vector<string> O, vector<string> States, vector<double> Pi, vector<vector<double>> Trans, vector<vector<double>> Emission)
{
    vector<vector<double>> V(Observations.size(), vector<double>(States.size()));
    vector<vector<int>> Path(Observations.size(), vector<int>(States.size()));
    for (int i = 0; i < States.size(); i++)
    {
        V[0][i] = Pi[i] * GetProbality(Observations[0], i, Emission, O);
        Path[0][i] = 0;
    }

    for (int i = 1; i < Observations.size(); i++)
    {
        for (int j = 0; j < States.size(); j++)
        {
            double maxP = -1;
            for (int k = 0; k < States.size(); k++)
            {
                if (V[i - 1][k] == 0)
                    continue;
                double cmpNum = V[i - 1][k] * Trans[k][j] * GetProbality(Observations[i], j, Emission, O);
                if (cmpNum > maxP)
                {
                    maxP = cmpNum;
                    Path[i][j] = k;
                }
            }
            V[i][j] = maxP;
        }
    }
    int maxIndex = 0;
    double maxProbability = -1;
    for (int i = 0; i < States.size(); i++)
    {
        if (V[Observations.size() - 1][i] > maxProbability)
        {
            maxProbability = V[Observations.size() - 1][i];
            maxIndex = i;
        }
    }

    PrintPath(maxIndex, Path, States);
    cout << endl
         << "With highest probability of " << maxProbability << endl;
}

int main()
{

    vector<string> Observations;
    for (int i = 0; i < 100; i++)
    {
        int r = rand() % 6 + 1;
        Observations.push_back(to_string(r));
    }
    vector<string> O{"1", "2", "3", "4", "5", "6"};
    vector<string> States{"Balance", "Inbalance"};
    vector<double> Pi = {0.1, 0.9};
    vector<vector<double>> Trans = {{0.8, 0.2}, {0.7, 0.3}};
    vector<vector<double>> Emission = {{1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6}, {0.1, 0.1, 0.1, 0.1, 0.1, 0.5}};
    ViterbiAlgorithm(Observations, O, States, Pi, Trans, Emission);
    // 
}
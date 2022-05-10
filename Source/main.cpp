#include"viterbiAlgorithm.h"

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
    vector<double> Pi = {0, 1};
    vector<vector<double>> Trans = {{0.8, 0.2}, {0.7, 0.3}};
    vector<vector<double>> Emission = {{1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6}, {0.1, 0.1, 0.1, 0.1, 0.1, 0.5}};
    ViterbiAlgorithm(Observations, O, States, Pi, Trans, Emission);
    // 
}
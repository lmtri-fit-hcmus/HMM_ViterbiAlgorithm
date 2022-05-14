#include"viterbiAlgorithm.h"
#include<fstream>
const string ObservationDataPath = "Observationdata.txt";

vector<string> GetObservations(string filePath, vector<string> &res)
{
    fstream f;
    vector<string> Observations;
    f.open(ObservationDataPath);
    string line ="";
    while(getline(f,line))
    {
        Observations.push_back(line.substr(1,1));
        res.push_back((line[5]=='I') ? "Inbalanced" : "Balanced");
    }
    f.close();
    return Observations;
}

int main()
{
    vector<string> res;
    vector<string> Observations = GetObservations(ObservationDataPath,res);
    vector<string> O{"1", "2", "3", "4", "5", "6"};
    vector<string> States{"Balanced", "Inbalanced"};
    vector<double> Pi = {0.5, 0.5};
    vector<vector<double>> Trans = {{0.8, 0.2}, {0.7, 0.3}};
    vector<vector<double>> Emission = {{1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6}, {0.1, 0.1, 0.1, 0.1, 0.1, 0.5}};
    vector<string> predictionState = ViterbiAlgorithm(Observations, O, States, Pi, Trans, Emission);

    //Prediction (calc accuracy)
    int positive = 0;
    for(int i = 0 ; i<predictionState.size();i++)
    {
        if(predictionState[i] == res[i])
            positive++;
    }
    cout << "Accuracy = " << positive << "%";
    // 
}

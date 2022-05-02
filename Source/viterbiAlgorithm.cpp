#include"viterbiAlgorithm.h"

//Hàm lấy xác suất trong bảng Emission tại Observation cho trước và State thứ j trong 
//bảng các State
/*
    Giả sử có States("Heathy","Fever") và Observations(Normal, cold, dizzy)
    Khi gọi hàm GetEmissionProb("Heathy",1,Emisssion,States) sẽ trả về xác xuất Emission["Heathy"]["Normal"]
chính xác suất khi quan sát Normal biểu thị trạng thái Healthy
*/
double GetEmissionProb(string Observation, int j, vector<vector<double>> Emission, vector<string> O)
{
    for (int i = 0; i < O.size(); i++)
        if (O[i] == Observation)
        {
            return Emission[j][i];
        }
    return 0;
}
//Hàm in ra đường đi tối ưu nhất với maxIndex là vị trí cuối cùng của State tối ưu
//Vector Path lưu đường đi tối ưu nhất, vector States để truy xuất đường đi từ Path
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

//Hàm thuật toán Viterbi
/*
    - Observations là vector các quan sát được
    - O là vector là tập các giá trị có thể quan sát được
    - States là tập các trạng thái ẩn
    - Pi là tập xác suất khởi tạo
    - Trans và Emission lần lượt là tập xác suất chuyển tiếp và xác suất "Emission"
*/
void ViterbiAlgorithm(vector<string> Observations, vector<string> O, vector<string> States, 
vector<double> Pi, vector<vector<double>> Trans, vector<vector<double>> Emission)
{
    //V lưu xác suất tối ưu nhất tới Observation thứ i với States j
    vector<vector<double>> V(Observations.size(), vector<double>(States.size()));
    //Path lưu đường đi của xác suất tối ưu đó
    //Path[i][j] lưu vị trí tối ưu nhất của States của Observation trước đó (theo tinh thần 
    //quy hoạch động)
    vector<vector<int>> Path(Observations.size(), vector<int>(States.size()));
    //Khởi tạo V
    for (int i = 0; i < States.size(); i++)
    {
        V[0][i] = Pi[i] * GetEmissionProb(Observations[0], i, Emission, O);
        Path[0][i] = 0;
    }
    // Chạy dòng for trên mỗi observation
    for (int i = 1; i < Observations.size(); i++)
    {
        // Chạy các State j tương ứng với Observation i
        for (int j = 0; j < States.size(); j++)
        {
            double maxP = -1;
            //Tìm đường đi tối ưu nhất tới State hiện tại từ Observation trước đó (
            //dùng công thức quy hoạch động)
            for (int k = 0; k < States.size(); k++)
            {
                //Nếu đường đi có xác suất bằng 0 thì bỏ đường đi đó
                if (V[i - 1][k] == 0)
                    continue;
                double cmpNum = V[i - 1][k] * Trans[k][j] * GetEmissionProb(Observations[i], j, Emission, O);
                if (cmpNum > maxP)
                {
                    maxP = cmpNum;
                    //Lưu vị trí đường đi tối ưu
                    Path[i][j] = k;
                }
            }
            V[i][j] = maxP;
        }
    }
    //Sau khi tìm được ma trận V, ta tìm xác suất có khả nang xảy ra cao nhất
    //MaxIndex là biến đại diện thứ tự của States có khả năng xảy ra cao nhất của Observation cuối cùng
    //Bắt đầu tìm xác suất tối ưu trong V(Chỉ duyệt cột cuối cùng)
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
    //In ra đường đi tương ứng với xác suất đó
    PrintPath(maxIndex, Path, States);
    cout << endl
         << "With highest probability of " << maxProbability << endl;
}


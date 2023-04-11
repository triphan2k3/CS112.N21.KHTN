
#include <bits/stdc++.h>

using namespace std;

const string TASKNAME = "RELAX";  //ten bai`

typedef long long ll;
typedef pair<int, int> ptq;

const int iFirst = 1;
const int iLast = 10;



template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to)
{
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
    <
        std::is_integral<Numeric>::value
        , std::uniform_int_distribution<Numeric>
        , std::uniform_real_distribution<Numeric>
    >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}

string intToString(int x)
{
    stringstream ss;
    ss << x;
    string st; ss >> st;
    if (x < 10) st = "0" + st;
    if (x == 0) st = "00";
    return st;
}


void MakeTest(ofstream& cout, int iTest)  // ham sinh test
{
    if (iTest == 1) {
        cout << "1\n1 1";
        return;
    }

    int low = 1;
    int high = 15;
    if (iTest > 5)
        low = 500, high = 1000;

    int t = random(150, 200);
    cout << t;
    while (t--) {
        int a = random(low, high);
        int b = random(low, high);
        cout << '\n' << a << ' ' << b;
    }
}

int main()
{
    srand(time(NULL));

    #ifdef __linux__
        system(((string)"rm -rf INPUT").c_str());
        system(((string)"rm -rf OUTPUT").c_str());
    #endif

    system(((string)"mkdir INPUT").c_str()); // create INP forder 
    system(((string)"mkdir OUTPUT").c_str()); // creata OUT forder

    string inputForder = "INPUT";
    string outputForder = "OUTPUT";
    for(int iTest = iFirst; iTest <= iLast; iTest++)
    {
        //string testForder = TASKNAME + "\\Test" + intToString(iTest); //ten folder SUM\\Test
    
        string inputFile = TASKNAME + ".INP";
        string outputFile = TASKNAME + ".OUT";
        //system(("mkdir " + testForder).c_str());
        ofstream inp (inputFile.c_str());

        MakeTest(inp, iTest);
        inp.close();
        
        #ifdef __linux__
            system(("./"+TASKNAME).c_str());  // bat buoc phai co file (TASKNAME + ".exe") thi chuong trinh moi chay duoc
        #else
            system((TASKNAME+".exe").c_str())
        #endif

        string newinputFile = intToString(iTest) + ".INP";
        string newoutputFile = intToString(iTest) + ".OUT";

        #ifdef __linux__
            system(("mv " + inputFile + " ./" + inputForder + "/" + newinputFile).c_str());
            system(("mv " + outputFile + " ./" + outputForder + "/" + newoutputFile).c_str());
        #else
            system(("rename " + inputFile + " " + newinputFile).c_str());
            system(("rename " + outputFile + " " + newoutputFile).c_str());

            system(("move /y " + newinputFile + " " + inputForder).c_str());
            system(("move /y " + newoutputFile + " " + outputForder).c_str());
        #endif
    }
}
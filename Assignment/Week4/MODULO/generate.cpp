
#include <bits/stdc++.h>

using namespace std;

const string TASKNAME = "MODULO";  //ten bai`

typedef long long ll;
typedef pair<int, int> ptq;

const int iFirst = 0;
const int iLast = 40;



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
    if (iTest <= 8) {
        if (iTest == 0) {
            cout << "2\n1 4 4 5\n2 8 3 2";
            return;
        }
        if (iTest == 1) {
            cout << 45*45*45;
            for (int a = 1; a <= 45; a++)
            for (int b = 1; b <= 45; b++)
            for (int c = 1; c <= 45; c++)
                cout << '\n' << 1 << " " << a << " " << b << " " << c;
            return;
        }
        int t = random(50000, 100000);
        cout << t;
        while(t--) {
            int a = random(1, 1000000000);
            int b = random(1, 1000000000);
            int c = random(1, 1000000000);
            cout << '\n' << 1 << " " << a << " " << b << " " << c;
        }
    } else if (iTest <= 16) {
        int t = random(800, 1000);
        cout << t;
        while (t--) {
            int a = random(1, 10000);
            int b = random(1, min(a, 100));
            int c = random(1, min(a, 100));
            cout << '\n' << 2 << " " << a << " " << b << " " << c;
        }
    } else if (iTest <= 24) {
        int t = random(80000, 100000);
        cout << t;
        while (t--) {
            int a = random(1, 1000000000);
            int b = random(1, min(a, 100000));
            int c = random(1, min(a, 100000));
            int type = random(1, 2);
            cout << '\n' << type << " " << a << " " << b << " " << c;
        }
    } else {
        int t = random(80000, 100000);
        cout << t;
        while (t--) {
            ll a = random(1LL, (ll)1e18);
            ll b = random(1LL, min(a, (ll)1e12));
            ll c = random(1LL, min(a, (ll)1e12));
            int type = random(1, 2);
            cout << '\n' << type << " " << a << " " << b << " " << c;
        }
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
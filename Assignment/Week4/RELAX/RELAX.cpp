#include <bits/stdc++.h>
#define TASK ""
#define pb push_back
#define F first
#define S second
#define FOR(i, a, b) for (int i=a; i<=b; i++)
#define FOr(i, a, b) for (int i=a; i<b ; i++)
#define FOD(i, a, b) for (int i=a; i>=b; i--)
#define FOd(i, a, b) for (int i=a; i>b ; i--)
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;

const int N=1e6+7;
const int MOD=1e9+7;
const ll INF=(ll)1e18+7;

class bigNum {
    private:
        vector<int> digits;
    public:
        bigNum() {}
        bigNum(int a) {
            if (a == 0) {
                digits.push_back(0);
            }
            else {
                while (a) {
                    digits.push_back(a % 10);
                    a /= 10;
                }
            }
        }
        
        bigNum operator + (bigNum other) {
            bigNum res;
            int carry = 0;
            for (int i = 0; i < max(digits.size(), other.digits.size()); i++) {
                if (i >= digits.size())
                    carry += other.digits[i];
                else if (i >= other.digits.size())
                    carry += digits[i];
                else
                    carry += digits[i] + other.digits[i];
                res.digits.push_back(carry % 10);
                carry /= 10;
            }
            if (carry)
                res.digits.push_back(1);
            return res;
        }

        bigNum operator * (bigNum other) {
            bigNum res;
            res.digits = vector<int> (digits.size() + other.digits.size() - 1, 0);
            for (int i = 0; i < digits.size(); i++)
                for (int j = 0; j < other.digits.size(); j++)
                    res.digits[i + j] += digits[i] * other.digits[j];
            for (int i = 0; i + 1 < res.digits.size(); i++) {
                res.digits[i + 1] += res.digits[i] / 10;
                res.digits[i] %= 10;
            }
            if (res.digits.back() >= 10) {
                int tempVal = res.digits.back() / 10;
                res.digits.back() %= 10;
                res.digits.push_back(tempVal);
            }
            return res;
        }

        bigNum operator ^ (int y) {
            if (y == 0) {
                return bigNum(1);
            }
            bigNum temp = (*this) ^ (y / 2);
            if (y % 2)
                return temp * temp * (*this);
            return temp * temp;
        }
        friend ostream& operator << (ostream& cout, bigNum num);
};

ostream& operator << (ostream& cout, bigNum num) {
    for (int i = num.digits.size() - 1; i >= 0; i--) {
        cout << num.digits[i];
    }
    return cout;
}

int main() {
    freopen("RELAX.INP","r",stdin);
    freopen("RELAX.OUT","w",stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, a, b;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        cout << (bigNum(a) ^ b) + (bigNum(b) ^ a) << "\n";
    }
}
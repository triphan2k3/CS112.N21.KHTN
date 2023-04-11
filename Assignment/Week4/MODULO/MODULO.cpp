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

ll mulmod(ll a, ll b, ll m) {
    if (a == 0) return 0;
    if (b == 0) return 0;

    ll tmp = mulmod(a, b / 2, m);
    tmp = tmp * 2 % m;

    if (b & 1) tmp = (tmp + a) % m;
    return tmp;
}

int main() {
    freopen("MODULO.INP", "r", stdin);
    freopen("MODULO.OUT", "w", stdout);

    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; 
    cin >> t;
    while (t--) {
        int type; 
        ll a, b, c; 
        cin >> type >> a >> b >> c;
        if (type == 1) 
            cout << mulmod(a, b, c) << '\n';
        else {
            ll gcd = __gcd(b, c);
            ll del = b / gcd;
            if (del > a / c) 
                cout << min(b, c) - 1 << '\n';
            else {
                del *= c;
                ll num = a / del;
                ll ans = num * min(b, c);
                ans += min({b, c, a - num * del + 1});
                --ans;
                cout << ans << '\n';
            }
        }
    }
    return 0;
}

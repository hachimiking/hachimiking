#include <bits/stdc++.h>

using namespace std;
const int maxn = 1005, inf = 1e9 + 7;

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    s = " " + s;
    t = " " + t;
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, inf));
    dp[0][0]=0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int flag = (s[i] == t[j] ? 0 : 1);
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + flag});
        }
    }
    cout<<"ans="<<dp[n][m]<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    //cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

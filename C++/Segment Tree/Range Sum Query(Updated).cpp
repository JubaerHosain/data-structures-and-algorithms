#include<bits/stdc++.h>
using namespace std;
#define all(v)                  v.begin(), v.end()
#define endl                    '\n'//in interactive problem should not use this
#define print(var)              cout << var << endl
#define out(a, b)               cout << a << " " << b << endl
#define rep(i, s, n)            for(int i = s; i < n; i++)
#define rrep(i, n, s)           for(int i = n; i >= s; i--)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 2e5+5;

/*************Range Sum Query*************/
vector<int> a(N);
vector<int> tree(4*N);

int buildST(int i, int l, int r) {
    if(l == r) 
        return tree[i] = a[l];
    
    int mid = (l + r) / 2;
    return tree[i] = buildST(2*i+1, l, mid) + buildST(2*i+2, mid+1, r);
}

int get_sum(int i, int sl, int sr, int l, int r) {
    if(sl >= l && sr <= r)          // total overlap
        return tree[i];
    else if(sr < l || r < sl)       // no overlap;
        return 0;

    int mid = (sl + sr) / 2;
    return get_sum(2*i+1, sl, mid, l, r) + get_sum(2*i+2, mid+1, sr, l, r);
}

void update(int i, int sl, int sr, int pos, int diff) {
    if(pos < sl || pos > sr) 
        return;

    tree[i] += diff;
    if(sl != sr) {
        int mid = (sl + sr) / 2;
        update(2*i+1, sl, mid, pos, diff);
        update(2*i+2, mid+1, sr, pos, diff);
    }
}

int get_sum(int l, int r, int n) {
    return get_sum(0, 0, n-1, l, r);
}

void update(int pos, int val, int n) {
    int diff = val - a[pos];
    update(0, 0, n-1, pos, diff);
}

/*************User defined function*************/
void solve() {
    int n;
    cin >> n;

    rep(i, 0, n) cin >> a[i];

    //must have to call buildST function first
    //root of the tree is 0'th index
    buildST(0, 0, n-1);

    update(9, 1, n);

    print(get_sum(0, n-1, n));
    print(get_sum(2, 5, n));
    print(get_sum(3, 6, n));
    print(get_sum(2, 7, n));
} 

/*************main function*************/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    cout << fixed << showpoint;
    cout << setprecision(16);

    int test = 1;
    //cin >> test;
    while(test--) {
        solve();
    }

    return 0;
}    

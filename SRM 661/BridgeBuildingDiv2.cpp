#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int INF=~0U>>2;
const int MAXN=15;
int ar[MAXN];
vector<int> a,b;
int mat[MAXN<<1][MAXN<<1];
class BridgeBuildingDiv2 {
	int ans;
	int n,k;
	int calc()
	{
		memset(mat,-1,sizeof(mat));
		for(int i=0;i<n-1;++i)
			mat[i][i+1]=mat[i+1][i]=a[i];
		for(int i=0;i<n-1;++i)
			mat[i+n][i+n+1]=mat[i+n+1][i+n]=b[i];
		for(int i=0;i<2*n;++i)
			for(int j=0;j<2*n;++j)
			{
				if(mat[i][j]!=-1) continue;
				if(i==j) mat[i][j]=0;
				else mat[i][j]=INF;
			}
		for(int i=0;i<k;++i) mat[ar[i]][ar[i]+n]=mat[ar[i]+n][ar[i]]=0;
		int res=0;
		for(int k=0;k<n*2;++k)
			for(int i=0;i<n*2;++i)
				for(int j=0;j<n*2;++j)
					mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
		for(int i=0;i<n*2;++i)
			for(int j=0;j<n*2;++j)
				res=max(res,mat[i][j]);
				//printf("%d\n",mat[i][j]);
		return res;
	}
	void dfs(int cur,int dep)
	{
		if(dep==k)
		{
			ans=min(ans,calc());
			return;
		}
		for(int i=cur;i<n;++i)
		{
			ar[dep]=i;
			dfs(i+1,dep+1);
		}
	}
    public:
    int minDiameter(vector<int> _a, vector<int> _b, int K) {
		a=_a;b=_b;
		n=a.size()+1;k=K;
		ans=INF;
		dfs(0,0);
		return ans;
    }
};

// CUT begin
ifstream data("BridgeBuildingDiv2.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<int> a, vector<int> b, int K, int __expected) {
    time_t startClock = clock();
    BridgeBuildingDiv2 *instance = new BridgeBuildingDiv2();
    int __result = instance->minDiameter(a, b, K);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1434115571;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "BridgeBuildingDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

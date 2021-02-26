#include <bits/stdc++.h>
using namespace std;

vector< string > combs;
void combo(vector<string> a, int n, int r, int index, vector<string> data, int i) {
    if (index == r)  
    {  
        string c = "";
        for (int j = 0; j < r; j++)  
            c += data[j] + "^";  
        combs.push_back(c); 
        return;  
    }  
    if (i >= n)  
        return;  
  
    data[index] = a[i];  
    combo(a, n, r, index + 1, data, i + 1);  
    combo(a, n, r, index, data, i+1);  
}

void genProb(int k, int m, int n) {
    vector<string> posVars;
    char chara = 'a';
    for(int i=0; i<n; i++) {
        string s;
        s.insert(0, 1, chara);
        posVars.push_back(s);
        chara++;
    }

    vector<string> negVars;
    for(int i=0; i<n; i++){
        negVars.push_back("~" + posVars[i]);
    }

    vector<string> totalVars = posVars;
    totalVars.insert(totalVars.begin()+n, negVars.begin(), negVars.end());

    vector<string> data(k);

    combo(totalVars, n*2, k, 0, data, 0);

    map<string, int> problems;
    string problem;

    for(int i=0; i<m; ) {
        srand(time(0));
        int pos = rand() % (n*2);
        string p = combs[pos];
        if (problems[p] == 0 ){
            i++;
            problems[p]++;
        }
    }

    for(auto i=problems.begin(); i!=problems.end(); i++){
        cout<<" ("<<(*i).first<<") ";
    }
    cout<<endl;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int k, m, n;
    cout<<"Enter length of each clause:\t"<<flush;
    cin >> k;
    cout<<"Enter number of clauses:\t"<<flush;
    cin >> m;
    cout<<"Enter number of variables:\t"<<flush;
    cin >> n;
    genProb(k, m, n);
    return 0;
}

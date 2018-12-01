#include<bits/stdc++.h>
using namespace std;

struct node
{
    string process;
    int arrival;
    int cpu;

    node(string p,int a,int c)
    {
        process = p;
        arrival = a;
        cpu = c;
    }
};

bool cmp(node a,node b)
{
    return a.arrival < b.arrival;
}

struct compare
{
    bool operator()(node a,node b)
    {
        if(a.cpu == b.cpu)
            return a.arrival > b.arrival;

        return a.cpu > b.cpu;
    }
};

int main()
{
    int n;
    cout<<"Enter the number of process: ";
    cin>>n;

    vector<node>v;
    map<string,int>mp;

    int maxi = 0;

    for(int i=0; i<n; i++)
    {
        string p;
        int a,c;

        cin>>p>>a>>c;
        v.push_back(node(p,a,c));
        mp[p] = i+1;
    }

    sort(v.begin(),v.end(),cmp);
    int cnt = 0;

    priority_queue<node,vector<node>,compare >pq;
    vector<pair<int,int> >wait[10];

    int total = 0;
    int tb,ta;

    for(int i=0,j=i+1; j<=v.size(); i++,j++)
    {
        string _p;
        int diff,_a,_cpu;

        tb = total;

        if(j<v.size())
        {
            diff = v[j].arrival - v[i].arrival;
        }

        _p = v[i].process;
        _a = v[i].arrival;
        _cpu = v[i].cpu;

        pq.push(node(_p,_a,_cpu));

        if(i == v.size()-1) break;

        _p = pq.top().process;
        _a = pq.top().arrival;
        _cpu = pq.top().cpu;

        if(_cpu > diff)
        {
            total += diff;
            _cpu -= diff;

            pq.pop();
            pq.push(node(_p,_a,_cpu));
        }

        else
        {
            total += _cpu;
            pq.pop();
        }

        ta = total;
        wait[mp[_p]].push_back({tb,ta});
    }

    while(!pq.empty())
    {
        string _p = pq.top().process;
        tb = total;
        int _cpu = pq.top().cpu;
        total += _cpu;
        ta = total;

        wait[mp[_p]].push_back({tb,ta});
        pq.pop();
    }

    int waiting_time;
    int total_waiting_time = 0;
    int total_turn_around_time = 0;

    for(int i=1; i<=n; i++)
    {
        int sz = wait[i].size();
        int init = v[i-1].arrival;
        waiting_time = 0;

        for(int j=0; j<sz; j++)
        {
            int starting = wait[i][j].first - init;
            waiting_time += starting;
            init = wait[i][j].second;
        }

        total_waiting_time += waiting_time;
        total_turn_around_time += waiting_time + v[i-1].cpu;
    }

    double avrg_waiting = (double)total_waiting_time / (double)n;
    double avrg_turn_around = (double)total_turn_around_time / (double)n;

    cout<<"\nAverage waiting time: "<<setprecision(2)<<fixed<<avrg_waiting<<endl;
    cout<<"Average turn around time: "<<setprecision(2)<<fixed<<avrg_turn_around<<endl;

    return 0;
}

/**
os theory lecture
p1 0 7
p2 2 4
p3 4 1
p4 5 4
*/


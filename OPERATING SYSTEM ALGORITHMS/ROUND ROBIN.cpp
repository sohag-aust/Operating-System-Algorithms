#include<bits/stdc++.h>
using namespace std;

typedef tuple<string,int,int> tii;
int visit[10] = {0};

struct node
{
    string process;
    int process_id;
    int arrival;
    int cpu;
} st[10];

bool cmp(node a,node b)
{
    if(a.arrival == b.arrival)
        return a.process_id < b.process_id;

    return a.arrival < b.arrival;
}

int main()
{
    int n;

    cout<<"Enter the number of process: ";
    cin>>n;

    map<string,int>mp;

    for(int i=0; i<n; i++)
    {
        cin>>st[i].process>>st[i].arrival>>st[i].cpu;
        st[i].process_id = i+1;
        mp[st[i].process] = i+1;
    }

    sort(st,st+n,cmp);

    queue<tii>q;

    int quan;

    cout<<"Enter the time quantum: ";
    cin>>quan;

    q.push(tii(st[0].process,st[0].process_id,st[0].cpu));
    visit[st[0].process_id] = 1;

    int total_time = 0;
    int cnt = 0;

    vector<pair<int,int> >wait[10];

    int tb,ta;

    while(!q.empty())
    {
        string _process = get<0>(q.front());
        int _process_id = get<1>(q.front());
        int _cpu = get<2>(q.front());

        tb = total_time;

        if(_cpu < quan)
            total_time += _cpu;

        else
            total_time += quan;

        _cpu -= quan;

        ta = total_time;

        wait[mp[_process]].push_back({tb,ta});

        q.pop();

        if(cnt < n)
        {
            for(int i=0; i<n; i++)
            {
                int _process_id1 = st[i].process_id;

                if(!visit[_process_id1] && st[i].arrival <= total_time)
                {
                    cnt++;
                    q.push(tii(st[i].process,st[i].process_id,st[i].cpu));
                    visit[_process_id1] = 1;
                }
            }
        }

        if(_cpu > 0)
            q.push(tii(_process,_process_id,_cpu));
    }

    int waiting_time;
    int total_waiting_time = 0;
    int total_turn_around_time = 0;

    for(int i=1; i<=n; i++)
    {
        int sz = wait[i].size();
        int init = st[i-1].arrival;
        waiting_time = 0;

        for(int j=0; j<sz; j++)
        {
            int starting = wait[i][j].first - init;
            waiting_time += starting;
            init = wait[i][j].second;
        }

        total_waiting_time += waiting_time;
        total_turn_around_time += waiting_time + st[i-1].cpu;
    }

    double avrg_waiting = (double)total_waiting_time / (double)n;
    double avrg_turn_around = (double)total_turn_around_time / (double)n;

    cout<<"\nAverage waiting time: "<<setprecision(2)<<fixed<<avrg_waiting<<endl;
    cout<<"Average turn around time: "<<setprecision(2)<<fixed<<avrg_turn_around<<endl;

    return 0;
}

/** moinul sir

p1 0 7
p2 2 4
p3 5 5
p4 9 4
p5 13 3
*/

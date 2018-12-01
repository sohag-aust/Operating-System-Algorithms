#include<bits/stdc++.h>
using namespace std;

map<int,string>mp;
map<int,pair<int,int> >mp1;

struct node
{
    string process;
    int process_id;
    int arrival;
    int cpu;
    int priority;

    node(string p,int pid,int ar,int cp,int prio)
    {
        process = p;
        process_id = pid;
        arrival = ar;
        cpu = cp;
        priority = prio;
    }
};

struct compare
{
    bool operator()(node a, node b)
    {
        return a.priority > b.priority; /// creating min heap ; (<) dile max heap hoe jabe;
    }
};

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

    vector<node>v;

    for(int i=0; i<n; i++)
    {
        string p;
        int pid,arr,cp,prio;

        cin>>p>>arr>>cp>>prio;
        pid = i+1;

        mp[pid] = p;
        mp1[pid] = {arr,cp};

        v.push_back(node(p,pid,arr,cp,prio));
    }

    sort(v.begin(),v.end(),cmp);

    priority_queue<node, vector<node>, compare>pq,pq1;

    int gantt = 0;
    int cnt = 0;

    vector<int>vv[10];

    for(int i=0; i<n; i++)
    {
        int diff,_cpu,_pid1;

        if(i == 0)
        {
            diff = v[i+1].arrival - v[i].arrival;
            gantt += diff;
            _cpu = v[i].cpu;
            _cpu -= diff;

            if(_cpu > 0)
            {
                pq.push(node(v[i].process,v[i].process_id,v[i].arrival,_cpu,v[i].priority));
            }

            cnt++;
        }

        else
        {
            diff = 0;

            if(cnt <= n)
            {
                if(i+1 < n)
                {
                    diff = v[i+1].arrival - v[i].arrival;
                    gantt += diff;
                }

                if(pq.size() > 0)
                {
                    pq.push(v[i]);
                    _cpu = pq.top().cpu;

                    string _p1 = pq.top().process;
                    _pid1 = pq.top().process_id;
                    int _arrival1 = pq.top().arrival;
                    int _priority1 = pq.top().priority;

                    pq.pop();

                    if(!diff)
                    {
                        gantt += _cpu;
                        _cpu -= _cpu;
                    }

                    else
                        _cpu -= diff;

                    if(_cpu > 0)
                    {
                        pq.push(node(_p1,_pid1,_arrival1,_cpu,_priority1));
                    }
                }

                else if(pq.size() == 0)
                {
                    _cpu = v[i].cpu;
                    _cpu -= diff;

                    if(_cpu > 0)
                        pq.push(node(v[i].process,v[i].process_id,v[i].arrival,_cpu,v[i].priority));
                }

                vv[_pid1].push_back(gantt);
            }

            cnt++;
        }
    }

    pq1 = pq;

    while(!pq1.empty())
    {
        int _cpu = pq1.top().cpu;
        int _process_id = pq1.top().process_id;
        gantt += _cpu;

        vv[_process_id].push_back(gantt);
        pq1.pop();
    }

    int total_turn = 0;
    int total_waiting = 0;

    cout<<endl;

    cout<<"Process   "<<" waiting time    "<<"turn around time"<<endl;

    for(int i=1; i<=n; i++)
    {
        int sz = vv[i].size();
        int turn_around = vv[i][sz-1] - mp1[i].first;
        int waiting = turn_around - mp1[i].second;

        total_turn += turn_around;
        total_waiting += waiting;

        cout<<mp[i]<<setw(15)<<waiting<<setw(19)<<turn_around<<endl;
    }

    double avrg_turn = (double)total_turn / (double)n;
    double avrg_waiting = (double)total_waiting / (double)n;

    cout<<"\nAverage waiting time: "<<setprecision(3)<<fixed<<avrg_waiting<<endl;
    cout<<"Average turn around time: "<<setprecision(3)<<fixed<<avrg_turn<<endl;

    return 0;
}


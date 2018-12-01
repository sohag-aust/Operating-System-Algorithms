#include<bits/stdc++.h>
using namespace std;

typedef tuple<string,int,int>tii;

struct node
{
    string process;
    int process_id;
    int arrival_time;
    int cpu_time;
} st[10];

bool cmp(node a,node b)
{
    if(a.arrival_time == b.arrival_time)
        return a.process_id < b.process_id;

    return a.arrival_time < b.arrival_time;
}

int main()
{
    int n;

    cout<<"Enter the number of process: ";
    cin>>n;

    for(int i=0; i<n; i++)
    {
        cin>>st[i].process>>st[i].arrival_time>>st[i].cpu_time;
        st[i].process_id = i+1;
    }

    sort(st,st+n,cmp);

    map<int,tii>mp;

    int sum = 0;
    int total_sum = 0;
    int art = 0;

    int waiting,turn_around;

    for(int i=0; i<n; i++)
    {
        if(i == 0)
        {
            waiting = st[i].arrival_time;
            total_sum += st[i].cpu_time;
            turn_around = total_sum;

            mp[i] = tii(st[i].process,waiting,turn_around);
        }

        else
        {
            waiting = total_sum - st[i].arrival_time;
            total_sum += st[i].cpu_time;
            turn_around = waiting + st[i].cpu_time;

            mp[i] = tii(st[i].process,waiting,turn_around);
        }
    }

    cout<<"\nNew Scheduling ->\n"<<endl;

    double avrg_waiting = 0;
    double avrg_turn = 0;

    for(int i=0; i<n; i++)
    {
        string a;
        int b,c;

        a = get<0>(mp[i]);
        b = get<1>(mp[i]);
        c = get<2>(mp[i]);

        avrg_waiting += b;
        avrg_turn += c;

        cout<<a<<" "<<b<<" "<<c<<endl;
    }

    cout<<endl;

    cout<<"avrg waiting time: "<<avrg_waiting/(double)n<<endl;
    cout<<"avrg_turn_around time: "<<avrg_turn/(double)n<<endl;

    return 0;
}


#include<bits/stdc++.h>
using namespace std;

const int maxi = 50;
int ara[maxi];
int visit[maxi];
int n,page,val;
map<int,int>mp;

struct node
{
    int value;
    int cnt;

    node(int v,int c)
    {
        value = v;
        cnt = c;
    }
};

struct compare
{
    bool operator()(node a, node b)
    {
        return a.cnt < b.cnt;
    }
};

priority_queue<node, vector<node>, compare>pq,temp;

void print()
{
    static int step = 0;
    cout<<"\nStep -> "<<++step<<": ";

    temp = pq;

    while(!temp.empty())
    {
        cout<<" # "<<temp.top().value<<" "<<temp.top().cnt;
        temp.pop();
    }
}

void increment(int val1)
{
    while(!pq.empty())
    {
        int top = pq.top().value;
        pq.pop();
        if(top == val && val1){val1 = 0; continue;}
        temp.push(node(top,++mp[top]));
    }
    pq = temp;
}

int lru()
{
    memset(visit,0,sizeof(visit));
    int pc = 0;
    int hit = 0;

    for(int i=0; i<n; i++)
    {
        pq.push(node(ara[i],mp[ara[i]]));

        if(pc++ < page)
        {
            if(!visit[ara[i]])
            {
                visit[ara[i]] = 1;
                increment(0);
            }

            else
            {
                mp[ara[i]] = 0;
                increment(1);
                hit++;
            }
        }

        else
        {
            int top = pq.top().value;
            val = ara[i];

            if(!visit[val])
            {
                mp[top] = 0;
                pq.pop();
                increment(0);
                visit[val] = 1;
                visit[top] = 0;
            }

            else
            {
                mp[ara[i]] = 0;
                increment(1);
                hit++;
            }
        }

        print();
    }

    return hit;
}

int main()
{
    cout<<"Enter the number of references string: ";
    cin>>n;

    cout<<"\nEnter the references values -> "<<endl;
    for(int i=0; i<n; i++)
        cin>>ara[i];

    cout<<"\nEnter the number of pages: ";
    cin>>page;

    int fault = n - lru();
    cout<<"\nNumber of page fault: "<<fault<<endl;

    cout<<"\nPage Fault Rate: "<<((fault*1.0) / (n*1.0)) * 100.0<<endl;

    return 0;
}

/// 22
/// 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
/// 3

/// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

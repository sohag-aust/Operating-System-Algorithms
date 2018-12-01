#include<bits/stdc++.h>
using namespace std;

const int maxi = 50;
int ara[maxi];
int visit[maxi] = {0};
int n,page,hit = 0,index,val;

vector<int>v[maxi];
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
        if(a.cnt == b.cnt) return a.value < b.value;
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

void _update(int val1)
{
    while(!pq.empty())
    {
        int top = pq.top().value;
        int ind = pq.top().cnt;
        pq.pop();
        if(top == val && val1){val1 = 0; continue;}
        temp.push(node(top,ind));
    }
    pq = temp;
}

void _generate()
{
    mp[val]++;

    if(mp[val] >= v[val].size())
        index = INT_MAX;
    else
        index = v[val][mp[val]];

    pq.push(node(val,index));
}

int optimal()
{
    int pg = 0;

    for(int i=0; i<n; i++)
    {
        val = ara[i];

        if(pg++ < page)
        {
            if(!visit[val])
            {
                _generate();
                visit[val] = 1;
            }

            else
            {
                hit++;
                _update(1);
                _generate();
            }
        }

        else
        {
            if(!visit[val])
            {
                int top = pq.top().value;
                pq.pop();
                _generate();
                visit[val] = 1;
                visit[top] = 0;
            }

            else
            {
                hit++;
                _update(1);
                _generate();
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
    {
        cin>>ara[i];
        v[ara[i]].push_back(i);
    }

    cout<<"\nEnter the number of pages: ";
    cin>>page;

    int fault = n - optimal();
    cout<<"\nNumber of page fault: "<<fault<<endl;
    cout<<"\nPage Fault Rate: "<<((fault*1.0) / (n*1.0)) * 100.0<<endl;

    return 0;
}

/// 22
/// 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
/// 3

/// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

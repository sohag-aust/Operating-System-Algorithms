#include<bits/stdc++.h>
using namespace std;

const int maxi = 30;
int visit[maxi];
int ara[maxi];
deque<int>dq;

void print()
{
    static int cs = 0;
    cout<<"Step: "<<++cs<<" -> ";
    deque<int>::iterator it = dq.begin();
    while(it!=dq.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}

void update(int val)
{
    deque<int>::iterator it = dq.begin();
    it = find(dq.begin(), dq.end(), val);
    int pos = it-dq.begin();
    dq.erase(dq.begin()+pos);
}

int main()
{
    int n,page;

    cout<<"Enter number of page: ";
    cin>>page;
    cout<<"\nEnter number of references value: ";
    cin>>n;

    cout<<"\nEnter the values -> "<<endl;

    for(int i=0; i<n; i++)
        cin>>ara[i];

    cout<<endl;

    for(int i=0; i<n; i++)
    {
        int temp = ara[i];

        if(!visit[temp] && page)
        {
            dq.push_front(temp);
            visit[temp] = 1;
            page--;
        }

        else if(visit[temp] && page) continue;

        else if(!visit[temp] && !page)
        {
            int last = dq.at(dq.size()-1);
            dq.pop_back();
            dq.push_front(temp);
            visit[last] = 0;
            visit[temp] = 1;
        }

        else
        {
            update(temp);
            dq.push_front(temp);
        }

        print();
    }

    return 0;
}

/// 22 3
/// 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1


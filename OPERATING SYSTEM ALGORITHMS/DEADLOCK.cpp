#include<bits/stdc++.h>
using namespace std;

const int maxi=30;

map<string,int>mp1;
map<int,string>mp2;
vector<int>edges[maxi];
vector<int>redges[maxi];
vector<int>temp;
stack<int>st;
bool visit[maxi];

void dfs(int i)
{
    if(visit[i]) return ;

    visit[i]=true;

    int si=edges[i].size();

    for(int j=0; j<si; j++)
    {
        int val=edges[i][j];

        if(!visit[val])
            dfs(val);
    }

    st.push(i);
}

void dfs_rev(int i)
{
    if(visit[i]) return ;

    temp.push_back(i);

    visit[i]=true;

    int si=redges[i].size();

    for(int j=0; j<si; j++)
    {
        int val=redges[i][j];

        if(!visit[val])
            dfs_rev(val);
    }
}

int main()
{
    int node,edge;

    cout<<"Enter the no.of node: ";
    cin>>node;

    cout<<"Enter the no.of edge: ";
    cin>>edge;

    cout<<"Enter the edges: "<<endl;

    for(int i=1; i<=edge; i++)
    {
        static int cnt = 0;
        string s1,s2;
        cin>>s1>>s2;

        if(mp1[s1] == 0)
        {
            mp1[s1] = ++cnt;
            mp2[cnt] = s1;
        }

        if(mp1[s2] == 0)
        {
            mp1[s2] = ++cnt;
            mp2[cnt] = s2;
        }

        edges[mp1[s1]].push_back(mp1[s2]);
        redges[mp1[s2]].push_back(mp1[s1]);
    }

    cout<<"Deadlock Detected Among nodes -> "<<endl;

    memset(visit,false,sizeof(visit));

    for(int i=1; i<=node; i++)
    {
        if(!visit[i])
            dfs(i);
    }

    memset(visit,false,sizeof(visit));

    int cnt=0,flag;

    while(!st.empty())
    {
        flag=0;
        int top=st.top();
        st.pop();

        temp.clear();

        dfs_rev(top);

        sort(temp.begin(),temp.end());

        int si=temp.size();

        if(si > 1)
        {
            for(int j=0; j<si; j++)
            {
                cout<<mp2[temp[j]]<<" ";
            }

            cout<<endl;
        }
    }

    return 0;
}

/**
13
13

R A
A S
C S
F S
W F
D S
D T
T E
E V
V G
G U
U D
B T
*/

/**
6
7

1 2
2 3
3 1
2 4
4 5
5 6
6 4
*/

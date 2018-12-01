#include<bits/stdc++.h>
using namespace std;

const int maxi = 10;

int allocation[maxi][maxi];
int maximum[maxi][maxi];
int need[maxi][maxi];
int available[maxi];
int resources[maxi];
int visit[maxi] = {0};
int no_p,cnt = 0;

vector<int>ans;

void bankers_algo()
{
    while(cnt < no_p)
    {
        bool ok = true;

        for(int i=0;i<no_p;i++)
        {
            ok = true;

            for(int j=0;j<3;j++)
            {
                int val = need[i][j];

                if(val > available[j])
                {
                    ok = false;
                    break;
                }
            }

            if(ok && !visit[i])
            {
                for(int j=0;j<3;j++)
                    available[j] += allocation[i][j];

                cnt++;
                ans.push_back(i+1);
                visit[i] = 1;
                break;
            }
        }
    }
}

int main()
{
    cout<<"Enter the resources of A, B, C -> "<<endl;

    for(int i=0;i<3;i++) cin>>resources[i];

    cout<<"\nEnter the number of process: ";
    cin>>no_p;

    cout<<"\nEnter the Allocation Matrix -> "<<endl;
    for(int i=0; i<no_p; i++)
    {
        for(int j=0; j<3; j++)
        {
            cin>>allocation[i][j];
        }
    }

    cout<<"\nEnter the Max Matrix -> "<<endl;
    for(int i=0;i<no_p;i++)
    {
        for(int j=0;j<3;j++)
        {
            cin>>maximum[i][j];
        }
    }

    cout<<"\nThe Need Matrix -> "<<endl;
    for(int i=0;i<no_p;i++)
    {
        for(int j=0;j<3;j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            cout<<need[i][j]<<" ";
        }

        cout<<endl;
    }

    memset(available,0,sizeof(available));

    for(int j=0;j<3;j++)
    {
        for(int i=0;i<no_p;i++)
        {
            available[j] += allocation[i][j];
        }

        available[j] = resources[j] - available[j];
    }

    bankers_algo();

    cout<<"\nProcesses : <";

    for(int i=0;i<ans.size();i++)
    {
        cout<<"P"<<ans[i]<<" ";
    }
    cout<<"> is the safe sequences."<<endl;

    return 0;
}


/**
lab manual test case - 1:

resources:
20 19 16

process:
7

allocation:
1 1 1
2 3 3
3 0 5
2 2 0
3 1 0
1 2 1
1 1 1

max:
7 5 6
5 8 5
9 2 8
8 8 6
14 4 5
4 6 3
2 9 2
*/


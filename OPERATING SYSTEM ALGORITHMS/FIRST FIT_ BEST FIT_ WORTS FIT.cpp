#include<bits/stdc++.h>
using namespace std;

const int maxi = 10;
int process[maxi];
int holes[maxi];
int temp[maxi];
int np,hole;

struct node
{
    int val;
    int id;
} st[maxi];

bool cmp(node a,node b)
{
    if(a.val == b.val) return a.id < b.id;
    return a.val < b.val;
}

bool cmp1(node a,node b)
{
    if(a.val == b.val) return a.id < b.id;
    return a.val > b.val;
}

void print()
{
    static int cnt = 0;
    cout<<"Step -> "<<++cnt<<": ";

    for(int i=0; i<hole; i++)
        cout<<temp[i]<<" ";
    cout<<endl;
}

void fragmentation()
{
    int sum = 0;
    cout<<"\nExternal Fragmentation: ";

    for(int i=0; i<hole; i++)
        sum += temp[i];

    cout<<sum<<endl;
}

void first_fit()
{
    cout<<endl;

    for(int i=0; i<np; i++)
    {
        int process_value = process[i];
        bool ok = false;

        for(int j=0; j<hole; j++)
        {
            int hole_value = temp[j];

            if(process_value <= hole_value)
            {
                temp[j] -= process_value;
                ok = true;
                break;
            }
        }

        if(!ok)
        {
            fragmentation();
            return ;
        }

        print();
    }

    cout<<"\nNo External Fragmentation.."<<endl;
}

void Fitting()
{
    for(int i=0; i<np; i++)
    {
        int process_value = process[i];
        bool ok = false;

        for(int j=0; j<hole; j++)
        {
            int hole_value = st[j].val;

            if(process_value <= hole_value)
            {
                temp[st[j].id] -= process_value;
                st[j].val = temp[st[j].id];
                ok = true;
                break;
            }
        }

        if(!ok)
        {
            fragmentation();
            return ;
        }

        print();
    }

    cout<<"\nNo External Fragmentation.."<<endl;
}

void best_fit()
{
    cout<<endl;

    for(int i=0; i<hole; i++)
    {
        st[i].val = holes[i];
        st[i].id = i;
    }

    sort(st,st+hole,cmp);

    Fitting();
}

void worst_fit()
{
    cout<<endl;

    for(int i=0; i<hole; i++)
    {
        st[i].val = holes[i];
        st[i].id = i;
    }

    sort(st,st+hole,cmp1);

    Fitting();
}

int main()
{
    cout<<"Enter the number of processes: ";
    cin>>np;

    cout<<"\nEnter the processes value -> "<<endl;

    for(int i=0; i<np; i++)
        cin>>process[i];

    cout<<"\nEnter the number of holes: ";
    cin>>hole;

    cout<<"\nEnter the holes value -> "<<endl;
    for(int i=0; i<hole; i++)
    {
        cin>>holes[i];
        temp[i] = holes[i];
    }

    cout<<"\nPress '1' to run First Fit."<<endl;
    cout<<"Press '2' to run Best Fit."<<endl;
    cout<<"Press '3' to run Worst Fit."<<endl;

    cout<<"\nEnter your desire key: ";
    int press;
    cin>>press;

    switch(press)
    {
    case 1:
    {
        first_fit();
        break;
    }

    case 2:
    {
        best_fit();
        break;
    }

    case 3:
    {
        worst_fit();
        break;
    }
    }

    return 0;
}
/// number of process: 7
/// process val: 5 20 5 50 130 45 35
/// number of hole: 6
/// holes val: 20 50 100 130 5 5

/// output: first = 55 ; best = no ; worst = 230;


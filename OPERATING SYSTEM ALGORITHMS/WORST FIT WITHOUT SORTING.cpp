#include<bits/stdc++.h>
using namespace std;

const int maxi = 10;

int np,hole;
int process[maxi];
int holes[maxi];

void print()
{
    static int cnt = 0;

    cout<<"\nStep: "<<++cnt<<"-> ";

    for(int i=0; i<hole; i++)
        cout<<holes[i]<<" ";
    cout<<endl;
}

void fragmentation()
{
    int sum = 0;
    for(int i=0; i<hole; i++)
        sum += holes[i];

    cout<<"\nExternal Fragmentation: "<<sum<<endl;
}

void worst_fit()
{
    int max_id = 0;
    int max_val = 0;

    for(int i=0; i<np; i++)
    {
        int val = process[i];

        bool ok = false;

        for(int j=0; j<hole; j++)
        {
            int hole_val = holes[j];

            if(val <= hole_val)
            {
                if(hole_val > max_val)
                {
                    ok = true;
                    max_val = hole_val;
                    max_id = j;
                }
            }
        }

        if(!ok)
        {
            fragmentation();
            return ;
        }

        holes[max_id] -= val;
        max_val = 0;
        print();
    }

    cout<<"\nNo external Fragmentation.."<<endl;
}

int main(void)
{
    cout<<"Enter the number of process: ";
    cin>>np;

    cout<<"Enter the value of the process: ";
    for(int i=0; i<np; i++)
        cin>>process[i];

    cout<<"Enter the number of hole in the process: ";
    cin>>hole;

    cout<<"Enter the value of the holes: ";
    for(int i=0; i<hole; i++)
        cin>>holes[i];

    worst_fit();

    return 0;
}

/// 5 20 5 50 130 45 35
/// 20 50 100 130 5 5

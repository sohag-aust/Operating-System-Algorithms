#include<bits/stdc++.h>
using namespace std;

const int maxi = 30;
int visit[maxi];
int ara[maxi];

typedef struct link_list node;

struct link_list
{
    int data;
    node *link;
};

node *head = NULL;
node *last = NULL;
int cnt;

int find_last()
{
    node *temp;
    temp = head;

    while(temp!=NULL)
    {
        last = temp;
        temp = temp->link;
    }

    return last->data;
}

void insert_first(int value)
{
    node *temp;
    temp = (node*) malloc(sizeof(node));
    temp->data = value;
    temp->link = head;
    head = temp;
}

void delete_value(int value)
{
    node *temp, *f_link=NULL, *l_link;
    temp = head;

    int f,cnt;
    f = cnt = 0;

    while(true)
    {
        if(temp->data == value)
        {
            f=1;
            break;
        }

        f_link = temp;
        temp = temp->link;

        if(temp==NULL) break;
        cnt++;
    }

    if(cnt==0)
        head = temp->link;

    else
    {
        l_link = temp->link;

        if(l_link!=NULL)
            f_link->link = l_link;

        else
            f_link->link = NULL;
    }
}

void print()
{
    static int cs = 0;
    cout<<"Step: "<<++cs<<" -> ";

    node *temp;
    temp = head;

    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->link;
    }
    cout<<endl;
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
            insert_first(temp);
            visit[temp] = 1;
            page--;
        }

        else if(visit[temp] && page) continue;

        else if(!visit[temp] && !page)
        {
            int _last = find_last();
            delete_value(_last);
            insert_first(temp);
            visit[_last] = 0;
            visit[temp] = 1;
        }

        else
        {
            delete_value(temp);
            insert_first(temp);
        }

        print();
    }

    return 0;
}

/// 22 3
/// 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1



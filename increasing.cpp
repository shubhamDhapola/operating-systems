#include <bits/stdc++.h>
using namespace std;
bool 
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        vector<int> arr;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&arr[i]);
        }
        sort(arr.begin(),arr.end());
        for(int i=0;i+1<n;i++)
        {
            if(arr[i]==arr[i+1])
           { cout<<"YES"<<endl;
           break;}
        }

    }
}
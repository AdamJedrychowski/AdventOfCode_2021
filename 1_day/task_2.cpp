#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream plik;
    plik.open("data.txt", ios::in);
    int a,b,c,num=0, sum_prev, sum_curr;
    
    plik>>a;
    plik>>b;
    plik>>c;
    sum_prev=a+b+c;
    while(!plik.eof())
    {
        a=b;
        b=c;
        plik>>c;
        sum_curr=a+b+c;
        if(sum_curr>sum_prev) num++;
        sum_prev=sum_curr;
    }
    cout<<num<<endl;
    plik.close();
}
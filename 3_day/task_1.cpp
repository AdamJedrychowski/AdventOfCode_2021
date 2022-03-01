#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    fstream plik;
    plik.open("binary.txt", ios::in);
    string bin;
    int zero_amount[12]={0}, one_amount[12]={0};

    while(!plik.eof())
    {
        plik>>bin;
        for(register int i=0; i<12;i++)
        {
            if(bin[i]=='1') (one_amount[i])++;
            else (zero_amount[i])++;
        }
    }
    int gamma=0, epsilon=0;

    for( int i=0; i<12;i++)
    {
        if(one_amount[i]>zero_amount[i]) gamma+=pow(2,11-i);
        else epsilon+=pow(2,11-i);
    }
    cout<<gamma*epsilon<<endl;

    plik.close();
}
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// qsort by byl szybszy


int main()
{
    fstream plik;
    plik.open("binary.txt", ios::in);
    int num_1=0;
    {
        string temp;
        while(getline(plik, temp)) num_1++;
    }
    int num_0=num_1;
    string *bin_1 = new string[num_1], *tab_1, *bin_0 = new string[num_0], *tab_0;

    plik.close();
    plik.open("binary.txt", ios::in);
    for(int i=0; i<num_1; i++)
    {
        plik>>bin_1[i];
        bin_0[i]=bin_1[i];
    }
    plik.close();
    
    int j=0, k, one_amount;
    while(num_1!=1 && j<12)
    {
        one_amount=0;
        for(int i=0; i<num_1; i++)
            if(bin_1[i][j]=='1') one_amount++;

        k=-1;
        if(2*one_amount>=num_1)
        {
            tab_1=new string[one_amount];
            for(int i=0; i<one_amount; i++)
            {
                do{
                    k++;
                    if(bin_1[k][j]=='1')
                    tab_1[i]=bin_1[k];
                }while(bin_1[k][j]!='1');
            }
            num_1=one_amount;
        }
        else
        {
            tab_1=new string[num_1-one_amount];
            for(int i=0; i<num_1-one_amount; i++)
            {
                do{
                    k++;
                    if(bin_1[k][j]=='0')
                    tab_1[i]=bin_1[k];
                }while(bin_1[k][j]!='0');
            }
            num_1-=one_amount;
        }
        delete []bin_1;
        bin_1=tab_1;

        j++;
    }

    j=0;
    int zero_amount;
    while(num_0!=1 && j<12)
    {
        zero_amount=0;
        for(int i=0; i<num_0; i++)
            if(bin_0[i][j]=='0') zero_amount++;

        k=-1;
        if(2*zero_amount>num_0)
        {
            tab_0=new string[num_0-zero_amount];
            for(int i=0; i<num_0-zero_amount; i++)
            {
                do{
                    k++;
                    if(bin_0[k][j]=='1')
                    tab_0[i]=bin_0[k];
                }while(bin_0[k][j]!='1');
            }
            num_0-=zero_amount;
        }
        else
        {
            tab_0=new string[zero_amount];
            for(int i=0; i<zero_amount; i++)
            {
                do{
                    k++;
                    if(bin_0[k][j]=='0')
                    tab_0[i]=bin_0[k];
                }while(bin_0[k][j]!='0');
            }
            num_0=zero_amount;
        }
        delete []bin_0;
        bin_0=tab_0;

        j++;
    }

    cout<<bin_0[0]<<endl;
    cout<<bin_1[0]<<endl;

    int more=0, less=0;
    for(int i=0; i<12; i++)
    {
        more+=(bin_1[0][11-i]=='1')?pow(2,i):0;
        less+=(bin_0[0][11-i]=='1')?pow(2,i):0;
    }

    cout<<less*more<<endl;
    delete []bin_1;
    delete []bin_0;

    

    return 0;
}
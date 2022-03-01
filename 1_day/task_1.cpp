#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int a, b, num=0;
    fstream plik;
    plik.open("data.txt", ios::in);

    plik>>a;
    while(!plik.eof())
    {
        plik>>b;
        if(b>a) num++;
        a=b;
    }
    cout<<num;

    plik.close();
}
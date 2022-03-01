#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream plik;
    plik.open("commands.txt", ios::in);
    int horizontal=0, depth=0, number;
    string direction;

    while(!plik.eof())
    {
        plik>>direction;
        plik>>number;
        if(direction=="forward") horizontal+=number;
        else if(direction=="down") depth+=number;
        else depth-=number;
    }
    cout<<depth*horizontal<<endl;
    
    plik.close();
} 
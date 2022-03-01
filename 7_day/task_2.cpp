#include <iostream>
#include <fstream>
#include <cmath>

int ReadFile(int **tab, std::fstream &file);
unsigned long int MinFuel(int *tab, int size);

int main()
{
    std::fstream file;
    file.open("position.txt", std::ios::in);
    int *TabOfCrabs=new int[1];
    int CountOfCrabs=ReadFile(&TabOfCrabs, file);
    
    std::cout<<MinFuel(TabOfCrabs, CountOfCrabs)<<std::endl;

    delete []TabOfCrabs;
    return 0;
}

unsigned long int MinFuel(int *tab, int size)
{
    unsigned long int Fuel=0, MinFuel=0, n;
    for(int i=0; i<size; i++)
    {
        Fuel=0;
        for(int j=0; j<size; j++)
        {
            n=abs(i-tab[j]);
            Fuel+=n*(n+1)/2;
        }
        if(i==0) MinFuel=Fuel;
        if(MinFuel>Fuel) MinFuel=Fuel;
    }
    return MinFuel;
}

int ReadFile(int **tab, std::fstream &file)
{
    int size=0;
    while(file>>**tab)
    {
        file.seekg(1, std::ios::cur);
        size++;
    }
    file.clear();
    file.seekg(0, std::ios::beg);

    delete [](*tab);
    *tab=new int[size];

    for(int i=0; i<size; i++)
    {
        file>>*(*tab+i);
        file.seekg(1, std::ios::cur);
    }

    file.close();
    return size;
}
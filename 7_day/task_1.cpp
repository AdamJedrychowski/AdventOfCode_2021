#include <iostream>
#include <fstream>
#include <cmath>

int ReadFile(int **tab, std::fstream &file);
int compere(const void *first, const void *sec);
int MinFuel(int *tab, int size);

int main()
{
    std::fstream file;
    file.open("position.txt", std::ios::in);
    int *TabOfCrabs=new int[1];
    int CountOfCrabs=ReadFile(&TabOfCrabs, file);
    qsort(TabOfCrabs, CountOfCrabs, sizeof(int), compere);
    
    std::cout<<MinFuel(TabOfCrabs, CountOfCrabs)<<std::endl; // fart ze fuel jest liczba sposrod liczb w TabOfCrabs

    delete []TabOfCrabs;
    return 0;
}

int MinFuel(int *tab, int size)
{
    int median=(tab[size/2-1]+tab[size/2])/2; //size parzyste
    int fuel=0;
    for(int i=0; i<size; i++)
    {
        fuel+=abs(median-tab[i]);
    }
    return fuel;
}

int compere(const void *first, const void *sec)
{
    return (*static_cast<const int*>(first) > *static_cast<const int*>(sec) - (*static_cast<const int*>(first) < *static_cast<const int*>(sec)));
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
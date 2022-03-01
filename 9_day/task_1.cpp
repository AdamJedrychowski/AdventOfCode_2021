#include <iostream>
#include <fstream>
#include <cstring>
bool right(char *tab, int PositionInTab, int *size);
bool left(char *tab, int PositionInTab, int *size);
bool up(char *tab, int PositionInTab, int *size);
bool down(char *tab, int PositionInTab, int *size);

int main()
{
    std::fstream file;
    file.open("heightmap.txt", std::ios::in);
    std::string line;
    int size[2]={0};
    while(getline(file, line)) size[0]++;
    size[1]=line.size();
    file.clear();
    file.seekg(0, std::ios::beg);
    char Locations[size[0]][size[1]];
    for(int i=0; !file.eof(); i++) file>>*(*Locations+i);
    file.close();

    int sum=0;
    for(int i=0; i<size[0]; i++)
    {
        for(int j=0; j<size[1]; j++)
        {
            if(Locations[i][j]=='9') continue;
            if(right(&Locations[i][j], &Locations[i][j]-*Locations, size) && left(&Locations[i][j], &Locations[i][j]-*Locations, size) &&
            up(&Locations[i][j], &Locations[i][j]-*Locations, size) &&down(&Locations[i][j], &Locations[i][j]-*Locations, size))
                sum+=Locations[i][j]-47;
        }
    }
    std::cout<<sum<<std::endl;
}

bool right(char *tab, int PositionInTab, int *size)
{
    if(PositionInTab%size[1]==size[1]-1) return 1;
    if(*tab<*(tab+1)) return 1;
    return 0;
}

bool left(char *tab, int PositionInTab, int *size)
{
    if(PositionInTab%size[1]==0) return 1;
    if(*tab<*(tab-1)) return 1;
    return 0;
}

bool up(char *tab, int PositionInTab, int *size)
{
    if(static_cast<double>(PositionInTab)/size[1]<1) return 1;
    if(*tab<*(tab-size[1])) return 1;
    return 0;
}

bool down(char *tab, int PositionInTab, int *size)
{
    if(static_cast<double>(PositionInTab)/size[1]>size[0]-1) return 1;
    if(*tab<*(tab+size[1])) return 1;
    return 0;
}
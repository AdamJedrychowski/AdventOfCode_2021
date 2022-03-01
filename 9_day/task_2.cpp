#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#define COL 100
#define ROW 100
int CheckArea(int position, char (*tab)[COL]);

int main()
{
    std::fstream file;
    file.open("heightmap.txt", std::ios::in);
    std::string line;
    int size[2]={0};
    while(getline(file, line)) size[0]++;
    size[1]=line.size();
    std::cout<<"rows: "<<size[0]<<"   col: "<<size[1]<<std::endl;
    file.clear();
    file.seekg(0, std::ios::beg);
    char Locations[ROW][COL];
    for(int i=0; !file.eof(); i++) file>>*(*Locations+i);
    file.close();

    int MaxAreas[3]={0}, Area;
    for(int i=0; i<size[0]; i++)
    {
        for(int j=0; j<size[1]; j++)
        {
            if(Locations[i][j]=='9') continue;
            Area=CheckArea(&Locations[i][j]-*Locations, Locations);
            if(Area>MaxAreas[2])
            {
                MaxAreas[0]=MaxAreas[1];
                MaxAreas[1]=MaxAreas[2];
                MaxAreas[2]=Area;
            }
            else if(Area>MaxAreas[1])
            {
                MaxAreas[0]=MaxAreas[1];
                MaxAreas[1]=Area;
            }
            else if(Area>MaxAreas[0]) MaxAreas[0]=Area;
        }
    }
    std::cout<<MaxAreas[0]*MaxAreas[1]*MaxAreas[2]<<std::endl;
}

int CheckArea(int position, char (*tab)[COL])
{
    tab[position/COL][position%COL]='9';

    return 1 + ((position<COL*(ROW-1))?((tab[(position+COL)/COL][position%COL]!='9')?CheckArea(position+COL, tab):0):0) //down
    + ((position%COL!=9)?((tab[position/COL][(position+1)%COL]!='9')?CheckArea(position+1, tab):0):0) //right
    + ((position%COL!=0)?((tab[position/COL][(position-1)%COL]!='9')?CheckArea(position-1, tab):0):0) //left
    + ((position>=COL)?((tab[(position-COL)/COL][position%COL]!='9')?CheckArea(position-COL, tab):0):0); //up
}
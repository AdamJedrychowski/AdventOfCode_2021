#include <iostream>
#include <fstream>

struct Octopus
{
    char LevelOfEnergy;
    bool BeforeFlash=1;
    Octopus() = default;
    Octopus(char Energy) : LevelOfEnergy{Energy} {}
};

void Flesh(int position, Octopus *Current);

int main()
{
    std::fstream file;
    file.open("octopus.txt", std::ios::in);
    Octopus Grid[100];
    for(int i=0; i<100; i++) file>>(Grid+i)->LevelOfEnergy;
    file.close();

    int NumberOfFleshes=0;
    for(int i=0; i<100; i++)
    {
        for(int j=0; j<100; j++) Grid[j].LevelOfEnergy++;
        for(int j=0; j<100; j++)
        {
            if(Grid[j].LevelOfEnergy>57 && Grid[j].BeforeFlash)
            {
                Grid[j].BeforeFlash=0;
                Flesh(j, &Grid[j]);
                j=-1;
            }
        }
        for(int j=0; j<100; j++)
        {
            if(Grid[j].LevelOfEnergy>57)
            {
                Grid[j].LevelOfEnergy='0';
                NumberOfFleshes++;
            }
            Grid[j].BeforeFlash=1;
        }
    }
    
    for(int i=0; i<100; i++)
    {
        std::cout<<((i%10)?" ":"\n")<<Grid[i].LevelOfEnergy;
    }

    std::cout<<std::endl<<NumberOfFleshes<<std::endl;
}

void Flesh(int position, Octopus *Current)
{
    if(position%10!=9 && (Current+1)->BeforeFlash) //right
    {
        (Current+1)->LevelOfEnergy++;
    }
    if(position%10!=0 && (Current-1)->BeforeFlash) //left
    {
        (Current-1)->LevelOfEnergy++;
    }
    if(position>9 && (Current-10)->BeforeFlash) //top
    {
        (Current-10)->LevelOfEnergy++;
    }
    if(position<90 && (Current+10)->BeforeFlash) //bottom
    {
        (Current+10)->LevelOfEnergy++;
    }
    if(position%10!=0 && position>=10 && (Current-11)->BeforeFlash) //top-left
    {
        (Current-11)->LevelOfEnergy++;
    }
    if(position%10!=9 && position>=10 && (Current-9)->BeforeFlash) //top-right
    {
        (Current-9)->LevelOfEnergy++;
    }
    if(position%10!=0 && position<=90 && (Current+9)->BeforeFlash) //bottom-left
    {
        (Current+9)->LevelOfEnergy++;
    }
    if(position%10!=9 && position<=90 && (Current+11)->BeforeFlash) //bottom-right
    {
        (Current+11)->LevelOfEnergy++;
    }
}
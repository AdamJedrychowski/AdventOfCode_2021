#include <iostream>
#include <vector>
#include <fstream>
void ReadFile(int *tab, std::fstream &file);

int main()
{
    std::fstream file;
    file.open("fish.txt", std::ios::in);
    int CountOfFishes[7]={0};
    ReadFile(CountOfFishes, file);
    file.close();

    std::vector<short int> FishDay={0};
    FishDay.resize(1500);
    int size=1, tempSize, tab[7];
    for(int i=0; i<80; i++)
    {
        if(i==79) tab[1]=size;
        else if(i==78) tab[2]=size;
        else if(i==77) tab[3]=size;
        else if(i==76) tab[4]=size;
        else if(i==75) tab[5]=size;
        else if(i==74) tab[6]=size;

        tempSize=size;
        for(int j=0; j<tempSize; j++)
        {
            if(FishDay[j]==0)
            {
                FishDay[j]=6;
                FishDay[size]=8;
                size++;
                continue;
            }
            FishDay[j]--;
        }
    }
    tab[0]=size;
    for(int i=0; i<7; i++) std::cout<<i<<" - "<<tab[i]<<" ryb\n";
    
    int sum=0;
    for(int i=0; i<7; i++) sum+=tab[i]*CountOfFishes[i];
    std::cout<<std::endl<<sum<<std::endl;
}

void ReadFile(int *tab, std::fstream &file)
{
    int temp;
    while(file>>temp)
    {
        tab[temp]++;
        file.seekg(1, std::ios::cur);
    }
}
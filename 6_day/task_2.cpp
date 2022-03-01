#include <iostream>
#include <vector>
#include <fstream>
void ReadFile(int *after128, std::fstream &file);

int main()
{
    std::fstream file;
    file.open("fish.txt", std::ios::in);
    int CountOfFishes[9]={0};
    ReadFile(CountOfFishes, file);
    file.close();

    std::vector<short int> FishDay={0};
    FishDay.resize(100000);
    int size=1, tempSize, after128[9]={0}, countAfter[9][9]={0};
    for(int i=0; i<128; i++)
    {
        if(i==127)
        {
            after128[1]=size;
            for(int k=0; k<size; k++) countAfter[1][FishDay[k]]++;
        }
        else if(i==126)
        {
            after128[2]=size;
            for(int k=0; k<size; k++) countAfter[2][FishDay[k]]++;
        }
        else if(i==125)
        {
            after128[3]=size;
            for(int k=0; k<size; k++) countAfter[3][FishDay[k]]++;
        }
        else if(i==124)
        {
            after128[4]=size;
            for(int k=0; k<size; k++) countAfter[4][FishDay[k]]++;
        }
        else if(i==123)
        {
            after128[5]=size;
            for(int k=0; k<size; k++) countAfter[5][FishDay[k]]++;
        }
        else if(i==122)
        {
            after128[6]=size;
            for(int k=0; k<size; k++) countAfter[6][FishDay[k]]++;
        }
        else if(i==121)
        {
            after128[7]=size;
            for(int k=0; k<size; k++) countAfter[7][FishDay[k]]++;
        }
        else if(i==120)
        {
            after128[8]=size;
            for(int k=0; k<size; k++) countAfter[8][FishDay[k]]++;
        }

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
    after128[0]=size;
    for(int k=0; k<size; k++) countAfter[0][FishDay[k]]++;


    long long unsigned int after256[9]={0}, sum=0;
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
            {
                after256[i]+=countAfter[i][j]*after128[j];
            }
        std::cout<<i<<" - "<<after256[i]<<std::endl;
        sum+=CountOfFishes[i]*after256[i];
    }
    std::cout<<std::endl<<sum<<std::endl;
}

void ReadFile(int *after128, std::fstream &file)
{
    int temp;
    while(file>>temp)
    {
        after128[temp]++;
        file.seekg(1, std::ios::cur);
    }
}
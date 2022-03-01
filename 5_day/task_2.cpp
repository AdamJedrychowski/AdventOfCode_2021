#include <iostream>
#include <fstream>

using namespace std;
int AmountOfLines(fstream &file);
void FillTables(int (*tab)[4], int size, fstream &file);
void MarkAreas(int (*tab)[1000], int *Lines);
int CountToxicAreas(int (*tab)[1000]);

int main()
{
    fstream file;
    file.open("toxic_areas.txt", ios::in);
    int count=AmountOfLines(file);
    file.seekg(0, ios::beg);
    int SetOfLines[count][4];

    FillTables(SetOfLines, count, file);
    int ToxicAreas[1000][1000]={0};

    for(int i=0; i<count; i++)
    {
        MarkAreas(ToxicAreas, *SetOfLines+4*i);
    }

    cout<<CountToxicAreas(ToxicAreas)<<endl;
}
/////////////////////////////////////////////////////////////////////////////////


int CountToxicAreas(int (*tab)[1000])
{
    int count=0;
    for(int i=0; i<1000000; i++)
        if(*(*tab+i)>=2) count++;

    return count;
}

void MarkAreas(int (*Toxic)[1000], int *Lines)
{
    if(Lines[0]==Lines[2])
    {
        int iter, iterUntil;
        if(Lines[1]<Lines[3])  { iter=Lines[1]; iterUntil=Lines[3]; }
        else { iter=Lines[3]; iterUntil=Lines[1]; }

        for(; iter<=iterUntil; iter++)
        Toxic[iter][Lines[0]]++;
    }
    else if(Lines[1]==Lines[3])
    {
        int iter, iterUntil;
        if(Lines[0]<Lines[2])  { iter=Lines[0]; iterUntil=Lines[2]; }
        else { iter=Lines[2]; iterUntil=Lines[0]; }

        for(; iter<=iterUntil; iter++)
        Toxic[Lines[1]][iter]++;
    }
    else if(Lines[0]<Lines[2])
    {
        int iterX=Lines[0], iterY=Lines[1];
        if(Lines[1]<Lines[3])
        {
            for(; iterX<=Lines[2]; iterX++, iterY++)
                Toxic[iterY][iterX]++;
        }
        else
        {
            for(; iterX<=Lines[2]; iterX++, iterY--)
                Toxic[iterY][iterX]++;
        }
    }
    else if(Lines[0]>Lines[2])
    {
        int iterX=Lines[2], iterY=Lines[3];
        if(Lines[1]<Lines[3])
        {
            for(; iterX<=Lines[0]; iterX++, iterY--)
                Toxic[iterY][iterX]++;
        }
        else
        {
            for(; iterX<=Lines[0]; iterX++, iterY++)
                Toxic[iterY][iterX]++;
        }
    }
}

int AmountOfLines(fstream &file)
{
    int num=0;
    string text;
    while(getline(file, text))
    {
        num++;
    }
    file.clear();
    file.seekg(0, ios::beg);

    return num;
}

void FillTables(int (*tab)[4], int size, fstream &file)
{
    for(int i=0; i<size; i++)
    {
        file>>tab[i][0];
        file.seekg(1, ios::cur);
        file>>tab[i][1];
        file.seekg(4, ios::cur);
        file>>tab[i][2];
        file.seekg(1, ios::cur);
        file>>tab[i][3];
    }
    file.close();
}
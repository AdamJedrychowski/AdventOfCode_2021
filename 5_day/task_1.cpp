#include <iostream>
#include <fstream>

using namespace std;
int CorrectLines(fstream &file);
void FillTables(int (*tab)[4], int size, fstream &file);
void MarkAreas(int (*tab)[1000], int *Lines);
int CountToxicAreas(int (*tab)[1000]);

int main()
{
    fstream file;
    file.open("toxic_areas.txt", ios::in);
    int count=CorrectLines(file);
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
    int iter, iterUntil;
    if(Lines[0]==Lines[2])
    {
        if(Lines[1]<Lines[3])  { iter=Lines[1]; iterUntil=Lines[3]; }
        else { iter=Lines[3]; iterUntil=Lines[1]; }

        for(; iter<=iterUntil; iter++)
        Toxic[iter][Lines[0]]++;
    }
    else
    {
        if(Lines[0]<Lines[2])  { iter=Lines[0]; iterUntil=Lines[2]; }
        else { iter=Lines[2]; iterUntil=Lines[0]; }

        for(; iter<=iterUntil; iter++)
        Toxic[Lines[1]][iter]++;
    }
}

int CorrectLines(fstream &file)
{
    int x[2],y[2], num=0;
    while(file>>x[0])
    {
        file.seekg(1, ios::cur);
        file>>y[0];
        file.seekg(4, ios::cur);
        file>>x[1];
        file.seekg(1, ios::cur);
        file>>y[1];
        if(x[0]==x[1] || y[0]==y[1]) num++;
    }
    file.clear();
    file.seekg(0, ios::beg);

    return num;
}

void FillTables(int (*tab)[4], int size, fstream &file)
{
    int x[2], y[2];
    for(int i=0; i<size; i++)
    {
        do
        {
            file>>x[0];
            file.seekg(1, ios::cur);
            file>>y[0];
            file.seekg(4, ios::cur);
            file>>x[1];
            file.seekg(1, ios::cur);
            file>>y[1];
            if(x[0]==x[1] || y[0]==y[1])
            {
                tab[i][0]=x[0];
                tab[i][1]=y[0];
                tab[i][2]=x[1];
                tab[i][3]=y[1];
            }
        } while((x[0]!=x[1]) && (y[0]!=y[1]));
    }
    file.close();
}
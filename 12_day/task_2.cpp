#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

class Cave
{
    public:
    std::string _NameOfCave;
    std::vector<Cave*> _connections;

    Cave() = default;
    Cave(std::string name) : _NameOfCave{name} {}
};

std::string NameOfCaves(std::string &cave, size_t position);
void Connect(std::string &cave_1, std::string &cave_2, std::vector<Cave> &AllCaves);
int find_if(std::vector<Cave> &AllCaves, std::string &cave);
int Paths(Cave &AllCaves, bool ReturnPath);
int Find(std::vector<Cave*> &Path, Cave &search, bool Flag);
void Print(std::vector<Cave*> &tab);

int main()
{
    std::fstream file;
    file.open("paths.txt", std::ios::in);
    std::string line;
    std::vector<Cave> AllCaves; //better is array<>
    AllCaves.reserve(15); //change to avoid reallocating memory

    while(getline(file, line))
    {
        std::string name=NameOfCaves(line, line.find('-'));
        Connect(name, line, AllCaves);
    }
    file.close();

    int NumOfPaths;
    for(Cave &it : AllCaves)
    {
        if(it._NameOfCave=="start")
            {
                NumOfPaths=Paths(it, 0);
                break;
            }
    }
    std::cout<<NumOfPaths<<std::endl;
}

int Find(std::vector<Cave*> &Path, Cave &search, bool Flag)
{
    int Count=0;
    for(Cave *it : Path)
        if(it==&search) Count++;
    
    if(Flag && Count!=0 && search._NameOfCave[0]>=96) return 3;
    return Count;
}

int Paths(Cave &ActualCave, bool ReturnPath)
{
    static std::vector<Cave*> PossiblePath;
    int CountPaths=0;
    static bool Flag=false;

    if(ActualCave._NameOfCave=="end")
    {
        Print(PossiblePath);
        return 1;
    }

    for(Cave *it : ActualCave._connections)
    {
        if(it->_NameOfCave[0]<96 || (Find(PossiblePath, *it, Flag)<2 && it->_NameOfCave!="start"))
        {
            if(ActualCave._connections.size()==1 && ReturnPath && ActualCave._NameOfCave!="start")
            {
                PossiblePath.push_back(&ActualCave);
            }
            else if(!PossiblePath.size() || PossiblePath.back()!=&ActualCave) PossiblePath.push_back(&ActualCave);
            if(!Flag && ActualCave._NameOfCave[0]>=96 && Find(PossiblePath, ActualCave, Flag)==2) Flag=true;
            CountPaths+=Paths(*it, (ActualCave._NameOfCave[0]>96)?0:1);
        }
    }
    if(&ActualCave==PossiblePath.back()) PossiblePath.pop_back();

    return CountPaths;
}

void Print(std::vector<Cave*> &tab)
{
    for(Cave *it : tab) std::cout<<it->_NameOfCave<<" ";
    std::cout<<"end"<<std::endl;
}

int find_if(std::vector<Cave> &AllCaves, std::string &cave)
{
    for(Cave &it : AllCaves)
        if(it._NameOfCave==cave) return &it-&AllCaves[0];
    return -1;
}

void Connect(std::string &cave_1, std::string &cave_2, std::vector<Cave> &AllCaves)
{
    int WhereIs_1=find_if(AllCaves, cave_1);
    int WhereIs_2=find_if(AllCaves, cave_2);

    if(WhereIs_1==-1)
    {
        AllCaves.push_back(Cave{cave_1});
        if(WhereIs_2==-1)
        {
            AllCaves.push_back(Cave{cave_2});
            AllCaves.back()._connections.push_back(&(AllCaves.back())-1);
            (AllCaves.end()-2)->_connections.push_back(&AllCaves.back());
        }
        else
        {
            AllCaves.back()._connections.push_back(&AllCaves[WhereIs_2]);
            AllCaves[WhereIs_2]._connections.push_back(&AllCaves.back());
        }
    }
    else
    {
        if(WhereIs_2==-1)
        {
            AllCaves.push_back(Cave{cave_2});
            AllCaves.back()._connections.push_back(&AllCaves[WhereIs_1]);
            AllCaves[WhereIs_1]._connections.push_back(&AllCaves.back());
        }
        else
        {
            AllCaves[WhereIs_1]._connections.push_back(&AllCaves[WhereIs_2]);
            AllCaves[WhereIs_2]._connections.push_back(&AllCaves[WhereIs_1]);
        }
    }
}

std::string NameOfCaves(std::string &cave, size_t position)
{
    std::string sec_cave={&cave[position+1]};
    cave.erase(position);
    
    return sec_cave;
}
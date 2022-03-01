#include <iostream>
#include <fstream>

using namespace std;

class bingo
{
    public:
    int board[5][5]; 
    bool hit[5][5];
    
    bingo() : hit{0} {}

    int win();
    void check(int number);
};

int main()
{
    fstream file;
    file.open("data.txt", ios::in);
    string line;
    int bingo_num=0;

    for(int i=-2; getline(file, line); ++i)
    {
        if(i%5==0) bingo_num++;
        if(line=="") --i;
    }

    bingo tab[bingo_num];
    file.close();
    file.open("data.txt", ios::in);
    getline(file, line);

    {
    int i=0;
    while(!file.eof())
    {
        getline(file, line);
        for(int j=0; j<5; j++)
        {
            file>>tab[i].board[j][0]>>tab[i].board[j][1]>>tab[i].board[j][2]>>
                tab[i].board[j][3]>>tab[i].board[j][4];
        }
        i++;
    }
    }
    
    file.close();
    file.open("data.txt", ios::in);
    int random_num, j=0, NumOfWin=0;
    bool IfWin[bingo_num]={0};

    for(int i=0; 1; i++)
    {
        file>>random_num;
        file.seekg(1, ios::cur);
        
        j=0;
        for(; j<bingo_num ; j++)
        {
            if(IfWin[j]) continue;

            tab[j].check(random_num);
            if(i>4 && tab[j].win())
            {
                NumOfWin++;
                if(NumOfWin==bingo_num) break;

                IfWin[j]=1;
            } 
        }
        if(NumOfWin==100)
        {
            break;
        }
    }

    int sum=0;
    for(int i=0; i<25; i++)
    {
        if(tab[j].hit[0][i]==0) sum+=tab[j].board[0][i]; 
    }
    cout<<sum*random_num<<endl;

    file.close();
    return 0;
}

int bingo::win()
{
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
        {
            if(hit[i][j]==0) break;
            if(j==4) return 1;
        }
    
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
        {
            if(hit[j][i]==0) break;
            if(j==4) return 1;
        }

    return 0;
}

void bingo::check(int number)
{
    for(int i=0; i<25; i++)
    {
        if(number==*(*board+i))
        {
            *(*hit+i)=1;
            return;
        }
    }
}
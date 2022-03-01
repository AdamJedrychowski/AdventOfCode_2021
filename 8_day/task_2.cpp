#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>
char *configuration(std::fstream &file);
unsigned int decrypt(char *tab, std::fstream &file);
struct{
    bool operator()(std::string a, std::string b) { return (a.size()<b.size())?1:0; }
} cmp;


/*  numerowanie dictionary

        2
    |-------|
  3 |       | 1
    |       |
    |-------|
    |   4   |
  6 |       | 0
    |-------|
        5
*/

int main()
{
    std::fstream file;
    file.open("digits.txt", std::ios::in);
    
    char *dictionary;
    std::string text;
    unsigned int sum=0; 
    while(!file.eof())
    {
        dictionary=configuration(file);
        file>>text;
        sum+=decrypt(dictionary, file);
        delete []dictionary;
    }
    std::cout<<sum<<std::endl;
    file.close();
}

unsigned int decrypt(char *tab, std::fstream &file)
{
    int output=0;
    std::string text;
    for(int i=0; i<4; i++)
    {
        file>>text;
        if(text.size()==2) output+=std::pow(10, 3-i); // 1
        else if(text.size()==4) output+=4*std::pow(10, 3-i); // 4
        else if(text.size()==3) output+=7*std::pow(10, 3-i); // 7
        else if(text.size()==7) output+=8*std::pow(10, 3-i); // 8
        else if(text.size()==5) // 2,3,5
        {
            if(text.find(tab[3])!=std::string::npos) output+=5*std::pow(10, 3-i);
            else if(text.find(tab[6])!=std::string::npos) output+=2*std::pow(10, 3-i);
            else output+=3*std::pow(10, 3-i);
        }
        else if(text.size()==6) // 0,6,9
        {
            if(text.find(tab[4])==std::string::npos) output+=0;
            else if(text.find(tab[6])!=std::string::npos) output+=6*std::pow(10, 3-i);
            else output+=9*std::pow(10, 3-i);
        }
    }
    return output;
}

char *configuration(std::fstream &file)
{
    std::string text[10];
    char tab[7][2]={0};
    for(int i=0; i<10; i++) file>>text[i];
    std::sort(text, text+10, cmp);

    tab[1][0]=tab[0][0]=text[0][0]; // 1
    tab[1][1]=tab[0][1]=text[0][1];

    text[1].erase(text[1].find(tab[0][0]), 1); // 7
    text[1].erase(text[1].find(tab[0][1]), 1);
    tab[2][0]=text[1][0];
    
    text[2].erase(text[2].find(tab[0][0]), 1); // 4
    text[2].erase(text[2].find(tab[0][1]), 1);
    tab[3][0]=tab[4][0]=text[2][0];
    tab[3][1]=tab[4][1]=text[2][1];

    for(int i=3, flag=0; i<6; i++)
    {
        if(tab[5][0]==0 && text[i].find(tab[3][0])!=std::string::npos && text[i].find(tab[3][1])!=std::string::npos)
        {
            text[i].erase(text[i].find(tab[2][0]), 1);
            text[i].erase(text[i].find(tab[3][0]), 1);
            text[i].erase(text[i].find(tab[3][1]), 1);
            if(text[i].find(tab[0][0])!=std::string::npos) tab[1][0]=tab[1][1];
            else tab[0][0]=tab[0][1];

            text[i].erase(text[i].find(tab[0][0]), 1);
            tab[5][0]=text[i][0];
            flag=i;
            i=2;
            continue;
        }
        if(tab[5][0]!=0 && flag!=i && text[i].find(tab[0][0])>text[i].size())
        {
            text[i].erase(text[i].find(tab[1][0]), 1);
            text[i].erase(text[i].find(tab[2][0]), 1);
            text[i].erase(text[i].find(tab[5][0]), 1);
            if(text[i].find(tab[4][0])!=std::string::npos) tab[3][0]=tab[3][1];
            else tab[4][0]=tab[4][1];

            text[i].erase(text[i].find(tab[4][0]), 1);
            tab[6][0]=text[i][0];
            break;
        }
    }
    return new char[7]{tab[0][0], tab[1][0], tab[2][0], tab[3][0], tab[4][0], tab[5][0], tab[6][0]};
}
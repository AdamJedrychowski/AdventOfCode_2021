#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

int main()
{
    std::fstream file;
    file.open("signs.txt", std::ios::in);
    std::vector<char> operators;
    std::string line;
    long unsigned int score=0;
    bool flag=0;
    std::vector<long unsigned int> AllScores;

    while(getline(file, line))
    {
        flag=0;
        for(unsigned int i=0; i<line.size(); i++)
        {
            if(line[i]=='[' || line[i]=='(' || line[i]=='{' || line[i]=='<')
            {
                operators.push_back(line[i]);
                continue;
            }
            if((line[i]=='>' && operators.back()!='<') || (line[i]==']' && operators.back()!='[') || (line[i]=='}' && operators.back()!='{') || (line[i]==')' && operators.back()!='('))
            {
                operators.clear();
                flag=1;
                break;
            }

            operators.pop_back();
        }
        if(flag) continue;

        while(operators.size())
        {
            score*=5;
            if(operators.back()=='(') score+=1;
            else if(operators.back()=='[') score+=2;
            else if(operators.back()=='{') score+=3;
            else if(operators.back()=='<') score+=4;
            operators.pop_back();
        }
        AllScores.push_back(score);
        score=0;
    }

    std::sort(AllScores.begin(), AllScores.end());
    std::cout<<AllScores[AllScores.size()/2]<<std::endl;
    file.close();
}
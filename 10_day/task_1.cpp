#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

int main()
{
    std::fstream file;
    file.open("signs.txt", std::ios::in);
    std::vector<char> operators;
    std::string line;
    int SyntaxError=0;

    while(getline(file, line))
    {
        for(unsigned int i=0; i<line.size(); i++)
        {
            if(line[i]=='[' || line[i]=='(' || line[i]=='{' || line[i]=='<')
            {
                operators.push_back(line[i]);
                continue;
            }
            if(line[i]=='>' && operators.back()!='<')
            {
                SyntaxError+=25137;
                break;
            }
            else if(line[i]==']' && operators.back()!='[')
            {
                SyntaxError+=57;
                break;
            }
            else if(line[i]=='}' && operators.back()!='{')
            {
                SyntaxError+=1197;
                break;
            }
            else if(line[i]==')' && operators.back()!='(')
            {
                SyntaxError+=3;
                break;
            }
            operators.pop_back();
        }
        operators.clear();
    }
    std::cout<<SyntaxError<<std::endl;
    file.close();
}
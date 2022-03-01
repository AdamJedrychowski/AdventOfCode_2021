#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
    std::fstream file;
    file.open("digits.txt", std::ios::in);
    std::string text;
    int num=0;
    while(file>>text)
    {
        if(text=="|")
        {
            for(int i=0; i<4; i++)
            {
                file>>text;
                switch (text.size())
                {
                case 2: case 3: case 4: case 7:
                    num++;
                    break;
                }
            }
        }
    }
    std::cout<<num<<std::endl;
}
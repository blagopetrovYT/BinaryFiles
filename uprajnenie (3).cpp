// uprajnenie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>;

struct Student
{
    char* FN = new char;
    char* Name = new char;
    char grade[4];
};

struct Student2
{
    char* FN = new char;
    char* Name = new char;
    char grade[4];
};




void strc_cin(Student& s)
{
    
        std::cin >> s.FN;
        std::cin >> s.Name;
        std::cin >> s.grade;
}


void zapis(const Student* s, std::ofstream& file1,int size)
{
    for(int i = 0;i<size;i++)
    {
        file1 << s[i].FN<<" ";
        file1 << s[i].Name << " ";
        file1 << s[i].grade<< " ";
        file1 << std::endl;
    }
   
}

void put_struct_part(char* strc, char*& line)
{
    while (*line != '\0' && *line != ' ')
    {
        *strc = *line;
            strc++;
            line++;
    }
    *strc = '\0';
    line++;
}

void put_in_struct(Student2* s,char* line,int size)
{
    
        put_struct_part(s[size].FN, line);
        put_struct_part(s[size].Name, line);
        put_struct_part(s[size].grade, line);
    
}

void delete_memorry(Student& s, Student2& s2)
{
    delete[] s.FN;
    delete[] s.Name;
    delete[] s2.FN;
    delete[] s2.Name;
}


int main()
{
    const unsigned int size = 1024; 
    std::ofstream file1("text.txt");
    if (!file1.is_open())
    {
        return -1;
    }

    

    int broi;
    std::cin >> broi;
    Student* student = new Student[broi];
    for (int i = 0; i < broi; i++)
    {
        strc_cin(student[i]);
    }

   
    zapis(student,file1,broi);

    std::ifstream file2("text.txt");
    if (!file2.is_open())
    {
        return -1;
    }
    
    Student2* student2 = new Student2[broi];
    char str[1024];
    for(int i = 0;i<broi;i++)
    {
        file2.getline(str, 1024);
        put_in_struct(student2, str,i);
    }

    for (int i = 0; i < broi; i++)
    {
        std::cout << student2[i].FN;
        std::cout << std::endl;
        std::cout << student2[i].Name;
        std::cout << std::endl;
        std::cout << student2[i].grade;
        
        std::cout<<std::endl;
     }

    delete[] student;
    delete[] student2;
    file1.close();
    file2.close();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

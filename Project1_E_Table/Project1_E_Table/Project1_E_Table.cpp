#include<iostream>
#include<fstream>
#pragma warning(disable : 4996)
#include "DynamicCharArray.h"
void console();
void open_comm();

int main()
{
    //std::cout << sizeof(Challenge);

    console();
}
void console()
{
    char command[10] = "start";
    do {
        std::cin >> command;
        std::cin.ignore();
        if (strcmp(command, "open") == 0)
        {
            open_comm();

        }
        /*else if (strcmp(command, "challenge") == 0)
        {
            challenge_comm();

        }
        else if (strcmp(command, "finish") == 0)
        {
            finish_comm();

        }
        else if (strcmp(command, "profile_info") == 0)
        {
            prof_inf_comm();

        }
        else if (strcmp(command, "list_by") == 0)
        {
            list_by_comm();

        }*/
        else 
        {
            std::cout << "Invalid command" << std::endl;

        }
    } while (strcmp(command, "exit"));

}
void open_comm() {
    char command[10] = "start";
    std::ifstream original_file;
    std::ofstream temp_file;
    char ch;
    DynamicCharArray file;
    char temp_file_name[20]("temp.txt");
    char letter{ 'a' };
    for (int i = 0; i < 3; i++)
    {
        if (i == 0) {
            file.reserve(1);
            while (true)
            {
                std::cin.get(letter);
                if (!(letter >= 33))
                    break;
                file.push_back(letter);
            }
            if (letter == '\n')
                break;

        }
    }
    original_file.open(file.get_char());
    if (original_file.fail())
    {
        std::ofstream new_file(file.get_char());
        std::cerr << "Such file doesn't exist. A new empty file with the given name was created for you!" << std::endl;
        new_file.close();
        original_file.open(file.get_char());
    }

    
    temp_file.open(temp_file_name);

    while (original_file.get(ch)) {
        temp_file << ch;
    }

    while (true)
    {
        std::cin >> command;

        if (strcmp(command, "close") == 0)
        {
            temp_file.close();
            std::cout << "Successfully closed " << file.get_char();
            break;
        }
    original_file.close();
    temp_file.close();
}
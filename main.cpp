#include <iostream>
#include <string>
#include <fstream>

bool check_empty(std::string file_name) // this expects a full file name, along with the extension
{
    std::ifstream in_file;
    in_file.open(file_name);
    if (in_file.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << "I found nothing in the file";
        in_file.close();
        return true;
    }
    else
    {
        in_file.close();
        return false;
    }
}

int main()
{
    std::ofstream list_index;
    std::ofstream list;
    std::string name;
    const std::string list_base = "list_index.txt";
    list_index.open(list_base, std::ios_base::app);
    if (!list_index)
        return 1;
    std::cout << "Enter a list name: ";
    std::getline(std::cin, name);

    if (!check_empty(list_base))
       list_index << "\n" << name;
    else
       list_index << name;

    list.open(name + ".txt", std::ios_base::app);
    list.close();

    list_index.close();
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

void display_menu()
{
    std::cout << "Welcome to Todoer";
    std::cout << "\nThe available options are: "
              << "\nL - display all the To-do lists."
              << "\nO list number - opens a list (i.e. O 2, opens list no. 2)."
              << "\nA - adds a new list and prompts for a name for it."
              << "\nD list number - deletes a list"
              << "\nQ - quits Todoer.\n";
}

std::vector<std::string> grab_lists(const std::string &file_name)
{
    std::ifstream input(file_name);
    std::vector<std::string> lists_vector {};
    std::string line {};
    while(std::getline(input, line))
        lists_vector.push_back(line);
    input.close();
    return lists_vector;
}

std::vector<std::string> add_position(std::vector<std::string> &list)
{
    int positions_added {};
    std::string user_input {};
    std::cin.ignore(1000, '\n');

    std::cout << "\nEnter Q to discard changes and return to the menu."
              << "\nEnter S to save all changes and return to the menu."
              << "\nPlease enter a position (list or task name): ";
    while(getline(std::cin, user_input))
    {
        if (user_input == "Q" || user_input == "q")
        {
            for (int i = 0; i < positions_added; i++)
                list.pop_back();
            return list;
        }
        else if (user_input == "S" || user_input == "s")
        {
            return list;
        }
        else
        {
            list.push_back(user_input);
            positions_added++;
            std::cout << "List added, please enter another name, S or Q: ";
        }
    }
    return list;
}

void display_lists(const std::vector<std::string> &lists_vector)
{
    for (size_t i = 0; i < lists_vector.size(); ++i)
        std::cout << i + 1 << ". " << lists_vector.at(i) << std::endl;
}

int main()
{
    const std::string list_base = "list_index.txt";
    std::vector<std::string> lists {};
    lists = grab_lists(list_base);
    char selection {};
    display_menu();
    while (std::cin >> selection)
    {
        selection = toupper(selection);
        switch (selection)
        {
            case 'A':
            {
                lists = add_position(lists);
                break;
            }
            case 'L':
            {
                display_lists(lists);
                break;
            }
            case 'Q':
            {
                std::cout << "\nThanks for using Todoer :)"
                          << "\nBye!";
                return 0;
            }
            default:
            {
                std::cout << "Command not recognized\n";
                break;
            }
        }
    }
    return 0;
}
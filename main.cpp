#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string list_base = "list_index.txt";

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

bool save(std::vector<std::string> &list, std::ofstream &output_file) // saves the source vector in the destination file 
{
    if (!output_file)
        return false;
    for (size_t i = 0; i < list.size(); i++)
        output_file << list.at(i) << std::endl;
    return true;
}

void display_main_menu()
{
    std::cout << "Welcome to Todoer";
    std::cout << "\nThe available options are: "
              << "\nL - display all the To-do lists."
              << "\nO list number - opens a list (i.e. O 2, opens list no. 2)."
              << "\nA - adds a new list and prompts for a name for it."
              << "\nD list number - deletes a list"
              << "\nQ - quits Todoer.\n";
}

std::vector<std::string> grab_lists(const std::string &file_name) // opens a file and reads it line by line to create a vector of lists
{
    std::ifstream input(file_name);
    std::vector<std::string> lists_vector {};
    std::string line {};
    while(std::getline(input, line))
        lists_vector.push_back(line);
    input.close();
    return lists_vector;
}

// if another list isn't specified, this will save in the index of lists
std::vector<std::string> add_position(std::vector<std::string> &list, std::string list_name = list_base)
{
    int positions_added {};
    std::string user_input {};
    std::cin.ignore(1000, '\n');
    std::ofstream output_list;

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
            if (list_name == list_base)
                output_list.open(list_name);
            else
                output_list.open(list_name + ".txt");
            save(list, output_list);
            output_list.close();
            return list;
        }
        else
        {
            list.push_back(user_input);
            positions_added++;
            std::cout << "Position added, please enter another one, S or Q: ";
        }
    }
    return list;
}

void display_lists(const std::vector<std::string> &lists_vector)
{
    for (size_t i = 0; i < lists_vector.size(); ++i)
        std::cout << i + 1 << ". " << lists_vector.at(i) << std::endl;
}

std::vector<std::string> open_list(const std::string &list_name)
{
    std::vector<std::string> current_list;
    current_list = grab_lists(list_name + ".txt");
    display_lists(current_list);
    return current_list;
}

int main()
{
    
    std::string current_list_name {};
    std::vector<std::string> lists {};
    std::vector<std::string> current_list{};
    lists = grab_lists(list_base);
    char selection {};
    int num_selection {};
    display_main_menu();
    while (std::cin >> selection)
    {
        selection = toupper(selection);
        switch (selection)
        {
            case 'L':
            {
                display_lists(lists);
                break;
            }
            case 'O':
            {
                std::cin >> num_selection;
                current_list = open_list(lists.at(num_selection - 1));
                break;
            }
            case 'A':
            {
                lists = add_position(lists);
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
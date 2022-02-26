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

bool save(std::vector<std::string> &list, const std::string &list_name) // saves the source vector in the destination file 
{
    std::ofstream output_file;
    if (list_name == list_base)
        output_file.open(list_name);
    else
        output_file.open(list_name + ".txt");
    if (!output_file)
        return false;
    for (size_t i = 0; i < list.size(); i++)
        output_file << list.at(i) << std::endl;
    output_file.close();
    return true;
}

void display_main_menu()
{
    std::cout << "\n\nWelcome to Todoer";
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

// if another list isn't specified, this will add the position in the index of lists
std::vector<std::string> add_position(std::vector<std::string> &list, const std::string &list_name = list_base)
{
    int positions_added {};
    std::string user_input {};
    std::cin.ignore(1000, '\n');
    
    std::cout << "\n\nEnter Q to discard changes and return to the menu."
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
            save(list, list_name);
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

// if another list isn't specified, this will delete from the index of lists
std::vector<std::string> delete_position(std::vector<std::string> &list, const std::string &list_name = list_base)
{
    int position_no {0};
    std::cin >> position_no;
    char selection {};
    std::cout << "\nDeleting position " << position_no << ", are you sure? (Y/N) ";
    std::cin.ignore(1000, '\n');
    if (std::cin >> selection)
    {
        selection = toupper(selection);
        switch (selection)
        {
            case 'Y':
            {
                list.erase(list.begin() + (position_no - 1));
                std::cout << "\nPosition deleted.";
                save(list, list_name);
                break;
            }
            case 'N':
            {
                std::cout << "\nPosition was not deleted.";
                break;
            }
            default:
                break;
        }
    }
    else
    {
        std::cin.ignore(1000, '\n');
        std::cout << "\nBad input";
    }
    return list;
}

void display_lists(const std::vector<std::string> &lists_vector)
{
    if (lists_vector.size() == 0)
    {
        std::cout << "The index is empty, please add a list first.\n";
        return;
    }
    std::cout << std::endl;
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

void task_menu(std::vector<std::string> &list, const std::string &list_name)
{
    char selection {};
    std::cout << "\n\nEnter 'A' to add a new task."
              << "\nEnter 'D' to delete a task."
              << "\nEnter 'Q' to return to the main menu.\n";
    if (!(std::cin >> selection))
        return;
    selection = toupper(selection);
    switch(selection)
    {
        case 'A':
        {   
            add_position(list, list_name);
            break;
        }
        case 'D':
        {
            delete_position(list, list_name);
            break;
        }
        case 'Q':
            return;
        default:
            break;
    }
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
                display_main_menu();
                break;
            }
            case 'O':
            {
                std::cin >> num_selection;
                current_list_name = lists.at(num_selection - 1);
                current_list = open_list(lists.at(num_selection - 1));
                task_menu(current_list, current_list_name);
                display_main_menu();
                break;
            }
            case 'A':
            {
                lists = add_position(lists);
                display_main_menu();
                break;
            }
            case 'D':
            {
                lists = delete_position(lists);
                display_main_menu();
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
                std::string staying_open {};
                std::cout << "\nError: Command not recognized\nPlease enter anything to continue.";
                std::cin >> staying_open;
                display_main_menu();
                break;
            }
        }
    }
    return 0;
}
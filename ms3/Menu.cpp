/* Name;sabin khatiwada
class;NJJ
Email;skhatiwada3@myseneca.ca
student id; 157195215
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "Utils.h"
#include <cstring>

namespace sdds
{

    //   MENUITEM
    MenuItem::MenuItem()
    {
        setEmpty();
    }

    MenuItem::MenuItem(const char *textContent)
    {
        if (textContent && textContent[0])
        {
            Content = new char[strlen(textContent) + 1];
            strcpy(Content, textContent);
        }
        else
        {
            setEmpty();
        }
    }

    MenuItem::~MenuItem()
    {
        delete[] Content;
    }

    // Set to safe state
    void MenuItem::setEmpty()
    {
        Content = nullptr;
    }

    // Check if empty or not
    MenuItem::operator bool() const
    {
        return (Content && Content[0]);
    };

    // get address of content string
    MenuItem::operator const char *() const
    {
        return Content;
    }

    // Display contents
    std::ostream &MenuItem::display(std::ostream &os)
    {
        if (*this)
        {
            os << Content;
        }
        return os;
    }

    //  MENU
    Menu::Menu()
    {
        Count = 0;
    };

    Menu::Menu(const char *title) : heading(title){};

    Menu::~Menu()
    {
        unsigned int i;
        for (i = 0; i < MAX_MENU_ITEMS; i++)
        {
            delete menuItems[i];
        }
    };

    // Display title
    std::ostream &Menu::displayMenuTitle(std::ostream &os)
    {
        if (heading)
        {
            heading.display();
        }

        return os;
    }

    // Display content of menu
    std::ostream &Menu::displayMenu(std::ostream &os)
    {
        if (heading)
        {
            heading.display();
            os <<""<< std::endl;            //colon removed here
        }

        unsigned int i;
        for (i = 0; i < Count; i++)
        {
            os.width(2);
            os.setf(std::ios::right);
            os.fill(' ');
            os << i + 1 << "- ";
            os.unsetf(std::ios::right);
            menuItems[i]->display(os);
            os << std::endl;
        }
        os << " 0- Exit" << std::endl;
        os << "> ";

        return os;
    }

    // get no of menu items
    Menu::operator int()
    {
        return Count;
    }
    Menu::operator unsigned int()
    {
        return Count;
    }

    // checks if items are more than 0
    Menu::operator bool()
    {
        return (Count > 0);
    }

    // Overloading the Insertion operator
    std::ostream &operator<<(std::ostream &os, Menu &menu)
    {
        return (menu.displayMenuTitle(os));
    }

    // Shows menu
    int Menu::run()
    {
        int user_input;
        displayMenu();
        user_input = getIntegerInput(0, Count);
        return user_input;
    }

    // Operators overloading
    int Menu::operator~()
    {
        return run();
    }

    Menu &Menu::operator<<(const char *M_Content)
    {
        if (Count < MAX_MENU_ITEMS)
        {
            MenuItem *newMenuItem = new MenuItem(M_Content);
            menuItems[Count] = newMenuItem;
            Count++;
        }

        return *this;
    }

    const char *Menu::operator[](unsigned int index) const
    {
        if (index > Count)
        {
            return menuItems[index %= Count]->Content;
        }
        else
        {
            return menuItems[index]->Content;
        }
    }
};
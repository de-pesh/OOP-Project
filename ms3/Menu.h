#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds
{
    const unsigned int MAX_MENU_ITEMS = 20;

    class MenuItem
    {
    private:
        // store string
        char *Content{};
        MenuItem();
        MenuItem(const char *textContent);
        ~MenuItem();

        // To restrict copying
        MenuItem(const MenuItem &menuItem) = delete;
        void operator=(const MenuItem &MI) = delete;

        // Sets MenuItem to safe state
        void setEmpty();

        // Checks if empty or not
        operator bool() const;

        // return address of content string
        operator const char *() const;

        // Display MenuItem
        std::ostream &display(std::ostream &os = std::cout);

        friend class Menu;
    };

    class Menu
    {
    private:
        MenuItem heading{};
        MenuItem *menuItems[MAX_MENU_ITEMS]{};
        unsigned int Count = 0;

    public:
        Menu();
        Menu(const char *title);
        ~Menu();

        // To restrict copying
        Menu(const Menu &M) = delete;
        void operator=(const Menu &M) = delete;

        // Show title
        std::ostream &displayMenuTitle(std::ostream &os);

        // Shows menu content
        std::ostream &displayMenu(std::ostream &os = std::cout);

        // Return  no of menu items .
        operator int();

        operator unsigned int();

        // Checks if items are more than 0
        operator bool();

        // Starts interaction
        int run();

        // to envoke run
        int operator~();

        // Overloading
        Menu &operator<<(const char *menuitemContent);
        const char *operator[](unsigned int index) const;
    };
    std::ostream &operator<<(std::ostream &os, Menu &menu);
}

#endif
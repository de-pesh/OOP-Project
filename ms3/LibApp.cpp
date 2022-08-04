#include<iostream>
#include "LibApp.h"

using namespace std;
namespace sdds
{
    //constructor
    const char main_heading[] = "Seneca Library Application";
    const char end_heading[] = "Changes have been made to the data, what would you like to do?";
    LibApp::LibApp():m_mainMenu(main_heading),m_exitMenu(end_heading)
    {
        m_changed = false;
        m_mainMenu<<"Add New Publication";
        m_mainMenu<<"Remove Publication";
        m_mainMenu<<"Checkout publication from library";
        m_mainMenu<<"Return publication to library";
        m_exitMenu<<"Save changes and exit";
        m_exitMenu<<"Cancel and go back to the main menu";
        load();
    }
    //confirm method
    bool LibApp::confirm(const char* message)
    {
        Menu sec_menu(message);
        sec_menu<<"Yes";
        int check = sec_menu.run();
        if(check == 1)
            return true;
        else
            return false;
    }
    //loading  message
    void LibApp::load()
    {
        cout<<"Loading Data"<<endl;
    }
    //saving data message
    void LibApp::save()
    {
        cout<<"Saving Data"<<endl;
    }
    //searching message
    void LibApp::search()
    {
        cout<<"Searching for publication"<<endl;
    }
    //returning book message
    void LibApp::returnPub()
    {
        search();
        cout<<"Returning publication"<<endl;
        cout<<"Publication returned\n"<<endl;
        m_changed = true;
    }
    //adding book
    void LibApp::newPublication()
    {
        cout<<"Adding new publication to library"<<endl;
        bool check = confirm("Add this publication to library?");
        if(check)
        {
            m_changed = true;
            cout<<"Publication added"<<endl;
        }
        else
        {
            cout<<endl;
        }
    }
    //removing bok
    void LibApp::removePublication()
    {
        cout<<"Removing publication from library"<<endl;
        search();
        bool check = confirm("Remove this publication from the library?");
        if(check)
        {
            m_changed = true;
            cout<<"Publication removed\n"<<endl;
        }
    }
    //checkout book
    void LibApp::checkOutPub()
    {
        search();
        bool check = confirm("Check out publication?");
        if(check)
        {
            m_changed = true;
            cout<<"Publication checked out\n"<<endl;
        }
    }
    //driver method
    void LibApp::run()
    {
        int choice = 1;
        while(choice != 0) {
            choice = m_mainMenu.run();
            if(choice == 1)
            {
                newPublication();
            }
            else if(choice == 2)
            {
                removePublication();
            }
            else if(choice == 3)
            {
                checkOutPub();
            }
            else if(choice == 4)
            {
                returnPub();
            }
        }
        if(m_changed)
        {
            int check = m_exitMenu.run();
            if(check == 0)
            {
                confirm("This will discard all the changes are you sure?");
            }
            else if(check == 1)
            {
                cout<<"Saving Data"<<endl;
            }
            else if(check == 2)
            {
                cout<<endl;
                run();
                return;
            }
        }
        cout<<endl<<"-------------------------------------------"<<endl;
        cout<<"Thanks for using Seneca Library Application"<<endl;
    }
}
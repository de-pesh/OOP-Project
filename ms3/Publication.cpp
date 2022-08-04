#include<string.h>
#include <sstream> 
#include<iostream>
#include<iomanip>
#include "Publication.h"
#include "Date.h"
using namespace std;

namespace sdds {
        Date d ;
        int membership;
        char shelfno[50];

        Publication::Publication() {
            m_title = nullptr;
            strcpy(m_shelfId, "");
            m_membership = 0;
            m_libRef = -1;
            resetDate();
        }
        //modifiers
        void Publication::set(int member_id) { 
            m_membership = member_id;
            membership = member_id;
        }
        // Sets the membership attribute to either zero or a five-digit integer.
        void Publication::setRef(int value) {
            m_libRef = value;
        }
        // Sets the **libRef** attribute value
        void Publication::resetDate(){
            d.Today();
            m_date.Today();
        }
        // Sets the date to the current date of the system.

        //Queries
        char Publication::type()const {
            return 'P';
        }
        //Returns the character 'P' to identify this object as a "Publication object"
        bool Publication::onLoan()const {
            if(m_membership == 0) {
                return false;
            }
            return true;
        }
        //Returns true is the publication is checkout (membership is non-zero)
        Date Publication::checkoutDate()const {
            return m_date;
        }
        //Returns the date attribute
        bool Publication::operator==(const char* title)const {
            char *check = strstr(m_title, title); 
            if(check) {
                return true;
            }
            return false;
        }
        //Returns true if the argument title appears anywhere in the title of the 
        //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
        Publication::operator const char* ()const {
            return m_title;
        }
        //Returns the title attribute
        int Publication::getRef()const {
            return m_libRef;
        }
        //Returns the libRef attirbute. 

        bool Publication::conIO(ios& io)const {
            if(&io == &cin || &io == &cout) {
                return true;
            }
            return false;
        }

        ostream& Publication::write(ostream& os) const {
            if(conIO(os)) {
                os<<"| "<<shelfno<<" | "<<setfill('.')<<setw(30)<<left<<m_title<<" | ";
                if(membership == 0) {
                    os<<" N/A "<<" | "<<d<<" |";
                } else {
                    os<<membership<<" | "<<d<<" |";
                }
            } else {
                os<<type()<<"\t"<<m_libRef<<"\t"<<shelfno<<"\t"<<m_title<<"\t"<<membership<<"\t"<<d;
            }
            return os;
        }

        istream& Publication::read(istream& istr) {
            if(m_title != nullptr) {
                delete [] m_title;
            }
            m_title = nullptr;
            strcpy(m_shelfId, "");
            m_membership = 0;
            m_libRef = -1;
            resetDate();
            char title[255];
            int  ref;
            if(conIO(istr)) {
                cout<<"Shelf No: ";
                istr>>shelfno;
                if(strlen(shelfno)>4) {
                    cin.setstate(ios::failbit);
                    cout<<"Title: "<<"Date: ";
                    return istr;
                } 
                cout<<"Title: ";
                istr.ignore(1000,'\n');
                istr.getline(title, 255);
                cout<<"Date: ";
                cin>>d;
                if(d.errCode() != 0) {
                    resetDate();
                    cin.setstate(ios::failbit);
                    return istr;
                }
                strcpy(m_shelfId, shelfno);
                m_title = new char[255];
                strcpy(m_title, title);
                m_date = d;
            } else {

                string line;
                getline(istr, line);
                for(int i = 0; line[i]!='\0'; i++) {
                    if(line[i] == ' '){
                        line[i] = '_';
                    } else {
                        line[i] = line[i];
                    }
                }
                istringstream iss(line);
                iss>>ref;
                iss >> shelfno;
                iss >> title;
                iss >> membership;
                iss >> d;
                for(int i = 0; title[i]!='\0'; i++) {
                    if(title[i] == '_') {
                        title[i] = ' ';
                    }
                }
                m_membership = membership;
                strcpy(m_shelfId, shelfno);
                m_title = new char[255];
                strcpy(m_title, title);
                m_date = d;
            }
            
            return istr;
        }

        Publication::operator bool() const {
            if(m_title == nullptr || strcmp(m_shelfId, "") == 0) {
                return false;
            }
            return true;
        }

        Publication::~Publication() {
            if(m_title != nullptr ) {
                //cout<<"\nDELETED\n";
                m_title = new char[5];
                delete [] m_title;
            }
            m_title = nullptr;
        }

        Publication::Publication(const Publication &pub) {
            m_title = new char[strlen(pub.m_title)+1];
            m_title = pub.m_title;
            strcpy(m_shelfId, pub.m_shelfId);
            m_membership = pub.m_membership;
            m_libRef = pub.m_libRef;
            m_date = pub.m_date;
        }

        Publication& Publication::operator=(const Publication& pub) {
            if(this != &pub) {
                m_libRef = pub.m_libRef;
                m_membership = pub.m_membership;
                strcpy(m_shelfId, pub.m_shelfId);
                if(m_title != nullptr) {
                    delete  [] m_title;
                }
                m_title = nullptr;
                m_title = new char[sizeof(pub.m_title)+1]; 
                m_title = pub.m_title;
            }
            return *this;
        }


        ostream &operator<<(ostream &os,  Streamable &obj) {
            if(obj.operator bool()) {
                return obj.write(os);
            }
            return os;
        }
        istream &operator>>(istream &is, Streamable &obj) {
            return obj.read(is);
        }
}
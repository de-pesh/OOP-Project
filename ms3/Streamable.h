#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include<iostream>
using namespace std;
namespace sdds {
    class Streamable {
    public:
        virtual ostream& write(ostream& os) const = 0;
        virtual istream& read(istream& istr) = 0;
        virtual bool conIO(ios& io)const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable()  {};
        friend ostream &operator<<(ostream &os,  Streamable &obj);
        friend istream &operator>>(istream &is, Streamable &obj);
    };
}

#endif
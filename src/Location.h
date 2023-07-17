#include <iostream>
namespace WMB
{
    class Location
    {
    public:
        int i;
        int j;
        Location() { i = -1; j = -1; }
        Location(int li, int lj) { i = li; j = lj; }

        bool operator == (const Location& p)
        {
            if (i == p.i && j == p.j) { return true; }
            return false;
        }

        Location operator += (const Location l)
        {
            this->i += l.i;
            this->j += l.j;
            return *this;
        }

        Location operator /= (const int num)
        {
            this->i /= num;
            this->j /= num;
            return *this;
            //return Location(this->i / num, this->j / num);
        }

        Location operator / (const int num)
        {
            Location temp;
            temp.i = i / num;
            temp.j = j / num;
            return temp;
        }


        friend std::ostream& operator<<(std::ostream& out, Location const& data)
        {
            return out << "(" << data.i << ", " << data.j << ")";
        }

    };
}
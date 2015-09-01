#include <iostream>

using namespace std;

int main()
{
    int drives[] = { 10, 3, 7, 5, 8, 10, 2, 4, 10 };
    int count = sizeof(drives) / sizeof(int);

    int incl = 10;
    int excl = 0;

    for (int i = 1; i < count; ++i)
    {
        int new_excl = max(incl, excl);
        int new_incl = drives[i] + excl;
        excl = new_excl;
        incl = new_incl;
    }

    cout << max(excl, incl) << endl;
}

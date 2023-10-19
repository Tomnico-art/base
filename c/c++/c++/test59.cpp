#include <iostream>
#include <vector>

using namespace std;

void show(vector<int> vInt, int n)
{
    if(!vInt.empty() && n < vInt.size())
    {
        cout << vInt[n] << endl;
        show(vInt, n+1);
    }

}

int main()
{
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    show(v, 0);

    return 0;
}


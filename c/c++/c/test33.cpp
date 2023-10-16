#include <iostream>
#include <vector>
using namespace std;

class A
{

};

int main()
{
    cout << sizeof(A) << endl;

    vector<int> list1 = {1,2,3,4,5,6};
    vector<int> list1_1 = {1,2,3,4,5,6};

    vector<int> list2;//元素为空

    vector<int> list3 = list1;

    vector<int> list4(list1.begin()+2, list1.end()-1);  //{3,4,5}

    vector<int> list5(10); //10个0；

    vector<int> list6(10, 3);    //10个3



    return 0;
}
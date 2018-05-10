/*

    a01_tmpnam

    tmpnam()可以产生临时文件名，最大长度L_tmpnam。TMP_MAX是其可产生的单一文件名最大数量.


*/

#include <iostream>
#include <cstdio>

int main()
{
    using namespace std;
    cout << "Up to "<< TMP_MAX << " temporary name of up to "<<L_tmpnam <<" chars\n";

    char sName[L_tmpnam] = {'\0'};
    cout << "names: \n";
    for(int i = 0; i<10; i++)
    {
        tmpnam(sName);
        cout<<sName<<endl;
    }
    return 0;
}


/*
http://en.cppreference.com/w/cpp/string/basic_string/at
http://en.cppreference.com/w/cpp/string/basic_string/operator_at

*/
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

void doAt()
{
    string s("message"); // for capacity

    s = "abc";
    s.at(2) = 'x'; // ok
    cout << s << '\n';     //abx

    cout << "string size = " << s.size() << '\n';          //string size = 3
    cout << "string capacity = " << s.capacity() << '\n';  //string capacity = 7

    try {
        // throw, even if capacity allowed to access element
        s.at(3) = 'x';
    }
    catch (out_of_range const& exc) {
        cout << exc.what() << '\n';    //basic_string::at
    }
}

void doOp()
{

    string const e("Exemplar");
    for (unsigned i = e.length() - 1; i != 0; i /= 2)
        cout << e[i];
    cout << '\n';           //rmx

    const char* c = &e[0];
    cout << c << '\n'; // print as a C string   //Exemplar

    //Change the last character of s into a 'y'
    string s("Exemplar ");
    s[s.size()-1] = 'y';
    cout << s << '\n';      //Exemplary
}

void doFrontAndBack()
{
    {
      string s("Exemplary");
      char& f = s.front();
      f = 'e';
      cout << s << '\n'; // "exemplary"
    }

    {
      string const c("Exemplary");
      char const& f = c.front();
      cout << &f << '\n'; // "Exemplary"
    }

    {
      string s("Exemplary");
      char& back = s.back();
      back = 's';
      cout << s << '\n'; // "Exemplars"
    }

    {
      string const c("Exemplary");
      char const& back = c.back();
      cout << back << '\n'; // 'y'
    }
}

void doData()
{
    string const s("Emplary");
    const char *p = s.data();
    assert(s.size() == strlen(s.data()));
    assert(equal(s.begin(), s.end(), s.data()));
    assert(equal(s.data(), s.data() + s.size(), s.begin()));
    assert(0 == *(s.data() + s.size()));
}

void doCstr()
{
    string const s("Emplary");
    assert(s.size() == strlen(s.c_str()));
    assert(equal(s.begin(), s.end(), s.c_str()));
    assert(equal(s.c_str(), s.c_str() + s.size(), s.begin()));
    assert(0 == *(s.c_str() + s.size()));
}

void doBeginEnd()
{
    string s("abcde");
    *s.begin() = '1';
    cout << s <<'\n';  //1bcde

    auto i = s.cbegin();
    cout << *i << '\n';    //1

    *(s.end()-1)='0';
    cout<<s<<'\n'; //1bcd0;

}

int main()
{

    doAt();
    doOp();
    doFrontAndBack();
    doData();
    doCstr();
    doBeginEnd();
    return 0;
}

#include <cassert>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

void doInsert()
{
    std::string s = "xmplr";

    // insert(size_type index, size_type count, char ch)
    s.insert(0, 1, 'E');
    assert("Exmplr" == s);

    // insert(size_type index, const char* s)
    s.insert(2, "e");
    assert("Exemplr" == s);

    // insert(size_type index, string const& str)
    s.insert(6, "a");
    assert("Exemplar" == s);

    // insert(size_type index, string const& str,
    //     size_type index_str, size_type count)
    s.insert(8, " is an example string.", 0, 14);
    assert("Exemplar is an example" == s);

    // insert(const_iterator pos, char ch)
    s.insert(s.cbegin() + s.find_first_of('n') + 1, ':');
    assert("Exemplar is an: example" == s);

    // insert(const_iterator pos, size_type count, char ch)
    s.insert(s.cbegin() + s.find_first_of(':') + 1, 2, '=');
    assert("Exemplar is an:== example" == s);

    // insert(const_iterator pos, InputIt first, InputIt last)
    {
        std::string seq = " string";
        s.insert(s.begin() + s.find_last_of('e') + 1,
            std::begin(seq), std::end(seq));
        assert("Exemplar is an:== example string" == s);
    }

    // insert(const_iterator pos, std::initializer_list<char>)
    s.insert(s.cbegin() + s.find_first_of('g') + 1, { '.' });
    assert("Exemplar is an:== example string." == s);

}

void doErase()
{
    std::string s = "This is an example";
    std::cout << s << '\n';

    s.erase(0, 5); // Erase "This "
    std::cout << s << '\n';     //is an example

    s.erase(std::find(s.begin(), s.end(), ' ')); // Erase ' '
    std::cout << s << '\n';     //isan example

    s.erase(s.find(' ')); // Trim from ' ' to the end of the string
    std::cout << s << '\n';     //isan
}

/*output
1) ***
2) ***string
3) ***stringing
4) ***stringing Two
5) ***stringing Two C-string
6) ***stringing Two C-string and one
7) ***stringing Two C-string and one list
 */
void doAppend()
{
    std::basic_string<char> str = "string";
    const char* cptr = "C-string";
    const char carr[] = "Two and one";

    std::string output;

    // 1) Append a char 3 times.
    // Notice, this is the only overload accepting chars.
    output.append(3, '*');
    std::cout << "1) " << output << "\n";

    //  2) Append a whole string
    output.append(str);
    std::cout << "2) " << output << "\n";

    // 3) Append part of a string (last 3 letters, in this case)
    output.append(str, 3, 3);
    std::cout << "3) " << output << "\n";

    // 4) Append part of a C-string
    // Notice, because `append` returns *this, we can chain calls together
    output.append(1, ' ').append(carr, 4);
    std::cout << "4) " << output << "\n";

    // 5) Append a whole C-string
    output.append(cptr);
    std::cout << "5) " << output << "\n";

    // 6) Append range
    output.append(&carr[3], std::end(carr));
    std::cout << "6) " << output << "\n";

    // 7) Append initializer list
    output.append({ ' ', 'l', 'i', 's', 't' });
    std::cout << "7) " << output << "\n";

}

/*result
""
"This"
"This is "
"This is a"
"This is a string."
"This is a string.L"
*/
void doOpPlusEq()
{
    std::string str;
    str.reserve(50); //reserves sufficient storage space to avoid memory reallocation
    std::cout << str << '\n'; //empty string

    str += "This";
    std::cout << str << '\n';

    str += std::string(" is ");
    std::cout << str << '\n';

    str += 'a';
    std::cout << str << '\n';

    str += {' ','s','t','r','i','n','g','.'};
    std::cout << str << '\n';

    str += 76.85; // equivalent to str += static_cast<char>(76.85), might not be the intent
    std::cout << str << '\n';
}

void doCompare()
{
    // 1) Compare with other string
    {
        int compare_value{
            std::string{"Batman"}.compare(std::string{"Superman"})
        };
        std::cout << (
            compare_value < 0 ? "Batman comes before Superman\n" :
            compare_value > 0 ? "Batman comes before Superman\n" :
            "Superman and Batman are the same.\n"
        );
    }

    // 2) Compare substring with other string
    {
        int compare_value{
            std::string{"Batman"}.compare(3, 3, std::string{"Superman"})
        };
        std::cout << (
            compare_value < 0 ? "man comes before Superman\n" :
            compare_value > 0 ? "Superman comes before man\n" :
            "man and Superman are the same.\n"
        );
    }

    // 3) Compare substring with other substring
    {
        std::string a{"Batman"};
        std::string b{"Superman"};

        int compare_value{a.compare(3, 3, b, 5, 3)};

        std::cout << (
            compare_value < 0 ? "man comes before man\n" :
            compare_value > 0 ? "man comes before man\n" :
            "man and man are the same.\n"
        );
        // Compare substring with other substring
        // defaulting to end of other string
        assert(compare_value == a.compare(3, 3, b, 5, std::string::npos));
    }

    // 4) Compare with char pointer
    {
        int compare_value{std::string{"Batman"}.compare("Superman")};

        std::cout << (
            compare_value < 0 ? "Batman comes before Superman\n" :
            compare_value > 0 ? "Superman comes before Batman\n" :
            "Superman and Batman are the same.\n"
        );
    }

    // 5) Compare substring with char pointer
    {
        int compare_value{std::string{"Batman"}.compare(3, 3, "Superman")};

        std::cout << (
            compare_value < 0 ? "man comes before Superman\n" :
            compare_value > 0 ? "Superman comes before man\n" :
            "man and Superman are the same.\n"
        );
    }

    // 6) Compare substring with char pointer substring
    {
        int compare_value{std::string{"Batman"}.compare(0, 3, "Superman", 5)};

        std::cout << (
            compare_value < 0 ? "Bat comes before Super\n" :
            compare_value > 0 ? "Super comes before Bat\n" :
            "Super and Bat are the same.\n"
        );
    }
}

void doReplace()
{
    std::string str("The quick brown fox jumps over the lazy dog.");

    str.replace(10, 5, "red"); // (5)

    str.replace(str.begin(), str.begin() + 3, 1, 'A'); // (6)

    std::cout << str << '\n';
}

void doCopy()
{
    std::string foo("quuuux");
    char bar[7];
    foo.copy(bar, sizeof bar);
    bar[6] = '\0';
    std::cout << bar << '\n';
}

/*result
before swap
a: AAA
b: BBB
after swap
a: BBB
b: AAA
*/
void doSwap()
{
    std::string a = "AAA";
    std::string b = "BBB";

    std::cout << "before swap" << '\n';
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';

    a.swap(b);

    std::cout << "after swap" << '\n';
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
}

void print(std::string::size_type n, std::string const &s)
{
    if (n == std::string::npos) {
        std::cout << "not found\n";
    } else {
        std::cout << "found: " << s.substr(n) << '\n';
    }
}

/*result
found: is is a string
found: is a string
found: a string
not found
*/
void doFind()
{
    std::string::size_type n;
    std::string const s = "This is a string";

    // search from beginning of string
    n = s.find("is");
    print(n, s);

    // search from position 5
    n = s.find("is", 5);
    print(n, s);

    // find a single character
    n = s.find('a');
    print(n, s);

    // find a single character
    n = s.find('q');
    print(n, s);
}

void printr(std::string::size_type n, std::string const &s)
{
    if (n == std::string::npos) {
        std::cout << "not found\n";
    } else {
        std::cout << "found: \"" << s.substr(n) << "\" at " << n << '\n';
    }
}

/*result
found: "is a string" at 5
found: "is is a string" at 2
found: "string" at 10
not found
*/
void doRfind()
{
    std::string::size_type n;
    std::string const s = "This is a string";

    // search backwards from end of string
    n = s.rfind("is");
    printr(n, s);
    // search backwards from position 4
    n = s.rfind("is", 4);
    printr(n, s);
    // find a single character
    n = s.rfind('s');
    printr(n, s);
    // find a single character
    n = s.rfind('q');
    printr(n, s);
}

/*
4
7
1
4
18446744073709551615        <--- npos value
*/
void doFindFirstOf()
{
    // the test string
    std::string str = std::string("Hello World!");

    // strings and chars to search for
    std::string search_str = std::string("o");
    const char* search_cstr = "Good Bye!";

    std::cout << str.find_first_of(search_str) << '\n';
    std::cout << str.find_first_of(search_str, 5) << '\n';
    std::cout << str.find_first_of(search_cstr) << '\n';
    std::cout << str.find_first_of(search_cstr, 0, 4) << '\n';
    // 'x' is not in "Hello World', thus it will return std::string::npos
    std::cout << str.find_first_of('x') << '\n';
}

void doOperatorPlus()
{
    std::string s1 = "Hello";
    std::string s2 = "world";
    std::cout << s1 + ' ' + s2 + "!\n";         //Hello world!
}

/*result
Hello, whirled!
Hello,
*/
void doStream()
{
    std::string greeting = "Hello, whirled!";
    std::istringstream is(greeting);
    std::string hello_comma;
    is >> hello_comma;              //终止到space.
    std::cout << greeting << '\n' << hello_comma << '\n';
}

int main()
{
    doInsert();
    doErase();
    doAppend();
    doOpPlusEq();
    doCompare();
    doReplace();
    doCopy();
    doSwap();
    doFind();
    doRfind();
    doFindFirstOf();
    doOperatorPlus();
    doStream();
    std::cout << "Hello World!" << std::endl;
    return 0;
}

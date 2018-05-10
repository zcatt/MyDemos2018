#include <iostream>
#include <vector>
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}

/*result
words1: [the, frogurt, is, also, cursed]
words2: [the, frogurt, is, also, cursed]
words3: [the, frogurt, is, also, cursed]
words4: [Mo, Mo, Mo, Mo, Mo]
*/
void doConstruct()
{
    // c++11 initializer list syntax:
    std::vector<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
    std::cout << "words1: " << words1 << '\n';

    // words2 == words1
    std::vector<std::string> words2(words1.begin(), words1.end());
    std::cout << "words2: " << words2 << '\n';

    // words3 == words1
    std::vector<std::string> words3(words1);
    std::cout << "words3: " << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    std::vector<std::string> words4(5, "Mo");
    std::cout << "words4: " << words4 << '\n';
}



void print_vec(const std::vector<int>& vec)
{
    for (auto x: vec) {
         std::cout << ' ' << x;
    }
    std::cout << '\n';
}

/*result
100 100 100
200 100 100 100
300 300 200 100 100 100
300 300 400 400 200 100 100 100
501 502 503 300 300 400 400 200 100 100 100
*/
void doInsert()
{
    std::vector<int> vec(3,100);
    print_vec(vec);

    auto it = vec.begin();
    it = vec.insert(it, 200);
    print_vec(vec);

    vec.insert(it,2,300);
    print_vec(vec);

    // "it" no longer valid, get a new one:
    it = vec.begin();

    std::vector<int> vec2(2,400);
    vec.insert(it+2, vec2.begin(), vec2.end());
    print_vec(vec);

    int arr[] = { 501,502,503 };
    vec.insert(vec.begin(), arr, arr+3);
    print_vec(vec);
}

int main()
{
    doConstruct();
    doInsert();

    cout << "Hello World!" << endl;
    return 0;
}

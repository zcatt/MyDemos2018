/*
http://en.cppreference.com/w/cpp/container/list/list

*/
#include <list>
#include <string>
#include <iostream>

using namespace std;



template<typename T>
std::ostream& operator<<(std::ostream& s, const std::list<T>& v) {
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
void doListConstructor()
{
    // c++11 initializer list syntax:
    std::list<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
    std::cout << "words1: " << words1 << '\n';

    // words2 == words1
    std::list<std::string> words2(words1.begin(), words1.end());
    std::cout << "words2: " << words2 << '\n';

    // words3 == words1
    std::list<std::string> words3(words1);
    std::cout << "words3: " << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    std::list<std::string> words4(5, "Mo");
    std::cout << "words4: " << words4 << '\n';
}

void display_sizes(const std::list<int>& nums1,
                   const std::list<int>& nums2,
                   const std::list<int>& nums3)
{
    std::cout << "nums1: " << nums1.size()
              << " nums2: " << nums2.size()
              << " nums3: " << nums3.size() << '\n';
}

/*result
Initially:
nums1: 6 nums2: 0 nums3: 0
After assigment:
nums1: 6 nums2: 6 nums3: 0
After move assigment:
nums1: 0 nums2: 6 nums3: 6
*/
void doOperatorEq()
{
    std::list<int> nums1 {3, 1, 4, 6, 5, 9};
    std::list<int> nums2;
    std::list<int> nums3;

    std::cout << "Initially:\n";
    display_sizes(nums1, nums2, nums3);

    // copy assignment copies data from nums1 to nums2
    nums2 = nums1;

    std::cout << "After assigment:\n";
    display_sizes(nums1, nums2, nums3);

    // move assignment moves data from nums1 to nums3,
    // modifying both nums1 and nums3
    nums3 = std::move(nums1);

    std::cout << "After move assigment:\n";
    display_sizes(nums1, nums2, nums3);

}

/*result
The first character is o
*/
void doFront()
{
    std::list<char> letters {'o', 'm', 'g', 'w', 't', 'f'};

    if (!letters.empty()) {
        std::cout << "The first character is: " << letters.front() << '\n';
    }
}

/*result
Sum of ints: 31
First fruit: orange
list 'empty' is indeed empty.
*/
void doIterator()
{
    std::list<int> ints {1, 2, 4, 8, 16};
    std::list<std::string> fruits {"orange", "apple", "raspberry"};
    std::list<char> empty;

    // Sums all integers in the list ints (if any), printing only the result.
    int sum = 0;
    for (auto it = ints.cbegin(); it != ints.cend(); it++)
        sum += *it;
    std::cout << "Sum of ints: " << sum << "\n";

    // Prints the first fruit in the list fruits, without checking if there is one.
    std::cout << "First fruit: " << *fruits.begin() << "\n";

    if (empty.begin() == empty.end())
        std::cout << "list 'empty' is indeed empty.\n";
}

/*result
construct A
construct B
begin doInsert
copy construct A
copy construct B
end doInsert
copy construct A
A
destruct A
copy construct B
B
destruct B
destruct B
destruct A
destruct A
destruct B
*/
void doInsert()
{
    class CA
    {
    public:
        CA(const char* name):m_s(name)
        {
            cout<<"construct "<<m_s<<endl;
        }
        CA(const CA& a): m_s(a.m_s)
        {
            cout<<"copy construct "<<m_s<<endl;

        }

        ~CA()
        {
            cout<<"destruct "<<m_s<<endl;

        }

    public:
        string m_s;
    };

    list<CA> alist;
    CA a("A");              //construct A
    CA b("B");              //construct B

    cout<<"begin doInsert"<<endl;
    alist.insert(alist.begin(), a); //copy construct A
    alist.insert(alist.end(), b);   //copy construct B
    cout<<"end doInsert"<<endl;

    for(CA a : alist)       //copy construct A/B
    {
        cout<<a.m_s<<endl;  //A/B
    }                       //desctruct A/B
}                           //destruct B             for CB b("B")
                            //destruct A             for CA a("A")
                            //destruct A and B       for alist's elements


/*result
0 1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
1 2 6 7 8 9
1 7 9
*/
void doErase()
{
    std::list<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    c.erase(c.begin());

    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    std::list<int>::iterator range_begin = c.begin();
    std::list<int>::iterator range_end = c.begin();
    std::advance(range_begin,2);        // 3
    std::advance(range_end,5);          // 6

    c.erase(range_begin, range_end);

    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    // Erase all even numbers (C++11 and later)
    for (auto it = c.begin(); it != c.end(); ) {
        if (*it % 2 == 0) {
            it = c.erase(it);       //返回删除元素的下一个pos
        } else {
            ++it;
        }
    }

    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

/*result
list1:   0 1 3 5 9
list2:   2 4 6 7 8
merged:  0 1 2 3 4 5 6 7 8 9
*/
void doMerge()
{
    std::list<int> list1 = { 5,9,0,1,3 };
    std::list<int> list2 = { 8,7,2,6,4 };

    list1.sort();
    list2.sort();
    std::cout << "list1:  " << list1 << "\n";
    std::cout << "list2:  " << list2 << "\n";
    list1.merge(list2);
    std::cout << "merged: " << list1 << "\n";
}

/*result
list1:  1 2 10 20 30 40 50 3 4 5
list2:
list1:  1 2 10 20 30 40 50
list2:  3 4 5
*/
void doSplice()
{
    std::list<int> list1 = { 1, 2, 3, 4, 5 };
    std::list<int> list2 = { 10, 20, 30, 40, 50 };

    auto it = list1.begin();
    std::advance(it, 2);        //3

    list1.splice(it, list2);        //it仍有效，

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";

    list2.splice(list2.begin(), list1, it, list1.end());

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";
}

/*
2 3 10 -1
*/
void doRemove()
{
    std::list<int> l = { 1,100,2,3,10,1,11,-1,12 };

    l.remove(1); // remove both elements equal to 1
    l.remove_if([](int n){ return n > 10; }); // remove all elements greater than 10

    for (int n : l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

/*result
before:      8 7 5 9 0 1 3 2 6 4
ascending:   0 1 2 3 4 5 6 7 8 9
descending:  9 8 7 6 5 4 3 2 1 0
*/
void doSort()
{
    std::list<int> list = { 8,7,5,9,0,1,3,2,6,4 };

    std::cout << "before:     " << list << "\n";
    list.sort();
    std::cout << "ascending:  " << list << "\n";
    list.sort(std::greater<int>());
    std::cout << "descending: " << list << "\n";
}

int main()
{
    doListConstructor();
    doOperatorEq();
    doIterator();
    doInsert();
    doErase();
    doMerge();
    doSplice();
    doRemove();
    doSort();

    cout << "Hello World!" << endl;
    return 0;
}

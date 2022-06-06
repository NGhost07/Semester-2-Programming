#include <iostream>
#include <vector>

using namespace std;

template <class iterator, class object>
bool all_of(const iterator& begin, const iterator& end, bool(& func)(object)) {
    for (auto i = begin; i != end; i++)
        if (func(*i) == false)
            return false;
    return true;
}

template <class iterator, class object>
bool any_of(const iterator &begin, const iterator &end, bool (&func)(object)) {
    for (auto i = begin; i != end; i++)
        if (func(*i) == false)
            return false;
    return true;
}

template <class iterator, class object>
bool none_of(const iterator &begin, const iterator &end, bool (&func)(object)) {
    for(auto i = begin; i != end; i++)
        if(func(*i) == true)
            return false;
    return true;
}

template<class iterator, class object>
bool one_of(const iterator &begin, const iterator &end, bool (&func)(object)) {
    int cnt = 0;
    for (auto i = begin; i != end; i++)
        if (func(*i) == true)
            cnt++;
    if (cnt == 1)
        return true;
    return false;
}

template <class iterator, class object>
bool is_sorted(const iterator &begin, const iterator &end, bool(&func)(object, object)) {
    iterator prev = begin;
    for (auto i = std::next(begin); i != end; i++) {
        if (func(*prev, *i) == false)
            return false;
        prev = i;
    }
    return true;
}

template <class iterator, class object>
bool is_partitioned(const iterator &begin,const iterator &end, bool (&func)(object)) {
    int cnt = 0;
    for (auto i = next(begin); i != end; i++)
        if (func(*i) != func(*(prev(i))))
            cnt ++;
    if (cnt == 1)
        return true;
    return false;
}

template <class iterator, class object>
bool find_not(const iterator &begin, const iterator &end, const object O) {
    for (auto i = begin; i != end; i++)
        if ((*i) != O)
            return true;
    return false;
}

template <class iterator, class object>
bool  find_backward(const iterator &begin, const iterator &end, const object O) {
    for (auto i = end; i != begin; i--)
        if (*i == O)
            return true;
    return false;
}

template <class iterator, class object>
bool is_palindrome(const iterator& begin, const iterator& end, bool(& func)(object, object)) {
    for (auto iLeft = begin, iRight = prev(end); static_cast<void>(iLeft != end), iRight != begin;
         iLeft = next(iLeft), iRight = prev(iRight))
        if (func(*iLeft, *iRight) == false)
            return false;
    return true;
}

template <class Types>
bool predicate(Types value) {
    if (value > 0)
        return true;
    return false;
}

template <class Types>
bool sort(Types number1, Types number2) {
    if (number1 <= number2)
        return true;
    return false;
}

template <class Types>
bool palindrome( Types number1, Types number2) {
    if (number1 == number2)
        return true;
    return false;
}

class Point{
private:
    int x, y;
public:
    Point(){
        this->x = 0;
        this->y = 0;
    }
    Point(int _x, int _y){
        this->x = _x;
        this->y = _y;
    }
    int getX(){
        return this->x;
    }
    int getY(){
        return this->y;
    }
    friend bool operator < (const Point &p, int number) {
        return (p.x < number || p.y < number);
    }
    friend bool operator > (const Point &p, int number) {
        return (p.x > number || p.y > number);
    }
    friend bool operator <= (const Point &p1, const Point &p2) {
        return (p1.x <= p2.x && p1.x <= p2.y );
    }
    friend bool operator == (const Point &p1, const Point &p2) {
        return(p1.x == p2.x && p1.y == p2.y);
    }
    friend bool operator != (const Point &p1, const Point &p2) {
        return(p1.x != p2.x || p1.y != p2.y);
    }
    ~Point(){
    }
};

void print_result (bool tmp){
    cout << (tmp ? "True" : "False") << endl;
}

int main(int argc, const char * argv[]) {
    vector<int> vti = {1,-2,3,-4,5};
    cout << "Original vector: ";
    for (auto i: vti)
        cout << i << "  ";
    cout << endl;
    cout << "1. all_of : ";
    print_result(all_of(vti.begin(), vti.end(), predicate<int>));
    cout << "2. any_of : ";
    print_result(any_of(vti.begin(), vti.end(), predicate<int>));
    cout << "3. none_of : ";
    print_result(none_of(vti.begin(), vti.end(), predicate<int>));
    cout << "4. one_of : ";
    print_result(one_of(vti.begin(), vti.end(), predicate<int>));
    cout << "5. is_sorted : ";
    print_result(is_sorted(vti.begin(), vti.end(), sort<int>));
    cout << "6. is_partitioned : ";
    print_result(is_palindrome(vti.begin(), vti.end(), sort<int>));
    cout << "7. find_not : ";
    print_result(find_not(vti.begin(), vti.end(), 3));
    cout << "8. find_backward : ";
    print_result(find_backward(vti.begin(), vti.end(), 3));
    cout << "9. is_palindrome : ";
    print_result(is_palindrome(vti.begin(), vti.end(), palindrome<int>));
    cout << endl;
    
    vector<Point> vtp = {{0,1},{1,2},{2,3},{3,4},{4,5}};
    cout << "Original vector: ";
    for (auto i: vtp)
        cout << "{" << i.getX() << "," << i.getY() << "}" << "  ";
    cout << endl;
    cout << "1. all_of : ";
    print_result(all_of(vtp.begin(), vtp.end(), predicate<Point>));
    cout << "2. any_of : ";
    print_result(any_of(vtp.begin(), vtp.end(), predicate<Point>));
    cout << "3. none_of : ";
    print_result(none_of(vtp.begin(), vtp.end(), predicate<Point>));
    cout << "4. one_of : ";
    print_result(one_of(vtp.begin(), vtp.end(), predicate<Point>));
    cout << "5. is_sorted : ";
    print_result(is_sorted(vtp.begin(), vtp.end(), sort<Point>));
    cout << "6. is_partitioned : ";
    print_result(is_palindrome(vtp.begin(), vtp.end(), sort<Point>));
    cout << "7. find_not : ";
    print_result(find_not(vtp.begin(), vtp.end(), Point(2,3)));
    cout << "8. find_backward : ";
    print_result(find_backward(vtp.begin(), vtp.end(), Point(2,3)));
    cout << "9. is_palindrome : ";
    print_result(is_palindrome(vtp.begin(), vtp.end(), palindrome<Point>));
    cout << endl;
    return 0;
}

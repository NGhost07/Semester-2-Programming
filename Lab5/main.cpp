#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename Type>
class C_Buffer{
private:
    int size = 0;
    Type *A;
protected:
    class iterator : public std::iterator<random_access_iterator_tag, Type>{
        // Random-access iterators are iterators that can be used to access elements at an arbitrary offset position relative to the element they point to, offering the same functionality as pointers
    private:
        Type *p;
    protected:
        iterator() : p(nullptr){
        }
        iterator(Type *p) : p(p){
        }
        iterator(const iterator &i) : p(i.p){
        }
        Type &operator * () const{
            return *p;
        }
        Type &operator [] (int i) const{
            return p[i];
        }
        Type &operator -> () const{
            return p;
        }
        iterator &operator ++ (){
            p++;
            return *this;
        }
        iterator &operator -- (){
            p--;
            return *this;
        }
        iterator operator + (int number){
            return iterator(p + number);
        }
        iterator operator - (int number){
            return iterator(p - number);
        }
        ptrdiff_t operator - (const iterator &i){
            return p - i.p;
        }
        bool operator == (const iterator &i){
            return p == i.p;
        }
        bool operator != (const iterator &i){
            return p != i.p;
        }
        bool operator >= (const iterator &i){
            return p >= i.p;
        }
        bool operator <= (const iterator &i){
            return p <= i.p;
        }
        bool operator > (const iterator &i){
            return p > i.p;
        }
        bool operator < (const iterator &i){
            return p < i.p;
        }
    };
public:
    C_Buffer(){
        size = 0;
        A = nullptr;
    }
    C_Buffer(int _size){
        size = _size;
        A = new Type(size);
        for (int i=0; i<size; i++) 
            A[i] = 0;
    }
    C_Buffer (int _size, Type value){
        size = _size;
        for (int i=0; i<size; i++)
            A[i] = value;
    }
    C_Buffer (int _size, Type *tmp){
        size = _size;
        A = tmp;
    }
    void push_back(Type x){
        if (size == 0) {
            size ++;
            A = new Type[size];
            A[0] = x;
        }else{
            size ++;
            Type *tmp = new Type(size);
            tmp[size-1] = x;
            for (int i=0; i<size-1; i++)
                tmp[i] = A[i];
            A = tmp;
        }
    }
    void pop_back(){
        if (size == 0) {
            size = 0;
            A = nullptr;
        }else{
            size --;
            Type *tmp = new Type(size);
            for (int i=0; i<size; i++)
                tmp[i] = A[i];
            A = tmp;
        }
    }
    void push_front(Type x){
        if (size == 0) {
            size++;
            A = new Type[size];
            A[0] = x;
        }else{
            size++;
            Type *tmp = new Type(size);
            tmp[0] = x;
            for (int i=1; i<size; i++)
                tmp[i] = A[i-1];
            A = tmp;
        }
    }
    void pop_front(){
        if (size == 0) {
            size = 0;
            A = nullptr;
        }else{
            size--;
            Type *tmp = new Type(size);
            for (int i=0; i<size; i++)
                tmp[i] = A[i+1];
            A=tmp;
        }
    }
    Type first(){
        return A[0];
    }
    Type last(){
        return A[size-1];
    }
    const Type operator [] (int i){
        if (i >= size)
            throw invalid_argument("Circular buffer out of range");
        else
            return A[i];
    }
    void resize (const size_t & _size){
        Type *New_Buffer;
        if (_size < size) {
            New_Buffer = new Type((int)_size);
            for (int i=0; i<_size; i++)
                New_Buffer[i] = A[i%size];
            delete [] A;
            A = New_Buffer;
            size = (int) _size;
        }else{
            New_Buffer = new Type((int)_size);
            for (int i=0; i<_size; i++)
                New_Buffer[i] = A[i%size];
            delete [] A;
            A = New_Buffer;
            size = (int)_size;
        }
    }
    void print(){
        if (size == 0)
            cout << "empty" << endl;
        else{
            for (int i=0; i<size; i++)
                cout << A[i] << "   ";
            cout << endl;
        }
    }
    ~C_Buffer(){
    }
};

int main(int argc, const char * argv[]) {
    int arr[6] = {1, 5, 7, 8 ,-2, -10};
    C_Buffer<int> B(6, arr);
    B.print();
    B.push_back(2);
    B.print();
    B.pop_back();
    B.print();
    B.push_front(10);
    B.print();
    B.pop_front();
    B.print();
    cout << B.first() << endl;
    cout << B.last() << endl;
    cout << B[2] << endl;
    B.resize(5);
    B.print();
    return 0;
}

#include <string>
#include <iostream>
#include <regex>
#include <thread>
using namespace std;

/****************** performance must be measured and not assumed. *********************/
//////////////////////////////////////////////////////////////////////////////////////
// 0- In c++17 you can easily define static class member inside the calss
//  static int x = 5;

// C++ 11 new features.
// 1- lambda expression
/* you can define some helper functions locally.

[capture mode](parameters)-> return
{
    // the body.
}
*/

int count_evens(const std::vector<int>& vec)
{
    int count = 0;
    for_each(std::begin(vec), std::end(vec), 
        [&count](int item){
            if(item%2 == 0)
            {
                count++;
            }
        }
    );

    return count;
}

// 2- automatic type deduction of obejects and decltype.
// auto is the type is deduced from the right hand side of assignment.
// decltype the type is deduced from the evaluated expression inside decltype.

// 3- uniform initializatin syntax
// using {} to initilaize different types even the POD ones.
// in class initialization of data member of the class.
class UI
{
private:
    int x, y;
    float z = 5.2;  // in class data member initialization.
public:
    UI(int x, int y): x{x}, y{y} {}

    void print()
    {
        std::cout << "x = " << x << "\n" <<
                    "y = " << y << "\n" << 
                    "z = " << z << "\n";
    }
};

void test_UI()
{
    UI ui {5, 6};
    ui.print();

    int* a = new int[3] {0};

}

// 4- delegating constructors.
class DC
{
    int x, y;
    char* p;

public:
    DC(int v): x(v), y(0), p(new char[5]{'a', 'a', 'a', 'a', '\0'}) {}

    DC(): DC(0) {} // construction delegation.

    void print()
    {
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << p << std::endl;
    }
};

void test_dc()
{
    DC dc;
    dc.print();
}
// 5- delete and default functions declarttion
struct DADFD
{
    std::string name;
    DADFD(const std::string& name_): name(name_) {}

    DADFD() = default;         // instructs the compiler to generate the defualt implementations for construction.
    virtual ~DADFD()=default;  

    DADFD(const DADFD& other) = delete; // inform the compiler to not generate the default copy constructor.
    DADFD& operator = (const DADFD& other) = delete; 

    void print_quote()
    {
        std::cout << "The only way to learn a new programming language is by writing programs in it.\n";
    }
};

// 6- nullptr
std::string f(int){ return "f(int)";}
std::string f(int*){ return "f(int*)";}
void test_nullptr()
{
    // std::cout << f(NULL) << std::endl; // compile-time error `call f is ambiguous`
    // std::cout << f(0) << std::endl; // will call the f(int)
    // std::cout << f(nullptr) << std::endl; // will call the one takes pointer, it is strongely typed.

    // some crazy stuff.
    std::string (*f_int)(int) = f;        // pointer to function.
    std::cout << (*f_int)(5) << std::endl;
}

class MFP{
private:
    int x, y;
public:
    MFP(int xx, int yy): x(xx), y(yy){}

    void f();
};

void MFP::f()
{
    std::cout << x << "|" << y << std::endl;
    std::cout << "The only way to learn a new programming language is by writing programs in it.\n";
}

void test_mfp()
{
    void (MFP::*fptr)() = &MFP::f; // pointer to member function x inside class A.

    MFP a {1, 1};
    MFP b{2, 2};

    (a.*fptr)();  // bind the fptr to the f function in a object.
    (b.*fptr)();  // bind the fptr to the f function in b object.
}

// 7- rvalue references the most important concept introduced by c++ which leads to move semantcs concepts.
// refenence types in C++03 can only bind to lvalues.
// C++11 introduces a new category of refernce types called rvalue refernces.
// rvalue refernces can bind to rvalues, e.g. temporary objects and literals.
// the primary reason for adding rvalue ref is move semantics.
// unlike copying the move semantics move the ownership responsabitity from an entity to another one.
// lvalue object has a name but the rvalue objec doesn't have a name (temporary object)
class CMSemantics
{
private:
int strSize = 100;
char* str;

void init() noexcept
{
    this->str = new char[this->strSize];
}

public:

    // default constructor.
    CMSemantics()
    {
        this->init();
    }

    // string constructor.
    CMSemantics(const char* s): CMSemantics() // delegate allocation to the default constructor.
    {
        std::cout << "-- string constructor." << std::endl;
        std::strcpy(str, s);
    }

    // copy constructor.
    CMSemantics(const CMSemantics& cms): CMSemantics()
    {
        std::cout << "-- Copy constructor." << std::endl;
        if (cms.str != nullptr && this != &cms)
        {
            std::strcpy(this->str, cms.str);
        }
    }

    // if it isn't implemented and the copy constructor is implemented the copy construcotr will be called.
    // non-template, non-static member function.
    // copy assignment.
    CMSemantics& operator = (const CMSemantics& cms)
    {
        std::cout << "-- Copy assignment operator." << std::endl;
        if (cms.str != nullptr && this != &cms)
        {
            std::strcpy(this->str, cms.str);
        }

        return *this;
    }

    // move constructor
    CMSemantics(CMSemantics&& cms)
    {
        std::cout << "-- Move constructor." << std::endl;

        this->init();

        if(cms.str != nullptr )
        {
            std::strcpy(this->str, cms.str);

            // you can just call the destructor of cms.
            delete cms.str;
            cms.str = nullptr;
        }
    }

    // move assignment operator
    // if you don't implement it the copy assignment operator will be called.
    CMSemantics& operator = (CMSemantics&& cms)
    {
        std::cout << "-- Move assignment operator." << std::endl;

        if(cms.str != nullptr)
        {
            std::strcpy(this->str, cms.str);
            delete cms.str;
            cms.str = nullptr;
        }

        return *this;
    }

    // destructor.
    ~CMSemantics()  noexcept
    {
        if(str != nullptr)
        {
            delete str;
            str = nullptr;
        }
    }
};

void test_cmsemantices()
{
    // string construction.
    CMSemantics sms1 ("string construction");

    // copy construction.
    CMSemantics sms_cc(sms1);
    CMSemantics sms_cc1 = sms_cc;

    // copy assignment operator. 
    sms_cc1 = sms_cc;

    // move constructor.
    auto sms_mc = std::move(sms_cc); // stop use sms_cc it is moved, it is dead

    sms_mc = std::move(sms_cc1);    // stop use sms_cc1 it is moved, it is dead.

}

// 8- multithreading library
// thread library, async, promise, future, ......
// std::thread takes a function object and an optional series of args to pass to it.
void test_thread()
{
    auto print = [](int x){std::cout << "hello" << x << std::endl;};

    std::thread thread_handle(print, 5);
    
    std::cout << "hello madam\n";

    thread_handle.join();
}

// 9- async function

// 10- new containers
// unorder_set, unorder_map, multiset, multimap.

// 11- type traits.

// 12- new alogorithms 
// any_of, all_of, none_of(), iota, copy_n(src_begin_ptr, elements_num, des_ptr);

// 13- Strongly-typed enums
// enum class Category : enum_to_inherit_from {isSmall = 0, ....};

// 14- static_assert. 
// assert at compile time

// 14- variadic templates.
// a variadic template is a template that can take an arbitrary number of template arguments of any type.
// both class and functions can be variadic template
template<typename U, typename... Args>
static void S_Construct(U* p, Args&&... args)
{
    new (p) U(std::forward<Args>(args)...);
}

// 15- range-based for loop.
static void printAsJson(const std::vector<std::tuple<const char*, const char*, double>>& data)
{
    std::map<const char*, double> json;

    for (const auto& datum : data)
    {
        json[std::get<1>(datum)] = std::get<2>(datum) * 1000;
    }
}

// 16- noexcept
// declare the function or member function that it will not throw an exception
// good for some reasons
// * better interface design.
// * helps the compiler to produce better obj code where
//   - no need to keep unwindouble state if the function is throws.
//   - objects don't have to be destructed in inverse order of construction.
static int foo()noexcept {return 0;}

// 17- override identifier.
// override special identifier means that the compiler will check the base class to see if there is a virtual function with this exact signature.
// And if ther is not the compiler will indicate and an error.
class OI
{
public:
    virtual void print() const = 0;

    // declaring non-virtual destructor will be dispatched statically and obfuscate the destructor of the derived class.
    virtual ~OI() // if you don't define it virtual the derived class will not be called and the base destructor will be called.
    {
        std::cout << "I am the destructor of the base class\n";
    }
};

// in polymorphism, derived classes are handled through base class handler a ref or a pointer.
class OII1 : public OI
{
public:
    void print() const override
    {
        std::cout << "hello world1" << std::endl;
    }

    ~OII1()
    {
        std::cout << "I am the destructor of OII1" << std::endl;
    }
};

class OII2 : public OI
{
public:
    void print() const override
    {
        std::cout << "hello world2" << std::endl;
    }
};

void test_polymorphism()
{
    OI* io_ptr = new OII1();
    io_ptr->print();
    delete io_ptr;             // will call the destructor of the derived class then the base one.

    // io_ptr = new OII2();
    // io_ptr->print();
    // delete io_ptr;
}

// inheritence hierarchy.
struct A
{
    int x = 1, y=2;
    void print()
    {
        std::cout << "X = " << A::x << std::endl;
        std::cout << "Y = " << A::y << std::endl;
    }
};

struct B : public virtual A
{
    
};

struct C : public virtual A
{

};

struct  CC : public A
{
};

struct D : public B, C
{
    void update_values()
    {
        B::x = 2;
        B::y = 5;
        B::A::x = 0;
        B::A::y = 0;
        C::A::x = 1;
        C::A::y = 1;
    }
};


void test_inheritence_hierarchy()
{
    std::cout << sizeof(A{}) << std::endl;   // base class
    std::cout << sizeof(CC{}) << std::endl;  // not virtual inheritence of A, the same size as A
    std::cout << sizeof(B{}) << std::endl;   // virtual inheritence doubled the size because there are A::x, A::y, B::x, B::y
    std::cout << sizeof(D{}) << std::endl;   // sizeof(B) + sizeof(C)
    D d;
    d.update_values();
    // d.print();
}

// virtual functions
// for every class has at least one virtual function the compiler will create vtable for it and every vfunction will be added to it.
// stores a pointer to its defintion. entries in vtable can point to a either functions declared in the class itself or inherited from 
// another class. 
//Note that vtables exist at the class level, meaning there exists a single vtable per class, and is shared by all instances.
// the vtable is shared by all instances of a specific class.
//Note that the vpointer is just another class member added by the compiler and increases the size of every object that has a vtable by 

class sos{
    
public:
    sos() {std::cout << "I am the sos constructor.\n";}
    void print()
    {
        std::cout << this << std::endl;
    }

    virtual void vf() {std::cout << "hello\n";} // will create vtablePtr with 8 bytes.

    virtual void vf1() {std::cout << "hello\n";} // will create vtablePtr with 8 bytes.

    virtual void vf2() {std::cout << "hello\n";} // will create vtablePtr with 8 bytes.
};

class boom : public sos
{
    public:
    boom() {std::cout << "I am the boom constructor\n";} // the base class is called first.
};

// inheritence hierachy
// virtual inheritence is a technique to solve the diamond heirarchy of objects.
// and it ensures that only one copy of a base class's member variables are inherited by second-level derivatives.
// You don't have to use virtual inheritance everywher, `You only pay for what you use`, If you don't need it, don't use it.
// always put in your mind the called virtual function is the most derived one.
// the more use of it may complicate your project structure and made the code less readable and less maintainable.
//All virtual base subobjects are initialized before any non-virtual base subobject, 
//so only the most derived class calls the constructors of the virtual bases in its member initializer list:

// @ref copied from cppreference site.
// /*** PUBLIC INHERITENCE ***/
// when a class uses public member access specifier to derive from a base, all public members of the base class are accessible as public members
// of the derived class and all protected members of the base class are accessible as protected members of the derived class.
// private members of the base are never accessible unless friended.

// **** PROTECTED INHERITENCE ****
// all public and protected members of the base class are accessible as protected members of the derived class private members of the base class are
// never accessible unless frieended.
// protected inheritance may be used for "Controlled polymorphism" within the members of Derived, as well as within the members of all 
// further-derived classes, the derived class IS-A bases

// **** PRIVATE INHERITENCE ****
// when a class uses private member access specifier to derive from a base, all public and protected members of the base class are accessible
// as private members of the derived class 
// private inheritance is commonly used in "Policy-based Design", since policies are usually empty classes, and using them as bases
// both enables static polymorphism and leverages empty-base optimization.
// can also be used to implement the composition relationship where the base class has an implementation details of the derived class.
// using a member provide better encapsulation
template<typename Transport>
class Service : private Transport
{
public:
void transmit(){this->send();}
};

class Tcp
{
public:
void send();
};

class Udp
{
public:
void send();
};


struct B1 {int n;};
class X : public virtual B1{};  // add more 12 bytes for vptr. virtual to solve the diamond problem.
class Y : virtual public B1{
    virtual void vfn(){}
};

class Z : public B1 {};
class AA : X, Y, Z              // 4 bytes for x, 12 bytes for AA vptr, 12 bytes for Y/X vptr.
{
    int k[1];
    AA()
    {
        X::n = 1; // modifies the virtual B subobject's member.
        Y::n = 2; // modifies the same virtual B subobject's member.
        Z::n = 3; // modifies the non-virtual B subobject's member.
    }
};

void test_virtual_inheritence()
{
    std::cout << sizeof(B1) << std::endl;
    std::cout << sizeof(Z) << std::endl;
    std::cout << sizeof(X) << std::endl;
    std::cout << sizeof(AA) << std::endl;
}

struct XX {int x; char c; char d; char w; char y; double m;};
struct XX1: virtual public XX {int y;}; // size of XX and size of vtablePtr
struct XX2: public XX {};
struct XX3: public XX1, XX2 { // duplicate indirect inheritance of XX from XX1 and XX2
    void set_x() 
    {
        XX1::x = 100;
    }
};

void check_classes_sizes() 
{
    std::cout << sizeof(XX) << std::endl;
    std::cout << sizeof(XX1) << std::endl;
    std::cout << sizeof(XX2) << std::endl;
    std::cout << sizeof(XX3) << std::endl;
}

struct P{int x = 5;};
struct Ch: P{int y = 6;};

/*******************  C++11 Features ***************************/
////////////////////////////////////////////////////////////////
// 1- move semantics 
// main benefit is performance optimization. Instead of copying, moving is cheaper way to transfer resources.
// the object will be destroyed why copying it just move it to another object.
// make it possible for non-copyable types such as std::unique_ptr to guarantee that there is only one instance of a resource being managed at a time.


// 2- Rvalue reference (T&&) -> where T isn't a non-template type parameter.
// rvalue only bind to rvalues
// you can think of rvalue as a ref to a tmp object or an object you can't take its address.
// all variables are lvalue types and they can have types of rvalue ref `ofcourse refering to rvalue values` or lvalue ref 
/*
int x = 0; // lvalue of type int.
int& xl = x; // lvaue value of type int&
int&& xr = x; // compiler error lvalue can't bind to rvalue check the above note.
int&& xr2 = 0; // xr2 is an `lvaue` of type `int&&` binds to the rvalue temporary 0

void f(int&){}
void f(int&&) {}

f(x); // calls f(int&) where x is lvalue.
f(xl); // calls f(int&)
f(3) // calls f(int&&)
f(std::move(x)) // calls f(int&&)
f(xr2); // calls f(int&), the xr2 is lvalue but its type of int&& to an rvalue. as you know all variables are lvalue but they can have lvalue or rvalue type.
f(std::move(xr2)) // calss f(int&&)

// 3- universal/forwarding references. (T&&) or (auto&&) -> where T is a template type parameter.
/*
- This enables perfect forwarding: the ability to pass arguments while maintaining their value category (lvalue stays lvalues, temporaries are forwarded as rvalues)
- Forwarding references allow a reference to bind to either an lvalue or rvalue depending on the type
- Forwarding references follow the rules of reference collapsing.
.. T& & -> T&
.. T& && -> T&
.. T&& & -> T&
.. T&& && -> T&&
- auto type deduction with lvalues and rvalues.
.. int x = 0; // lvalue of type int.
.. auto&& al = x; // lvalue of type int& binds to the lvalue x.
.. auto&& al = 0; // lvalue of type int&& binds to the rvalue of temporary 0
*/

// c++14 or later
void print(auto&& v)
{
    std::cout << v << std::endl;
}

void xxx(int x)
{
    std::cout << x << std::endl;
}

/* c++11 or later
template<typename T>
void print(T&& v)
{
    std::cout << v << std::endl;
}
*/ 

// 4- decltype: operator returns the declared type of an expression passed to it.
void test_decltype()
{
    int a = 1;
    decltype(a) b = a; // decltype a is int.

    auto add = [](int x, int y) -> decltype(x+y){return x+y;};
}

class FOO{
    int x;
    public:
    FOO()
    {
        this->xx();
    }

    virtual void xx() noexcept
    {
        std::cout << "-- I am xx() from the base class" << std::endl;
    } 
};

class BOO: public FOO
{
    public:
    BOO()
    {
        this->xx();
    }

    void xx() noexcept override
    {
        std::cout << "I am xx() from the derived class." << std::endl;
    }

};

class Noo
{
private:
    int w;
public:

    explicit Noo(int x): w{x} {} 
};


/****  C++20  ****************/
// ---------------------------/
// 1- Coroutines.
/* ------------
- they are special functions that have their execution suspended or resumed when they invoke again with the same state.
- The co_return, co_await, co_yield keywords must be present in the function's body. 
- They are stackless, unless optimized by the compiler.
- Their state is allocated on the heap.
*/




int main() 
{
    // std::cout << count_evens({1, 2, 5});
    // test_UI();
    // test_nullptr();
    // test_mfp();
    // test_dc();
    // test_cmsemantices();
    // test_polymorphism();
    // test_inheritence_hierarchy();
    // test_thread();
    // test_virtual_inheritence();
    Noo n{5.5};
    

    return 0;
}

  
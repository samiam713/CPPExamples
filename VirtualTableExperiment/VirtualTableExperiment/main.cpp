//
//  main.cpp
//  VirtualTableExperiment
//
//  Created by Samuel Donovan on 2/9/21.
//

#include <iostream>

typedef void(*func_ptr_t)(void*);

void f0(void* x) {
    
}

void f1(void* x) {
    
}

template <class Class>
class Virtual {
    func_ptr_t* vtable;
    Class c;
};

void applyToVirtual(void* virtualClass, int which) {
    func_ptr_t* vtable = reinterpret_cast<func_ptr_t*>(virtualClass);
    void* classPtr = vtable + 1;
    (vtable[which])(classPtr);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

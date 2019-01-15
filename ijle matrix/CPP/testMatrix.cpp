#include "SparseMatrix.h"
#include "../memleak/debug_new.h"
#include <iostream>
#include <string>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void testMatrix(){
    cout << "initializing matrix ..." << endl;
    SparseMatrix m(6,6);
    cout << "matrix initialized..." << endl;
    m.add_element(4,3,"element43");
    m.add_element(4,5,"element45");
    m.add_element(4,4,"element44");
    m.add_element(4,2,"element42");
    m.add_element(4,1,"element41");
    m.add_element(1,1,"element11");
    m.add_element(1,2,"element12");
    m.add_element(1,3,"element13");
    m.add_element(1,4,"element14");
    m.add_element(1,5,"element15");
    m.add_element(3,2,"element32");
    m.add_element(5,5,"element55");
    cout << "added elements ..." << endl;
    m.print();

    assert(m.add_element(6,1,"wrong") == -3);
    assert(m.add_element(3,6,"wrong") == -2);
    assert(m.add_element(3,-1,"wrong") == -2);
    assert(m.add_element(1,5,"wrong") == -1);

    string word;
    cout << endl << "retrieved element: " << endl;
    
    assert(m.get(1,4,word) == 0);
    assert(word == "element14");


    assert(m.get(6,1,word) == -3);
    assert(m.get(3,6,word) == -2);
    assert(m.get(3,-1,word) == -2);
    
    assert(m.get(3,3,word) == -1);

    m.remove_element(1,4);
    m.remove_element(3,2);
    cout << endl << "removed elements (1,4) and (3,2)" << endl;
    m.print();
    assert(m.get(1,4,word) == -1);
    assert(m.get(3,2,word) == -1);

    m.transpose();
    cout << endl << "transposed matrix" << endl;
    m.print();
    assert(m.get(1,4,word) == 0);
    assert(word == "element41");
    assert(m.get(5,1,word) == 0);
    assert(word == "element15");
    assert(m.get(4,5,word) == -1);
	SparseMatrix k(m);
	cout << endl << "copy constructor" << endl;
	k.print();
	assert(m.get(1,4,word) == 0);
    assert(word == "element41");
    assert(m.get(5,1,word) == 0);
    assert(word == "element15");
    assert(m.get(4,5,word) == -1);
	cout << endl << "operator +" << endl;
	SparseMatrix l(2,8);
    cout << "matrix initialized..." << endl;
    l.add_element(1,7,"element17");
    l.add_element(0,3,"element03");
    l.print();
	SparseMatrix n=m+l;
	n.print();
    
}

int main(){
    testMatrix();
	getchar();
}

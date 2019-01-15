#include "SparseMatrix.h"
#include <iostream>
using namespace std;
int MatrixElement::getColumnNr() const{
    return this->columnNr;
}
string& MatrixElement::getWord(){
    return (this->word);
}
MatrixElement* MatrixElement::getNext() const{
    return this->next;
}
void MatrixElement::setNext(MatrixElement * el){
    this->next = el;
}

MatrixRow::MatrixRow():first(NULL){

}
MatrixRow::~MatrixRow(){
    MatrixElement* tmp = this->first;
    while (tmp != NULL){
        MatrixElement* tmp2 = tmp;
        tmp = tmp->getNext();
        delete tmp2;
    }
}
int MatrixRow::add(int columnNr, const string& word){
    
    MatrixElement* cur = this->first;
    MatrixElement* prev = NULL;
    while (cur != NULL && cur->getColumnNr() <= columnNr){
        if (cur->getColumnNr()==columnNr){
            //colomun bestaat al!
            return -1;
        }
        prev = cur;
        cur = cur->getNext();
       
    }
    MatrixElement* add= new MatrixElement(columnNr, cur, word);
            if (prev == NULL){
                this->first = add;
                return 0;
            }else{
                prev->setNext(add);
                return 0;
            }
    return 0;
    

}
int MatrixRow::remove(int columnNr){
    MatrixElement* cur = this->first;
    MatrixElement* prev = NULL;
    while (cur != NULL){
        if (cur->getColumnNr()==columnNr){
            if (prev == NULL){
                this->first = cur->getNext();
                delete cur;
                return 0;
            }else{
                prev->setNext(cur->getNext());
                delete cur;
                return 0;
            }
        }
        prev = cur;
        cur = cur->getNext();
    }
    return -1;
}

int MatrixRow::get(int columnNr, std::string& word) const {
    MatrixElement* cur = this->first;
    while (cur != NULL){
        if (cur->getColumnNr()==columnNr){
            word = cur->getWord();
            return 0;
        }
        cur = cur->getNext();
    }
    return -1;
}
RowIterator MatrixRow::getIterator() const{
    return RowIterator(this->first);
}
RowIterator::RowIterator(MatrixElement* start):current(start){
}
bool RowIterator::hasNext() const{
    return this->current!=NULL;
}
string& RowIterator::next(int& columnNr){
    string& word = this->current->getWord();
    columnNr = this->current->getColumnNr();
    this->current = this->current->getNext();
    return word;
}
SparseMatrix::SparseMatrix(int r, int c){
    this->number_of_columns = c;
    this->number_of_rows = r;
    this->rows = new MatrixRow[r];
}
SparseMatrix::SparseMatrix(const SparseMatrix& sm) {
    number_of_rows=sm.number_of_rows;
	number_of_columns=sm.number_of_columns;
	rows = new MatrixRow[sm.number_of_rows];
	for(int r = 0; r < sm.number_of_rows; r++) {
        RowIterator i = sm.rows[r].getIterator();
        while(i.hasNext()){
            int c;
            string s = i.next(c);
			add_element(r,c,s);
        }
    }
}
int SparseMatrix::add_element(int r, int c, const string& word){
    if (r < 0  || r >= this->number_of_rows ){
            return -3;
    }
    if (c < 0 || c >= this->number_of_columns ){
            return -2;
    }

    return this->rows[r].add(c, word);
}
SparseMatrix::~SparseMatrix(){
    delete[] rows; 
}

int SparseMatrix::remove_element(int r, int c){
    if (r < 0  || r >= this->number_of_rows ){
            return -3;
    }
    if (c < 0 || c >= this->number_of_columns ){
            return -2;
    }
    
    return this->rows[r].remove(c);
}
int SparseMatrix::get(int r, int c, std::string& s) const{
    if (r < 0  || r >= this->number_of_rows ){
            return -3;
    }
    if (c < 0 || c >= this->number_of_columns ){
            return -2;
    }
    
    return this->rows[r].get(c,s);
}
void SparseMatrix::print() const{
    for(int r = 0; r < number_of_rows; r++) {
        RowIterator li = this->rows[r].getIterator();
        while(li.hasNext()){
            int c;
            string s = li.next(c);
            cout << "(" << r << "," << c << "): " << s << endl;
        }
    }
    cout << "end of Matrix" << endl;
}
void SparseMatrix::transpose() {
    // keep old values for traversing matrix
    int old_cols = number_of_columns;
    int old_rows = number_of_rows;
    MatrixRow* old_mtrx = this->rows;

    // new values
    number_of_rows = old_cols;
    number_of_columns = old_rows;
    this->rows = new MatrixRow[number_of_rows];


    // make transposed matrix by adding elements from old matrix
    for(int r = 0; r < old_rows; r++) {
        RowIterator li = old_mtrx[r].getIterator();
        while(li.hasNext()){
            int c;
            string s = li.next(c);
            add_element(c, r, s);
        }
    }
    delete[] old_mtrx;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& sm){
	int combinedNumberOfRows;
	int combinedNumberOfColumns;
	if(number_of_rows>=sm.number_of_rows)
		combinedNumberOfRows=number_of_rows;
	else
		combinedNumberOfRows=sm.number_of_rows;
	if(number_of_columns>=sm.number_of_columns)
		combinedNumberOfColumns=number_of_columns;
	else
		combinedNumberOfColumns=sm.number_of_columns;
	SparseMatrix temp(combinedNumberOfRows,combinedNumberOfColumns);
	for(int r = 0; r < number_of_rows; r++) {
        RowIterator li = this->rows[r].getIterator();
        while(li.hasNext()){
            int c;
            string s = li.next(c);
			temp.add_element(r,c,s);
        }
    }
	for(int r = 0; r < sm.number_of_rows; r++) {
        RowIterator li = sm.rows[r].getIterator();
        while(li.hasNext()){
            int c;
            string s = li.next(c);
			temp.add_element(r,c,s);
        }
    }
	return temp;
}






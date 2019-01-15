#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <string>

class MatrixElement{
	int columnNr;
	std::string word;
	MatrixElement* next;

	public:
	    MatrixElement(int columnNr, MatrixElement* next, const std::string& word): columnNr(columnNr), word(word), next(next) {}
		int getColumnNr() const;
		std::string& getWord();
		MatrixElement* getNext() const;
		void setNext(MatrixElement*);
};

class RowIterator {
    MatrixElement* current;

    public:
		RowIterator(MatrixElement* start);
		
		std::string& next(int& columnNr);
		bool hasNext() const;
};

class MatrixRow {
    MatrixElement* first;

    public:
		MatrixRow();
		~MatrixRow();

	    int add(int columnNr, const std::string& word);
	    int remove(int columnNr);
	    int get(int columnNr, std::string& word) const;
	    RowIterator getIterator() const;
};

class SparseMatrix{
    int number_of_rows;
    int number_of_columns;
   //TODO add needed members
	MatrixRow* rows;
    public:
		SparseMatrix(int r, int c);
		SparseMatrix(const SparseMatrix&);
		~SparseMatrix();
		
	    int add_element(int r, int c, const std::string& s);
	    int remove_element(int r, int c);
	    int get(int r, int c, std::string& s) const;
	    void transpose();
	    void print() const;
		SparseMatrix operator+(const SparseMatrix&);
};

#endif

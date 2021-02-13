#include <stdio.h>
#include <stdexcept>
#include <iostream>

class Matrix
{
private:
    size_t _rows;
    size_t _columns;
    double *_data;

public:
    Matrix(): _rows(0), _columns(0), _data(nullptr) {}
    Matrix(size_t rows, size_t columns) : _rows(0), _columns(0), _data(nullptr)
    {
        resize(rows, columns);
    }

    Matrix(const Matrix& m): _rows(0), _columns(0), _data(nullptr) { // copy constructor
        *this = m;
    }

    void operator=(const Matrix& m) { // member-wise copy operator.
        resize(m._rows, m._columns);
        memcpy(_data, m._data, sizeof(double)*_rows*_columns);
    }

    ~Matrix() //<<
    {
        delete[] _data; //<<
        _data = nullptr;
        _rows = 0;
        _columns = 0;
    }

    

    void resize(size_t new_rows, size_t new_columns){
        if (new_rows == _rows && new_columns == _columns) return;
        double* new_data = new double[new_rows * new_columns];
        // new double call constructor must give 0;
        // double a = double(); << 0  double constructor.
        // new malloc + call construct
        
        size_t R = _rows < new_rows? _rows: new_rows;
        size_t C = _columns < new_columns? _columns: new_columns;

        for (size_t r = 0; r < R; r++) {
            const double* src = &_data[r * _columns]; //<<
            const double* end = src + C;
            double* dst = &new_data[r * new_columns]; //<< 
            for (; src < end; dst++, src++) { *dst = *src; }
        }
        delete[] _data;
        _data = new_data;
        _rows = new_rows;
        _columns = new_columns;
    }

    double& e(size_t r, size_t c) //<< 
    {
        if (r >= _rows || c >= _columns)
        {
            throw std::runtime_error("out of range.");
        }

        return _data[_columns * r + c];
    }

    double& operator()(size_t r, size_t c){
        return e(r, c);
    }

    // Matrix operator*(const Matrix& a) const {
    //     // 
    // }

    void print()
    {
        for (size_t r = 0; r < _rows; r++)
        {
            for (size_t c = 0; c < _columns; c++)
            {
                std::cout << e(r, c) << ", ";
            }
            std::cout << "\n";
        }
    }
};

int main()
{
    Matrix m(2, 2);
    m(0, 1) = 1;
    Matrix a;
    a = m;
    a(1, 1) = 1;
    // m.e(0, 0) = 1; // <<[][]
    // m(0, 1) = 2;
    // m.resize(5, 5); // 1, 2
    a.print();
    m.print();
}

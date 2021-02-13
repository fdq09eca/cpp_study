#include <iostream>

class Vector
{
public:
    double x, y, z;
    Vector() {}
    Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_){};  
    Vector(double s) : x(s), y(s), z(s){};

    Vector &mul(const Vector &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    

    double dot(const Vector &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
};

class Matrix
{
public:
    Vector cx;
    Vector cy;
    Vector cz;
    Matrix(){};
    Matrix(const Vector &cx_, const Vector &cy_, const Vector &cz_)
        : cx(cx_), cy(cy_), cz(cz_){};
    Matrix(double xx, double xy, double xz, // cx
           double yx, double yy, double yz, // cy
           double zx, double zy, double zz) // cz
        : cx(xx, xy, xz), cy(yx, yy, yz), cz(zx, zy, zz){};
    Matrix(double s) : cx(s), cy(s), cz(s) {}

    static Matrix identity()
    {
        return Matrix(1, 0, 0,
                      0, 1, 0,
                      0, 0, 1);
    }

    Vector row_x() const { return Vector(cx.x, cy.x, cz.x); }

    Vector row_y() const { return Vector(cx.y, cy.y, cz.y); }

    Vector row_z() const { return Vector(cx.z, cy.z, cz.z); }

    Matrix operator*(const Matrix &a) const
    {
        Matrix tmp;
        tmp.cx = Vector(cx.dot(a.row_x()), cx.dot(row_y()), cx.dot(row_z()));
        tmp.cy = Vector(cy.dot(a.row_x()), cy.dot(row_y()), cy.dot(row_z()));
        tmp.cz = Vector(cz.dot(a.row_x()), cz.dot(row_y()), cz.dot(row_z()));
        return tmp;
    }

    Matrix transpose()
    {
        return Matrix(row_x(), row_y(), row_z());
    }

    void self_transpose(int) {
        *this = transpose();
    }

    double det() const
    {
        
    }

    Matrix inverse() const {
        return *this;}

    Matrix &
    operator*=(const Matrix &a)
    {
        *this = *this * a;
    }
};

std::ostream &operator<<(std::ostream &s, const Vector &v)
{
    s << v.x << "," << v.y << "," << v.z << "\n";
    return s;
}

std::ostream &operator<<(std::ostream &s, const Matrix &m)
{
    s << m.cx;
    s << m.cy;
    s << m.cz;
    return s;
}

int main()
{
    Matrix m(2);
    Matrix n(4);
    Matrix s(1, 2, 3, 4, 5, 6, 7, 8, 9);
    s.transpose();
    std::cout << s;
    // m.mul(n);
    //numpy check!!

    // Matrix I = Matrix::identity();
    // std::cout << I;
    // std::cout << m;
    // m.mul(I);
    // std::cout << m;
    return 0;
}
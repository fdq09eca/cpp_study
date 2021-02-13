#include <iostream>
#define dump_var(X)                \
    do                             \
    {                              \
        std::cout << #X ": " << X; \
    } while (false)
//====

class Vector
{
public:
    double x;
    double y;
    double z;
    friend std::ostream &operator<<(std::ostream &os, const Vector &v); // <<
    Vector(const Vector &v) : x(v.x), y(v.y), z(v.z){};                 //
    Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_){};
    Vector(){};

    Vector &add(const Vector &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    void operator+=(const Vector &v)
    {
        add(v);
    }

    Vector operator++(int) // post
    {
        Vector tmp = *this;
        ++(*this);
        return tmp;
    }

    const Vector &operator++() // pre
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    Vector operator-() const //unary
    {
        return Vector(-x, -y, -z);
    }

    Vector operator+(const Vector &v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    double dot(const Vector &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector cross(const Vector &v) const
    {
        return Vector(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }
};

std::ostream &operator<<(std::ostream &s, const Vector &v)
{
    s << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")\n";
    return s;
};

int main()
{

    Vector a(1, 2, 3);
    Vector b(4, 5, 6);
    // a.add(b).add(b)
    // a+=b;
    b = a++;
    dump_var(b);
    dump_var(a);
    b = ++a;
    dump_var(b);
    dump_var(a);
    // Vector c = a += b;
    // Vector d(7, 8, 9);
    // d = b; // <<
    // dump_var(c);
    // dump_var(a + c);
    // dump_var(d);
}
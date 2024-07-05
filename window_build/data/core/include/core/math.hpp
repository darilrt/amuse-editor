//
// This file is part of the "clay" project, and is released under the "MIT License".
// See the LICENSE file for more information.
// Created by Daril Rodriguez on 2024-03-01.
//
// clay_math.hpp - A simple math library for 2D, 3D, and 4D vectors, 4x4 matrices, and quaternions.
//
// Usage:
// #define CLAY_MATH_IMPLEMENTATION
// #include "clay_math.hpp"
// #undef CLAY_MATH_IMPLEMENTATION
//
// #include "clay_math.hpp"
//
// Vec2 a = Vec2(1.0f, 2.0f);
// Vec2 b = Vec2(3.0f, 4.0f);
// Vec2 c = a + b;
//
#pragma once

#include <cmath>
#include <string>

#include "dll.hpp"

class AMUSE_API Vec2
{
public:
    float x, y;

    Vec2(float value)
    {
        x = value;
        y = value;
    }

    Vec2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    Vec2(const Vec2 &other)
    {
        x = other.x;
        y = other.y;
    }

    Vec2()
    {
        x = 0;
        y = 0;
    }

    float dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    float length() const
    {
        return sqrt(dot(*this));
    }

    float length_squared() const
    {
        return dot(*this);
    }

    Vec2 normalize() const
    {
        return *this / length();
    }

    std::string to_string() const
    {
        return "Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    Vec2 operator+(const Vec2 &other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator+=(const Vec2 &other)
    {
        *this = *this + other;
        return *this;
    }

    Vec2 operator-(const Vec2 &other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator-=(const Vec2 &other)
    {
        *this = *this - other;
        return *this;
    }

    Vec2 operator*(const Vec2 &other) const
    {
        return Vec2(x * other.x, y * other.y);
    }

    Vec2 operator*=(const Vec2 &other)
    {
        *this = *this * other;
        return *this;
    }

    Vec2 operator/(const Vec2 &other) const
    {
        return Vec2(x / other.x, y / other.y);
    }

    Vec2 operator/=(const Vec2 &other)
    {
        *this = *this / other;
        return *this;
    }

    Vec2 operator+(float value) const
    {
        return Vec2(x + value, y + value);
    }

    Vec2 operator+=(float value)
    {
        *this = *this + value;
        return *this;
    }

    Vec2 operator-(float value) const
    {
        return Vec2(x - value, y - value);
    }

    Vec2 operator-=(float value)
    {
        *this = *this - value;
        return *this;
    }

    Vec2 operator*(float value) const
    {
        return Vec2(x * value, y * value);
    }

    Vec2 operator*=(float value)
    {
        *this = *this * value;
        return *this;
    }

    Vec2 operator/(float value) const
    {
        return Vec2(x / value, y / value);
    }

    Vec2 operator/=(float value)
    {
        *this = *this / value;
        return *this;
    }

    Vec2 operator-() const
    {
        return Vec2(-x, -y);
    }

    bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2 &other) const
    {
        return x != other.x || y != other.y;
    }
};

class AMUSE_API Vec2i
{
public:
    int x, y;

    Vec2i(int value)
    {
        x = value;
        y = value;
    }

    Vec2i(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    Vec2i(const Vec2i &other)
    {
        x = other.x;
        y = other.y;
    }

    Vec2i()
    {
        x = 0;
        y = 0;
    }

    std::string to_string() const
    {
        return "IVec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    Vec2i operator+(const Vec2i &other) const
    {
        return Vec2i(x + other.x, y + other.y);
    }

    Vec2i operator+=(const Vec2i &other)
    {
        *this = *this + other;
        return *this;
    }

    Vec2i operator-(const Vec2i &other) const
    {
        return Vec2i(x - other.x, y - other.y);
    }

    Vec2i operator-=(const Vec2i &other)
    {
        *this = *this - other;
        return *this;
    }

    Vec2i operator*(const Vec2i &other) const
    {
        return Vec2i(x * other.x, y * other.y);
    }

    Vec2i operator*=(const Vec2i &other)
    {
        *this = *this * other;
        return *this;
    }

    Vec2i operator/(const Vec2i &other) const
    {
        return Vec2i(x / other.x, y / other.y);
    }

    Vec2i operator/=(const Vec2i &other)
    {
        *this = *this / other;
        return *this;
    }

    Vec2i operator+(int value) const
    {
        return Vec2i(x + value, y + value);
    }

    Vec2i operator+=(int value)
    {
        *this = *this + value;
        return *this;
    }

    Vec2i operator-(int value) const
    {
        return Vec2i(x - value, y - value);
    }

    Vec2i operator-=(int value)
    {
        *this = *this - value;
        return *this;
    }

    Vec2i operator*(int value) const
    {
        return Vec2i(x * value, y * value);
    }

    Vec2i operator*=(int value)
    {
        *this = *this * value;
        return *this;
    }

    Vec2i operator/(int value) const
    {
        return Vec2i(x / value, y / value);
    }

    Vec2i operator/=(int value)
    {
        *this = *this / value;
        return *this;
    }

    Vec2i operator-() const
    {
        return Vec2i(-x, -y);
    }

    bool operator==(const Vec2i &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2i &other) const
    {
        return x != other.x || y != other.y;
    }

    bool operator<(const Vec2i &other) const
    {
        return x < other.x && y < other.y;
    }

    bool operator>(const Vec2i &other) const
    {
        return x > other.x && y > other.y;
    }

    bool operator<=(const Vec2i &other) const
    {
        return x <= other.x && y <= other.y;
    }

    bool operator>=(const Vec2i &other) const
    {
        return x >= other.x && y >= other.y;
    }
};

class AMUSE_API Vec3
{
public:
    float x = 0;
    float y = 0;
    float z = 0;

    Vec3() = default;

    Vec3(float value)
    {
        x = value;
        y = value;
        z = value;
    }

    Vec3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3(const Vec3 &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    float dot(const Vec3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    float length() const
    {
        return sqrt(dot(*this));
    }

    float length_squared() const
    {
        return dot(*this);
    }

    Vec3 normalize() const
    {
        return *this / length();
    }

    Vec3 cross(const Vec3 &other) const
    {
        return Vec3(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
    }

    Vec3 operator+(const Vec3 &other) const
    {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3 operator-(const Vec3 &other) const
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator-=(const Vec3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 operator*(const Vec3 &other) const
    {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }

    Vec3 operator*=(const Vec3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vec3 operator/(const Vec3 &other) const
    {
        return Vec3(x / other.x, y / other.y, z / other.z);
    }

    Vec3 operator/=(const Vec3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vec3 operator+(float value) const
    {
        return Vec3(x + value, y + value, z + value);
    }

    Vec3 operator+=(float value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    Vec3 operator-(float value) const
    {
        return Vec3(x - value, y - value, z - value);
    }

    Vec3 operator-=(float value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }

    Vec3 operator*(float value) const
    {
        return Vec3(x * value, y * value, z * value);
    }

    Vec3 operator*=(float value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vec3 operator/(float value) const
    {
        return Vec3(x / value, y / value, z / value);
    }

    Vec3 operator/=(float value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    bool operator==(const Vec3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3 &other) const
    {
        return !(*this == other);
    }
};

class AMUSE_API Vec3i
{
public:
    int x, y, z;

    Vec3i(int value)
    {
        x = value;
        y = value;
        z = value;
    }

    Vec3i(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3i(const Vec3i &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    Vec3i()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    std::string to_string() const
    {
        return "IVec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    Vec3i operator+(const Vec3i &other) const
    {
        return Vec3i(x + other.x, y + other.y, z + other.z);
    }

    Vec3i operator+=(const Vec3i &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3i operator-(const Vec3i &other) const
    {
        return Vec3i(x - other.x, y - other.y, z - other.z);
    }

    Vec3i operator-=(const Vec3i &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3i operator*(const Vec3i &other) const
    {
        return Vec3i(x * other.x, y * other.y, z * other.z);
    }

    Vec3i operator*=(const Vec3i &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vec3i operator/(const Vec3i &other) const
    {
        return Vec3i(x / other.x, y / other.y, z / other.z);
    }

    Vec3i operator/=(const Vec3i &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vec3i operator+(int value) const
    {
        return Vec3i(x + value, y + value, z + value);
    }

    Vec3i operator+=(int value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    Vec3i operator-(int value) const
    {
        return Vec3i(x - value, y - value, z - value);
    }

    Vec3i operator-=(int value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }

    Vec3i operator*(int value) const
    {
        return Vec3i(x * value, y * value, z * value);
    }

    Vec3i operator*=(int value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vec3i operator/(int value) const
    {
        return Vec3i(x / value, y / value, z / value);
    }

    Vec3i operator/=(int value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    Vec3i operator-() const
    {
        return Vec3i(-x, -y, -z);
    }

    bool operator==(const Vec3i &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3i &other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    bool operator<(const Vec3i &other) const
    {
        return x < other.x && y < other.y && z < other.z;
    }

    bool operator>(const Vec3i &other) const
    {
        return x > other.x && y > other.y && z > other.z;
    }

    bool operator<=(const Vec3i &other) const
    {
        return x <= other.x && y <= other.y && z <= other.z;
    }

    bool operator>=(const Vec3i &other) const
    {
        return x >= other.x && y >= other.y && z >= other.z;
    }

    Vec3i operator%(const Vec3i &other) const
    {
        return Vec3i(x % other.x, y % other.y, z % other.z);
    }

    Vec3i operator%=(const Vec3i &other)
    {
        x %= other.x;
        y %= other.y;
        z %= other.z;
        return *this;
    }
};

class AMUSE_API Vec4
{
public:
    float x, y, z, w;

    Vec4(float value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
    }

    Vec4(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    Vec4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    Vec4(const Vec3 &v, float w)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = w;
    }

    Vec4(const Vec4 &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }

    float dot(const Vec4 &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float length() const
    {
        return sqrt(dot(*this));
    }

    float length_squared() const
    {
        return dot(*this);
    }

    Vec4 normalize() const
    {
        return *this / length();
    }

    Vec4 operator+(const Vec4 &other) const
    {
        return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vec4 operator+=(const Vec4 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Vec4 operator-() const
    {
        return Vec4(-x, -y, -z, -w);
    }

    Vec4 operator-(const Vec4 &other) const
    {
        return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vec4 operator-=(const Vec4 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Vec4 operator*(const Vec4 &other) const
    {
        return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vec4 operator*=(const Vec4 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    Vec4 operator/(const Vec4 &other) const
    {
        return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    Vec4 operator/=(const Vec4 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    Vec4 operator+(float value) const
    {
        return Vec4(x + value, y + value, z + value, w + value);
    }

    Vec4 operator+=(float value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }

    Vec4 operator-(float value) const
    {
        return Vec4(x - value, y - value, z - value, w - value);
    }

    Vec4 operator-=(float value)
    {
        x -= value;
        y -= value;
        z -= value;
        w -= value;
        return *this;
    }

    Vec4 operator*(float value) const
    {
        return Vec4(x * value, y * value, z * value, w * value);
    }

    Vec4 operator*=(float value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    Vec4 operator/(float value) const
    {
        return Vec4(x / value, y / value, z / value, w / value);
    }

    Vec4 operator/=(float value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    bool operator==(const Vec4 &other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool operator!=(const Vec4 &other) const
    {
        return !(*this == other);
    }
};

class AMUSE_API Quat;

class AMUSE_API Mat4
{
public:
    float data[16];

    Mat4();

    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33);

    Mat4 inverse();

    Mat4 transpose();

    Mat4 cofactor();

    float determinant();

    void translate(Vec3 translation);

    void rotate(Quat rotation);

    void scale(Vec3 scale);

    void print();

    inline float *ptr() { return &data[0]; }

    static Mat4 identity();

    static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);

    static Mat4 perspective(float fov, float aspect, float near, float far);

    Mat4 operator+(const Mat4 &other);

    Mat4 operator*(const Mat4 &other);

    Vec4 operator*(const Vec4 &other);
};

class AMUSE_API Quat
{
public:
    float i, j, k, r;

    Quat(float value)
    {
        i = value;
        j = value;
        k = value;
        r = value;
    }

    Quat(float i, float j, float k, float r)
    {
        this->i = i;
        this->j = j;
        this->k = k;
        this->r = r;
    }

    Quat()
    {
        i = 0.0f;
        j = 0.0f;
        k = 0.0f;
        r = 1.0f;
    }

    Quat normalize() const
    {
        float length = sqrt(i * i + j * j + k * k + r * r);
        return Quat(i / length, j / length, k / length, r / length);
    }

    Quat conjugate() const
    {
        return Quat(-i, -j, -k, r);
    }

    Quat inverse() const
    {
        return conjugate() / (i * i + j * j + k * k + r * r);
    }

    float dot(const Quat &b)
    {
        return i * b.i + j * b.j + k * b.k + r * b.r;
    }

    Vec3 to_euler() const
    {
        float sqw = r * r;
        float sqx = i * i;
        float sqy = j * j;
        float sqz = k * k;
        float unit = sqx + sqy + sqz + sqw;
        float test = i * j + k * r;

        if (test > 0.499f * unit)
        {
            return Vec3(
                0.0f,
                2.0f * atan2(i, r),
                3.14159265358979323846f / 2.0f);
        }

        if (test < -0.499f * unit)
        {
            return Vec3(
                0.0f,
                -2.0f * atan2(i, r),
                -3.14159265358979323846f / 2.0f);
        }

        return Vec3(
            atan2(2.0f * j * r - 2.0f * i * k, sqx - sqy - sqz + sqw),
            atan2(2.0f * i * r - 2.0f * j * k, -sqx + sqy - sqz + sqw),
            asin(2.0f * test / unit));
    }

    static Quat lerp(Quat &a, Quat &b, float t)
    {
        return (a * (1.0f - t) + b * t).normalize();
    }

    static Quat identity()
    {
        return Quat();
    }

    static Quat from_axis_angle(const Vec3 &axis, float angle);

    static Quat from_euler(const Vec3 &euler);

    static Quat look_at(const Vec3 &from, const Vec3 &to, const Vec3 &up);

    Mat4 to_mat4();

    static Quat slerp(Quat &a, const Quat &b, float t)
    {
        float cos_half_theta = a.dot(b);

        if (abs(cos_half_theta) >= 1.0f)
        {
            return a;
        }

        float half_theta = acos(cos_half_theta);
        float sin_half_theta = sqrt(1.0f - cos_half_theta * cos_half_theta);

        if (abs(sin_half_theta) < 0.001f)
        {
            return Quat(
                (a.i * 0.5f + b.i * 0.5f),
                (a.j * 0.5f + b.j * 0.5f),
                (a.k * 0.5f + b.k * 0.5f),
                (a.r * 0.5f + b.r * 0.5f));
        }

        float ratio_a = sin((1.0f - t) * half_theta) / sin_half_theta;
        float ratio_b = sin(t * half_theta) / sin_half_theta;

        return Quat(
            (a.i * ratio_a + b.i * ratio_b),
            (a.j * ratio_a + b.j * ratio_b),
            (a.k * ratio_a + b.k * ratio_b),
            (a.r * ratio_a + b.r * ratio_b));
    }

    Quat operator+(const Quat &b)
    {
        return Quat(i + b.i, j + b.j, k + b.k, r + b.r);
    }

    Quat operator-(const Quat &b)
    {
        return Quat(i - b.i, j - b.j, k - b.k, r - b.r);
    }

    Quat operator*(const Quat &b)
    {
        return Quat(
            i * b.r + j * b.k - k * b.j + r * b.i,
            -i * b.k + j * b.r + k * b.i + r * b.j,
            i * b.j - j * b.i + k * b.r + r * b.k,
            -i * b.i - j * b.j - k * b.k + r * b.r);
    }

    Quat operator*(float s)
    {
        return Quat(i * s, j * s, k * s, r * s);
    }

    Quat operator/(float s)
    {
        return Quat(i / s, j / s, k / s, r / s);
    }

    Vec4 operator*(const Vec4 &v)
    {
        Quat q = Quat(v.x, v.y, v.z, 0.0f);
        Quat result = q * conjugate();
        result = *this * result;
        return Vec4(result.i, result.j, result.k, 1.0f);
    }

    Vec3 operator*(const Vec3 &v)
    {
        Vec4 result = *this * Vec4(v.x, v.y, v.z, 1.0f);
        return Vec3(result.x, result.y, result.z);
    }

    Quat &operator+=(const Quat &other)
    {
        *this = *this + other;
        return *this;
    }

    Quat &operator-=(const Quat &other)
    {
        *this = *this - other;
        return *this;
    }

    Quat &operator*=(const Quat &other)
    {
        *this = *this * other;
        return *this;
    }

    Quat &operator*=(float s)
    {
        *this = *this * s;
        return *this;
    }

    Quat &operator/=(float s)
    {
        *this = *this / s;
        return *this;
    }

    bool operator==(const Quat &other) const
    {
        return i == other.i && j == other.j && k == other.k && r == other.r;
    }

    bool operator!=(const Quat &other) const
    {
        return !(*this == other);
    }
};

namespace math
{
    constexpr float pi = 3.14159265358979323846f;
    constexpr float half_pi = 1.57079632679489661923f;

    // Returns the linear interpolation between a and b at time t
    // example:
    // ```c++
    // float lerped = math::lerp(0.0f, 1.0f, 0.5f);
    // lerped == 0.5f // true
    // ```
    template <typename T>
    T lerp(T a, T b, float t)
    {
        return a + (b - a) * t;
    }

    // Returns the value clamped between min and max
    // example:
    // ```c++
    // float clamped = math::clamp(5.0f, 0.0f, 1.0f);
    // clamped == 1.0f // true
    // ```
    template <typename T>
    T clamp(T value, T min, T max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    template <typename T>
    T min(T a, T b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    T max(T a, T b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    T abs(T value)
    {
        return value < 0 ? -value : value;
    }

    template <typename T>
    T sign(T value)
    {
        return value < 0 ? -1 : 1;
    }

    template <typename T>
    T sqrt(T value)
    {
        return std::sqrt(value);
    }

    template <typename T>
    T pow(T value, T exponent)
    {
        return std::pow(value, exponent);
    }

    template <typename T>
    T sin(T value)
    {
        return std::sin(value);
    }

    template <typename T>
    T cos(T value)
    {
        return std::cos(value);
    }

    template <typename T>
    T tan(T value)
    {
        return std::tan(value);
    }

    template <typename T>
    T asin(T value)
    {
        return std::asin(value);
    }

    template <typename T>
    T acos(T value)
    {
        return std::acos(value);
    }

    // Returns the angle in radians between the positive x-axis and the ray from (0, 0) to (x, y)
    // example:
    // ```c++
    // float angle = math::atan(1.0f);
    // angle == 0.78539816339f // true
    // ```
    template <typename T>
    T atan(T value)
    {
        return std::atan(value);
    }

    // Returns the angle in radians between the positive x-axis and the ray from (0, 0) to (x, y)
    // example:
    // ```c++
    // float angle = math::atan2(1.0f, 1.0f);
    // angle == 0.78539816339f // true
    // ```
    template <typename T>
    T atan2(T y, T x)
    {
        return std::atan2(y, x);
    }

    // Returns the lowest integer less than or equal to a number
    // example:
    // ```c++
    // int floor = math::floor(1.5f);
    // floor == 1 // true
    template <typename T>
    T floor(T value)
    {
        return std::floor(value);
    }

    // Returns the smallest integer greater than or equal to a number
    // example:
    // ```c++
    // int ceiling = math::ceil(1.5f);
    // ceiling == 2 // true
    // ```
    template <typename T>
    T ceil(T value)
    {
        return std::ceil(value);
    }

    // Rounds a number to the nearest integer
    // example:
    // ```c++
    // int rounded = math::round(1.5f);
    // rounded == 2 // true
    // ```
    template <typename T>
    T round(T value)
    {
        return std::round(value);
    }

    // Returns the fractional part of a number
    // example:
    // ```c++
    // float fraction = math::frac(1.5f);
    // fraction == 0.5f // true
    // ```
    template <typename T>
    T frac(T value)
    {
        return value - floor(value);
    }

    // Returns the modulus of the value and the divisor
    // example:
    // ```c++
    // float remainder = math::mod(5.0f, 2.0f);
    // remainder == 1.0f // true
    // ```
    template <typename T>
    T mod(T value, T divisor)
    {
        return value - floor(value / divisor) * divisor;
    }

    // Takes a value in radians and returns a value in degrees
    // example:
    // ```c++
    // float radians = math::rad(90.0f);
    // radians == 1.57079632679f // true
    // ```
    template <typename T>
    inline T rad(T value)
    {
        return (value * pi) / 180.0f;
    }

    // Takes a value in degrees and returns a value in radians
    // example:
    // ```c++
    // float degrees = math::deg(1.57079632679f);
    // degrees == 90.0f // true
    // ```
    template <typename T>
    T deg(T value)
    {
        return value * (T)57.2957795131;
    }

    template <typename T>
    T lerp_angle(T a, T b, float t)
    {
        T delta = mod(b - a, (T)360);
        if (delta > (T)180)
            delta -= (T)360;
        return a + delta * t;
    }

    template <typename T>
    T inverse_lerp(T a, T b, T value)
    {
        return (value - a) / (b - a);
    }

    template <typename T>
    T smoothstep(T a, T b, T value)
    {
        T t = clamp(inverse_lerp(a, b, value), (T)0, (T)1);
        return t * t * (3 - 2 * t);
    }
} // namespace math

#ifdef CLAY_MATH_IMPLEMENTATION

Mat4 Quat::to_mat4()
{
    return Mat4(
        1.0f - 2.0f * j * j - 2.0f * k * k,
        2.0f * i * j - 2.0f * k * r,
        2.0f * i * k + 2.0f * j * r,
        0.0f,
        2.0f * i * j + 2.0f * k * r,
        1.0f - 2.0f * i * i - 2.0f * k * k,
        2.0f * j * k - 2.0f * i * r,
        0.0f,
        2.0f * i * k - 2.0f * j * r,
        2.0f * j * k + 2.0f * i * r,
        1.0f - 2.0f * i * i - 2.0f * j * j,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f);
}

Quat Quat::from_euler(const Vec3 &euler)
{
    double c1 = cos(euler.x / 2.0);
    double c2 = cos(euler.y / 2.0);
    double c3 = cos(euler.z / 2.0);
    double s1 = sin(euler.x / 2.0);
    double s2 = sin(euler.y / 2.0);
    double s3 = sin(euler.z / 2.0);

    return Quat(
        s1 * c2 * c3 + c1 * s2 * s3,
        c1 * s2 * c3 - s1 * c2 * s3,
        c1 * c2 * s3 + s1 * s2 * c3,
        c1 * c2 * c3 - s1 * s2 * s3);
}

Quat Quat::from_axis_angle(const Vec3 &axis, float angle)
{
    float half_angle = angle / 2.0f;
    float s = sin(half_angle);
    return Quat(axis.x * s, axis.y * s, axis.z * s, cos(half_angle));
}

Quat Quat::look_at(const Vec3 &from, const Vec3 &to, const Vec3 &up)
{
    Vec3 forward = (to - from).normalize();
    Vec3 right = forward.cross(up).normalize();
    Vec3 new_up = right.cross(forward).normalize();

    float w = sqrt(1.0f + right.x + new_up.y + forward.z) / 2.0f;
    float w4_recip = 1.0f / (4.0f * w);
    return Quat(
        (new_up.z - forward.y) * w4_recip,
        (forward.x - right.z) * w4_recip,
        (right.y - new_up.x) * w4_recip,
        w);
}

Mat4::Mat4()
{
    data[0] = 0.0f;
    data[1] = 0.0f;
    data[2] = 0.0f;
    data[3] = 0.0f;
    data[4] = 0.0f;
    data[5] = 0.0f;
    data[6] = 0.0f;
    data[7] = 0.0f;
    data[8] = 0.0f;
    data[9] = 0.0f;
    data[10] = 0.0f;
    data[11] = 0.0f;
    data[12] = 0.0f;
    data[13] = 0.0f;
    data[14] = 0.0f;
    data[15] = 0.0f;
}

Mat4::Mat4(float m00, float m01, float m02, float m03,
           float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23,
           float m30, float m31, float m32, float m33)
{
    data[0] = m00;
    data[1] = m01;
    data[2] = m02;
    data[3] = m03;
    data[4] = m10;
    data[5] = m11;
    data[6] = m12;
    data[7] = m13;
    data[8] = m20;
    data[9] = m21;
    data[10] = m22;
    data[11] = m23;
    data[12] = m30;
    data[13] = m31;
    data[14] = m32;
    data[15] = m33;
}

Mat4 Mat4::inverse()
{
    Mat4 result = *this;

    float det = determinant();

    if (det == 0.0f)
        return result;

    Mat4 transpose_matrix = cofactor().transpose();

    for (int i = 0; i < 16; i++)
        result.data[i] = transpose_matrix.data[i] / det;

    return result;
}

Mat4 Mat4::transpose()
{
    return Mat4(data[0], data[4], data[8], data[12],
                data[1], data[5], data[9], data[13],
                data[2], data[6], data[10], data[14],
                data[3], data[7], data[11], data[15]);
}

Mat4 Mat4::cofactor()
{
    Mat4 result{};

    result.data[0] = data[5] * (data[10] * data[15] - data[11] * data[14]) - data[6] * (data[9] * data[15] - data[11] * data[13]) + data[7] * (data[9] * data[14] - data[10] * data[13]);
    result.data[1] = -(data[4] * (data[10] * data[15] - data[11] * data[14]) - data[6] * (data[8] * data[15] - data[11] * data[12]) + data[7] * (data[8] * data[14] - data[10] * data[12]));

    result.data[2] = data[4] * (data[9] * data[15] - data[11] * data[13]) - data[5] * (data[8] * data[15] - data[11] * data[12]) + data[7] * (data[8] * data[13] - data[9] * data[12]);
    result.data[3] = -(data[4] * (data[9] * data[14] - data[10] * data[13]) - data[5] * (data[8] * data[14] - data[10] * data[12]) + data[6] * (data[8] * data[13] - data[9] * data[12]));

    result.data[4] = -(data[1] * (data[10] * data[15] - data[11] * data[14]) - data[2] * (data[9] * data[15] - data[11] * data[13]) + data[3] * (data[9] * data[14] - data[10] * data[13]));
    result.data[5] = data[0] * (data[10] * data[15] - data[11] * data[14]) - data[2] * (data[8] * data[15] - data[11] * data[12]) + data[3] * (data[8] * data[14] - data[10] * data[12]);

    result.data[6] = -(data[0] * (data[9] * data[15] - data[11] * data[13]) - data[1] * (data[8] * data[15] - data[11] * data[12]) + data[3] * (data[8] * data[13] - data[9] * data[12]));
    result.data[7] = data[0] * (data[9] * data[14] - data[10] * data[13]) - data[1] * (data[8] * data[14] - data[10] * data[12]) + data[2] * (data[8] * data[13] - data[9] * data[12]);

    result.data[8] = data[1] * (data[6] * data[15] - data[7] * data[14]) - data[2] * (data[5] * data[15] - data[7] * data[13]) + data[3] * (data[5] * data[14] - data[6] * data[13]);
    result.data[9] = -(data[0] * (data[6] * data[15] - data[7] * data[14]) - data[2] * (data[4] * data[15] - data[7] * data[12]) + data[3] * (data[4] * data[14] - data[6] * data[12]));

    result.data[10] = data[0] * (data[5] * data[15] - data[7] * data[13]) - data[1] * (data[4] * data[15] - data[7] * data[12]) + data[3] * (data[4] * data[13] - data[5] * data[12]);
    result.data[11] = -(data[0] * (data[5] * data[14] - data[6] * data[13]) - data[1] * (data[4] * data[14] - data[6] * data[12]) + data[2] * (data[4] * data[13] - data[5] * data[12]));

    result.data[12] = -(data[1] * (data[6] * data[11] - data[7] * data[10]) - data[2] * (data[5] * data[11] - data[7] * data[9]) + data[3] * (data[5] * data[10] - data[6] * data[9]));
    result.data[13] = data[0] * (data[6] * data[11] - data[7] * data[10]) - data[2] * (data[4] * data[11] - data[7] * data[8]) + data[3] * (data[4] * data[10] - data[6] * data[8]);

    result.data[14] = -(data[0] * (data[5] * data[11] - data[7] * data[9]) - data[1] * (data[4] * data[11] - data[7] * data[8]) + data[3] * (data[4] * data[9] - data[5] * data[8]));
    result.data[15] = data[0] * (data[5] * data[10] - data[6] * data[9]) - data[1] * (data[4] * data[10] - data[6] * data[8]) + data[2] * (data[4] * data[9] - data[5] * data[8]);

    return result;
}

float Mat4::determinant()
{
    float det = 0.0f;

    det += data[0] * (data[5] * (data[10] * data[15] - data[11] * data[14]) - data[6] * (data[9] * data[15] - data[11] * data[13]) + data[7] * (data[9] * data[14] - data[10] * data[13]));
    det -= data[1] * (data[4] * (data[10] * data[15] - data[11] * data[14]) - data[6] * (data[8] * data[15] - data[11] * data[12]) + data[7] * (data[8] * data[14] - data[10] * data[12]));
    det += data[2] * (data[4] * (data[9] * data[15] - data[11] * data[13]) - data[5] * (data[8] * data[15] - data[11] * data[12]) + data[7] * (data[8] * data[13] - data[9] * data[12]));
    det -= data[3] * (data[4] * (data[9] * data[14] - data[10] * data[13]) - data[5] * (data[8] * data[14] - data[10] * data[12]) + data[6] * (data[8] * data[13] - data[9] * data[12]));

    return det;
}

void Mat4::translate(Vec3 translation)
{
    data[12] += translation.x;
    data[13] += translation.y;
    data[14] += translation.z;
}

Mat4 Mat4::identity()
{
    return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.f);
}

void Mat4::rotate(Quat rotation)
{
    Mat4 rotation_matrix = rotation.to_mat4();
    *this = rotation_matrix * *this;
}

void Mat4::scale(Vec3 scale)
{
    data[0] *= scale.x;
    data[5] *= scale.y;
    data[10] *= scale.z;
}

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
{
    Mat4 result = Mat4::identity();

    result.data[0] = 2.0f / (right - left);
    result.data[5] = 2.0f / (top - bottom);
    result.data[10] = -2.0f / (far - near);
    result.data[12] = -(right + left) / (right - left);
    result.data[13] = -(top + bottom) / (top - bottom);
    result.data[14] = -(far + near) / (far - near);

    return result;
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far)
{
    float s = 1.0f / tan(fov / 2.0f);

    Mat4 result = Mat4::identity();

    result.data[0] = s / aspect;
    result.data[5] = s;
    result.data[10] = -far / (far - near);
    result.data[14] = -(far * near) / (far - near);

    result.data[11] = -1.0f;
    result.data[15] = 0.0f;

    return result;
}

Mat4 Mat4::operator+(const Mat4 &other)
{
    Mat4 result{};

    for (int i = 0; i < 16; i++)
    {
        result.data[i] = data[i] + other.data[i];
    }

    return result;
}

Mat4 Mat4::operator*(const Mat4 &other)
{
    Mat4 result{};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.data[i * 4 + j] = data[i * 4 + 0] * other.data[j + 0] +
                                     data[i * 4 + 1] * other.data[j + 4] +
                                     data[i * 4 + 2] * other.data[j + 8] +
                                     data[i * 4 + 3] * other.data[j + 12];
        }
    }

    return result;
}

Vec4 Mat4::operator*(const Vec4 &other)
{
    Vec4 result{};

    result.x = data[0] * other.x + data[4] * other.y + data[8] * other.z + data[12] * other.w;
    result.y = data[1] * other.x + data[5] * other.y + data[9] * other.z + data[13] * other.w;
    result.z = data[2] * other.x + data[6] * other.y + data[10] * other.z + data[14] * other.w;
    result.w = data[3] * other.x + data[7] * other.y + data[11] * other.z + data[15] * other.w;

    return result;
}

#endif
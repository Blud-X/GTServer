#pragma once
#include <string>
#include <vector>

namespace GrowtopiaServer {
    typedef struct _CL_Vec2f {
        float m_x;
        float m_y;

        _CL_Vec2f() {
            m_x = 0.0f;
            m_y = 0.0f;
        }
        _CL_Vec2f(float f) {
            m_x = f;
            m_y = f;
        }
        _CL_Vec2f(float x, float y) {
            this->m_x = x;
            this->m_y = y;
        }

        bool operator==(const _CL_Vec2f& other) const { return m_x == other.m_x && m_y == other.m_y; }
        bool operator!=(const _CL_Vec2f& other) const { return m_x != other.m_x || m_y != other.m_y; }
        _CL_Vec2f operator+(const _CL_Vec2f& other) const { return _CL_Vec2f(m_x + other.m_x, m_y + other.m_y); }
        _CL_Vec2f operator-(const _CL_Vec2f& other) const { return _CL_Vec2f(m_x - other.m_x, m_y - other.m_y); }
        _CL_Vec2f operator*(const float& other) const { return _CL_Vec2f(m_x * other, m_y * other); }
    } CL_Vec2f;

    typedef struct _CL_Vec2i {
        int m_x;
        int m_y;

        _CL_Vec2i() {
            m_x = 0;
            m_y = 0;
        }
        _CL_Vec2i(int f) {
            m_x = f;
            m_y = f;
        }
        _CL_Vec2i(int x, int y) {
            this->m_x = x;
            this->m_y = y;
        }
        _CL_Vec2i(uint32_t x, uint32_t y) {
            this->m_x = x;
            this->m_y = y;
        }

        bool operator==(const _CL_Vec2i& other) const { return m_x == other.m_x && m_y == other.m_y; }
        bool operator!=(const _CL_Vec2i& other) const { return m_x != other.m_x || m_y != other.m_y; }
        _CL_Vec2i operator+(const _CL_Vec2i& other) const { return _CL_Vec2i(m_x + other.m_x, m_y + other.m_y); }
        _CL_Vec2i operator-(const _CL_Vec2i& other) const { return _CL_Vec2i(m_x - other.m_x, m_y - other.m_y); }
        _CL_Vec2i operator*(const int& other) const { return _CL_Vec2i(m_x * other, m_y * other); }
    } CL_Vec2i;

    typedef struct _CL_Vec3f {
        float m_x;
        float m_y;
        float m_z;

        _CL_Vec3f() {
            m_x = 0.0f;
            m_y = 0.0f;
            m_z = 0.0f;
        }

        _CL_Vec3f(float f) {
            m_x = f;
            m_y = f;
            m_z = f;
        }

        _CL_Vec3f(float x, float y, float z) {
            this->m_x = x;
            this->m_y = y;
            this->m_z = z;
        }
        _CL_Vec3f(uint16_t x, uint16_t y, uint16_t z) {
            this->m_x = static_cast<float>(x);
            this->m_y = static_cast<float>(y);
            this->m_z = static_cast<float>(z);
        }

        bool operator==(const _CL_Vec3f& other) const {
            return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
        }

        bool operator!=(const _CL_Vec3f& other) const {
            return m_x != other.m_x || m_y != other.m_y || m_z != other.m_z;
        }

        _CL_Vec3f operator+(const _CL_Vec3f& other) const {
            return _CL_Vec3f(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
        }

        _CL_Vec3f operator-(const _CL_Vec3f& other) const {
            return _CL_Vec3f(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
        }

        _CL_Vec3f operator*(const float& other) const {
            return _CL_Vec3f(m_x * other, m_y * other, m_z * other);
        }
    } CL_Vec3f;

    typedef struct _CL_Vec3i {
        int x;
        int y;
        int z;

        _CL_Vec3i() {
            x = 0;
            y = 0;
            z = 0;
        }

        _CL_Vec3i(int f) {
            x = f;
            y = f;
            z = f;
        }

        _CL_Vec3i(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        bool operator==(const _CL_Vec3i& other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const _CL_Vec3i& other) const {
            return x != other.x || y != other.y || z != other.z;
        }

        _CL_Vec3i operator+(const _CL_Vec3i& other) const {
            return _CL_Vec3i(x + other.x, y + other.y, z + other.z);
        }

        _CL_Vec3i operator-(const _CL_Vec3i& other) const {
            return _CL_Vec3i(x - other.x, y - other.y, z - other.z);
        }

        _CL_Vec3i operator*(const int& other) const {
            return _CL_Vec3i(x * other, y * other, z * other);
        }
    } CL_Vec3i;

    typedef struct _CL_Rectf {
        float x;
        float y;
        float width;
        float height;

        _CL_Rectf() {
            x = 0.0f;
            y = 0.0f;
            width = 0.0f;
            height = 0.0f;
        }

        _CL_Rectf(float f) {
            x = f;
            y = f;
            width = f;
            height = f;
        }

        _CL_Rectf(float x, float y, float width, float height) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }

        bool operator==(const _CL_Rectf& other) const {
            return x == other.x && y == other.y && width == other.width && height == other.height;
        }

        bool operator!=(const _CL_Rectf& other) const {
            return x != other.x || y != other.y || width != other.width || height != other.height;
        }

        _CL_Rectf operator+(const _CL_Rectf& other) const {
            return _CL_Rectf(x + other.x, y + other.y, width + other.width, height + other.height);
        }

        _CL_Rectf operator-(const _CL_Rectf& other) const {
            return _CL_Rectf(x - other.x, y - other.y, width - other.width, height - other.height);
        }

        _CL_Rectf operator*(const float& other) const {
            return _CL_Rectf(x * other, y * other, width * other, height * other);
        }
    } CL_Rectf;

    typedef struct _CL_Recti {
        int x;
        int y;
        int width;
        int height;

        _CL_Recti() {
            x = 0;
            y = 0;
            width = 0;
            height = 0;
        }

        _CL_Recti(int f) {
            x = f;
            y = f;
            width = f;
            height = f;
        }

        _CL_Recti(int x, int y, int width, int height) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }

        bool operator==(const _CL_Recti& other) const {
            return x == other.x && y == other.y && width == other.width && height == other.height;
        }

        bool operator!=(const _CL_Recti& other) const {
            return x != other.x || y != other.y || width != other.width || height != other.height;
        }

        _CL_Recti operator+(const _CL_Recti& other) const {
            return _CL_Recti(x + other.x, y + other.y, width + other.width, height + other.height);
        }

        _CL_Recti operator-(const _CL_Recti& other) const {
            return _CL_Recti(x - other.x, y - other.y, width - other.width, height - other.height);
        }

        _CL_Recti operator*(const int& other) const {
            return _CL_Recti(x * other, y * other, width * other, height * other);
        }
    } CL_Recti;
}
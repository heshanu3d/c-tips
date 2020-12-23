#pragma once
#include <memory>

class four;

class three {
public:
    // ~three();
    ~three() {}
    void func();
    std::unique_ptr<four> fouru;
};
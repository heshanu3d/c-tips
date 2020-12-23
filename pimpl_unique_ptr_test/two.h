#pragma once
#include <memory>
class three;

class two {
public:
    // ~two();
    ~two() {}
    void func();
    std::unique_ptr<three> threeu;
    // std::shared_ptr<three> threeu;
};
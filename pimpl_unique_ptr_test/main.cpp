#include <iostream>
int main()
{
    std::cout << "在使用pimpl时候，当类很多，并且类中用到的指针是unique_ptr，切析构函数为默认时， 会发生invalid application of 'sizeof' to incomplete type 'xxx'的错误" << std::endl;
    std::cout << "主要原因在于当一个类Y拥有pimpl定义的class x，并且类中的定义了std::unique_ptr<x>时，默认的析构函数~Y会计算sizeof(x)，如果此时未在Y.cpp include x，如#include 'x.h',就会编译错误：" << std::endl;
    std::cout << "这里总结一下编译出现错误的前提条件" << std::endl;
    std::cout << "      1.未在Y.cpp include x，如#include 'x.h'" << std::endl;
    std::cout << "      2.使用的析构函数为默认，如~Y(){}或者~Y=default;" << std::endl;
    std::cout << "      3.对x的引用方式为unique_ptr" << std::endl;
    std::cout << "这有在这三种条件均满足的时候才会出现这种错误" << std::endl;
    std::cout << "乍一看以为三种条件要同时满足会很难，其实不然……" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "几个要注意的点:" << std::endl;
    std::cout << "      1.A 引入了unique_ptr<B>" << std::endl;
    std::cout << "        B 引入了unique_ptr<C>" << std::endl;
    std::cout << "        C 引入了unique_ptr<D>" << std::endl;
    std::cout << "      这种情况容易引起一个错误的地方就是，在A.cpp里 include B，在B.cpp里include C，在C.cpp里include D，但是编译却不过" << std::endl;
    std::cout << "      原因是这里C的析构函数销毁D，B的析构函数销毁C，A的析构函数销毁B" << std::endl;
    std::cout << "      所以在A中的析构函数，还会像递归一样去销毁C和D，有销毁unique_ptr的动作，那么就会计算sizeof(x)，A.cpp里并没有include C和D，那就会出现编译错误" << std::endl;
    std::cout << "      所以这种场景下，想要编译通过，就需要在A.cpp include BCD，在B.cpp include CD，在C.cpp include D " << std::endl;
    std::cout << "" << std::endl;
    std::cout << "总结一下，想要编译不出错，必须做到" << std::endl;
    std::cout << "      默认销毁的unique_ptr类，必须在cpp中include进来" << std::endl;
    std::cout << "对应的解决方案" << std::endl;
    std::cout << "      1.不用默认析构函数，使用自定义的析构函数" << std::endl;
    std::cout << "      2.不使用unique_ptr，改为原生指针或者其他的智能指针" << std::endl;
    std::cout << "      3.cpp中include所有会销毁的被pimpl以unique_ptr方式调用的类" << std::endl;
    std::cout << "      这里强烈建议还是使用方案3来更改~原因嘛，你懂的" << std::endl;

    return 0;
}
/*
 * main.cpp
 *
 *  Created on: 2015/06/22
 *      Author: Keisuke
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <slz/data_iarchive.h>

#include "slz/helper_macro.h"

class Component {
public:
    Component(double v) : _v(v) {}
private:
    double _v;

    SLZ_DEFAULT_CONSTRUCTOR(Component);
    SLZ_FRIEND_DECLARATION;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & SLZ_NVP(_v);
    }
};

class data_istream {
public:
    typedef data_istream this_type;
    typedef this_type istream_type;
    data_istream() {}

    istream_type& operator>>(bool& t)
    {
        t = true;
        return *this;
    }
    istream_type& operator>>(short& t)
    {
        t = 1;
        return *this;
    }
    istream_type& operator>>(unsigned short& t)
    {
        t = 1;
        return *this;
    }
    istream_type& operator>>(int& t)
    {
        t = 1;
        return *this;
    }
    istream_type& operator>>(unsigned int& t)
    {
        t = 1;
        return *this;
    }
    istream_type& operator>>(float& t)
    {
        t = 1.0;
        return *this;
    }
    istream_type& operator>>(double& t)
    {
        t = 1.0;
        return *this;
    }
};
class SerializeTest {
public:
    void test()
    {
    }
};

int main() {
    data_istream di;

    return 0;
}


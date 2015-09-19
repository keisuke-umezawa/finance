#ifndef BASIC_DATA_IARCHIVE_H
#define BASIC_DATA_IARCHIVE_H


#include <boost/config.hpp>
#include <boost/serialization/pfto.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/archive/detail/common_iarchive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

template<class Archive>
class basic_data_iarchive :
    public detail::common_iarchive<Archive>
{
protected:
    friend class detail::interface_iarchive<Archive>;
    typedef detail::common_iarchive<Archive> detail_common_iarchive;
    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        this->detail_common_iarchive::load_override(t, 0);
    }
    // text file don't include the optional information
    void load_override(class_id_optional_type & /*t*/, int) {}

    void load_override(version_type & /*t*/, int) {}

    ~basic_data_iarchive(){}
};

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BASIC_DATA_IARCHIVE_H

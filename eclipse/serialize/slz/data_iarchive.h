#ifndef DATA_IARCHIVE_H
#define DATA_IARCHIVE_H


#include <boost/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <slz/basic_data_iarchive.h>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

template<class Archive>
class data_iarchive_impl :
    public basic_data_iarchive<Archive>
{
    friend class detail::interface_iarchive<Archive>;
    friend class basic_data_iarchive<Archive>;
    friend class load_access;
protected:
    template<class T>
    void load(T & t){
        basic_data_iarchive<Archive>::load(t);
    }
    data_iarchive_impl(std::istream & is, unsigned int flags);
    ~data_iarchive_impl(){}
};


} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

// note special treatment of shared_ptr. This type needs a special
// structure associated with every archive.  We created a "mix-in"
// class to provide this functionality.  Since shared_ptr holds a
// special esteem in the boost library - we included it here by default.
#include <boost/archive/shared_ptr_helper.hpp>

namespace boost {
namespace archive {

class data_iarchive :
    public data_iarchive_impl<data_iarchive>,
    public detail::shared_ptr_helper
{
public:
    data_iarchive(std::istream & is_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        data_iarchive_impl<data_iarchive>(is_, flags)
    {}
    ~data_iarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::data_iarchive)

#endif // DATA_IARCHIVE_H

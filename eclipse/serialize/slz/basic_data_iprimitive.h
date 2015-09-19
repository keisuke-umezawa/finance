#ifndef BASIC_DATA_IPRIMITIVE.H
#define BASIC_DATA_IPRIMITIVE.H

#include <boost/assert.hpp>
#include <locale>
#include <cstddef> // size_t

#include <boost/config.hpp>

#include <boost/limits.hpp>
#include <boost/io/ios_state.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/static_assert.hpp>

#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

template<class IStream>
class basic_text_iprimitive
{
protected:
    IStream &is;
    io::ios_flags_saver flags_saver;
    io::ios_precision_saver precision_saver;

    template<class T>
    void load(T & t)
    {
        is >> t;
        return;
    }

    basic_text_iprimitive(IStream  &is, bool no_codecvt);
    ~basic_text_iprimitive();
public:
};

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BASIC_DATA_IPRIMITIVE.H

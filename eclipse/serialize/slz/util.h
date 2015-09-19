/*
 * util.h
 *
 *  Created on: 2015/06/22
 *      Author: Keisuke
 */

#ifndef SLZ_UTIL_H_INCLUDED
#define SLZ_UTIL_H_INCLUDED

#include <fstream>
#include <boost/utility/enable_if.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace slz {
    template <typename T> inline
    void save_text_archive(const T& t, const std::string& filename)
    {
        std::ofstream ofst(filename.c_str());
        save_text_archive_impl(t, ofst).close();
    }
    template <typename T, typename OStream> inline
    void save_text_archive_impl(const T& t, OStream& ostream)
    {
        boost::archive::text_oarchive oa(ostream);
        oa << t;
        return ostream;
    }
    template <typename T> inline
    void load_text_archive(const std::string& filename)
    {
        T t;
        std::ifstream ifst(filename.c_str());
        boost::archive::text_iarchive ia(ifst);
        ia >> t;
        ifst.close();
        return t;
    }
} // namespace slz {

namespace slz { namespace detail {
    template <typename T>
    struct reference_traits {
        typedef T& result_type;
        static result_type apply(const T& t)
        {
            return const_cast<T&>(t);
        }
    };

    template <typename T>
    struct reference_traits<boost::shared_ptr<const T> > {
        typedef boost::shared_ptr<T> result_type;
        static result_type apply(const boost::shared_ptr<const T>& t)
        {
            return boost::const_pointer_cast<T>(t);
        }
    };

}} // namespace slz { namespace detail {

namespace slz {
    template <typename T>
    typename detail::reference_traits<T>::result_type
    ref(const T& t)
    {
        return detail::reference_traits<T>::apply(t);
    }
} // namespace slz {

#endif // SLZ_UTIL_H_INCLUDED

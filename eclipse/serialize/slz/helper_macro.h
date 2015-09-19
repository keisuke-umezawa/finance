/*
 * helper_macro.h
 *
 *  Created on: 2015/06/22
 *      Author: Keisuke
 */

#ifndef SLZ_HELPER_MACRO_H_INCLUDED
#define SLZ_HELPER_MACRO_H_INCLUDED

#include <boost/preprocessor/stringize.hpp>
#include <boost/serialization/serialization.hpp>
#include "util.h"

namespace slz {
#define SLZ_AND ,
#define SLZ_DEFAULT_CONSTRUCTOR(name) \
    name() {}
#define SLZ_DEFAULT_CONSTRUCTOR_WITH_LIST(name, list) \
    name() : list {}
#define SLZ_FRIEND_DECLARATION \
    friend boost::serialization::access; \
    friend class SerializeTest; \
    template <typename SLZ_T> \
    friend SLZ_T slz::load_text_archive(const std::string& filename);
#define SLZ_NVP(name) \
    boost::serialization::make_nvp(BOOST_PP_STRINGIZE(name), slz::ref(name));
#define SLZ_BASE_NVP(name) \
    boost:serialization::make_nvp( \
        boost::serialization::base_object<name>(*this));
} // namespace slz {

#endif // SLZ_HELPER_MACRO_H_INCLUDED

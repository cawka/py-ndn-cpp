/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2014 Regents of the University of California.
 * @author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 * See BSD license, see COPYING for copyright and distribution information.
 */

#include <boost/python/operators.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/operators.hpp>

#include <ndn-cpp-dev/name.hpp>
#include <ndn-cpp-dev/interest.hpp>
#include <ndn-cpp-dev/data.hpp>
#include <ndn-cpp-dev/face.hpp>

#include "helpers.hpp"

namespace ndn {

using namespace boost::python;

BOOST_PYTHON_MODULE(ndn)
{
  class_<Block>("Block")
    .def("__str__", &BufferToString, args("self"))
    .def("__repr__", &BufferToString, args("self"))
    ;

  scope outer
    = class_<Name>("Name")
    .def(init<const Name&>())
    .def(init<const std::string&>())
    .def(str(self))
    .def(repr(self))
    .def(self < self)
    .def(self < other<const char*>())
    .def(self < other<std::string>())
    .def(self > self)
    .def(self > other<const char*>())
    .def(self > other<std::string>())
    .def(self <= self)
    .def(self <= other<const char*>())
    .def(self <= other<std::string>())
    .def(self >= self)
    .def(self >= other<const char*>())
    .def(self >= other<std::string>())
    .def(self == self)
    .def(self == other<const char*>())
    .def(self == other<std::string>())
    .def(self != self)
    .def(self != other<const char*>())
    .def(self != other<std::string>())

    .def("append", &appendNameCompoinent, (args("self"), args("component")),
         return_value_policy<reference_existing_object>())
    .def("append", (Name& (Name::*)(const name::Component&))&Name::append,
         return_value_policy<reference_existing_object>())
    .def("append", (Name& (Name::*)(const Name&))&Name::append,
         return_value_policy<reference_existing_object>())
    .def("appendVersion", (Name& (Name::*)(uint64_t))&Name::appendVersion,
         return_value_policy<reference_existing_object>())
    .def("appendVersion", (Name& (Name::*)())&Name::appendVersion,
         return_value_policy<reference_existing_object>())

    .def("clear", &Name::clear)

    .def("__iter__", iterator< const Name >())
    .def("__len__", &Name::size)
    .def("__getitem__", &Name::get,
         return_value_policy<reference_existing_object>())
    // .def(vector_indexing_suite< Name >())

    .def("getSubName", (Name (Name::*)(size_t, size_t) const)&Name::getSubName)
    .def("getSubName", (Name (Name::*)(size_t) const)&Name::getSubName)
    .def("getPrefix", &Name::getPrefix)
    .def("toUri", &Name::toUri)

    .def("isPrefixOf", &Name::isPrefixOf)

    .def("wireEncode", &wireEncode<Name>, (args("self")))
    .def("wireDecode", &wireDecode<Name>, (args("self"), args("wire")))
    ;

    class_<name::Component>("Component")
      .def(init<const std::string&>())
      .def(str(self))
      .def("__repr__", NameComponentToBufferString, (args("self")))
      .def("toNumber", &Name::Component::toNumber)
      .def("toSegment", &Name::Component::toSegment)
      .def("toVersion", &Name::Component::toVersion)
      .def(self == self)
      .def(self != self)
      .def(self <= self)
      .def(self < self)
      .def(self > self)
      .def(self >= self)
      ;
}

} // namespace ndn

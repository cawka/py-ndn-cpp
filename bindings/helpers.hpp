/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2014 Regents of the University of California.
 * @author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 * See BSD license, see COPYING for copyright and distribution information.
 */

#ifndef BINDINGS_HELPERS_HPP
#define BINDINGS_HELPERS_HPP

namespace ndn {

inline std::string
BufferToString(const Block& buf)
{
  return std::string(buf.begin(), buf.end());
}

std::string
NameComponentToBufferString(const name::Component& comp)
{
  if (comp.empty())
    return std::string();
  else
    return std::string(comp.value_begin(), comp.value_end());
}

Name&
appendNameCompoinent(Name& name, const std::string& component)
{
  name.append(name::Component(component));
  return name;
}

template<class T>
inline void
wireDecode(T& self, const std::string& data)
{
  try {
    self.wireDecode(Block(data.c_str(), data.size()));
  }
  catch(...) {
    // If an exception was thrown, translate it to Python
    boost::python::handle_exception();
  }
}

template<class T>
inline std::string
wireEncode(T& self)
{
  try {
    Block data = self.wireEncode();
    return std::string(data.begin(), data.end());
  }
  catch(...) {
    // If an exception was thrown, translate it to Python
    boost::python::handle_exception();
    return std::string();
  }
}

} // namespace ndn

#endif // BINDINGS_HELPERS_HPP

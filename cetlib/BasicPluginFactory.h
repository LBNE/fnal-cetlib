#ifndef cetlib_BasicPluginFactory_h
#define cetlib_BasicPluginFactory_h
////////////////////////////////////////////////////////////////////////
// BasicPluginFactory
//
// Refinement of PluginFactory for a common class of plugins featuring a
// "pluginType" function and a "makePlugin" function. The pluginType
// function must be compatible with the following signature:
//
//   std::string ()
//
// For a useful class template / macro combination to formalize the
// pluginType, see cetlib/PluginTypeDeducer.h
//
// The make function is arbitrary in signature: the result type must be
// specified but the arguments (if any) may be deduced.
//
////////////////////////////////////////////////////////////////////////

#include "cetlib/PluginFactory.h"

namespace cet {
  class BasicPluginFactory;
}

class cet::BasicPluginFactory : public PluginFactory {
public:
  BasicPluginFactory(std::string const & suffix = "plugin",
                     std::string const & makerName = "makePlugin",
                     std::string const & pluginTypeFuncName = "pluginType");

  // Find and call the makePlugin() function in the plugin library.
  template <typename RESULT_TYPE,
            typename... ARGS>
  RESULT_TYPE makePlugin(std::string const & libspec,
                         ARGS... args);

  // Find and call the pluginType() function in the plugin library.
  std::string pluginType(std::string const & libspec);

private:
  std::string const makerName_;
  std::string const pluginTypeFuncName_;

};

inline
std::string
cet::BasicPluginFactory::
pluginType(std::string const & libspec)
{
  return call<std::string>(libspec, pluginTypeFuncName_);
}

template <typename RESULT_TYPE, typename... ARGS>
inline
RESULT_TYPE
cet::BasicPluginFactory::
makePlugin(std::string const & libspec,
           ARGS... args)
{
  return call<RESULT_TYPE>(libspec, makerName_, args...);
}
#endif

// Local Variables:
// mode: c++
// End:

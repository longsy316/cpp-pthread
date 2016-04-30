//
//  cpp_pthread.hpp
//  cpp_pthread
//
//  Created by herbert koelman on 18/03/2016.
//
//

#ifndef pthread_pthread_hpp
#define pthread_pthread_hpp

#include "pthread/pthread.hpp"
#include "pthread/config.h"

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT
/* Define to the full name of this package. */
#undef PACKAGE_NAME
/* Define to the full name and version of this package. */
#undef PACKAGE_STRING
/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME
/* Define to the version of this package. */
#undef PACKAGE_VERSION

namespace pthread {

extern "C" const char *cpp_pthread_version(){
#ifndef CPP_PTHREAD_VERSION
  return "missing CPP_PTHREAD_VERSION define. Re-run configure" ;
#else
  return CPP_PTHREAD_VERSION ;
#endif
}

}
#endif /* pthread_pthread_hpp */

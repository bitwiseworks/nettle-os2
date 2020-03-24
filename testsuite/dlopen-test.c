#include "testutils.h"
#include "version.h"

#if HAVE_DLFCN_H
#include <dlfcn.h>
#endif

int
main (int argc UNUSED, char **argv UNUSED)
{
#if HAVE_LIBDL
#ifdef __OS2__
  void *handle = dlopen ("../nettle70.dll", RTLD_NOW);
#else
  void *handle = dlopen ("../libnettle.so", RTLD_NOW);
#endif
  int (*get_version)(void);
  if (!handle)
    {
      fprintf (stderr, "dlopen failed: %s\n", dlerror());
      FAIL ();
    }

#ifdef __OS2__
  get_version = (int(*)(void)) dlsym (handle, "_nettle_version_minor");
#else
  get_version = (int(*)(void)) dlsym (handle, "nettle_version_minor");
#endif
  if (!get_version)
    {
      fprintf (stderr, "dlsym failed: %s\n", dlerror());
      FAIL ();
    }
  if (get_version() != NETTLE_VERSION_MINOR)
    {
      fprintf (stderr, "unexpected nettle version\n");
      FAIL ();
    }
  dlclose (handle);
  return EXIT_SUCCESS;
#else
  SKIP();
#endif
}

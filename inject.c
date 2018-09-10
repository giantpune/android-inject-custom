#include <frida-core.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char * argv[])
{
  int result = 0;
  FridaInjector * injector;
  int pid;
  GError * error;
  guint id;

  if (argc != 2)
    goto bad_usage;
  printf( "injector line %d\n", __LINE__ );

  pid = atoi (argv[1]);
  if (pid <= 0)
    goto bad_usage;
  printf( "injector line %d\n", __LINE__ );

  frida_init ();
  
  printf( "injector line %d\n", __LINE__ );

  injector = frida_injector_new ();
  printf( "injector line %d\n", __LINE__ );

  error = NULL;
  
  const char *lib = "./agent.so";
  if( access( lib, R_OK ) )
  {
    printf("cant access %s\n", lib );
    return 1;
  }
  if( access( lib, X_OK ) )
  {
    printf("cant execute %s\n", lib );
    return 1;
  }
  id = frida_injector_inject_library_file_sync (injector, pid, lib, "example_agent_main", "example data", &error);
  
  
  printf( "injector line %d\n", __LINE__ );
  
  if (error != NULL)
  {
  printf( "injector line %d\n", __LINE__ );
    fprintf (stderr, "%s\n", error->message);
    g_error_free (error);

    result = 1;
  }
  printf( "injector line %d\n", __LINE__ );

  frida_injector_close_sync (injector);
  printf( "injector line %d\n", __LINE__ );
  g_object_unref (injector);
  printf( "injector line %d\n", __LINE__ );

  frida_deinit ();
  printf( "injector line %d\n", __LINE__ );

  return result;

bad_usage:
  {
    fprintf (stderr, "Usage: %s <pid>\n", argv[0]);
    return 1;
  }
}

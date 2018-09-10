#include <fcntl.h>
#include <frida-gum.h>

#include <android/log.h>

static int replacement_open (const char * path, int oflag, ...);

void
example_agent_main (const gchar * data, gboolean * stay_resident)
{
  __android_log_print(ANDROID_LOG_INFO, "MyTag", "line %d", __LINE__ );
#if 0
  GumInterceptor * interceptor;

  
  __android_log_print(ANDROID_LOG_INFO, "MyTag", "line %d", __LINE__ );
  /* We don't want to our library to be unloaded after we return. */
  *stay_resident = TRUE;

  gum_init_embedded ();

  __android_log_print(ANDROID_LOG_INFO, "MyTag", "example_agent_main()");

  interceptor = gum_interceptor_obtain ();

  /* Transactions are optional but improve performance with multiple hooks. */
  gum_interceptor_begin_transaction (interceptor);
  
  __android_log_print(ANDROID_LOG_INFO, "MyTag", "line %d", __LINE__ );
  

  gum_interceptor_replace_function (interceptor,
      (gpointer) gum_module_find_export_by_name (NULL, "open"), replacement_open, NULL);
  __android_log_print(ANDROID_LOG_INFO, "MyTag", "line %d", __LINE__ );
  /*
   * ^
   * |
   * This is using replace_function(), but there's also attach_listener() which
   * can be used to hook functions without any knowledge of argument types,
   * calling convention, etc. It can even be used to put a probe in the middle
   * of a function.
   */
  __android_log_print(ANDROID_LOG_INFO, "MyTag", "line %d", __LINE__ );

  gum_interceptor_end_transaction (interceptor);
  __android_log_print(ANDROID_LOG_INFO, "MyTag", "line %d", __LINE__ );
#endif
}

static int
replacement_open (const char * path, int oflag, ...)
{
  __android_log_print(ANDROID_LOG_INFO, "MyTag", "open(\"%s\", 0x%x)", path, oflag);

  return open (path, oflag);
}

/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <glade/glade.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "support.h"

#ifdef G_OS_WIN32
char *package_prefix;
char *package_datadir;
#endif


/* globals for now */
GtkWidget* main_window;
GtkWidget* gsc_quit_dialog;


int
main(int argc, char *argv[] )
{

  GladeXML* xml;
  GdkGLConfig* glconfig;

  GtkWidget* drawing_area;

  gboolean dummy;

#ifdef G_OS_WIN32
  gchar *temp;

  package_prefix = g_win32_get_package_installation_directory (NULL, NULL);
  package_datadir = g_strdup_printf ("%s%s", package_prefix, "/share");
#endif

#ifdef ENABLE_NLS
#ifdef G_OS_WIN32
  temp = g_strdup_printf ("%s%s", package_prefix, "/lib/locale");
  bindtextdomain (GETTEXT_PACKAGE, temp);
  g_free (temp);
#else
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
#endif
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  //gtk_set_locale ();

  gtk_init(&argc, &argv );
  gtk_gl_init(&argc, &argv );

  /* Try double-buffered visual */
  glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH | GDK_GL_MODE_DOUBLE );
  if(glconfig == NULL) {
    g_print ("*** Cannot find the double-buffered visual.\n");
    g_print ("*** Trying single-buffered visual.\n");

    /* Try single-buffered visual */
    glconfig = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH );
    if(glconfig == NULL) {
      g_print ("*** No appropriate OpenGL-capable visual found.\n");
      exit (1);
    }
  }


#ifdef G_OS_WIN32
  temp = g_strdup_printf ("%s/%s%s", package_datadir, PACKAGE, "/pixmaps");
  add_pixmap_directory (temp);
  g_free (temp);
#else
  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
#endif


  xml =glade_xml_new ("gnu_shader_composer.glade", NULL, NULL );
  //xml =glade_xml_new ("simple_gl_test.glade", NULL, NULL );
  //xml =glade_xml_new ("simple_simple.glade", NULL, NULL );

  glade_xml_signal_autoconnect(xml );
 
  main_window = glade_xml_get_widget(xml, "main_window" );

  //pre-create the dialogs
  gsc_quit_dialog =glade_xml_get_widget(xml, "exit_confirmation_dialog" );
  //gtk_widget_set_parent(gsc_quit_dialog, main_window );
/*   gtk_widget_set_parent_window(gsc_quit_dialog, //widget  */
/* 			       main_window );   //parent */

  gtk_container_set_reallocate_redraws (GTK_CONTAINER (main_window), TRUE );

  printf("drawing_area: %u\n", drawing_area );
  drawing_area = glade_xml_get_widget (xml, "drawing_area" );
  printf("drawing_area: %u\n", drawing_area );

  /* Add OpenGL-capability to drawingarea1. */
  dummy =gtk_widget_set_gl_capability(drawing_area, 
				      glconfig, 
				      NULL, 
				      TRUE, 
				      GDK_GL_RGBA_TYPE );

  printf("dummy: %s\n", dummy?"TRUE":"FALSE" );


  gtk_widget_show(main_window);

/*   g_signal_connect ((gpointer) main_window, "destroy", G_CALLBACK(gtk_main_quit), */
/*                     NULL); */

  gtk_main ();

#ifdef G_OS_WIN32
  g_free (package_prefix);
  g_free (package_datadir);
#endif
  return 0;
}
#ifdef _MSC_VER
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	return main (__argc, __argv);
}
#endif


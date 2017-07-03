/*
 * =====================================================================================
 * 
 *        Filename:  simple.c
 * 
 *     Description:  i
 * 
 *         Version:  1.0
 *         Created:  07/03/2017 20:06:35 BRT
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  Ricardo Fabbri (rfabbri), rfabbri.github.io
 *         Company:  Brown University
 * 
 * =====================================================================================
 */


#include <gtk/gtk.h>

int main(int argc, char *argv[]) {

  GtkWidget *window;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);  

  gtk_main();

  return 0;
}

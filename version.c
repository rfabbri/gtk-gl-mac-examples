/*
 * =====================================================================================
 * 
 *        Filename:  version.c
 * 
 *     Description:  i
 * 
 *         Version:  1.0
 *         Created:  07/03/2017 20:04:26 BRT
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

    gtk_init(&argc, &argv);

    g_printf("GTK+ version: %d.%d.%d\n", gtk_major_version, 
        gtk_minor_version, gtk_micro_version);
    g_printf("Glib version: %d.%d.%d\n", glib_major_version,
        glib_minor_version, glib_micro_version);    
        
    return 0;
}

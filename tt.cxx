#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <gl.h>
#include <math.h>
#include <iostream>

int
main (int argc, char **argv)
{
  // vgui_gtk2::init()
  gtk_init(&argc, &argv);
	gtk_gl_init (&argc, &argv);
  //!

  std::cerr << "Initialized\n";
    

  std::cerr << "Right before vgui::run()\n";
  // vgui_gtk2::run()
  gtk_main();
  //!
  std::cerr << "Finished vgui::run()\n";
}

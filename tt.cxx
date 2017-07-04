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

  // -------------------------------------------------------
  // vgui_window* win = vgui::produce_window(w, h, title);
  // 
  // --------- vgui_gtk2_window::vgui_gtk2_window()
  //
  // use_menubar(false)
  // use_statusbar(true)
  // adaptor(new vgui_gtk2_adaptor(this))
  // statusbar(new vgui_gtk2_statusbar)
  // last_menubar(new vgui_menu)
  // 
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), title);
  gtk_window_set_default_size(GTK_WINDOW(window),w,h);

  // vgui::out.rdbuf(static_cast<vgui_gtk2_statusbar*>(statusbar)->statusbuf);

  gtk_signal_connect(GTK_OBJECT(window), "delete_event",
                     GTK_SIGNAL_FUNC(delete_event_callback),
                     static_cast<vgui_gtk2_adaptor*>(adaptor));
  //!---------
  // --- vgui_gtk2_window::init()  TODO: is this being called too early?

  box = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER (window), box);

  if (use_menubar) {
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, TRUE, 0);
    gtk_widget_show(menubar);
  }

  // place glarea inside a frame
  GtkWidget *frame = gtk_frame_new(0);
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);
  gtk_container_set_border_width(GTK_CONTAINER(frame), 2);

  gtk_box_pack_start(GTK_BOX(box), frame, TRUE, TRUE, 0);
  gtk_widget_show(frame);

  std::cout << "XXX: after place glarea\n";

  // This re-parents the glarea widget, so the adaptor should yield
  // ownership.
  GtkWidget *glarea = static_cast<vgui_gtk2_adaptor*>(adaptor)->get_glarea_widget();
  gtk_container_add(GTK_CONTAINER(frame), glarea);
  gtk_widget_show(glarea);

  if (use_statusbar) {
    vgui_gtk2_statusbar* s = static_cast<vgui_gtk2_statusbar*>(statusbar);
    s->widget = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(box), s->widget, FALSE, TRUE, 0);
    gtk_widget_show(s->widget);
  }

  std::cout << "XXX: end of window init\n";

  gtk_widget_show(box);
  
  //!---
  //!-------------------------------------------------------
    


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // win->show() in basic app
  gtk_widget_show(window);

  //!xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  std::cerr << "Right before vgui::run()\n";
  // vgui_gtk2::run()
  gtk_main();
  //!
  std::cerr << "Finished vgui::run()\n";
}

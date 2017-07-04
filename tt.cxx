#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <gl.h>
#include <math.h>
#include <iostream>
#include <assert.h>


void make_current(GtkWidget *widget)
{
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);
  if (!gldrawable || !glcontext)
    std::cerr << "NULL GLDRAWABLE\n";
  assert( gldrawable );
  gdk_gl_drawable_make_current(gldrawable, glcontext);
}


gint handle_draw(
                               GtkWidget *widget,
                               GdkEvent *gev,
                               gpointer context)
{
  std::cerr << "XXX: draw called\n";
  // vgui_gtk2_adaptor* adaptor = (vgui_gtk2_adaptor*) context;
  // adaptor->draw();
  //
  //    Leaving out ovl stuff (see original file)
  //
  std::cout << "handle_draw) glarea widget mapped: " << GTK_WIDGET_MAPPED(widget) << std::endl;
  make_current(widget);
  return TRUE;
}

gint handle_configure(
                               GtkWidget *widget,
                               GdkEvent *gev,
                               gpointer context)
{
  std::cerr << "XXX:Configure called\n";
  std::cout << "handle_configure) glarea widget mapped: " << GTK_WIDGET_MAPPED(widget) << std::endl;
  // XXX vgui_gtk2_adaptor* adaptor = (vgui_gtk2_adaptor*) context;

  if (!GTK_WIDGET_MAPPED(widget))
      return FALSE;
  // The following 5 lines are required to make GL context available
  // so that some GL functions (such as glGenLists()) can succeed.
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);
  if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext)) {
    std::cerr << "XXX: FALSE\n";
    return FALSE;
  }
  gdk_gl_drawable_gl_end (gldrawable);

  // XXX adaptor->reshape();
  make_current(widget);
  // stuff related to ovl_helper
  return TRUE;
}

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
  bool use_menubar(false), 
       use_statusbar(true);


  // adaptor(new vgui_gtk2_adaptor(this))

  // Try double-buffered visual
  GdkGLConfig* glconfig = gdk_gl_config_new_by_mode (GdkGLConfigMode(GDK_GL_MODE_RGB |
                                                                     GDK_GL_MODE_DEPTH |
                                                                     GDK_GL_MODE_DOUBLE));
  if (glconfig == 0)
  {
    g_print ("*** Cannot find the double-buffered visual.\n");
    g_print ("*** Trying single-buffered visual.\n");

    // Try single-buffered visual
    glconfig = gdk_gl_config_new_by_mode(GdkGLConfigMode(GDK_GL_MODE_RGB |
                                                         GDK_GL_MODE_DEPTH));
    if (glconfig == 0)
    {
      g_print ("*** No appropriate OpenGL-capable visual found.\n");
      std::abort();
    }
  }

  GtkWidget *widget = gtk_drawing_area_new ();
  //gtk_widget_set_size_request (drawing_area, 300, 300);

  if (!widget)
  {
    std::cerr << __FILE__ << " : Could not get a GL widget!\n";
    std::abort();
  }

  // Set OpenGL-capability to the widget.
  if ( !gtk_widget_set_gl_capability(widget,
                                     glconfig,
                                     0 /*NULL*/,
                                     TRUE,
                                     GDK_GL_RGBA_TYPE) )
  {
    std::cerr << __FILE__ << " : Could not set GL capability!\n";
    std::abort();
  }
  std::cerr << "XXX: capabily ok\n";

  gtk_widget_set_events(widget,
                        GDK_EXPOSURE_MASK
    |
                        GDK_POINTER_MOTION_MASK |
                        GDK_POINTER_MOTION_HINT_MASK |
                        GDK_BUTTON_PRESS_MASK |
                        GDK_BUTTON_RELEASE_MASK |
                        GDK_KEY_PRESS_MASK |
                        GDK_KEY_RELEASE_MASK |
                        GDK_ENTER_NOTIFY_MASK |
                        GDK_LEAVE_NOTIFY_MASK);

  // Since we need to access the widget from time to time (e.g. to
  // make this OpenGL context the current context), we need to keep a
  // reference to the widget.
  gtk_object_ref( GTK_OBJECT(widget) );
#if 0

  gtk_widget_set_events(widget,
                        GDK_EXPOSURE_MASK
    |
                        GDK_POINTER_MOTION_MASK |
                        GDK_POINTER_MOTION_HINT_MASK |
                        GDK_BUTTON_PRESS_MASK |
                        GDK_BUTTON_RELEASE_MASK |
                        GDK_KEY_PRESS_MASK |
                        GDK_KEY_RELEASE_MASK |
                        GDK_ENTER_NOTIFY_MASK |
                        GDK_LEAVE_NOTIFY_MASK);
  gtk_signal_connect(GTK_OBJECT(widget), "configure_event", GTK_SIGNAL_FUNC(handle_configure), NULL);
  gtk_signal_connect(GTK_OBJECT(widget), "expose_event", GTK_SIGNAL_FUNC(handle_draw), NULL);
//  gtk_signal_connect(GTK_OBJECT(widget), "map_event", GTK_SIGNAL_FUNC(handle_draw), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "motion_notify_event", GTK_SIGNAL_FUNC(handle_motion_notify), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "button_press_event", GTK_SIGNAL_FUNC(handle_button), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "button_release_event", GTK_SIGNAL_FUNC(handle_button), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "key_press_event", GTK_SIGNAL_FUNC(handle_key), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "key_release_event", GTK_SIGNAL_FUNC(handle_key), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "enter_notify_event", GTK_SIGNAL_FUNC(handle_enter_leave), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "leave_notify_event", GTK_SIGNAL_FUNC(handle_enter_leave), this);
  GTK_WIDGET_SET_FLAGS(widget, GTK_CAN_FOCUS);
#endif

  bool redraw_requested = false;
  bool destroy_requested = false;
  


  // statusbar(new vgui_gtk2_statusbar)
  // last_menubar(new vgui_menu)
  // 



  //
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "test win");
  gtk_window_set_default_size(GTK_WINDOW(window),800,600);

  // vgui::out.rdbuf(static_cast<vgui_gtk2_statusbar*>(statusbar)->statusbuf);

  /*
  gtk_signal_connect(GTK_OBJECT(window), "delete_event",
                     GTK_SIGNAL_FUNC(delete_event_callback),
                     static_cast<vgui_gtk2_adaptor*>(adaptor));
                     */
  //!---------
  // --- vgui_gtk2_window::init()  TODO: is this being called too early?

  GtkWidget *box = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER (window), box);
#if 0

  if (use_menubar) {
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, TRUE, 0);
    gtk_widget_show(menubar);
  }
#endif

  // place glarea inside a frame
  GtkWidget *frame = gtk_frame_new(0);
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);
  gtk_container_set_border_width(GTK_CONTAINER(frame), 2);

  gtk_box_pack_start(GTK_BOX(box), frame, TRUE, TRUE, 0);

  std::cout << "XXX: after place glarea\n";

#if 0
  // This re-parents the glarea widget, so the adaptor should yield
  // ownership.
  GtkWidget *glarea = static_cast<vgui_gtk2_adaptor*>(adaptor)->get_glarea_widget();
#endif



  std::cout << "1) glarea widget mapped: " << GTK_WIDGET_MAPPED(widget) << std::endl;
  

  GtkWidget *glarea = widget;
  gtk_container_add(GTK_CONTAINER(frame), glarea);
  gtk_widget_show(frame);
  gtk_widget_show(glarea);
  gtk_widget_show(window);

  std::cout << "2) glarea widget mapped: " << GTK_WIDGET_MAPPED(widget) << std::endl;

#if 0
  if (use_statusbar) {
    vgui_gtk2_statusbar* s = static_cast<vgui_gtk2_statusbar*>(statusbar);
    s->widget = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(box), s->widget, FALSE, TRUE, 0);
    gtk_widget_show(s->widget);
  }
#endif

  std::cout << "XXX: end of window init\n";

  gtk_widget_show(box);
  std::cout << "3) glarea widget mapped: " << GTK_WIDGET_MAPPED(widget) << std::endl;
  
  //!---
  //!-------------------------------------------------------
    


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  gtk_signal_connect(GTK_OBJECT(widget), "configure_event", GTK_SIGNAL_FUNC(handle_configure), NULL);
  gtk_signal_connect(GTK_OBJECT(widget), "expose_event", GTK_SIGNAL_FUNC(handle_draw), NULL);
//  gtk_signal_connect(GTK_OBJECT(widget), "map_event", GTK_SIGNAL_FUNC(handle_draw), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "motion_notify_event", GTK_SIGNAL_FUNC(handle_motion_notify), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "button_press_event", GTK_SIGNAL_FUNC(handle_button), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "button_release_event", GTK_SIGNAL_FUNC(handle_button), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "key_press_event", GTK_SIGNAL_FUNC(handle_key), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "key_release_event", GTK_SIGNAL_FUNC(handle_key), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "enter_notify_event", GTK_SIGNAL_FUNC(handle_enter_leave), this);
//  gtk_signal_connect(GTK_OBJECT(widget), "leave_notify_event", GTK_SIGNAL_FUNC(handle_enter_leave), this);
  GTK_WIDGET_SET_FLAGS(widget, GTK_CAN_FOCUS);

  // win->show() in basic app
  gtk_widget_show(window);
  gtk_widget_show_all(window);
  std::cout << "4) glarea widget mapped: " << GTK_WIDGET_MAPPED(widget) << std::endl;

  //!xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  std::cerr << "Right before vgui::run()\n";
  // vgui_gtk2::run()
  gtk_main();
  //!
  std::cerr << "Finished vgui::run()\n";
}

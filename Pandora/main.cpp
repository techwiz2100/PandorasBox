/*
*	PandorasBox GTK window w/ CEF
*/

#include <gtk/gtk.h>

#include "include/cef_app.h"

#include "PandoraHandler.h"

CefRefPtr<PandoraHandler> g_handler;

void destroy(void) {
	// Tells CEF to quit its message loop so the application can exit.
	CefQuitMessageLoop();
}

int main(int argc, char* argv[]) {
	CefMainArgs main_args(argc, argv);

	int exitCode = CefExecuteProcess(main_args, NULL);
	if (exitCode >= 0) {
		return exitCode;
	}

	CefSettings settings;
	CefInitialize(main_args, settings, NULL);

	GtkWidget* window;
	GtkWidget* document;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "PandorasBox");
	// Set the window to 400x400
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

	gtk_window_fullscreen((GtkWindow *)window);
	gtk_window_fullscreen(GTK_WINDOW(gtk_widget_get_toplevel(window)));

	document = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), document);

	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

	CefBrowserSettings browserSettings;
	CefWindowInfo info;

	g_handler = new PandoraHandler();

	info.SetAsChild(document);
	CefBrowserHost::CreateBrowserSync(info, g_handler.get(),
		"http://www.google.com", browserSettings, NULL);

	gtk_widget_show_all(window);

	CefRunMessageLoop();

	CefShutdown();

	return 0;
}
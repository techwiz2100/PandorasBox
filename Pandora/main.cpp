/*
*	PandorasBox GTK window w/ CEF
*/

#include <gtk/gtk.h>
#include <fstream>
#include <string>

#include "include/cef_app.h"

#include "PandoraHandler.h"

CefRefPtr<PandoraHandler> g_handler;

void destroy(void) {
	// Tells CEF to quit its message loop so the application can exit.
	CefQuitMessageLoop();
}

void PandoraHandler::OnContextCreated(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame,CefRefPtr<CefV8Context> context) {
	CefRefPtr<CefV8Value> object = context->GetGlobal();

	std::ifstream in("../config.json", std::ios::in | std::ios::binary);
	std::string contents;
	if (in)	{
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
	}

	CefRefPtr<CefV8Value> str = CefV8Value::CreateString(contents.c_str());
	object->SetValue("config", str, V8_PROPERTY_ATTRIBUTE_NONE);
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
	gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

	gtk_window_fullscreen(GTK_WINDOW(window));
	gtk_window_maximize(GTK_WINDOW(window));

	document = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), document);

	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

	CefBrowserSettings browserSettings;
	CefWindowInfo info;

	g_handler = new PandoraHandler();

	info.SetAsChild(document);
	
	std::ifstream in("../config.json", std::ios::in | std::ios::binary);
	std::string contents;
	if (in)	{
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
	}

	CefBrowserHost::CreateBrowserSync(info, g_handler.get(),
		"http://192.168.56.101/", browserSettings, NULL);

	gtk_widget_show_all(window);

	CefRunMessageLoop();

	CefShutdown();

	return 0;
}
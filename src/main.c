#include <stdio.h>
#include <gtk/gtk.h>
#include <Python.h>

static void on_button_click(GtkWidget *widget, GtkWidget *box)
{
    GtkWidget *spinner = gtk_spinner_new();
    gtk_box_pack_start(GTK_BOX(box), spinner, TRUE, TRUE, 20);
    gtk_spinner_start(GTK_SPINNER(spinner));
    gtk_widget_show_now(spinner);

    Py_Initialize();
    PyRun_SimpleString("import os, sys");
    PyRun_SimpleString("sys.path.append(os.getcwd())");

    PyObject *pModule, *pFunc, *pArgs, *pValue;

    pModule = PyImport_ImportModule("scripts.hello");
    if (!pModule)
        g_print("Error importing module\n");
    pFunc = PyObject_GetAttrString(pModule, "hello");
    pArgs = PyTuple_Pack(1, PyUnicode_FromString("Anthony"));

    if (pFunc && PyCallable_Check(pFunc))
    {
        pValue = PyObject_CallObject(pFunc, pArgs);
    }

    g_print("%s", PyUnicode_AsUTF8(pValue));
    Py_Finalize();

    gtk_widget_destroy(spinner);
    GtkWidget *label;

    if (pValue != NULL)
    {
        label = gtk_label_new(PyUnicode_AsUTF8(pValue));
    }
    else
    {
        label = gtk_label_new("Error running Python script :c");
    }

    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 20);
    gtk_widget_show(label);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "My window");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 350);

    // Add box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, (gint)10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Add button
    GtkWidget *button_box;
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(box), button_box, TRUE, TRUE, 10);

    GtkWidget *button;
    button = gtk_button_new_with_label("Python time!");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_click), box);
    gtk_container_add(GTK_CONTAINER(button_box), button);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.neolight.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

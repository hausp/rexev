/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Interface.hpp"
#include "signals.hpp"
#include "DeSimoneTree.hpp"

Interface::Interface() {
    init();
}

void Interface::init() {
    builder = gtk_builder_new_from_file("view_simpl.ui");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    auto add_button = gtk_builder_get_object(builder, "add_button");
    g_signal_connect(window, "delete-event", G_CALLBACK(signals::close), nullptr);
    g_signal_connect(add_button, "clicked", G_CALLBACK(signals::add_regex), nullptr);
}

void Interface::show() {
    gtk_widget_show_all(window);
}

std::pair<std::string,std::string> Interface::show_add_dialog() {
    ECHO(1);
    dialog = GTK_WIDGET(gtk_builder_get_object(builder, "add_regex"));
    ECHO(2);
    std::pair<std::string,std::string> result = std::make_pair("","");
    ECHO(3);
    gtk_widget_show_all(dialog);
    ECHO(4);
    while (result.second.size() == 0) {
        ECHO(5);
        auto response = gtk_dialog_run(GTK_DIALOG(dialog));
        ECHO(6);
        if (response == GTK_RESPONSE_OK) {
            ECHO("ok");
            result = extract_add_dialog_entries();
        } else {
            ECHO("cancel");
            clean_add_dialog();
            break;
        }
    }
    ECHO(7);
    gtk_widget_hide(dialog);
    ECHO(8);
    return result;
}

void Interface::hide_add_dialog() {
    clean_add_dialog();
    gtk_widget_hide(dialog);
}

std::pair<std::string,std::string> Interface::extract_add_dialog_entries() {
    auto name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "regex_name_entry"));
    auto regex_entry = GTK_WIDGET(gtk_builder_get_object(builder, "regex_text"));
    auto regex_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(regex_entry));
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(regex_buffer, &start);
    gtk_text_buffer_get_end_iter(regex_buffer, &end);
    std::string name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    std::string regex = gtk_text_buffer_get_text(regex_buffer, &start, &end, false);
    // gtk_entry_set_text(GTK_ENTRY(name_entry), "");
    // gtk_text_buffer_set_text(regex_buffer, "\0", -1);
    return std::make_pair(name, regex);
}

void Interface::clean_add_dialog() {
    auto name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "regex_name_entry"));
    auto regex_text = GTK_WIDGET(gtk_builder_get_object(builder, "regex_text"));
    auto text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(regex_text));
    gtk_entry_set_text(GTK_ENTRY(name_entry), "");
    gtk_text_buffer_set_text(text_buffer, "\0", -1);
}

void Interface::destroy() {
    gtk_widget_destroy(window);

}

void Interface::show_error_message(const char* primary, const char* secondary) {
    auto message = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_CLOSE,
                                          primary,
                                          NULL);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(message), secondary);
    gtk_window_set_transient_for(GTK_WINDOW(message), GTK_WINDOW(dialog));
    gtk_window_set_modal(GTK_WINDOW(message), true);
    gtk_widget_show_all(message);
    gtk_dialog_run(GTK_DIALOG(message));
    gtk_widget_destroy(message);
}
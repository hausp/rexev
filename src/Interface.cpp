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
    dialog = GTK_WIDGET(gtk_builder_get_object(builder, "add_regex"));
    std::pair<std::string,std::string> result = std::make_pair("","");
    gtk_widget_show_all(dialog);
    
    while (result.second.size() == 0) {
        auto response = gtk_dialog_run(GTK_DIALOG(dialog));
        if (response == GTK_RESPONSE_OK) {
            ECHO("ok");
            result = extract_add_dialog_entries();
        } else {
            ECHO("cancel");
            clean_add_dialog();
            break;
        }
    }
    gtk_widget_hide(dialog);
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
    auto buffer = gtk_entry_get_buffer(GTK_ENTRY(name_entry));
    auto text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(regex_text));
    gtk_entry_buffer_delete_text(buffer, 0, -1);
    gtk_text_buffer_set_text(text_buffer, "\0", -1);
}

void Interface::destroy() {
    gtk_widget_destroy(window);

}
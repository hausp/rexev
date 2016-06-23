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
    auto regex_list = GTK_TREE_VIEW(gtk_builder_get_object(builder, "exp_list"));
    auto af_list    = GTK_TREE_VIEW(gtk_builder_get_object(builder, "automata_list"));
    auto regex_sel  = gtk_tree_view_get_selection(regex_list);
    auto af_sel     = gtk_tree_view_get_selection(af_list);

    gtk_tree_selection_set_select_function(regex_sel, signals::regex_selection, nullptr, nullptr);
    gtk_tree_selection_set_select_function(af_sel, signals::automata_selection, nullptr, nullptr);
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
            result = extract_add_dialog_entries();
        } else {
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

void Interface::put_regex(const std::string& name, unsigned id) {
    auto model = GTK_LIST_STORE(gtk_builder_get_object(builder, "exp_table"));
    GtkTreeIter iter;
    gtk_list_store_insert(model, &iter, -1);
    gtk_list_store_set(model, &iter, 0, name.c_str(), 1, id, -1);
}

void Interface::put_automaton(const std::string& name, unsigned id) {
    auto model = GTK_LIST_STORE(gtk_builder_get_object(builder, "automata_table"));
    GtkTreeIter iter;
    gtk_list_store_insert(model, &iter, -1);
    gtk_list_store_set(model, &iter, 0, name.c_str(), 1, id, -1);
}

void Interface::show_expression(const char* exp) {
    auto text_area = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "regex_view"));
    auto buffer = gtk_text_view_get_buffer(text_area);
    gtk_text_buffer_set_text(buffer, exp, -1);
}

void Interface::show_automaton(const std::vector<std::vector<std::string>>& values) {
    auto view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "dfa_tree"));
    GType* types = new GType[values[0].size()];

    for (unsigned i = 0; i < values[0].size(); i++) {
        types[i] = G_TYPE_STRING;
        auto renderer = gtk_cell_renderer_text_new();
       gtk_tree_view_insert_column_with_attributes(view, -1, values[0][i].c_str(),
                                                   renderer, nullptr);
    }
    
    auto model = gtk_list_store_newv(values[0].size(), types);
    g_free(types);

    for (auto v : values) {
        GtkTreeIter iter;
        gtk_list_store_insert(model, &iter, -1);
        unsigned i = 0;
        for (auto s : v) {
            ECHO(s);
            gtk_list_store_set(model, &iter, i, s.c_str(), -1);
            i++;
        }
    }
    gtk_tree_view_set_model(view, GTK_TREE_MODEL(model));
}

void Interface::select_expression(unsigned id) {
    auto tree = GTK_TREE_VIEW(gtk_builder_get_object(builder, "exp_list"));
    auto path = gtk_tree_path_new_from_string(std::to_string(id).c_str());
    gtk_tree_view_set_cursor(tree, path, nullptr, false);
}
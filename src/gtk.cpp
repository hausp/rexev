/* created by Ghabriel Nunes<ghabriel.nunes@gmail.com>& 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "gtk.hpp"

namespace gtk {
    void init(int argc, char** argv) {
        gtk_init(&argc, &argv);
    }

    void main() {
        gtk_main();
    }

    GtkWidget* new_window(const char* name, bool resizable, int bwidth) {
        GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), name);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
        gtk_container_set_border_width(GTK_CONTAINER(window), bwidth);
        gtk_window_set_resizable(GTK_WINDOW(window), resizable);
        return window;
    }

    GtkWidget* new_scrolled_window(GtkAdjustment* hadj, GtkAdjustment* vadj, 
                                   const GtkShadowType& shadow, int xmin,
                                   int ymin, int bwidth) {
        GtkWidget* scwin = gtk_scrolled_window_new(hadj, vadj);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scwin), shadow);
        gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scwin), xmin);
        gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scwin), ymin);
        gtk_container_set_border_width(GTK_CONTAINER(scwin), bwidth);
        return scwin;
    }

    GtkWidget* new_dialog(const GtkWidget* parent, const char* name, int bwidth) {
        GtkWidget* dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(dialog), name);
        gtk_window_set_resizable(GTK_WINDOW(dialog), false);
        gtk_window_set_modal(GTK_WINDOW(dialog), true);
        gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));
        gtk_window_set_type_hint(GTK_WINDOW(dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
        gtk_container_set_border_width(GTK_CONTAINER(dialog), bwidth);
        return dialog;
    }

    GtkWidget* new_paned(const GtkOrientation& orientation,
                         GtkWidget* chield1, bool expand1, bool shrink1,
                         GtkWidget* chield2, bool expand2, bool shrink2) {
        auto paned = gtk_paned_new(orientation);
        if (chield1) {
            gtk_paned_pack1(GTK_PANED(paned), chield1, expand1, shrink1);
        }
        if (chield2) {
            gtk_paned_pack2(GTK_PANED(paned), chield2, expand2, shrink2);
        }
        return paned;
    }

    GtkWidget* new_paned(const GtkOrientation& orientation,
                         GtkWidget* child1, GtkWidget* child2) {
        return new_paned(orientation, child1, false, false, child2, false, false);
    }

    GtkWidget* new_frame(const char* name, float xalign, float yalign, int bwidth) {
        GtkWidget* frame = gtk_frame_new(name);
        gtk_frame_set_label_align(GTK_FRAME(frame), xalign, yalign);
        gtk_container_set_border_width(GTK_CONTAINER(frame), bwidth);
        return frame;
    }

    GtkWidget* new_entry(const std::string& name, float align, int max, int mshow) {
        GtkWidget* entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(entry), name.c_str());
        gtk_entry_set_alignment(GTK_ENTRY(entry), align);
        set_entry_max_length(entry, max, mshow);
        return entry;
    }

    GtkWidget* new_button(const char* name, GtkWidget* parent, void (*action)()) {
        GtkWidget* button = gtk_button_new_with_mnemonic(name);
        if (parent) {
            gtk_container_add(GTK_CONTAINER(parent), button);
        }
        if (action) {
            g_signal_connect(button, "clicked", G_CALLBACK(action), NULL);
        }
        return button;
    }

    GtkWidget* new_box(const GtkOrientation& orientation, const GtkWidget* parent,
                       int spacing, bool homogeneous, int bwidth) {
        GtkWidget* box = gtk_box_new(orientation, spacing);
        gtk_box_set_homogeneous(GTK_BOX(box), homogeneous);
        gtk_container_set_border_width(GTK_CONTAINER(box), bwidth);
        if (parent) {
            gtk_container_add(GTK_CONTAINER(parent), box);
        }
        return box;
    }

    GtkWidget* new_grid(const GtkWidget* parent, int rspacing, int cspacing,
                        bool rh, bool ch, int bwidth) {
        GtkWidget* grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(grid), rspacing);
        gtk_grid_set_column_spacing(GTK_GRID(grid), cspacing);
        gtk_grid_set_row_homogeneous(GTK_GRID(grid), rh);
        gtk_grid_set_column_homogeneous(GTK_GRID(grid), ch);
        gtk_container_set_border_width(GTK_CONTAINER(grid), bwidth);
        if (parent) {
            gtk_container_add(GTK_CONTAINER(parent), grid);
        }
        return grid;
    }

    GtkWidget* new_list_box(GtkWidget* const parent) {
        auto list_box = gtk_list_box_new();
        if (parent) {
            gtk_container_add(GTK_CONTAINER(parent), list_box);
        }
        return list_box;
    }

    GtkWidget* new_button_box(const GtkOrientation& orientation,
                              bool homogeneous, int spacing) {
        auto buttonbox = gtk_button_box_new(orientation);
        gtk_box_set_homogeneous(GTK_BOX(buttonbox), homogeneous);
        gtk_box_set_spacing(GTK_BOX(buttonbox), spacing);
        return buttonbox;
    }

    GtkWidget* new_expander(const char* name, const bool expanded) {
        auto expander = gtk_expander_new_with_mnemonic(name);
        gtk_expander_set_expanded(GTK_EXPANDER(expander), expanded);
        return expander;
    }

    GtkWidget* new_expander_with_frame(const char* name, const bool expanded,
                                       const GtkShadowType& shadow) {
        auto expander = new_expander(name, expanded);
        auto frame = new_frame(NULL, 0, 0, 1);
        gtk_frame_set_shadow_type(GTK_FRAME(frame), shadow);
        gtk_container_add(GTK_CONTAINER(expander), frame);
        return frame;
    }

    void set_entry_max_length(const GtkWidget* entry, int length, int show) {
        gtk_entry_set_max_length(GTK_ENTRY(entry), length);
        gtk_entry_set_width_chars(GTK_ENTRY(entry), show);
        #if RECENT_COMPILER
        gtk_entry_set_max_width_chars(GTK_ENTRY(entry), show);
        #endif
    }

    void box_push_back(const GtkWidget* box, const std::vector<box_pack>& packets) {
        box_push(packets,[&box](GtkWidget* widget, bool alloc, bool expand, int offset) {
            gtk_box_pack_start(GTK_BOX(box), widget, alloc, expand, offset);
        });
    }

    void box_push_front(const GtkWidget* box, const std::vector<box_pack>& packets) {
        box_push(packets,[&box](GtkWidget* widget, bool alloc, bool expand, int offset) {
            gtk_box_pack_end(GTK_BOX(box), widget, alloc, expand, offset);
        });
    }

    void box_push(const std::vector<box_pack>& packets,
                   const std::function<void(GtkWidget*, bool, bool, int)>& fn) {
        for (auto packet : packets) {
            fn(packet.widget, packet.alloc, packet.expand, packet.offset);
        }
    }

    void set_margins(GtkWidget* widget, int left, int top, int right, int bottom) {
        #if RECENT_COMPILER
        gtk_widget_set_margin_start(widget, left);
        gtk_widget_set_margin_end(widget, right);
        #else
        gtk_widget_set_margin_left(widget, left);
        gtk_widget_set_margin_right(widget, right);
        #endif
        gtk_widget_set_margin_top(widget, top);
        gtk_widget_set_margin_bottom(widget, bottom);
    }

    void quit() {
        gtk_main_quit();
    }

    void queue_draw(GtkWidget* widget) {
        gtk_widget_queue_draw(widget);
    }
}

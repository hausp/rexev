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

    void quit() {
        gtk_main_quit();
    }
}

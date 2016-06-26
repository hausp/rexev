/* created by Ghabriel Nunes<ghabriel.nunes@gmail.com> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef GTK_HPP
#define GTK_HPP

#include <gtk/gtk.h>
#include <functional>
#include <iostream>
#include <vector>

namespace gtk {

    void init(int, char**);

    void main();

    void quit();
}

#endif /* GTK_HPP */
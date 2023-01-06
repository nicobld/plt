#include "Menu.h"

namespace view{
    
bool Menu::isClicked(int x, int y){
    return coords.contains(x, y);
}

}
#include "worms.hpp"

bool worms::isAlive() const{
  return health > 0; 
}

void worms::move(bool right){               // Is it here that we should link the keys of the keyboards to the features ew want to implement?
                                            // Hence set the right arrow to add say 5 velocity to the right.
                                            // Here are some ascii codes: 37(left arrow)
                                            //                            38(up arrow)
                                            //                            39(right arrow)
                                            //                            40(down arrow)
                                            
          
  
}
// This is also something that I found as an example of how to handle key inputs. Remark that the ascii is here not the same.
// We will have to see how it works depending on the keyboard.
/*
https://stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key
CODE:


#include <conio.h>
#include <iostream>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
    int c = 0;
    while(1)
    {
        c = 0;

        switch((c=getch())) {
        case KEY_UP:
            cout << endl << "Up" << endl;//key up
            break;
        case KEY_DOWN:
            cout << endl << "Down" << endl;   // key down
            break;
        case KEY_LEFT:
            cout << endl << "Left" << endl;  // key left
            break;
        case KEY_RIGHT:
            cout << endl << "Right" << endl;  // key right
            break;
        default:
            cout << endl << "null" << endl;  // not arrow
            break;
        }

    }

    return 0;
}

RESULT IN THE CONSOLE AFTER SOME TESTS:
Up

Down

Right

Left

Up

Left

Right

Right

Up
*/

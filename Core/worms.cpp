#include "worms.hpp"

bool worms::isAlive() const{
  return health > 0; 
}

void worms::move(){           // Takes care of all movements of the worms based on the keyboard inputs. NOT TESTED 
  
  // MOVE TO THE RIGHT
  if(int QKeyEvent::key() const == 0x44){           //If the input key is the right arrow which has code 0x01000014, then give force to the right to the rigid body.
    worms.addForce(QPair<double, double>(5, 0));
    if(bool QKeyEvent::isAutoRepeat() const == true && int QKeyEvent::key() const == 0x44){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
      worms.addForce(QPair<double, double>(5, 0));                                             // The way int QKeyEvent::key() const and bool QKeyEvent::isAutoRepeat() const work are explained in the text under.
      }
  }
  
  // MOVE TO THE LEFT
  if (int QKeyEvent::key() const == 0x41){ // To move to the left just take out 5 velocity.
    worms.addForce(QPair<double, double>(-5, 0));
    }
    if((bool QKeyEvent::isAutoRepeat() const == true && int QKeyEvent::key() const == 0x41){
      worms.addForce(QPair<double, double>(-5, 0));
      }
   
  // JUMP
  if (int QKeyEvent::key() const == 0x57){ // To move jump give a negative force to the y-axis (recall 
    worms.addForce(QPair<double, double>(0, -5));
    }
    if((bool QKeyEvent::isAutoRepeat() const == true && int QKeyEvent::key() const == 0x57){
      vy0 += 5;
      }
}


-----------------------------------------------------------------------------------------------
// Is it here that we should link the keys of the keyboards to the features ew want to implement?
                                            // Hence set the right arrow to add say 5 velocity to the right.
                                            // Here are some ascii codes: 37(left arrow)
                                            //                            38(up arrow)
                                            //                            39(right arrow)
                                            //                            40(down arrow)
// Problem: How to make it smooth? If we use the switch method, we should add the break; instruction after each successful 
// checking. Will it break the entire process? Is it fine like this?
  
// This is also something that I found as an example of how to handle key inputs. Remark that the ascii is here not the same.
// We will have to see how it works depending on the keyboard.
  
// Remark the function getch()
  
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
// TO IMPLEMENT USING QT
/*
bool QKeyEvent::isAutoRepeat() const

Returns true if this event comes from an auto-repeating key; returns false if it comes from an initial key press.

Note that if the event is a multiple-key compressed event that is partly due to auto-repeat, 
this function could return either true or false indeterminately.  
*/
  
/*
int QKeyEvent::key() const

Returns the code of the key that was pressed or released.

See Qt::Key for the list of keyboard codes. These codes are independent of the underlying window system. 
Note that this function does not distinguish between capital and non-capital letters, use the text() function
(returning the Unicode text the key generated) for this purpose.

A value of either 0 or Qt::Key_unknown means that the event is not the result of a known key; for example, 
it may be the result of a compose sequence, a keyboard macro, or due to key event compression.

See also Qt::WA_KeyCompression.
*/
  
/*
Qt::Key_Right	0x01000014
Qt::Key_Left	0x01000012
Qt::Key_Up	0x01000013
Qt::Key_Down	0x01000015

Qt::Key_A	0x41   Move to the left   
Qt::Key_D	0x44   Move to the right 
Qt::Key_W	0x57   jump
*/
-----------------------------------------------------------------------------------------------

void worms::pickUpWeapon(int weapon_ID, int ammo){
  // TO DO
}
       
       
int changeAngle(double angle_change){ //  Renvoie un degré
  
  
}
 
       

  

  
  

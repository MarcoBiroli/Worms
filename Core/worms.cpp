#include "worms.h"

Worm::Worm(): RigidBody (), team_number(0), personal_name("")
{

}

Worm::Worm(int team_number, std::string personal_name, int health, double mass, double x, double y, bool isTurn)
    : RigidBody(mass, x, y), team_number(team_number), personal_name(personal_name) {
    this->health = health;
    this-> isTurn = isTurn; //We added a isTurn parameter, to check whether it's this Worms turn or not.
}

Worm::~Worm() {
    //delete []ammo; // why do we need to delete?
}

bool Worm::isAlive() const{
  return health > 0; 
}

void Worm::pickUpWeapon(int weapon_ID, int iammo) {
    this->ammo[weapon_ID] += iammo;
}

void Worm::weaponSelect(int weapon_ID) {
    this->current_weapon = weapon_ID;
}

void Worm::changeHealth(int dmg) {
    this->health -= dmg;
}

void Worm::changeAngle(bool clockwise) { //Have we defined clockwise and anti-clockwise?
    if (clockwise){
        this->weapon_angle -= 2;
    }
    else{
        this->weapon_angle += 2;
    }
}


void Worm::fireWeapon(double power, QVector<Projectile> weapons, PhysicsEngine &engine, QVector<Projectile*> &projectiles) {
    Projectile* current_projectile = weapons[weapon_ID].clone(); //currently shot projectile is just a clone of a previously initialized one.
    // We sets its initial parameters:
    current_projectile->set_inital_position(this->x, this->y); //might need to offset initial position to avoid worm shooting himself
    double x_force =  power*cos(weapon_angle*(M_PI/180));
    double y_force = -power*sin(weapon_angle*(M_PI/180));
    current_projectile->addForce(QPair<double, double>(x_force, y_force)); //apply force generate by shot
    engine.add_RigidBody(current_projectile); //add projectile to projectile vector to be handle by physics engine
    projectiles.append(current_projectile);
}

void Worm::move(bool right){           // Takes care of all movements of the worms based on the keyboard inputs. NOT TESTED
  /*
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
    */
}

void Worm::wormDeath() {
    //call animation
    //should we call the destructor?
}

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

  

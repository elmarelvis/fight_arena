#include <iostream>
#include <fstream>
#include <cstdio> // atoi
using namespace std;

class Weapon {
protected:
    int damage;
    string name;
    virtual void save()=0;
public:
    Weapon (int damage, string name) : damage(damage), name(name) { }
    Weapon(){}
};

class Gun : public Weapon {
protected:
    int bullets;
public:
    Gun(){
    }
    Gun (int damage, string name) : Weapon(damage, name), bullets(0) {}
    void save() {  // gun;name;damage;bullets
        ofstream file;
        file.open("data.csv",ios::trunc);
        file << "gun," << name << "," << "Damage:," << damage << "[dmg]" << "," << "Bullets:," << bullets << "[dmg]" << endl;
        file.close();
    }
    void addBullets(unsigned int n) {
        bullets+= n;
    }
    int showbullets() {
        return bullets;
    }
    int shoot()  {
        return damage;
    }
    void load() {
        ifstream file;
        file.open("data.csv");
        char buffer[8192];
        file.getline(buffer,8192,';');
        file.getline(buffer,8192,';'); name = buffer;
        file.getline(buffer,8192,';'); damage = atoi(buffer);
        file.getline(buffer,8192); bullets = atoi(buffer);
        file.close();
    }
    friend void showg(const Gun& gun);
};

class Melee : public Weapon{
protected:
    int bleeding;
public:
    Melee(){}
    Melee (int damage, string name) : Weapon(damage, name), bleeding(0) {}
    void save() {  // gun;name;damage;bullets
        ofstream file;
        file.open("data.csv",ios::app);
        file << "melee," << name << "," << "Damage:," <<  damage << "[dmg]" << "," << "Bleeding:," << bleeding << "[dmg]" <<  endl;
        file.close();
    }
    void setbleeding(unsigned int n){
        bleeding = n;
    }
    int hit(){
        return damage = damage + bleeding;
    }
    void load() {
        ifstream file;
        file.open("data.csv");
        char buffer[8192];
        file.getline(buffer,8192,';');
        file.getline(buffer,8192,';'); name = buffer;
        file.getline(buffer,8192,';'); damage = atoi(buffer);
        file.getline(buffer,8192); bleeding = atoi(buffer);
        file.close();
    }


    friend void showm(const Melee& melee);
};

void showg(const Gun& gun) {
    cout << gun.name << " damage: " << gun.damage << " arrows: " << gun.bullets << endl;
}
void showm(const Melee& melee){
    cout << melee.name << " damage: " << melee.damage << " Bleeding: " << melee.bleeding <<  endl;
}


int main() {

    Gun bow(30, "Luk");  // set bow parameters
    bow.addBullets(10);
    bow.save();
    showg(bow);

    Melee knife(25, "Nuz"); // set knife parameters
    knife.setbleeding(40);
    knife.save();
    showm(knife);

    Melee axe(50, "Sekera");  // set axe parameters
    axe.setbleeding(10);
    axe.save();
    showm(axe);

    ofstream file;
    file.open("fight_log.csv",ios::trunc); // create new "fight" csv file
    int Warrlive = 5000;
    int Archlive = 3000;
    int Warratt = axe.hit();
    int Archatt = bow.shoot();
    int Archatt2 = knife.hit();
    int bowbullets = bow.showbullets() - 1;
    file << "warrior attack causing axe:," << Warratt << "," << "damage," << endl;
    file << "archer attack causing bow:," << Archatt << "," << "damage,"<< endl;
    file << "archer attack causing knife:, " << Archatt2 << "," << "damage," << endl;
    file << "Warrior remain:, " << Warrlive << "," << " hp," << endl;
    file << "Archer remain:, " << Archlive << "," << " hp," << endl << "↣↣↣ Archer attack ↣↣↣" << endl;
    int range = 10;
    while(Warrlive >= 0 && Archlive >= 0) {
        if (Warrlive <= 0 || Archlive <= 0){
            if (Warrlive <= 0) {file << "Archer is winner!!! Congratulation! ☠☠☠ Warriror is dead ☠☠☠,";}
            if (Archlive <= 0) {file << "Warrior is winner!!! Congratultion! ☠☠☠ Archer is dead ☠☠☠,";}
            break;
        }

        if (bowbullets == 0 && range <= 0){

            Warrlive = Warrlive - Archatt2;
        }
        else if (bowbullets > 0) {
            Warrlive = Warrlive - Archatt;
            bowbullets--;

        }
        else if (bowbullets == 0 && range > 0) {
            Warrlive = Warrlive - 0;
            range --;
            file << "Warrior remain:, " << Warrlive << "," << " hp," << endl << "→→→ Archer walk →→→" << endl;

        }
        if (range > 0){
            file << "Warrior remain:, " << Warrlive << "," << " hp," << endl << "→→→ Warrior walk →→→" << endl;
            Archlive = Archlive - 0;
            range --;


        } else if (range <= 0){ Archlive = Archlive - Warratt;
            file << "Warrior remain:, " << Warrlive << "," << " hp," << endl << "⚔⚔⚔ Warrior attack ⚔⚔⚔" << endl;}
        file << "Archer remain:, " << Archlive << "," << " hp," << endl;
        if (Warrlive <=0 || Archlive <= 0)
            continue;
        else file << "➳➳➳ Archer attack ➳➳➳" << endl;
    }
}



// TODO:
/*
   Zápis a načtení více zbraní do souboru
   Souboj
*/
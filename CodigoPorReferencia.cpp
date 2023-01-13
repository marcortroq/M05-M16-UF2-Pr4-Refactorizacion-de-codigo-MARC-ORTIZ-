#include <iostream>

using namespace std;


//variables combate
int dano;

//Variables enemigos1 
bool enemy1IsAlive = true;
int enemy1HP = 1000;
int enemyDamage;
int atack;
string enemyname = "Malo 1";

//Variables enemigo2

bool enemy2IsAlive = true;
int enemy2HP = 1000;
int enemy2Damage;
int attack;
string enemyname2 = "Malo 2";

//Variables heroe
string heroName;
int heroHP = 5000;
bool heroIsAlive = true;
int escoger = 0;
int heroDamage;

//Ataques heroes
int espada = 250;
int golpe = 400;
int magia = 500;
int limitado = 2;
int ataque;

void gameStart() {
    cout << "El enemigo " << enemyname << " y " << enemyname2 << " acaban de aparecer\nY tienen " << enemy1HP << " puntos de vida \n";
    cout << "Inserta el nombre del heroe que lo va a derrotar\n";
    cin >> heroName;
    cout << "\nEl nombre del heroe es: " << heroName << "\n";
}

int chooseEnemy() {
    escoger = 0;
    //PREGUNTAMOS A QUE ENEMIGO ATACAR
    cout << "A que enemigo quieres atacar [1/2]\n";
    cin >> escoger;
    //HASTA NO SELCCIONAR A UN ENEMIGO CORRECTO NOS VOLVERA A PREGUNTAR
    while (escoger != 1 && escoger != 2)
        //ENEMIGO SELECCIONADO
        if (escoger == 1 || escoger == 2) {
            cout << "Lanzas un ataque al enemigo " << escoger << "\n\n";
            return escoger;
        }
        else if (escoger != 1 && escoger != 2) {
            cout << "El enemigo escogido no existe\n";
            cout << "A que enemigo quieres atacar [1/2]\n";
            cin >> escoger;
        }
}

void attackChose(int& enemyHP) {
        if (ataque == 1) {
            enemyHP = enemyHP - espada;
        }
        else if (ataque == 2) {
            enemyHP = enemyHP - golpe;
        }
        else if (ataque == 3) {
            if (limitado != 0) {
                enemyHP = enemyHP - magia;
                limitado -= 1;
            }
            else {
                cout << "no has podido atacar con magia no te quedan usos\n";
            }
        }
        else
        {
            "Has fallado, no existe ese ataque";
        }
    }

bool checkStatus(bool& enemyIsAlive, int& enemyHP, string& enemynamef) {
    if (enemyHP <= 0) {
        enemyHP = 0;
        enemyIsAlive = false;
        cout << "Has derrotado al " << enemynamef << "\n";
    } else {
        return true;
    }
}

void chooseAtaque() {
    //ESCOGEMOS EL ATAQUE
    cout << "Que ataque quieres realizar:\n" "Espada[1]\n" "Golpe[2]\n" "Magia[3] Quedan " << limitado << " ataques restantes\n";
    cin >> ataque;

    //ATACAMOS AL ENEMIGO 1 Y COMPROBAMOS SI ESTA VIVO O MUERTO
    if (enemy1IsAlive) {
        if (escoger == 1) {
            attackChose(enemy1HP);
            enemy1IsAlive = checkStatus(enemy1IsAlive, enemy1HP, enemyname);
        }
    }
    else {
            cout << "\nEl " << enemyname << " esta muerto no puedes segir atacandole, has perdido el turno\n";
    }
    
    //ATACAMOS AL ENEMIGO 2 Y COMPROBAMOS SI ESTA VIVO O MUERTO
    if (enemy2IsAlive) {
        if (escoger == 2) {
            attackChose(enemy2HP);
            enemy2IsAlive = checkStatus(enemy2IsAlive, enemy2HP, enemyname2);
        }
    }
    else {
        cout << "\nEl " << enemyname2 << " esta muerto no puedes segir atacandole, has perdido el turno\n";
    }
    
    cout << "\nAl " << enemyname << " le quedan " << enemy1HP << " puntos de vida\n";
    cout << "\nAl " << enemyname2 << " le quedan " << enemy2HP<< " puntos de vida\n";
}

void enemiesAttack() {

    enemyDamage = rand() % 999 + 30;
    enemy2Damage = rand() % 999 + 30;

    if (enemy1IsAlive && enemy2IsAlive) {
        dano = enemyDamage + enemy2Damage;
        heroHP = heroHP - dano;
        if (heroHP <= 0) {
            heroHP = 0;
        }
        cout << "\nLos enemigos te han hecho " << dano << " te quedan " << heroHP << " puntos de vida\n\n";
    }
    else if (enemy1IsAlive && enemy2IsAlive == false) {
        heroHP = heroHP - enemyDamage;
        if (heroHP <= 0) {
            heroHP = 0;
        }
        cout << "\nEl " << enemyname << " te ha hecho " << enemyDamage << " te quedan " << heroHP << " puntos de vida\n\n";
    }
    else if (enemy1IsAlive == false && enemy2IsAlive) {
        heroHP = heroHP - enemy2Damage;
        if (heroHP <= 0) {
            heroHP = 0;
        }
        cout << "\nEl " << enemyname2 << " te ha hecho " << enemy2Damage << " te quedan " << heroHP << " puntos de vida\n\n";
    }
    else if (enemy1IsAlive == false && enemy2IsAlive == false) {
        cout << "Has Ganado el combate\n";
    }
}

bool checkHeroStatus() {
    if (heroHP <= 0) {
        cout << "El heroe ha sido derrotado\n ";
        return false;
    }
    else
    {
        return true;
    }
}

int main() {
    srand(time(NULL));
    gameStart();

    while ((enemy1IsAlive || enemy2IsAlive) && heroIsAlive) {
        //ELEGIMOS AL ENEMIGO QUE VAMOS A ATACAR
        chooseEnemy();
        //ESCOGEMOS EL ATAQUE QUE QUEREMOS REALIZAR
        chooseAtaque();
        //ATACAN LOS ENEMIGOS Y COMPROBAMOS SI ESTAN VIVOS
        enemiesAttack();
        //COMPROVAMOS SI EL HEROE ESTA VIVO
        heroIsAlive = checkHeroStatus();
    }

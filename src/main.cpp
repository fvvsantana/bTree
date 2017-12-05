#include <iostream>
#include <istream>
#include <windows.h>
#include <conio.h>
#include "library.hpp"

using namespace std;

// function prototypes
void changeColor(int color);
void printMenu(int menu);
void menuAction(int menu, Library lib);

// main is responsible for receiving user input and calling library methods
int main(int argc, char *argv[]){

    // Library managing file operations
    Library lib;

    // menu variables
    char c = 0;
    int menuOption = 1;

    // beginning of menu loop
    while (c != -1){

        // clear screen and print title
        system("cls");
        changeColor(207);
        cout<<"Menu B-Tree:";
        changeColor(15);

        // print options
        printMenu(menuOption);

        // read a char and proceed accordingly
        c = getch();

        // if it was a number key
        if (c >= 49 && c <= 54)
            menuOption = c - 48;

        // if it was arrow down
        else if (c == 80) {
            if(menuOption != 6)
                menuOption++;
            //If it is in the border, jump to the other side
            else
                menuOption = 1;
        }

        // if it was arrow up
        else if (c == 72) {
            if(menuOption != 1)
                menuOption--;
            //If it is in the border, jump to the other side
            else
                menuOption = 6;
        }

        // if it was ENTER key
        else if (c == 13) {
            // stop loop if it is option 6
            if (menuOption == 6)
                c = -1;
            else
                menuAction(menuOption, lib);
        }
    }

    // print finalization message
    changeColor(207);
    cout<<endl<<"Programa finalizado!";
    changeColor(15);

    return 0;
}

// change printing color
void changeColor(int color){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// print the menu options with the correct colors and highlights
void printMenu(int menu){
    //Index
    if(menu==1){
        cout << endl << "------->";
        changeColor(240);
        cout << "1. Criar Indice";
        changeColor(15);
    } else
        cout<<endl<<"\t1. Criar Indice";

    //Insert Music
    if(menu==2){
        cout<<endl<<"------->";
        changeColor(240);
        cout<<"2. Inserir Musica";
        changeColor(15);
    } else
        cout<<endl<<"\t2. Inserir Musica";

    // Search Music
    if(menu==3){
        cout<<endl<<"------->";
        changeColor(240);
        cout<<"3. Pesquisar Musica por ID";
        changeColor(15);
    } else
        cout<<endl<<"\t3. Pesquisar Musica por ID";

    // Remove Music
    if(menu==4){
        cout<<endl<<"------->";
        changeColor(240);
        cout<<"4. Remover Musica por ID";
        changeColor(15);
    } else
        cout<<endl<<"\t4. Remover Musica por ID";

    // Print B tree
    if(menu==5){
        cout<<endl<<"------->";
        changeColor(240);
        cout<<"5. Mostrar Arvore";
        changeColor(15);
    } else
        cout<<endl<<"\t5. Mostrar Arvore";

    //Close the program
    if(menu==6){
        cout<<endl<<"------->";
        changeColor(240);
        cout<<"6. Fechar o Programa";
        changeColor(15);
    } else
        cout<<endl<<"\t6. Fechar o Programa";
}

// receive the selected menu option and behave accordingly
void menuAction(int option, Library lib){
    // clear screen
    system("cls");

    // decides what to do
    switch(option){
        //Create index
        case 1:
            cout<<endl<<"Funcao de Criar Indice, aperte ENTER para prosseguir.";
            getchar();
            break;

        //Insert Music
        case 2: {
            cout << endl << "Funcao de Inserir musica, insira as informacoes abaixo.\n";
            Song newSong;

            cout << "\nId da musica:\n";
            cin >> newSong.id;
            cin.ignore(1000, '\n');

            cout << "\nTitulo da musica:\n";
            getline(cin, newSong.title);

            cout << "\nGenero da musica:\n";
            getline(cin, newSong.genre);

            lib.insertSong(newSong);
            cout << "\nMusica inserida com sucesso.\nAperte ENTER para prosseguir.";
            getchar();

            break;
        }
        //Search Music
        case 3:
            cout<<endl<<"Funcao de Procurar uma Musica, aperte ENTER para prosseguir.";
            getchar();
            break;
        //Remove Music
        case 4:
            cout<<endl<<"Funcao de Remover uma Musica, aperte ENTER para prosseguir.";
            getchar();
            break;
        //Show B tree
        case 5:
            cout<<endl<<"Funcao para Mostrar a B-tree, aperte ENTER para prosseguir.";
            getchar();
            break;
    }
}

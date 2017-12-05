#include <iostream>
#include <istream>
#include <windows.h>
#include <conio.h>
#include "library.hpp"

using namespace std;

// function prototypes
void changeColor(int color);
void printMenu(int menu);
void menuAction(int menu, Library &lib);

// main is responsible for receiving user input and calling library methods
int main(int argc, char *argv[]){

    // Library object that will manage file operations
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
        cout<<"5. Mostrar Arvore-B";
        changeColor(15);
    } else
        cout<<endl<<"\t5. Mostrar Arvore-B";

    //Close the program
    if(menu==6){
        cout<<endl<<"------->";
        changeColor(240);
        cout<<"6. Fechar o Programa";
        changeColor(15);
    } else
        cout<<endl<<"\t6. Fechar o Programa";
}

// read a numeric value from user input
int readNumber() {
    int number;
    while (! (cin >> number)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nValor invalido, insira novamente.\n";
    }
    cin.ignore(1000, '\n');
    return number;
}

// receive the selected menu option and behave accordingly
void menuAction(int option, Library &lib){
    // clear screen
    system("cls");

    // decides what to do
    switch(option){
        // Create index
        case 1: {
            if (lib.generateIndex())
                cout << "\nIndice criado com sucesso!";
            else
                cout << "\nO indice nao foi criado pois nao existe um arquivo de dados.";
            cout << "\n\nPressione ENTER para continuar.";
            getchar();
            break;
        }
        // Insert Music
        case 2: {
            cout << "\nFuncao de Inserir musica, insira as informacoes abaixo.\n";
            Song newSong;

            cout << "\nId da musica:\n";
            newSong.id = readNumber();

            cout << "\nTitulo da musica:\n";
            getline(cin, newSong.title);

            cout << "\nGenero da musica:\n";
            getline(cin, newSong.genre);

            lib.insertSong(newSong);
            cout << "\nMusica inserida com sucesso.\n\nPressione ENTER para continuar.";
            getchar();

            break;
        }

        // Search Music
        case 3: {
            cout << "\nFuncao de Procurar uma Musica.\n\nDigite o ID da musica procurada:\n";

            int id = readNumber();

            Song song = lib.searchSong(id);

            // verify if found the song
            if (song.id == -1)
                cout << "\nMusica nao encontrada.";
            else {
                cout << "\nMusica encontrada:"
                     << "\n Id: " << song.id
                     << "\n Titulo: " << song.title
                     << "\n Genero: " << song.genre;
            }

            cout << "\n\nPressione ENTER para continuar.";
            getchar();
            break;
        }
        // Remove Music
        case 4:
            cout << "\nFuncao de remocao nao implementada.\n\nPressione ENTER para continuar.";
            getchar();
            break;

        // Show B tree
        case 5:
            lib.showBTree();
            cout << "\nArvore-B impressa no arquivo de log.\n\nPressione ENTER para continuar.";
            getchar();
            break;
    }
}

#include <iostream>
#include <istream>
#include "library.hpp"
#include "song.hpp"
#include <windows.h>
#include "conio.h"

using namespace std;

//Change the statements' color
void TrocaCor(int x){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, x);
}


//menu management function
void GerenciaMenu(int menu){
    system("cls");
    //manages the menu from the menu variable
    switch(menu){
        //Create index
        case 1:
            cout<<endl<<"Funcao de Criar Indice, aperte ENTER para prosseguir.";
            getchar();
        break;
        //Insert Music
        case 2:
            cout<<endl<<"Funcao de Inserir Musica, aperte ENTER para prosseguir.";
            getchar();
        break;
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

//Print Menu Function
void PrintaMenu(int menu){
    //Index
    if(menu==1){
        cout << endl << "------->";
        TrocaCor(240);
        cout << "1. Criar Indice";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t1. Criar Indice";
    }
    //Insert Music
    if(menu==2){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"2. Inserir Musica";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t2. Inserir Musica";
    }
    // Search Music
    if(menu==3){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"3. Pesquisar Musica por ID";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t3. Pesquisar Musica por ID";
    }
    // Remove Music
    if(menu==4){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"4. Remover Musica por ID";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t4. Remover Musica por ID";
    }
    // Print B tree
    if(menu==5){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"5. Mostrar Arvore";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t5. Mostrar Arvore";
    }

    //Close the program
    if(menu==6){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"6. Fechar o Programa";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t6. Fechar o Programa";
    }


}


int main(int argc, char *argv[]){

    //menu
    //Library lib;



    int c,menu=1,TAM=6;

    while (c!=27){

        system("cls");
        TrocaCor(207);
        cout<<"Menu B-Tree:";
        TrocaCor(15);

        PrintaMenu(menu);

        c = getch();
            switch(c){
            //Down arrow
            case 80:
                if(menu!=TAM) menu++;
            break;

            //Up arrow
            case 72:
                if(menu!=1) menu--;
            break;

            //Enter
            case 13:
                //Close program if menu it is the case 6
                if (menu==TAM) c=27;
                else GerenciaMenu(menu);
            break;

            }
    }
    TrocaCor(207);
    cout<<endl<<"Programa finalizado!";
    TrocaCor(15);
    return 0;
}

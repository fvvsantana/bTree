#include <iostream>
#include <istream>
#include "library.hpp"
#include "song.hpp"
#include <windows.h>
#include "conio.h"

using namespace std;

//Muda a cor das letras na tela de saida
void TrocaCor(int x){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, x);
}


//funcao com objetivo de gerenciar o menu
void GerenciaMenu(int menu){
    system("cls");
    //gerencia qual funcao deverá ser chamada de acordo com o escolhido no menu
    switch(menu){
        //Cria Indice
        case 1:
            cout<<endl<<"Funcao de Criar Indice, aperte ENTER para prosseguir.";
            getchar();
        break;
        //Insere Musica
        case 2:
            cout<<endl<<"Funcao de Inserir Musica, aperte ENTER para prosseguir.";
            getchar();
        break;
        //Pesquisar Musica
        case 3:
            cout<<endl<<"Funcao de Procurar uma Musica, aperte ENTER para prosseguir.";
            getchar();
        break;
        //Remover Musica
        case 4:
            cout<<endl<<"Funcao de Remover uma Musica, aperte ENTER para prosseguir.";
            getchar();
        break;
        //Mostrar Arvore B
        case 5:
            cout<<endl<<"Funcao para Mostrar a B-tree, aperte ENTER para prosseguir.";
            getchar();
        break;
    }



}

//funçao que printa o menu inicial
void PrintaMenu(int menu){
    //Indice
    if(menu==1){
        cout << endl << "------->";
        TrocaCor(240);
        cout << "1. Criar Indice";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t1. Criar Indice";
    }
    //Inserir Musica
    if(menu==2){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"2. Inserir Musica";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t2. Inserir Musica";
    }
    // Pesquisar por uma Musica
    if(menu==3){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"3. Pesquisar Musica por ID";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t3. Pesquisar Musica por ID";
    }
    // Remover uma musica
    if(menu==4){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"4. Remover Musica por ID";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t4. Remover Musica por ID";
    }
    // Printar a arvore
    if(menu==5){
        cout<<endl<<"------->";
        TrocaCor(240);
        cout<<"5. Mostrar Arvore";
        TrocaCor(15);
    }else{
        cout<<endl<<"\t5. Mostrar Arvore";
    }

    //Fechar o programa
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
            //caso se seta para baixo
            case 80:
                if(menu!=TAM) menu++;
            break;

            //caso de seta para cima
            case 72:
                if(menu!=1) menu--;
            break;

            //caso de tecla enter
            case 13:
                //fim do programa nesse caso
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

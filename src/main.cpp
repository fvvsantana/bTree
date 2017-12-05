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

bool receveAndCheckSTRING(char checker[]){
    int flag = false, i = 0;

    while (checker[i] != '\0'){
        if(!((checker[i] >= 'a' && checker[i] <= 'z') ||
             (checker[i] >= 'A' && checker[i] <= 'Z') ||
             (checker[i] >= '0' && checker[i] <= '9') ||
              checker[i] == ' ')                        )   flag = true;
        ++i;
    }

    return flag;

}
bool receveAndCheckINT(char checker[]){
    int flag = false, i = 0;

    while (checker[i] != '\0'){
        if(!(checker[i] >= '0' && checker[i] <= '9'))   flag = true;
        ++i;
    }

    return flag;

}

//menu management function
void GerenciaMenu(int menu){
    system("cls");
    int id;
    int x = 0;
    int flag;
    char idchar[20];
    char title[20];
    char genre[20];

    //manages the menu from the menu variable
    switch(menu){
        //Create index
        case 1:
            cout<<endl<<"Funcao de Criar Indice, aperte ENTER para prosseguir.\n";

            getch();
        break;
        //Insert Music
        case 2:
            cout<<endl<<"Funcao de Inserir Musica"<<endl
            //Take music's ID
            <<"Digite o numero inteiro referente ao ID da musica, depois o titulo da musica, e por fim o genero: "<<endl;
            flag = true;
            while(flag){
                gets(idchar);
                flag = receveAndCheckINT(idchar);
                if (flag) cout <<"O id eh constituido por characteres invalidos. Digite novamente."<<endl;
                else id = atoi(idchar);
            }
            getchar();
            //Take Music's title
            flag = true;
            while(flag){
                fgets(title,20,stdin);
                flag = receveAndCheckSTRING(title);
                if (flag) cout <<"O titulo eh constituido por characteres invalidos. Digite novamente."<<endl;
            }

            //Take Music's genre
            getchar();
            flag = true;
            while(flag){
                fgets(genre,20,stdin);
                flag = receveAndCheckSTRING(genre);
                if (flag) cout <<"O genero da musica eh constituido por characteres invalidos. Digite novamente."<<endl;
            }
            cout<<endl<< "o id eh "<< id <<endl<< "o titulo eh "<< title <<endl<< "o genero eh "<< genre<<endl;


            getch();
        break;
        //Search Music
        case 3:
            cout<<endl<<"Funcao de Procurar uma Musica, aperte ENTER para prosseguir.";
            getchar();
        break;
        //Remove Music
        case 4:
            cout<<endl<<"Funcao de Remover uma Musica nao implementada ='[, aperte ENTER para prosseguir.";
            getch();
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
                //case 1
            case 49:
                menu = 1;
            break;
                //case 2
            case 50:
                menu = 2;
            break;
                //case 3
            case 51:
                menu = 3;
            break;
                //case 4
            case 52:
                menu = 4;
            break;
                //case 5
            case 53:
                menu = 5;
            break;
                //case 6
            case 54:
                menu = 6;
            break;
            //Down arrow
            case 80:
                if(menu!=TAM) menu++;
                //If it is in the border, jump to the other side
                else menu = 1;
            break;

            //Up arrow
            case 72:

                if(menu!=1) menu--;
                //If it is in the border, jump to the other side
                else menu = 6;
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

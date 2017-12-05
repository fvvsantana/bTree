#include <iostream>
#include <istream>
//#include <windows.h>
//#include <conio.h>
#include "library.hpp"

using namespace std;

/*//Change the statements' color
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

*/
int main(int argc, char *argv[]){

    //menu
    Library lib;

    Song song1, song2, song3, song4;

    /*song1.id = 326;
    song1.title = "A chuva";
    song1.genre = "molhado";

    song2.id = 5144;
    song2.title = "O sol";
    song2.genre = "quente";

    song3.id = 215;
    song3.title = "A lua";
    song3.genre = "queijo";

    song4.id = 9;
    song4.title = "O terra";
    song4.genre = "minhoca";

    lib.insertSong(song1);
    lib.insertSong(song2);
    lib.insertSong(song3);
    lib.insertSong(song4);*/

    lib.generateIndex();

    lib.showBTree();

    song1 = lib.searchSong(5144);

    cout << song1.title << ", " << song1.genre << '\n';



    /*int c,menu=1,TAM=6;

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
    TrocaCor(15);*/
    return 0;
}

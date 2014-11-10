//Programa "Buscar Objetos Escondidos"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <iomanip>
//declaraciones de constantes y de variables globales
using namespace std;
const int n = 10;
int ganar = 0;
int intentos = 50;
//prototipos de funciones
void llenarvacio(char);
void imprimir( char );
void ingresar(char, char, int , int, int);
bool limite(int, int , int, int);
bool chocaPalabra(char, int, int, int, int);
void verificaEspacio(char,char, int, int);
void mostrarCampos( char, char, int, int, bool);
void verifica(char, char, int, int, char, int);
void revisaMatriz(char, char);

// verifica si los objetos a insertar chocaran con otro
bool chocaPalabra(char valores[n][n], int fil, int col, int tam, int orientacion){
    bool choca = false;

    switch(orientacion)
        {
        case 0 : for(int i = 0; i < tam; i++){
                    if(valores[fil + i][col] != '~')
                        choca = true;
                }
        case 1 : for(int j = 0; j < tam; j++){
                    if(valores[fil][col + j] != '~')
                       choca = true;
                }
        }
    return choca;
}
//llena la matriz con el caracter '~'
void llenarvacio(char valores[n][n]){

    for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                    valores[i][j] = '~';
        }
    }
}
//imprime la matriz, se imprime tambien coordenadas para facilitarle al usuario la lectura de la matriz
void imprimir(char valores[n][n]){
    cout << "    0    1    2    3    4    5    6    7    8    9" << endl;

    for (int i = 0; i < n; i++){
        cout << i << " ";
            for ( int j = 0; j < n; j++){
                cout << "[ " << valores[i][j] << " ]";
                }
    cout << endl;
    }
}
//ingresa los objetos a la matriz
void ingresar(char valores[n][n], char palabra[], int fil, int col, int orientacion){

      int tam = strlen(palabra);
      bool des = limite(fil, col, tam, orientacion);
      bool choca = chocaPalabra(valores, fil,  col,  tam,  orientacion);

      if (des or choca) //si se desborde == true (osea se sale) vuelve a llamar a la función ingresar con otra fila, columna y orientación
        ingresar(valores, palabra, rand() % 10, rand () % 10, rand() % 2);

      else{ //sino ingresa la palabra

        switch (orientacion)
         {

         case 0: for (int i = 0; i < tam; i++)
                    valores[fil+i][col] = palabra[i];
                 break;

         case 1: for (int i = 0; i < tam; i++)
                    valores[fil][col+i] = palabra[i];
                 break;

         default: orientacion = rand() % 2;
                 break;
         }
      }

  }
//verifica si los objetos se saldran de la matriz
bool limite(int fil, int col, int tam, int orientacion){

    bool salida = true;
    switch (orientacion)
     {
     case 0: if (fil + tam < n) //0 es vertical
             salida = false;
             break;

     case 1: if (col + tam < n) //1 es horizontal
             salida = false;
             break;

     default:return true;
             break;
     }
  return salida;
}
//revisa los espacios para verificar si estos poseen algo para mostrar tambien se carga el contador ganar que acumula las encontradas
void verificaEspacio( char matrizUsuario[n][n], char valores[n][n], int i, int j){ //variable hay es para saber si en las opciones marcadas por el usuario existe alguna letra
        if (valores[i][j] != '~' and matrizUsuario[i][j] == '~'){
                matrizUsuario[i][j] = 'X';
                ganar++; //contador que indica cada acierto de los objetos
        }
        else if (matrizUsuario[i][j] == '~'){ //instruccion que hace que las casillas vayan desapareciendo las que no contengan letras
            matrizUsuario[i][j] = ' ';

        }
        else if (matrizUsuario[i][j] != '~'){ //delimita si el usuario digita la misma casilla o si bien digita un numero que exceda la matriz
            cout << "Error, ya se mostró esa casilla ó digitó casilla incorrecta" << endl << "Digite otra diferente " << endl << endl;
            intentos++; //aumenta un contador para que el usuario no pierda un intento si se equivoca y pone un numero que ya ingreso
        }
}
//cuando se encuentra una palabra revisa si esta va horizontal o vertical para despues hacer la impresion
void mostrarCampos(char valores[n][n],char matrizUsuario[n][n],int fil,int col,char valor,int orientacion){
    while(valores[fil][col] == valor){
            matrizUsuario[fil][col] = valores[fil][col];
            if(orientacion == 0)
                fil++;
            else if (orientacion == 1)
                col++;
    }
}
//se muestra la 'X'de que encontro una letra del objeto, comparando las dos matrices
void verifica(char valores[n][n],char matrizUsuario[n][n],int fil,int col,char valor,int orientacion){
    bool mostrar = true;

    switch(orientacion)
    {
        case 0 : for(int i = fil; valores[i][col] == valor; i++){
                    if(valores[i][col] == valor and matrizUsuario[i][col] != 'X'){
                        mostrar = false;
                 break;
                    }
                 }

        case 1 : for(int i = col; valores[fil][i] == valor; i++){
                    if(valores[fil][i] == valor and matrizUsuario[fil][i] != 'X'){
                        mostrar = false;
                 break;
                    }
                 }
    }

    if(mostrar){
        mostrarCampos(valores, matrizUsuario, fil, col, valor, orientacion);
    }
}
//asigna los valores de la matriz oculta y las guarda en un contador
void revisarMatriz(char valores[n][n], char matrizUsuario[n][n]){

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){

            if(valores[i][j] != '~' and matrizUsuario[i][j] == 'X' and valores[i - 1][j] != valores[i][j]  and valores[i][j - 1] != valores[i][j]){

                char valor = valores[i][j];

                if(valores[i][j + 1] == valor and  matrizUsuario[i][j + 1] == 'X'){
                    verifica(valores,matrizUsuario,i,j,valor, 1);
                }
                else if (valores[i + 1][j] == valor  and matrizUsuario[i + 1][j] == 'X'){
                    verifica(valores,matrizUsuario,i,j,valor, 0);
                }
            }
        }
    }
}
//cuerpo principal del programa
int main(){
    char matriz[n][n];
    char matrizUsuario[n][n];
    char valores [n][n];
    char candelabro[] = "CCCCC";
    char reloj[] = "RR";
    char espejo[] = "EEE";
    char anteojos[] = "AA";
    char nave[] = "NNNN";
    srand(time(NULL));
    char desea;
    int i = 0;
    int j = 0;
    bool mostrar;

    cout << "Bienvenido al programa Buscar Objetos Escondidos, ¿desea jugar? (S / N)"; //mensaje de bienvenida
    cin >> desea;
    //inicio de programa y llamada de variables
    while (desea == 'S' || desea == 's')
    {
        system("cls");
        llenarvacio(matriz);
        llenarvacio(matrizUsuario);
        ingresar(matriz, candelabro, rand() % 10, rand () % 10, rand() % 2);
        ingresar(matriz, reloj, rand() % 10, rand () % 10, rand() % 2);
        ingresar(matriz, reloj, rand() % 10, rand () % 10, rand() % 2);
        ingresar(matriz, espejo, rand() % 10, rand () % 10, rand() % 2);
        ingresar(matriz, espejo, rand() % 10, rand () % 10, rand() % 2);
        ingresar(matriz, anteojos, rand() % 10, rand () % 10, rand() % 2);
        ingresar(matriz, anteojos, rand() % 10, rand () % 10, rand() % 2);
        ingresar(matriz, nave, rand() % 10, rand () % 10, rand() % 2);

        imprimir(matrizUsuario);

        while (intentos > 0 and ganar != 23)
        {
            cout << endl;
            cout << endl;

            cout << "Digite el numero de casilla correspondiente a fila " << endl;
            cin >> i;
            cout << "Digite el numero de casilla correspondiente a columna " << endl;
            cin >> j;
            system("cls");
            verificaEspacio(matrizUsuario, matriz, i, j); //llamada de funciones
            revisarMatriz(matriz,matrizUsuario);
            imprimir(matrizUsuario);

            cout << endl;

            --intentos;
            cout << "Le quedan " << intentos << " intentos";
        }
        //contador de intentos
        intentos = 50;
        cout << endl << endl << "Encontró " << ganar << " de 23 objetos" << endl;

        if (ganar == 23)
        {
            cout << endl << "GANASTE!!" << endl << "Eres un excelente buscador " << endl << endl;

        } else {

            cout << "No lograste encontrar todos los objetos" << endl << endl;
            cout << "Solución del Juego " << endl << endl;
            imprimir(matriz);
            cout << endl << endl;
        }

        ganar = 0;
        cout << "¿Desea jugar otra vez? (S/N)" << endl;
        cin >> desea;
    }

    return 0;
    //fin del programa
}

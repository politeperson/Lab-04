#include <iostream>
#include "header-recursivo.h"//declaro mis funciones en el header
using namespace std;
/*Ejercicio 1: crear una funcion recursiva que imite un for */
void fori(int n){
  if(n == 0)
    return;
  cout << i <<endl;
  ++i;
  return fori(--n);
}
/*ejercicio 2: crear una funcion recursiva que 
imprima todos los numeros del 0 al n-1*/
void crece(int n){
  if(n == 0)
    return;
  crece(--n);
  cout << n << " ";
}
/*ejercicio 3: crear una funcion recursiva que imprima los 
numeros desde el n-1 hasta 0*/
void decrece(int n){
  if(n == 0)
    return;
  cout << n - 1 << " ";
  return decrece(--n);
}
/*Ejercicio 4: hacer una funcion recursiva que verifique
  si un numero es primo*/
void primo(int n){
  if(n == 1){
    cout << "NO" << endl;
    return;
  }
  if(j == n){
    cout << "YES" << endl;
    return;
  }
  if(n%j==0){
    cout << "NO" << endl;
    return;
  }
  ++j;
  return primo(n);
}
int main(){
  cout << "Ejercicio 1" << endl;
  fori(5);
  cout << "Ejercicio 2" << endl;
  crece(5);
  cout << endl;
  cout << "Ejercicio 3" << endl;
  decrece(5);
  cout << endl;
  cout << "Ejercicio 4" << endl;
  primo(5);
  cout << endl;
  return 0;
}

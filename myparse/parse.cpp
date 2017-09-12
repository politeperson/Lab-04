/*
Ejercicio 4: Hacer un programa que resuelva operaciones logicas con n <= 4
variables, ejm: A&B(C|D)^~A
*/
/*NOTA: Lamentablemente no pude terminar el trabajo, pero todo es mejor que cero, asi que le muestro lo que
 pude hacer*/
#include <iostream>
using namespace std;
/*AQUI TENGO MIS FUNCIONES LOGICAS NOT OR AND Y XOR, EN LAS CUALES PASO 
UN ARRAY POR REFERNCIA QUE SERA EL RESULTADO DE OPERAR EN EL CASO DE NOT
 SOLO UNA EXPRESION PERO EN EL CASO DEL RESTO CON DOS ARRAYS */
void NOT(bool *result, bool a[], int size){
  for(int i = 0; i < size; i++)
    result[i] = !a[i];
}
void OR(bool *result, bool a[], bool b[], int size){
  for(int i = 0; i < size; i++)
    result[i] = a[i] || b[i];
}
void AND(bool *result, bool a[], bool b[], int size){
  for(int i = 0; i < size; i++)
    result[i] = a[i] && b[i];
}
void XOR(bool *result, bool a[], bool b[], int size){
  for(int i = 0; i < size; i++)
    result[i] = a[i] xor b[i];
}
/*###################################################################*/

/*######## AQUI TENGO MI FUNCIONN QUE VERIFICA SI LA EXPRESIÓN ES CORRECTA ############*/
bool verificar(string operacion){
  if(operacion[operacion.size()-1] == '|' || operacion[operacion.size()-1] == '&' || operacion[operacion.size()-1] == '^'){
    return true;
  }
  if(operacion[operacion.size()-1] == '~')//VERIFICO QUE AL FINAL DE LA EXPRESION NO TENGA UN ERROR COMO ESTE "A&A~"
    return true;
  if(operacion[operacion.size()-1] == 'A' || operacion[operacion.size()-1] == 'B' || operacion[operacion.size()-1] == 'C' || operacion[operacion.size()-1] == 'D'){//verifico que al final de mi expresion no haya "A&AB"
    if(operacion[operacion.size()-2] == 'A' || operacion[operacion.size()-2] == 'B' || operacion[operacion.size()-2] == 'C' || operacion[operacion.size()-2] == 'D'){
      return true;
    }
  }
  int paren = 0;//esta variable es para contar el numero de parentesis
  for(int i = 0; i < operacion.size(); i++){
    if(operacion[i] == '~'){//para verificar que no haya errores como este: A~&A
      if(operacion[i + 1] == '&' || operacion[i + 1] == '|' || operacion[i+1] == '^'){
	return true;
      }
    }
    if(operacion[i] == '(')
      if(operacion[i+1] == ')')
	return true;//para verificar que no haya errores como este: A&()|B

    if(operacion[i] == ')')
      if(operacion[i+1] == '(')
	return true;//para verificar que no haya errores como este: (A|B)(A|A)

    if(operacion[i] == '(' || operacion[i] == ')')
      paren++;//aqui cuento el numero de parentesis
    
    if(operacion[i] == 'A' || operacion[i] == 'B' || operacion[i] == 'C' || operacion[i] == 'D'){
      if(operacion[i+1] == 'A' || operacion[i+1] == 'B' || operacion[i+1] == 'C' || operacion[i+1] == 'D'){
	return true;//para verificar que no haya errores como este: AA&B
      }
      else if(operacion[i+1] == '(')
	return true;//para verificar que no haya errores como este: A(B|C)
      else if(operacion[i+1] == '~')
	return true;//para verificar que no haya errores como este: A~&B
    }
    if(operacion[i] == '&' || operacion[i] == '|' || operacion[i] == '^'){//para verificar que no haya errores como este: A&&A
      if(operacion[i + 1] == '&' || operacion[i + 1] == '|' || operacion[i+1] == '^'){
	return true;
      }
    }
  }
  if(paren % 2)//si el numero de parentesis es impar entonces faltan parentesis de cerrada o salida
    return true;
}


int main(){
  string operacion;
  cin >> operacion;
  if(verificar(operacion)){//si la expresion esta mal envio el mensaje de error y cierro el programa
    cout << "La expresion esta mal planteada" << endl;
    return 0;
  }
  int vars[] = {0,0,0,0} , vars_size = sizeof(vars)/sizeof(vars[0]),num_vars=0,total_vars=0;//creo un array donde pongo todas mis variaables{A,B,C,D},una variable para contar el numero de variables
  for(int i = 0; i < operacion.size(); i++){ //por cada A,B,C o D que encuentre le sumo un valor a su posicion en vars
      if(operacion[i] == 'A')
	vars[0]++;
      if(operacion[i] == 'B')
	vars[1]++;
      if(operacion[i] == 'C')
	vars[2]++;
      if(operacion[i] == 'D')
	vars[3]++;
    }
    /*Aqui cuento el numero de variables que hay*/
  for(int i = 0; i < vars_size; i++)
    (vars[i] != 0)?num_vars++,total_vars+=vars[i]:num_vars=num_vars;/*y el total de variables*/
  
  bool ecuation[total_vars][1 << num_vars];//mi matriz de toda la expresion
  bool mat[num_vars][1 << num_vars];//mi matriz de tabla de verdad note que 1 << num_vars = 2^num_vars
  bool result[1 << num_vars];
  int aux_1;
  int aux_4 = 0;
  for(int i = 0; i < 1 << num_vars; i++){//aqui asigno los valores en binario que tomaran mis variables en la tabla logica
    aux_1 = i;
    result[i] = 0;
    for(int j = 0; j < num_vars; j++){
      mat[j][i] = aux_1 % 2;
      aux_1 /= 2;
    }
  }
  int aux_2 = 0,aux_3 = 0;
  int prior[total_vars],priority=0;

  
  for(int i = 0; i < operacion.size(); i++){//aqui asigno los valores para mi tabla logica de la expresion 
    if(operacion[i] == 'A'){
      for(int p = 0; p < 1 << num_vars ; p++)
	ecuation[aux_4][p] = mat[0][p];
      aux_4++;
    }
    else if(operacion[i] == 'B'){
      for(int p = 0; p < 1 << num_vars ; p++)
	ecuation[aux_4][p] = mat[1][p];
      aux_4++;
    }
    else if(operacion[i] == 'C'){
      for(int p = 0; p < 1 << num_vars ; p++)
	ecuation[aux_4][p] = mat[2][p];
      aux_4++;
    }
    else if(operacion[i] == 'D'){
      for(int p = 0; p < 1 << num_vars ; p++)
	ecuation[aux_4][p] = mat[3][p];
      aux_4++;
    }
  }
  
  for(int i = 0; i < operacion.size(); i++){/*Aqui le asigno prioridades a mi array de prioridades si hay un parentesis la prioridad aumenta*/
    if(operacion[i] == '('){
      priority++;
    }
    if(operacion[i] == ')'){
      priority--;
    }
    if(operacion[i] == 'A' || operacion[i] == 'B' || operacion[i] == 'C' || operacion[i] == 'D'){
      prior[aux_3] = priority;
      aux_3++;
    }
  }  

  for(int i = 1; i < operacion.size(); i++){//esta es la unica operacion que pude realizar hice la negación a cada una de las variables
    if(operacion[i] == 'A' || operacion[i] == 'B' || operacion[i] == 'C' || operacion[i] == 'D'){
      if(operacion[i-1] == '~'){
	for(int k = 0; k < 1 << num_vars; k++){
	  ecuation[aux_2][k] = !ecuation[aux_2][k];
	}
      }
      aux_2++;
    }
  }
  /*en esta sección simplemente imprimo lo que pude conseguir*/
  cout << "Mostrando las prioridades de mis variables en la operacion\n";
  cout << "######################################################################" << endl;
  for(int i = 0; i < total_vars; i++){
    cout << prior[i] << " ";
  }
  cout << endl<< "#########################################################################"<<endl;
  cout << "\nMostrando la tabla de verdad de cada una de mis variables: \n";
  cout << "############################################################################\n";
  for(int i = 0; i < 1 << num_vars; i++){
    for(int j = 0; j <  num_vars ; j++){
      cout << mat[j][i] << " ";
    }
    cout << "\n";
  }
  cout << "###############################################################################\n";
  cout << endl;
  cout << "Mostrando todas las tablas de mis variables en la expresion: \n";
  cout << "##################################################################\n";
  for(int i = 0; i < total_vars; i++){
    for(int j = 0; j < 1 << num_vars; j++){
      cout << ecuation[i][j] << " ";
    }
    cout << endl;
  }
  cout << "##################################################################\n";
  return 0;
}

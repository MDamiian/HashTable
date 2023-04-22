#include <iostream>

#include "menu.hpp"
#include "student.hpp"
#include "hashT.hpp"

using namespace std;

void Menu::mainMenu(HashT<Student>& myTable) {
  char myOption;
  Student myStudent;
  long int myLInt;
  string myString;
  float myFloat;
  HashT<Student>::Position position;

  do {
    system("cls");
    cout << "[TABLA HASH]" << endl << endl
         << "1) Insertar estudiante" << endl
         << "2) Eliminar estudiante" << endl
         << "3) Recuperar registro de estudiante" << endl
         << "4) Imprimir tabla" << endl
         << "5) Borrar tabla" << endl
         << "6) Guardar" << endl
         << "7) Cargar" << endl
         << "8) Salir" << endl << endl
         << "Seleccione una opcion: ";

    cin >> myOption;
    system("cls");

    switch(myOption) {
      case '1':
        cout << "Introduce el codigo del estudiante: ";
        cin >> myLInt;
        myStudent.setKey(myLInt);
        cin.ignore();

        cout << "Introduce el nombre del estudiante: ";
        getline(cin, myString);
        myStudent.setName(myString);

        cout << "Introduce la carrera del estudiante: ";
        getline(cin, myString);
        myStudent.setCareer(myString);

        cout << "Introduce el promedio del estudiante: ";
        cin >> myFloat;
        myStudent.setAverage(myFloat);
        cin.ignore();

        myTable.insertData(myStudent);
        break;

      case '2':
        cout << "Introduce el codigo del estudiante a eliminar: ";
        cin >> myLInt;
        myTable.deleteData(myLInt);
        cin.ignore();
        break;

      case '3':
        cout << "Introduce el codigo del estudiante: ";
        cin >> myLInt;
        position = myTable.findData(myLInt);
        cin.ignore();

        if(!position) {
          cout << "El estudiante con codigo " << myLInt
               << " no se encuentra en la tabla" << endl << endl;
          }

        else {
          cout << "Registro encontrado: "
               << myTable.retrieve(position).toString() << endl << endl;
          }

        break;

      case '4':
        cout << myTable.toString() << endl;
        break;

      case '5':
        myTable.deleteAll();
        break;

      case '6':
          myTable.writeToDisk();
        break;

      case '7':
          myTable.readFromDisk();
        break;
      }

    system("pause");
    }
  while(myOption != '8');
  }

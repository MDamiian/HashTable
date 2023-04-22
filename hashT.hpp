#ifndef HASHT_HPP_INCLUDED
#define HASHT_HPP_INCLUDED

#include <iostream>
#include <string>
#include <exception>
#include <fstream>

template <class T, int ARRAYSIZE = 97>
class HashT {
    ///\Node
    ///************************
  private:
    class Node {
      private:
        T data;
        Node *next;

      public:
        Node();
        Node(const T &);
        T getData() const;
        Node *getNext() const;

        void setData(const T &);
        void setNext(Node *);
      };
    ///\ExceptionHash
  public:
    class ExceptionHash : public std::exception {
      private:
        std::string msg;

      public:
        explicit ExceptionHash(const char *message) : msg(message) {}

        explicit ExceptionHash(const std::string &message) : msg(message) {}

        virtual ~ExceptionHash() throw() {}

        virtual const char *what() const throw() {
          return msg.c_str();
          }
      };

    ///\HashT
    ///************************
  private:
    Node **hashTable;
    unsigned int sizeTable;
    int hashFuntion(const long int &) const;

  public:
    typedef Node *Position;

  public:
    HashT();
    ~HashT();
    void insertData(const T &);
    void deleteData(const long int &);
    Node *findData(const long int &);
    T retrieve(Node *) const;
    std::string toString() const;
    void deleteAll();
    void writeToDisk();
    void readFromDisk();
  };

///\Node
///*********************************************************
template <class T, int ARRAYSIZE>
HashT<T, ARRAYSIZE>::Node::Node() : data(), next(nullptr) {}

template <class T, int ARRAYSIZE>
HashT<T, ARRAYSIZE>::Node::Node(const T &object) : data(object), next(nullptr) {}

template <class T, int ARRAYSIZE>
T HashT<T, ARRAYSIZE>::Node::getData() const {
  return data;
  }

template <class T, int ARRAYSIZE>
typename HashT<T, ARRAYSIZE>::Node *HashT<T, ARRAYSIZE>::Node::getNext() const {
  return next;
  }

template <class T, int ARRAYSIZE>
void HashT<T, ARRAYSIZE>::Node::setData(const T &object) {
  data = object;
  }

template <class T, int ARRAYSIZE>
void HashT<T, ARRAYSIZE>::Node::setNext(Node *n) {
  next = n;
  }

///\HashT
///************************************************************
template <class T, int ARRAYSIZE>
HashT<T, ARRAYSIZE>::HashT() : hashTable(nullptr), sizeTable(0) {
  hashTable = new Node *[ARRAYSIZE];

  if (!hashTable) {
    throw ExceptionHash("Memoria no disponible, HashT()");
    }

  for (int i = 0; i < ARRAYSIZE; i++) {
    hashTable[i] = nullptr;
    }
  }

template <class T, int ARRAYSIZE>
HashT<T, ARRAYSIZE>::~HashT() {
  deleteAll();
  delete[] hashTable;
  hashTable = nullptr;
  }

template <class T, int ARRAYSIZE>
int HashT<T, ARRAYSIZE>::hashFuntion(const long int &key) const {
  return key % ARRAYSIZE;
  }

template <class T, int ARRAYSIZE>
void HashT<T, ARRAYSIZE>::insertData(const T &object) {
  Node *aux = new Node(object);

  if (!aux) {
    throw ExceptionHash("Memoria no disponible, insertData()");
    }

  int myInt;
  myInt = aux->getData().getKey();
  myInt = hashFuntion(myInt);

  aux->setNext(hashTable[myInt]);
  hashTable[myInt] = aux;
  sizeTable++;
  }

template <class T, int ARRAYSIZE>
void HashT<T, ARRAYSIZE>::deleteData(const long int &key) {
  int index = hashFuntion(key);
  Node* current = hashTable[index];
  Node* previous = nullptr;

  while (current) {
    if (current->getData().getKey() == key) {
      if (!previous) {
        hashTable[index] = current->getNext();
        }
      else {
        previous->setNext(current->getNext());
        }
      delete current;
      sizeTable--;
      return;
      }

    previous = current;
    current = current->getNext();
    }
  }

template <class T, int ARRAYSIZE>
typename HashT<T, ARRAYSIZE>::Node *HashT<T, ARRAYSIZE>::findData(const long int &key) {
  int myInt = hashFuntion(key);
  Node *aux(hashTable[myInt]);

  while (aux and aux->getData().getKey() != key) {
    aux = aux->getNext();
    }

  return aux;
  }

template <class T, int ARRAYSIZE>
T HashT<T, ARRAYSIZE>::retrieve(Node *position) const {
  return position->getData();
  }

template <class T, int ARRAYSIZE>
std::string HashT<T, ARRAYSIZE>::toString() const {
  std::string result;

  for (int i = 0; i < ARRAYSIZE; i++) {
    if (hashTable[i]) {
      result += std::to_string(i) + ": ";
      }

    Node *aux = hashTable[i];
    while (aux) {
      result += aux->getData().toString();
      result += "\n   ";

      aux = aux->getNext();
      }

    if (hashTable[i]) {
      result += "\n";
      }
    }
  return result;

  }

template <class T, int ARRAYSIZE>
void HashT<T, ARRAYSIZE>::deleteAll() {
  if (sizeTable > 0) {
    for (int i = 0; i < ARRAYSIZE; i++) {
      Node *aux = hashTable[i];
      while (aux) {
        Node *tmp = aux;
        aux = aux->getNext();
        delete tmp;
        sizeTable--;
        }

      hashTable[i] = nullptr;
      }
    }
  }

template <class T, int ARRAYSIZE>
void HashT<T, ARRAYSIZE>::writeToDisk() {
  std::ofstream myFile("data.bin", std::ios::binary | std::ios::out);

  if(!myFile.is_open()) {
    std::cerr << "No se pudo abrir el archivo" << std::endl;
    }

  for(int i(0); i < ARRAYSIZE; i++) {
    Node* aux(hashTable[i]);

    while(aux) {
      T data(aux->getData());
      myFile.write((char*)&data, sizeof(T));
      aux = aux->getNext();
      }
    }
  myFile.close();
  }

template <class T, int ARRAYSIZE>
void HashT<T, ARRAYSIZE>::readFromDisk() {
  std::ifstream myFile("data.bin", std::ios::binary | std::ios::in);

  if(!myFile.is_open()) {
    std::cerr << "No se pudo abrir el archivo" << std::endl;
    }

  deleteAll();

  T data;

  while(myFile.read((char*)&data, sizeof(T))) {
    insertData(data);
    }

  myFile.close();
  }

#endif // HASHT_HPP_INCLUDED

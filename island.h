
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;



class FileNode{
        public:
        string fileName;
        FileNode* next;

};

class FileList {
private:
    FileNode* head;

public:
      FileList(){
        head = nullptr;
        }

   
    bool isValid(string file)
    {
        FileNode* node = head;
        while(node != nullptr){
            if(node->fileName != file == 0){
                return true;
            }
            node = node->next;
        }
        return false;
    }

    void addTheFile(string file) {
        FileNode* node = head;
        FileNode* newHead = new FileNode;
        newHead->fileName = file;
        while(node != nullptr){
            if(node->next == nullptr){
                node->next = newHead;
                return;
            }
            node = node->next;
        }
        head = newHead;
    }
    void deleteFile(const string& file){
        FileNode* node = head;
        FileNode* prevNode = node;
        
        if(head->fileName == file){
            head = head->next;
            delete prevNode;
            return;
        }

        while(node != nullptr){
            if(node->fileName == file){
                prevNode->next = node->next;
                delete node;
                return;
            }
            node = node->next;
        }
    }


   
};



class Node{
private:
    int island;
    Node * next;

public:
    //Constructor
    Node(int val){
        island = val;
        next = nullptr;
    }

    Node(int val, Node* nxt){
        island = val;
        next = nxt;
    }


    int getIsland() {
        return island;
    }

    Node * getNext(){
        return next;
    }

    void setIsland(int val){
        island = val;
    }

    void setNext(Node* nxt){
        next = nxt;
    }

};

class MyList{
private:
    Node* head;

public:

    MyList(){
        head = nullptr;
    }

    void setHead(Node*pr){
        head = pr;
    }
    Node * getHead(){
        return head;
    }

    void insert(int val){

        Node* temp = new Node(val, nullptr);
        Node* curr = head;
        Node* prev = nullptr;

        while(curr!= nullptr){
            if(curr->getIsland() == val){
                printf("Ferry ride already added!\n");
                return;
            }
            prev = curr;
            curr = curr->getNext();
        }
        if(prev == nullptr){
            head = temp;
        }
        else{
            prev->setNext(temp) ;
        }

    }

    void remove(int v1){

        Node * curr = head;
        Node * prev = nullptr;
        while(curr != nullptr && curr->getIsland() != v1){
            prev = curr;
            curr = curr->getNext();
        }
        if(curr == nullptr){
            printf("Ferry ride does not exist\n");
            return;
        }
        //if node to delete is at head of list
        if(prev == nullptr){
            prev = curr->getNext();
            delete curr;
            head = prev;
        }

        else{
            prev->setNext(curr->getNext());
            delete curr;
        }
    }

    int getListLength(){
        int total = 0;
        Node* tmp = head;

        while(tmp != nullptr){
            total++;
            tmp = tmp->getNext();
        }

        return total;
    }

    int getNthElem(int n){
        int curr = 0;
        Node * temp = head;
        while(temp != nullptr && curr != n){
            curr++;
            temp = temp->getNext();
        }

        if(temp == nullptr)
            return -999;

        else{
            return temp->getIsland();
        }
    }

    void printList(){
            Node* temp = head;
            while(temp != NULL){
                printf("%d  ", temp->getIsland());
                temp = temp->getNext();
            }
        }

    void printList2(){
    Node* Temp = head;

      while (Temp != nullptr) {
        cout << Temp->getIsland();
        if (Temp->getNext() != nullptr)
            cout << " - ";

         Temp = Temp->getNext();
        }   
      }



    void removeList()
    {
        Node* Temp;
        while (head != nullptr) {
            Temp = head;
            head = head->getNext();
            delete Temp;
        }

    }

    bool isTheListEmpty(){
        if(head == nullptr){
            return true;
        } else{
            return false;
        }
    }


};


class Island{
private:
    MyList *adjacent;
    bool visited;
    int previousLocation;
    int number;


public:
    Island(){
        adjacent = new MyList;
        visited = false;
        previousLocation = -1;
        number = 0;
    }

    MyList* getAdjacent(){
        return adjacent;
    }

    bool getVisited(){
        return visited;
    }

    void setVisited(bool status){
        visited = status;
    }

    int getPreviousLocation(){
          return previousLocation;
      }

    void setPreviousLocation(int pl){
          previousLocation = pl;
      }
    void setNumber(int p1){
      this->number = p1; 
    }

    int getSize(){
      return getAdjacent()->getListLength();
    }

};

class myQueue: public MyList{
private:
    Node* head;
    Node*next;
public:
    myQueue(){}
    void enqueue(int val){
        Node* cur = new Node(val);
        Node* temp  = getHead();
        if(this->getHead() == nullptr) {
            this->setHead(cur);
            return;
        }
        while(temp->getNext() != nullptr){
            temp = temp->getNext();
        }
        temp->setNext(cur);
        return;
    }
    void dequeue(){
            Node* tmp = this->getHead();
            this->setHead(this->getHead()->getNext());
            delete tmp;
        }
    int peak() {
        if(!isTheListEmpty()){
            return getHead()->getIsland();
        }
    }
};

class myStack : public MyList{
public:
    myStack(){}
    void push(int val){
        Node* cur = new Node(val);
        if(getHead() == nullptr){
            setHead(cur);
        } else {
            cur->setNext(getHead());
            setHead(cur);
        }
    }
    void pop(){
        Node *temp = getHead();
        setHead(getHead()->getNext());
        delete temp;
    }
    int top(){
        Node* curNode = this->getHead();
        while(curNode->getNext() != nullptr){
            curNode = curNode->getNext();
        }
        return curNode->getIsland();
    }
};

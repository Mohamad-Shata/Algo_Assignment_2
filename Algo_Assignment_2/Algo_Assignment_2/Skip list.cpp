#include <iostream>
using namespace std;
using namespace std;
const int MAX_LEVEL = 4;


class Player{
private:
    int score;
    int id;
public:
    Player(int id, int score){
        this->score = score;
        this->id = id;
    };
    Player()=default;

    void updateScore(int n){
        score+=n;
    };
    int getScore(){
        return score;
    }
    int getId(){
        return id;
    }




};
struct Node {
    Player data;
    Node** next;
    Node(Player data, int level) {
        this->data = data;
        next = new Node*[level + 1]; //Dynamic allocation
        for (int i = 0; i < level + 1; i++) {
            next[i] = nullptr;
        }
    }
};



class SkipList {
private:
    int size;
    Node* head;
    int currentLevel;
    int calculateLevel(int key) {
        int lvl = 1;
        while (rand() % 2 && lvl < MAX_LEVEL) {
            lvl++;
        }
        return lvl;
    }
public:
    SkipList() {
        size = 0;
        currentLevel = 1;
        Player p1;
        head = new Node(p1, MAX_LEVEL);
        srand(time(nullptr));
    }

    void insert(Player key) {
        Node* current = head;
        Node* update[MAX_LEVEL + 1];
        for (int i = currentLevel; i >= 1; i--) {
            while(current -> next[i] && current->next[i]->data.getScore() < key.getScore()) {
                current = current -> next[i];
            }
            update[i] = current;
        }
        current = current->next[1];
        if (!current || current->data.getScore() != key.getScore()) {
            size++;
            int newlvl = calculateLevel(key.getScore());
            if (newlvl > currentLevel) {
                for (int i = currentLevel + 1; i <= newlvl; i++) {
                    update[i] = head;
                }
                currentLevel = newlvl;
            }
            Node* newnode = new Node(key, newlvl);
            for(int i = 1 ; i<= newlvl; i++) {
                newnode->next[i] = update[i]->next[i];
                update[i]->next[i] = newnode;
            }
            cout<<"inserted player " << key.getId()<<" current score: "<<key.getScore() <<endl;
        }
    }

    void joinGame(Player key){
        if(!search(key)) {

            insert(key);
            return;
        }
        updateScore(key,key.getScore());
    }

    void leaveGame(Player key){
        remove(key);
    }

    void remove(Player key) {
        Node* current = head;
        Node* update[MAX_LEVEL + 1];
        for (int i = currentLevel; i >= 1; i--) {
            while(current -> next[i] && current->next[i] -> data.getScore() < key.getScore()) {
                current = current -> next[i];
            }
            update[i] = current;
        }
        current = current->next[1];
        if (current && current->data.getScore() == key.getScore() && current->data.getId() == key.getId()) {
            for(int i =1 ; i <= currentLevel; i++) {
                if(update[i]->next[i] != current) break;
                update[i]->next[i] = current->next[i];
            }
            while (currentLevel > 1 && head->next[currentLevel] == nullptr) {
                currentLevel--;
            }
            size--;
            delete current;
            cout<<"removed " << key.getId()<<" current score: "<<key.getScore() <<endl;
            //cout<<"removed " << key <<endl;
        }else {
            cout<<"Not found " << key.getId() <<endl;
        }
    }

    bool search(Player key) {
        Node* current = head;
        for (int i = currentLevel; i >= 1; i--) {
            while(current -> next[i] && current->next[i] -> data.getScore() < key.getScore()) {
                current = current -> next[i];
            }

        }
        current = current->next[1];
        if (current && current->data.getScore() == key.getScore() && current->data.getId() == key.getId()) {
            cout<<"Found player " << key.getId()<<" current score: "<<current->data.getScore() <<endl;
           // cout << "Found " << key << endl;
            return true;
        } else {
           // cout<<"Not found player " << key.getId()<<endl;
            //cout << "Not found " << key << endl;
            return false;
        }

    }

    void display() {
        for (int i = 1; i <= currentLevel; i++) {
            Node* current = head->next[i];
            cout << "Level " << i << ":\n";
            while (current) {
                cout << "Player id: "<<current->data.getId()<<" current score: "<< current->data.getScore() << " "<<endl;
                current = current->next[i];
            }
            cout << endl;
        }
    }

    bool updateScore(Player key,int newScore) {
        Node* current = head;
        for (int i = currentLevel; i >= 1; i--) {
            while(current -> next[i] && current->next[i] -> data.getScore() < key.getScore()) {
                current = current -> next[i];
            }
        }
        current = current->next[1];
        if (current && current->data.getScore() == key.getScore()) {
            cout<<"Found player " << key.getId()<<" current score: "<<key.getScore() <<endl;

            Player newPlayer(current->data.getId(),newScore+current->data.getScore());

            remove(current->data);

            insert(newPlayer);

            return true;
        } else {
            cout<<"Not found player " << key.getId()<<endl;

            return false;
        }

    }

    int getSize(){
        return size;
    }


    void topN(int n){

        for (int i = 1; i <= 1; i++) {
            Node* current = head->next[1];
            cout << "Level " << i << ":";
            int stop =0;
            while (current and stop<size-n ) {
                //cout << "Player id: "<<current->data.getId()<<" current score: "<< current->data.getScore() << " "<<endl;
                current = current->next[i];
                stop++;
            }
            while (current) {
                cout << "Player id: "<<current->data.getId()<<" current score: "<< current->data.getScore() << " "<<endl;
                current = current->next[i];
                stop++;
            }


            cout << endl;
        }




    }


};


int main()
{
    SkipList list;
    Player p1(1,200);
    Player p2(2,900);
    Player p4(3,199);
    Player p5(4,201);
   //Player p6(5,990);
    list.joinGame(p1);
    list.joinGame(p2);
    list.joinGame(p4);
    list.joinGame(p5);
   // list.remove(p4);

    list.search(p4);
    list.updateScore(p1,600);
    cout<<"//////////////////////////////////////////////////////////////////////////"<<endl;
    cout<<"Display all players:"<<endl;
    list.display();
//   list.topN(1);





    return 0;
}

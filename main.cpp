#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class ChatRoom {
    public:
    // Transmitir
    virtual void broadcast(string from, string msg)= 0;
};

class Person : public ChatRoom{
        public:
        string              name;
        ChatRoom*           room{nullptr};

        void broadcast(string , string ){};
        Person(string _name) { this->name = _name;}
        void say(string msg) { room->broadcast(name, msg);}
        void receive(string from, string msg) {
            string s{from + ": \"" + msg + "\""};
            cout << "[Chat de " << name << "]" << s << "\n";
        }
    };

class GoogleMeet : public ChatRoom
{
    public:
    vector<Person*>     people;
    // Transmitir
    void broadcast(string from, string msg) {
        for (auto p : people)
            if (p->name != from)
                p->receive(from, msg);
    }
    // Unen al chat 
    void join(Person *p) {
        string join_msg = p->name + " se unio al chat";
        broadcast("room", join_msg);
        p->room = this;
        people.push_back(p);
    }
};

int main() {
    GoogleMeet room;

    Person john("John");
    Person jane("Jane");
    
    room.join(&john);
    room.join(&jane);
    john.say("Jane hiciste la tarea?");
    jane.say("oh, hey john");

    Person simon("Simon");
    room.join(&simon);
    simon.say("Hola a todos!");

    return 0;
}
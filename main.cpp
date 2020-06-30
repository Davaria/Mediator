#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class ChatRoom {
    public:
    // Transmitir
    virtual void broadcast(string from, string msg)= 0;
    // Mensaje
    virtual void message(string from, string to, string msg)= 0;
};

class Person : public ChatRoom{
    public:
    string              name;
    ChatRoom*           room{nullptr};

    void broadcast(string , string ){};
    void message(string , string , string ){};
    Person(string _name) { this->name = _name;}
    
    void say(string msg) { room->broadcast(name, msg);}
    void pm(string to, string msg) { room->message(name, to, msg); }

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
        // p->room = apunta a la clase Google Meet
        p->room = this;
        people.push_back(p);
    }
    // Mensaje
    void message(string from, string to, string msg) {
        auto target = find_if(begin(people), end(people),
        [&](const Person *p) {
            return p->name == to;
        });

        if (target != end(people)) 
            (*target)->receive(from, msg);
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

    jane.pm("Simon", "Me alegro de que nos hayas encontrado, Simon!");

    return 0;
}
/*  
[Chat de John]room: "Jane se unio al chat"
[Chat de Jane]John: "Jane hiciste la tarea?"
[Chat de John]Jane: "oh, hey john"
[Chat de John]room: "Simon se unio al chat"
[Chat de Jane]room: "Simon se unio al chat"
[Chat de John]Simon: "Hola a todos!"
[Chat de Jane]Simon: "Hola a todos!"
[Chat de Simon]Jane: "Me alegro de que nos hayas encontrado, Simon!"
*/

// Entonces, lo que podemos sacar del ejemplo anterior es que tienes un componente central. En este caso, es el GoogleChaty cada persona de la sala de chat tiene una referencia o puntero a eso GoogleChat. Por lo tanto, todos se comunican exclusivamente a través de ese punto o no se comunican directamente.
// No tienen referencias o punteros entre sí, pero aún así, pueden enviar mensajes, por ejemplo, en este caso estoy usando el nombre de una persona que tiene el tipo de clave para pasar el mensaje y la sala de chat es el mediador quien realmente cuida el pegamento. La cosa que une todo.

// Beneficios del patrón de diseño de mediador
// Puede reemplazar cualquier componente en el sistema sin afectar a otros componentes y sistema.
// El patrón de diseño de mediador reduce la complejidad de la comunicación entre los diferentes componentes de un sistema. Promoviendo así el acoplamiento flojo y menos número de subclases .
// Para superar la limitación del Patrón de diseño del observador que funciona en una relación de uno a muchos, el Patrón de diseño de mediador puede emplearse para una relación de muchos a muchos.

// ¿Patrón de diseño de mediador vs fachada?
// El patrón de mediador puede verse como un patrón de fachada multiplexada. En el mediador, en lugar de trabajar con una interfaz de un solo objeto, está creando una interfaz multiplexada entre varios objetos para proporcionar transiciones suaves.

// ¿Patrón de diseño de mediador vs observador?
// - Patrón de diseño de observador = relación uno a muchos
// - Patrón de diseño de mediador = relación de muchos a muchos
// Debido al control centralizado de la comunicación, el mantenimiento del sistema diseñado usando el Patrón de diseño de mediador es fácil.

// Patrones de remitentes y receptores
// Cadena de responsabilidad, comando, mediador y observador, aborde cómo puede desacoplar remitentes y receptores, pero con diferentes compensaciones. La Cadena de responsabilidad pasa una solicitud de remitente a lo largo de una cadena de receptores potenciales. El comando normalmente especifica una conexión emisor-receptor con una subclase. El mediador tiene remitentes y receptores que se refieren indirectamente entre sí. Observer define una interfaz muy desacoplada que permite configurar múltiples receptores en tiempo de ejecución.
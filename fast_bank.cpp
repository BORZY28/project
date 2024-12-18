#include <iostream>
#include <string>
#include <ctime>

using namespace std;
// Я делал
// Класс Client
class Client {
private:
    int id;
    string requestType;
    time_t timestamp;

public:
    Client(int id, const string& requestType) : id(id), requestType(requestType) {
        timestamp = time(nullptr);
    }

    int getId() const { return id; }
    string getRequestType() const { return requestType; }
    time_t getTimestamp() const { return timestamp; }

    void displayInfo() const {
        cout << "ID: " << id << ", Тип запроса: " << requestType 
             << ", Время: " << ctime(&timestamp) << endl;
    }
};

// Класс Operator
class Operator {
private:
    int id;
    bool isBusy;

public:
    Operator(int id) : id(id), isBusy(false) {}
    
    bool getStatus() const { return isBusy; }

    string processRequest(Client* client) {
        isBusy = true;
        cout << "Оператор " << id << " обрабатывает запрос клиента ID " << client->getId() << endl;
        isBusy = false;
        return "Оператор " + to_string(id) + " обрабатал запрос клиента ID " + to_string(client->getId()) + '\n';
    }
};

// Реализация очереди (FIFO)
class Queue {
    Client** data;
    size_t size;

    public:
        Queue() {data = nullptr; size = 0;}
        ~Queue(){delete[] data;}

        void append(Client* client) {
            size += 1;
            Client** tmp = new Client* [size];
            for (size_t i = 0; i < size-1; ++i){
                tmp[i] = data[i];
            }

            tmp[size-1] = client;

            if (data) delete[] data;
            data = tmp;
        }

        void first_remove() {
            size -= 1;
            Client** tmp = new Client* [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = data[i+1];
            }

            if (data) delete[] data;
            data = tmp;
        }


        void out_queue(){
            if (data){
                for(size_t i = 0; i < size; ++i){
                    data[i]->displayInfo();
                }
            }
        }

};

// Реализация дека
class Deque {
    Client** data;
    size_t size;

    public:
        Deque() {data = nullptr; size = 0;}
        ~Deque(){delete[] data;}
        void front_push(Client* client){
            size += 1;
            Client** tmp = new Client* [size];

            if (data){
                for (size_t i = 0; i < size-1; ++i){
                    tmp[i+1] = data[i];
                }
            }
 
            tmp[0] = client;
            if (data) delete[] data;
            data = tmp;
        }
 
        void back_push(Client* client) {
                size += 1;
                Client** tmp = new Client* [size];
                
                if (data) {
                    for (size_t i = 0; i < size-1; ++i){
                        tmp[i] = data[i];
                    }
                }
                tmp[size-1] = client;

                if (data) delete[] data;
                data = tmp;
            }

            void front_pop() {
                size -= 1;
                Client** tmp = new Client* [size];
                for (size_t i = 0; i < size; ++i){
                    tmp[i] = data[i+1];
                }

                if (data) delete[] data;
                data = tmp;
            }

            void back_pop() {
                size -= 1;
                Client** tmp = new Client* [size];
                for (size_t i = 0; i < size; ++i){
                    tmp[i] = data[i];
                }

                if (data) delete[] data;
                data = tmp;
            }

            void out_line(){
            if (data){
                for(size_t i = 0; i < size; ++i){
                    data[i]->displayInfo();
                }
            }
        }
};

// Реализация стека
class Stack {
    string* operations;
    size_t size;

    public:
        Stack() {operations = nullptr; size = 0;}
        ~Stack(){delete[] operations;}

        void push(string oper) {
            size += 1;
            string* tmp = new string [size];
            for (size_t i = 0; i < size-1; ++i){
                tmp[i] = operations[i];
            }

            tmp[size-1] = oper;

            if (operations) delete[] operations;
            operations = tmp;
        }

        void pop() {
            size -= 1;
            string* tmp = new string [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = operations[i+1];
            }

            if (operations) delete[] operations;
            operations = tmp;
        }

        string top() {
            if (operations) return operations[size-1]; 
            else throw std::out_of_range("он пустой");
        } 
};


// Главная функция
int main() {
    Operator* operators[2];
    Stack stack_;
    
    Client client(0, "low");
    Client client_1(1, "high");
    
    Operator operator_(0);
    Operator operator_1(1);
    operators[0] = &operator_;

    cout << stack_.top();
    stack_.push(operators[0]->processRequest(&client_1));
    cout << stack_.top();

    return 0;
}
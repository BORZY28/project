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

    void processRequest(Client* client) {
        isBusy = true;
        cout << "Оператор " << id << " обрабатывает запрос клиента ID " << client->getId() << endl;
        isBusy = false;
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



// // Реализация стека
// class Stack {
// private:
//     struct Node {
//         string operation;
//         Node* next;
//         Node(const string& operation) : operation(operation), next(nullptr) {}
//     };

//     Node* top;

// public:
//     Stack() : top(nullptr) {}

//     ~Stack() {
//         while (top) {
//             Node* temp = top;
//             top = top->next;
//             delete temp;
//         }
//     }

//     void push(const string& operation) {
//         Node* newNode = new Node(operation);
//         newNode->next = top;
//         top = newNode;
//     }

//     string pop() {
//         if (!top) return "";
//         Node* temp = top;
//         string operation = temp->operation;
//         top = top->next;
//         delete temp;
//         return operation;
//     }

//     string peek() const {
//         return top ? top->operation : "";
//     }

//     bool isEmpty() const {
//         return top == nullptr;
//     }

//     void displayStack() const {
//         Node* temp = top;
//         while (temp) {
//             cout << temp->operation << endl;
//             temp = temp->next;
//         }
//     }
// };



// // Класс BankSystem
// class BankSystem {
// private:
//     Queue lowPriorityQueue;
//     Deque highPriorityDeque;
//     Stack history;
//     Operator* operators;
//     int operatorCount;
//     int clientIdCounter;

// public:
//     BankSystem(int operatorCount) : operatorCount(operatorCount), clientIdCounter(1) {
//         operators = new Operator[operatorCount];
//         for (int i = 0; i < operatorCount; ++i) {
//             operators[i] = Operator(i + 1);
//         }
//     }

//     ~BankSystem() {
//         delete[] operators;
//     }

//     void addClient(const string& requestType) {
//         Client* client = new Client(clientIdCounter++, requestType);
//         if (requestType == "high") {
//             highPriorityDeque.addRear(client);
//         } else {
//             lowPriorityQueue.enqueue(client);
//         }
//         history.push("Добавлен клиент ID " + to_string(client->getId()));
//     }

//     void processRequest() {
//         for (int i = 0; i < operatorCount; ++i) {
//             if (!operators[i].getStatus()) {
//                 Client* client = nullptr;
//                 if (!highPriorityDeque.isEmpty()) {
//                     client = highPriorityDeque.removeFront();
//                 } else if (!lowPriorityQueue.isEmpty()) {
//                     client = lowPriorityQueue.dequeue();
//                 }

//                 if (client) {
//                     operators[i].processRequest(client);
//                     history.push("Обработан запрос клиента ID " + to_string(client->getId()));
//                     delete client;
//                     return;
//                 } else {
//                     cout << "Нет запросов для обработки." << endl;
//                     return;
//                 }
//             }
//         }
//         cout << "Все операторы заняты." << endl;
//     }

//     void showQueues() const {
//         cout << "Очередь низкого приоритета:" << endl;
//         lowPriorityQueue.displayQueue();
//         cout << "Очередь высокого приоритета:" << endl;
//         highPriorityDeque.displayDeque();
//     }

//     void showHistory() const {
//         cout << "История операций:" << endl;
//         history.displayStack();
//     }

//     void undoLastOperation() {
//         if (!history.isEmpty()) {
//             string operation = history.pop();
//             cout << "Отмена операции: " << operation << endl;
//         } else {
//             cout << "История операций пуста." << endl;
//         }
//     }
// };

// Главная функция
int main() {
    // // BankSystem bank(2);
    // int choice;

    // do {
    //     cout << "=== Система обслуживания клиентов банка ===" << endl;
    //     cout << "1. Добавить клиента в систему" << endl;
    //     cout << "2. Обработать запрос клиента" << endl;
    //     cout << "3. Просмотреть состояние очередей" << endl;
    //     cout << "4. Показать историю завершенных операций" << endl;
    //     cout << "5. Отменить последнюю операцию" << endl;
    //     cout << "6. Выход" << endl;
    //     cout << "Ваш выбор: ";
    //     cin >> choice;

    //     switch (choice) {
    //     case 1: {
    //         string requestType;
    //         cout << "Введите тип запроса (low/high): ";
    //         cin >> requestType;
    //         bank.addClient(requestType);
    //         break;
    //     }
    //     case 2:
    //         bank.processRequest();
    //         break;
    //     case 3:
    //         bank.showQueues();
    //         break;
    //     case 4:
    //         bank.showHistory();
    //         break;
    //     case 5:
    //         bank.undoLastOperation();
    //         break;
    //     case 6:
    //         cout << "Выход из программы." << endl;
    //         break;
    //     default:
    //         cout << "Неверный выбор. Попробуйте снова." << endl;
    //     }
    // } while (choice != 6);

    // return 0;
    Client client(0, "low");
    Client client_1(1, "high");
    Deque line_1;
    line_1.front_push(&client);
    line_1.front_push(&client_1);
    line_1.out_line();
    line_1.back_push(&client);
    line_1.back_push(&client_1);
    line_1.out_line();
    
    line_1.back_pop();
    line_1.front_pop();
    line_1.out_line();
    


    return 0;
}
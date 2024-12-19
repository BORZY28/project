/*
Borzyaev, Sidorov, Drozdov, ...

██─██─████─███─████
─███──█──█──█──█──█
──█───████──█──█──█
──█───█──█──█──█──█
──█───█──█──█──████
*/

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Класс Client
class Client {
private:
    int id;                                                 // ID клиента
    string requestType;                                     // Тип запроса
    time_t timestamp;                                       // Время

public:
                                                            // конструктор 
    Client(int id, const string& requestType) : id(id), requestType(requestType) {
        timestamp = time(nullptr);
    }
    ~Client(){}                                             // деструктор

                                                            // возврат ID клиента
    int getId() const { return id; }                        
                                                            // возврат типа запроса
    string getRequestType() const { return requestType; }   
                                                            // возврат времени
    time_t getTimestamp() const { return timestamp; }       

                                                            // вывод информации о клиенте
    void displayInfo() const {                              
        cout << "ID: " << id << ", Тип запроса: " << requestType 
             << ", Время: " << ctime(&timestamp) << endl;
    }
};

// Класс Operator
class Operator {
private:
    int id;                                                  // ID оператора
    bool isBusy;                                             // Флаг статуса  оператора(занят/свободен)

public:
    Operator(int id) : id(id), isBusy(false) {}             // конструктор
    ~Operator(){}                                           // деструктор

    // возврат статуса
    bool getStatus() const { return isBusy; }               

                                                            // Запрос клиента: выводится информация о том, кого обрабатвает оператор,
                                                            // возвращается информация о запросе для записи в Steck
    string processRequest(Client* client) {                 
        isBusy = true;                                      
        cout << "Оператор " << id << " обрабатывает запрос клиента ID " << client->getId() << endl;
        isBusy = false;
        return "Оператор " + to_string(id) + " обрабатал запрос клиента ID " + to_string(client->getId()) + '\n';
    }
};

// Реализация очереди (FIFO)
class Queue {
    Client** data;                                          // Массив указателей на клиентов
    size_t size;                                            // Размер массива

    public:
        Queue() {data = nullptr; size = 0;}                 // конструктор
        ~Queue(){delete[] data;}                            // деструктор

                                                            // добавление клиентов в очередь в конец
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
                                                            // удаление первого клиента из  очереди
        void first_remove() {                               
            size -= 1;
            Client** tmp = new Client* [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = data[i+1];
            }

            if (data) delete[] data;
            data = tmp;
        }
                                                            // вывод данных про всех клиентов в очереди
        void out_queue(){                                   
            if (data){                      
                for(size_t i = 0; i < size; ++i){
                    data[i]->displayInfo();
                }
            }
        }

};

// Реализация дека(двухсторонняя очередь)
class Deque {
    Client** data;                                          // Массив указателей на клиентов
    size_t size;                                            // Размер массива

    public:
        Deque() {data = nullptr; size = 0;}                 // конуструктор
        ~Deque(){delete[] data;}                            // деструктор

                                                            // добавление клиента в начало очереди
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
                                                            // добавление клиента в конец очереди
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
                                                            // удаление клиента из начала очереди
        void front_pop() {
            size -= 1;
            Client** tmp = new Client* [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = data[i+1];
            }

            if (data) delete[] data;
            data = tmp;
        }

                                                            // удаление клиента из конца очереди
        void back_pop() {
            size -= 1;
            Client** tmp = new Client* [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = data[i];
            }

            if (data) delete[] data;
            data = tmp;
        }

                                                            // вывод данных про всех клиентов в очереди
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
    string* operations;                                     // массив операций
    size_t size;                                            // размер массива

    public:
        Stack() {operations = nullptr; size = 0;}           // конструктор
        ~Stack(){delete[] operations;}                      // деструктор

                                                            // добавление операции
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
                                                            // удаление последней операции
        void pop() {
            size -= 1;
            string* tmp = new string [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = operations[i+1];
            }

            if (operations) delete[] operations;
            operations = tmp;
        }
                                                            // возврат последней операции
        string top() {
            if (operations) return operations[size-1]; 
            else throw std::out_of_range("он пустой");
        } 
};
//ТЗ: Нужно наши классы объединить в один: BankSystem
//Интерфейс main как раз реализовывается через этот класс, в самом начале main можно создать один объект(например, BankSystem bank)
//То есть есть у нас вариант что пользователь выбрал 1. Добавить клиента 
//Тогда вызываем метод у нашего объекта (что-то типо bank.add_client(...))
//А метод этот будет принимать допустим нашу очередь, данные о клиенте, создавать новый объект типа Client и добавлять в очередь 
//В целом я надеюсь понятно, нужно просто то, что написано в интерфейсе в задании реализовать как функции класса BankSystem, ну и сам интерфейс в main написать 
//Если будут вопросы по реализации или по тому, как работают классы, которые мы написали до этого, можете написать в тг(@Udjin86)

// тесты в main
// int main() {
//     Operator* operators[2];
//     Stack stack_;
    
//     Client client(0, "low");
//     Client client_1(1, "high");
    
//     Operator operator_(0);
//     Operator operator_1(1);
//     operators[0] = &operator_;

//     cout << stack_.top();
//     stack_.push(operators[0]->processRequest(&client_1));
//     cout << stack_.top();

//     return 0;
// }

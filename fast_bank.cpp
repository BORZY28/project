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
        std::string std_id = to_string(id), std_client_id = to_string(client->getId());
        delete client;
        return "Оператор " + std_id + " обрабатал запрос клиента ID " + std_client_id + '\n';
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
    friend class BankSystem;

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
        Client* front_pop() {
            size -= 1;
            Client** tmp = new Client* [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = data[i+1];
            }

            Client* client = data[0];
            if (data) delete[] data;
            data = tmp;
            return client;
        }

                                                            // удаление клиента из конца очереди
        Client* back_pop() {
            size -= 1;
            Client** tmp = new Client* [size];
            for (size_t i = 0; i < size; ++i){
                tmp[i] = data[i];
            }

            Client* client = data[0];
            if (data) delete[] data;
            data = tmp;
            return client;
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
            if (size > 0) 
            {
                size -= 1;
                string* tmp = new string [size];
                for (size_t i = 0; i < size; ++i){
                    tmp[i] = operations[i+1];
                }

                if (operations) delete[] operations;
                operations = tmp;
            }

            else throw std::out_of_range("он пустой");
            
        }
                                                            // возврат последней операции
        string top() {
            if (operations) return operations[size-1]; 
            else throw std::out_of_range("он пустой");
        }
                                                            // Вывод операций
        void out_line()
        {
            if(operations)
            {
                for(size_t i = 0; i < size; ++i)
                {
                    std::cout << operations[i] << std::endl;
                }
            }
        }
};

class BankSystem
{
public:
    ~BankSystem()
    {
        for(size_t i = 0; i < deque.size; ++i)
        {
            delete deque.data[i];
        }
    };

    void add_client(int id, const std::string& requestType)
    {
        Client* client = new Client(id, requestType);
        deque.back_push(client);
    };

    void request_processing()
    {
        std::string operation;
        bool flag = false;
        Client* client = deque.front_pop();

        for(size_t i = 0; i < 5; ++i)
        {
            if(!operators[i].getStatus())
            {
                operation = operators[i].processRequest(client);
                flag = true;
                break;
            }
        }

        if(flag)
            stack.push(operation);
        else
            throw std::invalid_argument("No free operators");
    };

    void show_queue()
    {
        deque.out_line();
    };

    void show_stack()
    {
        stack.out_line();
    }

    void cancel_last_change() 
    {
        stack.pop();
    }

    
private:
    Deque deque;
    Stack stack;
    Operator operators[5] = {Operator(1), Operator(2), Operator(3), Operator(4), Operator(5)};
};
//ТЗ: Нужно наши классы объединить в один: BankSystem
//Интерфейс main как раз реализовывается через этот класс, в самом начале main можно создать один объект(например, BankSystem bank)
//То есть есть у нас вариант что пользователь выбрал 1. Добавить клиента 
//Тогда вызываем метод у нашего объекта (что-то типо bank.add_client(...))
//А метод этот будет принимать допустим нашу очередь, данные о клиенте, создавать новый объект типа Client и добавлять в очередь 
//В целом я надеюсь понятно, нужно просто то, что написано в интерфейсе в задании реализовать как функции класса BankSystem, ну и сам интерфейс в main написать 
//Если будут вопросы по реализации или по тому, как работают классы, которые мы написали до этого, можете написать в тг(@Udjin86)

// тесты в main
int main() {
    BankSystem bank;
    size_t id = 0;


    int choice = 0;

    while (true) {
        cout << "=== Система обслуживания клиентов банка ===\n";
        cout << "1. Добавить клиента в систему\n";
        cout << "2. Обработать запрос клиента\n";
        cout << "3. Просмотреть состояние очередей\n";
        cout << "4. Показать историю завершенных операций\n";
        cout << "5. Отменить последнюю операцию\n" ;
        cout << "6. Выход\n";
        cout << "Ваш выбор: \n";

        cin >> choice;

        switch (choice){
            case 1:
                bank.add_client(id, "Кредит");
                id ++;
                cout << '\n';
            
            
            case 2:
                try{
                    bank.request_processing();
                }
                catch (std::invalid_argument){
                    cout << "Все операторы заняты, нужно подождать\n";
                    cout << '\n';
                }
                
                cout << '\n';
            
            case 3:
                bank.show_queue();
                cout << '\n';
            
            case 4:
                try{
                    bank.show_stack();
                }
                catch (std::out_of_range){
                    cout << "Видимо ещё не было операций\n";
                    cout << '\n';
                }

            
            case 5:
                try{
                    bank.cancel_last_change();
                }
                catch (std::out_of_range){
                    cout << "Видимо ещё не было операций\n";
                    cout << '\n';
                }
                
                
            
            case 6:

                break;
            
            default:
                cout << "\nВведены недопустимые символы\n\n";
        }
    }

    return 0;
}

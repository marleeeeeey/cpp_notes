# javidx9 - Networking in C++: MMO Client/Server, ASIO & Framework Basics - 2020

- [About the course](#about-the-course)
- [Networking in C++ Part #1](#networking-in-c-part-1)
  - [`message_header<T>` - заголовок сообщения](#message_headert---заголовок-сообщения)
  - [`message<T>` - cтруктура для передачи по сети](#messaget---cтруктура-для-передачи-по-сети)
  - [`owned_message<T>` - сообщение с данными об отправителе](#owned_messaget---сообщение-с-данными-об-отправителе)
  - [`thread_safe_queue` - класс для безопасной много поточной работы с очередью](#thread_safe_queue---класс-для-безопасной-много-поточной-работы-с-очередью)
  - [Общая структура клиента и сервера](#общая-структура-клиента-и-сервера)
- [Networking in C++ Part #2](#networking-in-c-part-2)
- [Networking in C++ Part #3](#networking-in-c-part-3)
- [Networking in C++ Part #4](#networking-in-c-part-4)

## About the course

- Author: [javidx9](https://www.github.com/OneLoneCoder)
- [https://github.com/marleeeeeey/network_asio_experience](https://github.com/marleeeeeey/network_asio_experience)

## Networking in C++ Part #1

- https://www.youtube.com/watch?v=2hNdkYInj4g

### `message_header<T>` - заголовок сообщения

- `message_header` - известного размера заголовок с типом сообщения и длиной сообщения.
  - Тип сообщения `T` - это перечисление, которое определяет тип сообщения.
  - Так как это шаблон, пользователь либы может настроить тип сообщения на свой.

```cpp
template <typename T>
struct message_header
{
    T id{};
    uint32_t size = 0; // size_t is not used because it is platform dependent.
};
```

### `message<T>` - cтруктура для передачи по сети

- Стурктура `message<T>` содержит
  - `message_header`
  - Тело сообщения `body` - это массив байтов, который содержит данные сообщения.
  - Вспомогательные методы для удобной сериализации и десериализации данных в сообщение.

```cpp
template <typename T>
struct message
{
    message_header<T> header{};
    std::vector<uint8_t> body; // bytes
    // ... methods
    template <typename DataType>
    friend message<T>& operator<<(message<T>& msg, const DataType& data);
    template <typename DataType>
    friend message<T>& operator>>(message<T>& msg, DataType& data)
}
```

### `owned_message<T>` - сообщение с данными об отправителе

- Сервер должен понимать, от какого клиента пришло сообщение.
- `owned_message<T>` помимо сообщения содержит указатель на соединение, от которого пришло сообщение.

```cpp
template <typename T>
struct owned_message
{
    std::shared_ptr<connection<T>> remote = nullptr; // Server needs to identify which client sent the message.
    message<T> msg;

    // Overload the << operator for std::cout compatibility.
    friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg)
    {
        os << msg.msg;
        return os;
    }
};
```

### `thread_safe_queue` - класс для безопасной много поточной работы с очередью

```cpp
template <typename T>
class thread_safe_queue
{
public:
    thread_safe_queue() = default;
    thread_safe_queue(const thread_safe_queue<T>&) = delete;
    virtual ~thread_safe_queue() { clear(); }
public:
    const T& front();                   // <=== Main methods to work with the queue.
    const T& back();                    // <
    void push_back(const T& item);      // <
    void push_front(const T& item);     // <
    T pop_front();                      // <
    T pop_back();                       // <

    bool empty();
    size_t count();
    void clear();
    void wait();                        // Wait until the queue is not empty
protected:
    std::mutex muxQueue;                // Mutex to protect the double-ended queue.
    std::deque<T> deqQueue;             // Double-ended queue to hold the data.
    std::condition_variable cvBlocking; // Condition variable to block the thread until the queue has data.
    std::mutex muxBlocking;             // Mutex to protect the condition variable.
};
```

### Общая структура клиента и сервера

- `thread_safe_queue` - очередь, доступ к которой шариться между `connection` и `client`/`server`.
- `connection` responsabilities
  - Абстргирует детали и зависимость от ASIO.
- `client` responsabilities
  - Содержит `connection`, `ASIO context`, `socket`, `thread` для ASIO, очередь входящих сообщений.
  - Содержит только одно соединение.
  - Отвественный за настройку ASIO и соединения.
  - Точка доступа для общения с сервером.
- `server` responsabilities
  - Содержит `ASIO context`, `acceptor`, `thread` для ASIO, очередь входящих сообщений.
  - Содержит множество соединений.
  - Отвественный за настройку ASIO и соединений.
  - Точка доступа для общения с клиентами.
  - Запускает игру.

![javidx9_client_server_architecture](screenshots/javidx9_client_server_architecture.png)

## Networking in C++ Part #2

- https://www.youtube.com/watch?v=UbjxGvrDrbw

- ASIO context - это центральный класс, который управляет всеми асинхронными операциями в ASIO.
  - В него добавляются асинхронные задачи с калбеками.
  - Когда задача завершается, ASIO вызывает калбек.
  - Когда все задачи завершены, ASIO завершает работу, поэтому нужно постоянно кормить его задачами.

- Server
  - Начинает с acceptor задачи, которая
    - ждет подключения клиента
    - создает сокет для клиента
    - Создает класс `connection` для клиента
    - Проверяет, что

## Networking in C++ Part #3

- https://www.youtube.com/watch?v=hHowZ3bWsio

## Networking in C++ Part #4

- https://www.youtube.com/watch?v=f_1lt9pfaEo

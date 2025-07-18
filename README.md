# Взаимодействие между приложениями на C и Erlang через ZeroMQ

## Описание

Данный проект демонстрирует взаимодействие между двумя приложениями:

1. **Сервер на C** — принимает команду `send` из консоли и отправляет сообщение с текущим временем;

2. **Клиент на Erlang** — получает и выводит полученные сообщения в консоль.

Обмен сообщениями осуществляется по **протоколу TCP**.

## Состав проекта

* `server/` — директория сервера. Включает:

    * `server/src/` — исходный код сервера,

    * `server/libs/` — библиотеки для сборки сервера;

* `client/` — директория клиента. Включает:

    * `client/src/` — исходный код клиента,

    * `client/libs/` — библиотеки для сборки клиента.

## Зависимости

**Зависимости, необходимые для сборки проекта**:

* Erlang/OTP 26-28;

* GCC + libstdc++;

* make.

**Зависимости, которые включены в проект (глобальная установка не требуется)**:

* libzmq 4.3.5;

* rebar3 3.25;

* chumak 1.5.0.

## Скачивание и сборка

В качестве примера для скачивания репозитория используется `git`.

```
$ git clone https://github.com/gslprod/zeromq-apps-interaction.git
$ cd zeromq-apps-interaction/
$ make
```

## Запуск

### 1. Запустите сервер:

```
$ make run-server
```

Консоль сервера будет ожидать ввод команды:

```
Type 'send' to send message, 'exit' to quit program
> send
Message sent: 16:38:53
```

После ввода `send` сервер отправит сообщение с текущим временем.

### 2. Запустите клиент на другом терминале:

```
$ make run-client
```

Запустится оболочка rebar3. Вызовите в ней следующую функцию:

```
1> time_client:main().
```

В результате клиент подключится к сокету, подпишется на сообщения и будет выводить их на консоль.

## Очистка

```
$ make clean
```

Будут удалены все файлы, созданные в результате сборки.

## Пример работы

### Терминал 1 (сервер)

```
$ make run-server
...
Type 'send' to send message, 'exit' to quit program
> send
Message sent: 16:38:53
Type 'send' to send message, 'exit' to quit program
> send
Message sent: 16:39:19
Type 'send' to send message, 'exit' to quit program
> send
Message sent: 16:39:30
```

### Терминал 2 (клиент)

```
$ make run-client
...
Eshell V16.0.1 (press Ctrl+G to abort, type help(). for help)
===> Booted chumak

===> Booted client

1> time_client:main().
Connected successfully
Time received: 16:38:53
Time received: 16:39:19
Time received: 16:39:30
```
Платформа для решения задач с тестированием пользовательского кода в контейнере.

```
$ docker build -t cpp-code-tester docker/
$ g++ server.cpp mongoose.cpp tester.cpp -std=c++17 -lpthread -o server 
$ ./server
```

[Смотреть демо](https://drive.google.com/file/d/1Uv0l90QfBTgl9KolUGfKcY2EY-cKbCQV/view?usp=sharing)

[Примеры - EXAMPLES.md](EXAMPLES.md)

`generator.py` - скрипт, генерирующий тесты

`index.html` - основная страница

`json.hpp`, `mongoose.h`, `mongoose.cpp` - либы

`server.cpp` - бэк

`tasks.json` - файл с задачами, структура очевидна

`tester.h`, `tester.cpp` - всё, что связано с тестом кода

`/docker` - Dockerfile и run.sh. Нужны для тестирования. `run.sh` отвечает за запуск кода юзера и сравнение результата с эталоном, также отлавливает ошибки.

`/tests` - папка с папками для тестов задач

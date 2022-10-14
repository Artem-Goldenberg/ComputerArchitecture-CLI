# ComputerArchitecture-CLI
Учебный репозитория для выполнения задания по курсу 'Архитектура и проектирование систем'

# Описание
Небольшой пример расширяемой библиотеки, реализующей интерфейс командной строки. Интерфейс схожий с bash. Команды cat, echo, wc, pwd, exit реализованы самостоятельно, остальные команды вызываются с помощью поиска по директориям, перечисленным в PATH.

# Структура проекта
Проект имеет следующую структуру:

![alt text](/Diagrams/CLIArchitecture.png)

За запуск и в качествe "обертки" над командной строкой выступает класс Shell c едиственным методом "запустить" (runPipeline). Этот метод инициализирует все свои подклассы и запускает в цикле пайплайн, обеспечивая сообщение между этапами и отлов ошибок. Сам пайплайн состоит из следующих этапов:

* Ввод данных
* Подстановка локальных переменных
* Разбиение на лексемы (токены)
* Парсинг токенов
* Исполнение спаршенных команд
* Вывод данных

<details><summary>Подробное описание каждого этапа и структура сообщения между соседними этапами:</summary><br>
  <details open><summary>1. Ввод данных</summary><br>
    <p>
      Обеспечивается классом Input/Output, который разделяет ответственность так же и за вывод. За ввод данных отвечает метод incomingRequest, который возвращает прочитанную строку (одну).
    </p>
    <p>
      <b>Note</b>: Класс не разделен на два, так как IO может содержать в себе более сложную логику, общую и для ввода и для вывода данных. Например, вывод может осуществляться по ssh или сразу в udp-socket в переводом из bid-endian в little-endian... Подобные особенности предполагается инкапсулировать в один класс Input/Output, а не дублировать в каждом из классов Input и Output.
    </p>
  </details>
  <details open><summary>2. Подстановка локальных переменных</summary><br>
    <p>
      Обеспечивается классом Preprocessor, а конкретно его единственным методом substitute. Этот метод принимает строку из класса Input/Output, а так же представителя класса Environment, в котором хранятся все известные переменные. В соответствии с содержимым класса Environment, метод substitute подставляет все локальные переменные.
    </p>
    <p>
      Переменная в строке выглядит следующим образом: сначала символ '$', а потом без пробелов и символов '$' еще сколько-то символов, которые и считаются названием переменной. Если подстрока, начанающаяся с символа '$', окружена одинарными или двойными кавычками, то парсер не считает ее переменной и подстановка не производится. В ином случае Preprocessor будет считать такую подстроку переменной и в случае отсутствия ее в классе Environment, вернет обшибку (Result c текстом ошибки).
    </p>
    <p>
      <b>Note</b>: Данная процедура происходит до токенизации, чтобы, например, корректно определять одним токеном такие команды как $A$B, где A="p", B="wd".
    </p>
  </details>
  <details open><summary>2-3. Сообщение между этапом 2 и 3</summary><br>
    <p>
      Осуществляется с помощью обертки Result<String, String>, которая возвращается Preprocessor'ом и обрабатывается классом Shell. При возврате ошибки подстановки исполнение пайплайна останавливается и ошибка передавется в Input/Output для уведомления пользователя. При корректном завершении работы Preprocessor'а строка из Result передается в класс Lexer.
    </p>
  </details>
  <details open><summary>3. Разбиение на лексемы (токены)</summary><br>
    <p>
      Обеспечивается классом Lexer, а конкретно методом tokenize, принимающим строку из Preprocessor и возвращающим очередь(массив) структур типа Token (описаны ниже).
    </p>
    <p>
      <b>Note</b>: Ошибок этот модуль возвращать не может.
    </p>
  </details>
  <details open><summary>3-4. Сообщение между этапом 3 и 4</summary><br>
    <p>
      Осуществляется с помощью списка специальных структур под названием Token. Каждый объект типа Token имеет два поля: тип и строку-содержание.
    </p>
    <p>
      <b>Note</b>: Добавление новых фич в синтаксис командной строки потребует как добавления новых типов, так и изменения классов Lexer и Parser. Однако такая зависимость необходима, так как позволяет разделить анализ сырой строки и ее лексем.
    </p>
  </details>
  <details open><summary>4. Парсинг токенов</summary><br>
    <p>
      Обеспечивается классом Parser, а конкретно методом parse, который принимает на вход список структур типа Token и возвращает список структур типа CommandData. При обработке предполагается, что у каждой команды есть название, аргументы, входной и выходной потоки. В случае, если парсинг не удался, то возвращается пустой массив (лучше бы Result::None!).
    </p>
    <p>
      <b>Note</b>: Входные потоки реализованы с помощью абстракции на случай будущего распараллеливания. Предполагается, что эти потоки будут использоваться только для установки очередности исполнения команд, но не для передачи хитрых аргументов и костылей и т.д.
    </p>
  </details>
  <details open><summary>4-5. Сообщение между этапом 3 и 4</summary><br>
    <p>
      Осуществляется с помощью списка структур типа CommandData, который возвращается Parser'ом и обрабатывается классом Shell (проверка, что не пустой). При возврате ошибки подстановки исполнение пайплайна останавливается и ошибка передавется в Input/Output для уведомления пользователя. При корректном завершении работы Parser'а значение из Result передается в класс CommandExecutor.
    </p>
    <p>
      <b>Note</b>: Не обязательно в поле команды писать реальное название команды. Важно, чтобы обработчик этой команды в CommandExecutor был забинжен на данное название.
    </p>
  </details>
  <details open><summary>5. Исполнение спаршенных команд</summary><br>
    <p>
      Обеспечивается классом CommandExecutor, который принимает на вход список команд типа CommandData, а вернет Result<String, String>. Для исполнения команд используется специальное отображение CommandExecutor::command, которое названию команды сопоставляет обработчик.
    </p>
    <p>
      <b>Note</b>: если хочется как-то влиять на какие-либо объекты извне (например на environment), то в обработчик нужно захардкодить адрес при инициализации класса Shell.<br>
      <b>Note</b>: есть забинженное название ошибки _EXIT, его возвращать кастомным реализациям нельзя.
    </p>
  </details>
  <details open><summary>6. Вывод данных</summary><br>
    <p>
      Обеспечивается классом Input/Output, а конкретно методом writeResponce, который приниммает строку, которую нужно вывести. Эта строка передается классом Shell после обработки одного из этапов пайплайна.
    </p>
  </details>
</details>

# Установка
Инструкция появится позже

# Авторы
* [Артем Голденберг](https://github.com/Artem-Goldenberg)
* [Антон Рябков](https://github.com/Contramund)

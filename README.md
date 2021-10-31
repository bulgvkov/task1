# TASK 1 (Ниже условий задачи находится суть работы программы)

Реализовать программу на языке C\C++, которая должна включать
следующую последовательность действий:
1. Запрос какой-либо информации от пользователя (логин, номер
телефона, номер какого-либо документа, ключ любого вида и т.д. )
2. Произведение манипуляций по разработанному алгоритму с
введённой пользователем информацией для генерации ответа на
ключевой вопрос
3. Запрос ключа от пользователя и сравнение его со сгенерированным
ключом на этапе 2.
4. Выдача результата по принципу:
    сгенерированный и алгоритмом и введённый пользователем
ключи совпадают – TRUE->поздравление или доступ к какой
либо информации.
    Не совпадают – ошибка

## Суть работы программы
Валидные данные для ввода:
* validlogin
* validpassword

В начале кода вызывается обработчик, отлавливающий присутствие отладчика, под которым запущена программа. На вход подаются две строки - логин и пароль. Затем вызывается конструктор класса. Для логина и пароля создаются отдельные экземпляры класса. В конструкторе происходит инициализация полей, к некоторым из них не в дальнейшем не будут производиться никакие обращения (имитация перегруженного смыслом кода). Затем вычисляется размер блока для логина и пароля. Максимальный размер блока равен 4. Данные блоки не имеют никакой смысловой нагрузки и используются в дальнейшем, как побочная переменная для генерации строки для кодирования. После определения размера блока мы дополняем нашу строку символами 'a'. Количество итераций цикла, который добавляет этот символ равно размеру нашего блока. Затем полученная строка сжимается (повторяющие символы сжимаются до одного и добавляется после символа число его повторений. Например aaabbbbcc = a3b4c2).
Затем эта строка шифруется по алгоритму Base64. Полученные строки в Base64 - посимвольно берутся по модулю 93 + 33 (чтобы попасть в диапазон существующих символов на клавиатуре по ASCII таблице) и сравниваются с теми хэшами, которые хранятся в векторе с валидными хэшами.

## Среда разработки
* Visual Studio 2019 Community

## Компилятор
* (встроенный в IDE) msvc142


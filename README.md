# Lem-in
## О проекте
### Задача:

***Lem-in*** решает задачу о нахождении максимального потока заданного кол-ва муравьев за наименьшее кол-во строк решения.

Программа на `STDIN` получает карту муравьиной фермы. 
      
    ./lem-in < maps/others/map_6

Входящая карта в текстовом формате содержит:

* кол-во муравьев: *n*
* название комнат с координатами: *name x y*
* связи между ними: *name1-name2*
* коментарии, которые начинаются с хэш-символа: *# comment*
* команды **##start** после которой на новой строке идет название стартовой комнаты
* команды **##end** после которой на новой строке идет название завершающей комнаты 

Структуру входных данных можно разделить на три блока:

    number_of_ants
    the_rooms
    the_links

Пример валидной карты:

    3
    ##start
    0 1 0
    ##end
    1 5 0
    2 9 0
    # this is comment
    3 13 0
    0-2
    2-3
    3-1

Полученная карта преобразовывается в двусвязный граф, где ноды это комнаты, а ребра это связи между ними. Изначально муравьи находятся в стартовой комнате, их нужно переправить в конечную по правилу: в каждой комнате одновременно может находится только один муравей, исключением является начальная и конечная комната. Наконец, применяя алгоритм использующий наилучшую комбинацию путей в соответствии с количеством муравьев должен вывести в `STDOUT` маршруты муравьев в формате:
       
    Lx-y Lz-w Lr-o ...

* где *x*, *z*, *r* - это номера муравьев, 
* *y*, *w*, *o* - это название комнат.

Пример вывода решения:

    3
    1 0 2
    ##start
    0 2 0
    ##end
    4 2 6
    2 4 2
    3 4 4
    0-1
    0-2
    2-3
    3-4
    4-1
    
    L1-1 L2-2
    L1-4 L3-1 L2-3
    L3-4 L2-4

Требования по работе программы (в случае с 4000 комнатами):
1. Время работы: 2 или 3 секунды - отлично, 9 секунд - посредственно, 15 секунд - это слишком много.
2. Кол-во строк решения: 0 или меньше предложенной нормы генератора - отлично, на 1 или 2 линии больше - хорошо, от 3 до 10 линий - посредстенно, больше 10 - это слишком много

### Решение:
1. Двухсвязный граф преобразовываем в односвязную транспортную сеть с помощью добавления фиктивных нод. Таким образом начальная нода разбивается на две (исключением является стартовая нода из нее связи только выходят и завершающая нода в нее связи только входят): 
     * *"out"* нода из которой выходят все связи: node_name
     * *"in"* нода в которую входят все связи: #node_name
2. С помощью алгоритма **Эдмондса-Карпа** находим максимальный поток за наименьшее кол-во строк решения. Более подробно опишем его работу:
     * при помощи алгоритма **Дейкстры** с потенциалами **Джонсона** для нахождения кратчайшего пути в графе с отрицательными ребрами и метода **Форда-Факелрсона** поиска потока в остаточной сети - находим поток
     * для найденного потока расчитываем кол-во необходимых шагов для переправки муравьев от начальной ноды в конечную и запоминаем это кол-во
     * продолжаем до тех пор пока кол-во строк решения перестанет уменьшаться
3. Далее генерируем перемещения муравьев в соответсвии с требуемым форматом вывода и выводим его в `STDOUT`

### Итог:
Разработанное решение укладывается во все требования на отлично: решение карты с 4000 комнатами укладывается в 0.1 секунду и кол-во строк решения довольно часто меньше, чем указал генератор.

### Запуск:
    make; ./lem-in < maps/others/mp

### Приятные бонусы:
Данная реализация проекта *lem-in* поддерживает 6 флагов:

    usage: ./lem-in [OPTIONS] < map_file
    Options:
            --steps     show the number of lines of instructions
            --color     draw the output in different colors
            --paths     show the paths of the found flow
            --flows     show found flows
            --short     show only instructions without a map
            --multi     calculate multi maps at once
                        ./lem-in --multi {map_file_0} {map_file_1} ... {map_file_n}

Флаги можно комбинировать между собой, меняя вывод программы. Рассмотрим примеры работы этих флагов:


1. Выведем кол-во строк решения:
![lem-in steps](/img/steps.png)
2. Посмотрим итеративно найденные потоки:

![lem-in flows](/img/flows.png) 
3. Распечатаем на экране найденные оптимальные пути:

![lem-in paths](/img/paths.png)
4. Если же захотим посмотреть только решение, то для это используем флаг *--short*:

![lem-in short](/img/short.png)
5. Комбинация сразу нескольких флагов:

![lem-in combo](/img/combo.png)
6. А вот, что будет если добавить флаг *--color*:

![lem-in color](/img/color.png)
7. Флаг *--multi* позволяет в аргументах *cli* перечислить необходимые карты для решения, результат будет записан в отдельные файлы в том месте где лежит расчитываемая карта, но с суффиксом *"out"* в имени карты:


    ./lem-in --multi  maps/others/mp maps/others/map_6
![lem-in multi](/img/multi.png)

### Визуализация:

Саня тут дело за тобой

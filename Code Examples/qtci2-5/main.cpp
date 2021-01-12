#include <QCoreApplication>
#include <QLinkedList>
#include <QDebug>

// QLinkedList<T> is one of Qt's generic container classes.
// It stores a list of values and provides iterator-based access as well as constant time insertions and removals.

// If you need a real linked list, with guarantees of constant time insertions in the middle
// of the list and iterators to items rather than indexes, use QLinkedList.


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QLinkedList<int> list;
    for(int i = 0; i < 10; i++) {
        list.append(i);
    }

    list.removeFirst();
    list.removeLast();
    list.removeOne(5);
    if(list.contains(3)) qInfo() << "Contains 3";
    list.clear();

    qInfo() << "Done";


    return a.exec();
}

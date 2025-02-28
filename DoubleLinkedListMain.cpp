#include "DoubleLinkedList.tpp"
#include "DoubleLinkedList.cpp"

int main() {
    std::cout << "Test 1: Constructor with initializer list\n";
    double_linked_list<int> list = {1, 2, 3, 4, 5};

    std::cout << "Elements in list: ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    list.push_front(0);
    std::cout << "List after push_front(0): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    list.push_back(6);
    std::cout << "List after push_back(6): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    auto it = list.find(3); 
    if (it != list.end()) {
        list.insert(it, 7);
    }

    std::cout << "List after insert_after(3, 7): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    it = list.find(3); 
    if (it != list.end()) {
        list.erase(it);
    }

    std::cout << "List after erase_after(3): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    for (auto it = list.begin(); it != list.end(); ++it) {
        *it += 10;
    }

    std::cout << "List after modifying with iterator: ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    list.clear(); 
    std::cout << "List after clear(): ";
    if (list.begin() == list.end()) {
        std::cout << "List is empty!";
    } else {
        for (auto it = list.cbegin(); it != list.cend(); ++it) {
            std::cout << *it << " ";
        }
    }
    std::cout << "\n\n";

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    std::cout << "List after push_back(10), push_back(20), push_front(5): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}

#include "List.h"

int main() {
    List<double> list;
    list.InsertNode(5, 0);
    list.InsertNode(5.5, 0);
    list.PrintList();
    std::optional<double&> data = list.GetElement(0);
    if (data.has_value()) {
        double value = data.value();
        // Используйте значение value
    } else {
        // Элемент не найден
    }
    
    return 0;
}

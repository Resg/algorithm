#include <iostream>
#include <vector>
#include <string.h>

struct hashfunc
{
public:
    hashfunc() {
    }
    size_t operator()(const std::string &value) {
        const size_t kol = 5;
        const size_t n = value.length();
        if (!n)
            return 0;
        size_t result = 0;
        size_t i = n - 1;
        while (i > 0) {
            result += (size_t) value[i];
            result *= kol;
            --i;
        }
        result += (size_t) value[0];
        return result;
    }
};

template <class T, class HashFunc>
class HashTable
{
private:
    T* arr_val;
    bool* isempty;
    bool* arr_flag;
    size_t size;
    size_t capacity;
    void resize() {
        capacity *= 2;
        T* buf = arr_val;
        delete[] isempty;
        isempty = new bool[capacity];
        memset(isempty, true, capacity);
        arr_val = new T[capacity];
        delete [] arr_flag;
        arr_flag = new bool[capacity];
        memset(arr_flag, false, capacity);
        size = 0;
        for (size_t i = 0; i < capacity / 2; i++) {
            addelem(buf[i]);
        }
        delete [] buf;
    }
public:
    size_t hash(const T& val) {
        HashFunc HF;
        return HF(val) % capacity;
    }
    HashTable() : size(0), capacity(8) {
        arr_val = new T[capacity];
        isempty = new bool[capacity];
        arr_flag = new bool[capacity];
        memset(isempty, true, capacity);
        memset(arr_flag, false, capacity);
    }
    bool addelem(const T& val) {
        if (size >= capacity*3/4)
            resize();
        //if (haselem(val))
        //    return false;
        size_t HS = hash(val);
        size_t i = 1;
        size_t step = 1;
        int first_delete = -1;
        while ((!isempty[HS] && !arr_flag[HS]) || (isempty[HS] && arr_flag[HS])){
            if (arr_val[HS] ==  val && !isempty[HS])
                return false;
            if (step > capacity){
                break;
            }
            if (arr_flag[HS] == true && first_delete == -1)
                first_delete = HS;
            HS += i;
            HS %= capacity;
            step++;
        }
        if (first_delete != -1)
            HS = first_delete;
        /*while (!isempty[HS]) {
            HS += i;
            HS %= capacity;
            i++;
        }*/
        arr_flag[HS] = false;
        arr_val[HS] = val;
        size++;
        isempty[HS] = false;
        return true;
    }
    bool delelem(const T& val) {
        size_t HS = hash(val);
        size_t i = 1;
        size_t counter = 0;
        while (arr_val[HS] != val || isempty[HS]) {
            if (isempty[HS] && !arr_flag[HS])
                return false;
            if (counter > capacity)
                return false;
            counter++;
            HS += i;
            HS %= capacity;
            i++;
        }
        size--;
        isempty[HS] = true;
        arr_flag[HS] = true;
        return true;
    }
    bool haselem(const T& val) {
        size_t HS = hash(val);
        size_t i = 1;
        size_t counter;
        while (arr_val[HS] != val || isempty[HS]) {
            if (isempty[HS] && !arr_flag[HS])
                return false;
            if (counter > capacity)
                return false;
            HS += i;
            HS %= capacity;
            i++;
            counter++;
        }
        return  true;
    }


};

int main(int argc, char *argv[])
{
    char comand;
    std::string val;
    HashTable<std::string, hashfunc> table;
    while (std::cin >> comand >> val) {
        switch (comand) {
        case '+': {
            if (table.addelem(val))
                std::cout << "OK\n";
            else
                std::cout << "FAIL\n";
            break;
        }
        case '-': {
            if (table.delelem(val))
                std::cout << "OK\n";
            else
                std::cout << "FAIL\n";
            break;
        }
        case '?': {
            if (table.haselem(val))
                std::cout << "OK\n";
            else
                std::cout << "FAIL\n";
            break;
        }
        default:
            break;
        }
    }

    return 0;
}

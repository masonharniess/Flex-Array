#include <string>
#include <iostream>

using std::string;

class FlexArray {

public:
    // GENERAL CLASS CONSTRUCTION/ASSIGNMENT

    FlexArray();

    FlexArray(const int* arr, int size);

    ~FlexArray();

    FlexArray(const FlexArray& other);

    FlexArray& operator=(const FlexArray& other);

    // PRINTING AND SIZE INFORMATION

    int getSize() const;

    int getCapacity() const;

    string print() const;

    string printAll() const;

    // GETTERS AND SETTERS

    int get(int i) const;

    bool set(int i, int v);

    // STRUCTURAL MODIFIERS

    void push_back(int v);

    bool pop_back();

    void push_front(int v);

    bool pop_front();

    bool insert(int i, int v);

    bool erase(int i);

    static constexpr int INITIALCAP = 5;
    static constexpr int LO_THRESHOLD = 3;
    static constexpr int HI_THRESHOLD = 7;

private:

    int* arr_;
    int size_; 
    int capacity_; 

    int startIndex_;

    int* get_elements_();
    void resize_();
    void shift_shrink_(int index, int direction);
    void shift_(int index, int direction);

};
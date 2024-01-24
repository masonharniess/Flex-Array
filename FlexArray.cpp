#include "FlexArray.h"

FlexArray::FlexArray() {
    this->size_ = 0;
    this->capacity_ = INITIALCAP;
    this->arr_ = new int[this->capacity_];
    this->startIndex_ = -1;
}

FlexArray::FlexArray(const int* arr, int size) {
    this->capacity_ = LO_THRESHOLD * size;
    this->arr_ = new int[this->capacity_]; // create new constructor and set capacity
    this->size_ = size;

    this->startIndex_ = (this->capacity_ - this->size_) / 2; // centre the elements

    for (int i = 0; i < this->size_; ++i) {
        this->arr_[this->startIndex_ + i] = arr[i];
    }
}

FlexArray::~FlexArray() {
    if (this->arr_ != nullptr) {
        delete[] this->arr_;
    }
    
    this->arr_ = nullptr;
}

FlexArray::FlexArray(const FlexArray& other) {
   
    this->size_ = other.size_;
    this->startIndex_ = other.startIndex_;
    this->capacity_ = other.capacity_;

    this->arr_ = new int[this->capacity_];

    for (int i = 0; i < this->capacity_; ++i) {
        this->arr_[i] = other.arr_[i];
    }
}

FlexArray& FlexArray::operator=(const FlexArray& other) {
    if (this == &other) return *this;

    this->size_ = other.size_;
    this->startIndex_ = other.startIndex_;
    this->capacity_ = other.capacity_;

    delete[] this->arr_;
    this->arr_ = new int[this->capacity_];

    for (int i = 0; i < this->capacity_; ++i) {
        this->arr_[i] = other.arr_[i];
    }
    return *this;
}

int FlexArray::getSize() const {
    return this->size_;
}

int FlexArray::getCapacity() const {
    return this->capacity_;
}

string FlexArray::print() const {
    string output = "[";

    for (int i = 0; i < this->size_; ++i) {
        output += std::to_string(this->arr_[this->startIndex_ + i]);
        if (i != this->size_ - 1) output += ", ";
    }
    output += "]";

    return output;
}

string FlexArray::printAll() const {
    string output = "[";

    for (int i = 0; i < this->capacity_; ++i) {
        if (i < this->startIndex_) output += "X";
        else if (i >= this->startIndex_ + this->size_) output += "X";
        else output += std::to_string(this->arr_[i]);
        if (i != this->capacity_ - 1) output += ", ";
    }
    output += "]";

    return output;
}

int FlexArray::get(int i) const {
    return this->arr_[this->startIndex_ + i];
}

bool FlexArray::set(int i, int v) {
    if (i < 0) return false;
    if (i >= this->size_) return false;

    int index = this->startIndex_ + i;

    this->arr_[index] = v;
    return true;
}

void FlexArray::push_back(int v) {
    if (this->size_ == 0) this->startIndex_ = (this->capacity_ - 1) / 2;

    int index = this->startIndex_ + this->size_;
    
    if (index >= this->capacity_) {
        this->resize_();
        index = this->startIndex_ + this->size_;
    }

    ++this->size_;
    this->arr_[index] = v;
}

bool FlexArray::pop_back() {
    if (this->size_ < 1) return false;
    --this->size_;

    if (this->size_ == 0) return true;
    if (this->capacity_ > this->size_ * HI_THRESHOLD) this->resize_();

    return true;
}

void FlexArray::push_front(int v) {
    if (this->size_ == 0) this->startIndex_ = (this->capacity_ - 1) / 2;
    if (this->startIndex_ - 1 < 0) {
        this->resize_();
    }
    this->startIndex_ = this->size_ == 0 ? ((this->capacity_ - 1) / 2) : --(this->startIndex_);
    this->arr_[this->startIndex_] = v;
    ++this->size_;
}

bool FlexArray::pop_front() {
    if (this->size_ < 1) return false;
    int index = this->startIndex_ + 1;
    ++this->startIndex_;
    --this->size_;

    if (this->size_ == 0) return true;
    if (this->capacity_ > this->size_ * HI_THRESHOLD) this->resize_();

    return true;
}

bool FlexArray::insert(int i, int v) {
    if (i < 0) return false;

    if (i > this->size_) return false;

    if (this->startIndex_ + i == this->capacity_) {
        this->shift_(i, 1);
        this->set(i, v);
        return true;
    }

    if (i == this->size_) {
        this->push_back(v);
        return true;
    }

    int mid = this->size_ / 2;
    int direction = i <= mid ? 0 : 1;

    this->shift_(i, direction);
    this->set(i, v);

    return true;
}

void FlexArray::shift_(int index, int direction) {
    int finalDirection = direction;

    if (this->size_ == this->capacity_) this->resize_();

    if (direction == 0 && (this->startIndex_ - 1) < 0) {
        finalDirection = 1;
    }

    if (direction == 1 && (this->startIndex_ + this->size_) == this->capacity_) {
        finalDirection = 0;
    }

    ++this->size_;

    if (finalDirection == 0) {
        --this->startIndex_;
        for (int i = 0; i <= index; ++i) {
            this->set(i, this->get(i + 1));
        }
    }
    else {
        int tempValue = this->get(index);
        int currentTemp;
        for (int j = index + 1; j < this->size_ - 1; ++j) {
            currentTemp = this->get(j);
            this->set(j, tempValue);
            tempValue = currentTemp;
        }
        this->set(this->size_ - 1, tempValue);
    }

    this->set(index, 0);
}

void FlexArray::shift_shrink_(int index, int direction) {
    int finalDirection = direction;

    if (finalDirection == 0) {
        int tempValue = this->get(0);
        int curTemp;
        for (int i = 1; i <= index; ++i) {
            curTemp = this->get(i);
            this->set(i, tempValue);
            tempValue = curTemp;
        }
        ++this->startIndex_;
    }
    else {
        for (int i = index; i < (this->size_) - 1; ++i) {
            this->set(i, this->get(i + 1));
        }
    }

    --this->size_;
}

bool FlexArray::erase(int i) {
    if (i < 0) return false;

    if (i >= this->size_) return false;
    if (i == this->size_ - 1) {
        this->pop_back();
        return true;
    }

    int mid = this->size_ / 2;
    int direction = i < mid ? 0 : 1;

    this->shift_shrink_(i, direction);

    if (this->size_ == 0) return true;
    if (this->capacity_ > this->size_ * HI_THRESHOLD) this->resize_();

    return true;
}

void FlexArray::resize_() {
    FlexArray flexArr(this->get_elements_(), this->size_);
    *this = flexArr;
}

int* FlexArray::get_elements_() {
    int* elements = new int[this->size_];

    for (int i = 0; i < this->size_; ++i) {
        elements[i] = this->arr_[this->startIndex_ + i];
    }
    
    return elements;
}
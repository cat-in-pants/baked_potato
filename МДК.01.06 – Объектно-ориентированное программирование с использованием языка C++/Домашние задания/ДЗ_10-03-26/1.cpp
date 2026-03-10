class String {
private:
    char* data;
    size_t size;
public:
    String(const char* str = "") {
        size = 0;
        while (str[size] != '\0') size++;
        data = new char[size + 1];
        for (size_t i = 0; i <= size; i++) data[i] = str[i];
    }
    
    String(const String& other) {
        size = other.size;
        data = new char[size + 1];
        for (size_t i = 0; i <= size; i++) data[i] = other.data[i];
    }
    
    ~String() {
        delete[] data;
    }
    
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size + 1];
            for (size_t i = 0; i <= size; i++) data[i] = other.data[i];
        }
        return *this;
    }
};

class Buffer {
private:
    int* data;
    size_t size;
public:
    Buffer(size_t s = 0) : size(s) {
        data = (size > 0) ? new int[size]() : nullptr;
    }
    
    Buffer(const Buffer& other) : size(other.size) {
        data = (size > 0) ? new int[size] : nullptr;
        for (size_t i = 0; i < size; i++) data[i] = other.data[i];
    }
    
    ~Buffer() {
        delete[] data;
    }
    
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = (size > 0) ? new int[size] : nullptr;
            for (size_t i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }
};

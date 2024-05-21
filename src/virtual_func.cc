#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#include <numeric>

class Person {
   public:
    Person() {
        ++object_count;
        this->cur_id = Person::object_count;
    };

    virtual void getdata() {}

    virtual void putdata() {}

    static int object_count;
    int cur_id;
    string name;
    int age;
};

int Person::object_count = 0;

class Professor : public Person {
   public:
    Professor() : Person() {
        
    };

    void getdata() {
        cin >> this->name >> this->age >> this->publications;
    }

    void putdata() {
        cout << this->name << " " << this->age << " " << this->publications << " "
             << this->cur_id << endl;
    }

   private:
    int publications;
};

class Student : public Person {
   public:
    Student() : Person() {
    };

    void getdata() {
        cin >> this->name >> this->age;

        for (int i = 0; i < 6; i++) {
            cin >> marks[i];
        }
    }

    void putdata() {
        int sum = std::accumulate(this->marks.begin(), this->marks.end(), 0);

        cout << this->name << " " << this->age << " " << sum << " " << this->cur_id << endl;
    }

   private:
    vector<int> marks = vector<int>(6);
};

int main() {
    int n, val;
    cin >> n;  // The number of objects that is going to be created.
    Person* per[n];

    for (int i = 0; i < n; i++) {
        cin >> val;
        if (val == 1) {
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        } else
            per[i] = new Student;  // Else the current object is of type Student

        per[i]->getdata();  // Get the data from the user.
    }

    for (int i = 0; i < n; i++)
        per[i]->putdata();  // Print the required output for each object.

    return 0;
}

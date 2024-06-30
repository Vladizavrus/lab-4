struct Student{
    int student_id;
    string Name, Surname, Lastname;
    int age;
    ///Operator
    bool operator < (Student& other){
        return student_id < other.student_id;
    }
    bool operator > (Student& other){
        return student_id > other.student_id;
    }
    bool operator == (Student& other){
        return student_id == other.student_id;
    }
    bool operator >= (Student& other){
        return student_id >= other.student_id;
    }
    bool operator <= (Student& other){
        return student_id <= other.student_id;
    }
};
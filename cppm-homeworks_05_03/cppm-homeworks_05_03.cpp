// cppm-homeworks_05_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
//базовый родитель
class Figure {
protected:
    
    int sides = 0;//количество сторон
    std::string name = "Фигура"; //имя фигуры
    std::string status;//правильная или неправильная (зависит от значения shape при выводе информации в консоль)
    bool shape;
    //стороны
    int a;
    int b;
    int c;
    int d;
    //углы
    int A;
    int B;
    int C;
    int D;
    
    Figure(int a, int b, int c, int d, int A, int B, int C, int D) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        shape = check();
        

    }
    //проверка правильности базовой фигуры
    virtual bool check() {
        if (sides == 0) {
            return true;
        }
        else {
            return false;
        }

    }
public:
    Figure() :Figure(0, 0, 0, 0, 0, 0, 0, 0) {};
    virtual void get_info() {
        if (shape) {
            status = "Правильная";
        }
        else {
            status = "Неправильная";
        }
        std::cout << name << ":\n" << status << "\nКоличество сторон: " << sides << std::endl <<std::endl;
    }

};

//треугольник
class Triangle : public Figure {
protected:
    //проверка базового треугольника
    bool check() override {
        
        if ((A + B + C == 180)&&(sides == 3)) {
            return true;
        }
        else {
            return false;
        }

    };

public:
    //при создании базового треугольника используем конструктор базовой фигуры,
    //добавляя данные о сторонах (у треугольника 3 стороны -- логично же) и проверяя правильность формы
    Triangle(int a, int b, int c, int A, int B, int C) :Figure(a, b, c, 0, A, B, C, 0) {
        name = "Треугольник";
        sides = 3;
        shape = check();
    };


    void get_info() override {
        if (shape) {
            status = "Правильная";
        }
        else {
            status = "Неправильная";
        }
        
        std::cout << name << ":\n" << status << "\nКоличество сторон: " << sides << std::endl;
        std::cout <<"Cтороны: " << "a=" << a << " b=" << b << " c=" << c << std::endl;
        std::cout << "Углы: " << "A=" << A << " B=" << B << " C=" << C << std::endl << std::endl;
        
    }


};

//четырехугольник
class Quadrangle :public Figure {
protected:
    //проверка правильности формы базового четырехугольника
     bool check() override {
        if ((A + B + C + D == 360)&&(sides == 4)) {
            return true;
        }
        else {
            return false;
        }
    }

public:
    //при создании экземпляра четырехугольника используем конструктор базовой фигуры,
    //передавая при этом инфу о сторонах(четырехгольник -> четыре стороны) и проверяя правильность формы
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) :Figure(a, b, c, d, A, B, C, D) {
        name = "Четырехугольник";
        sides = 4;
        shape = check();
    }
    void get_info() override {
        if (shape) {
            status = "Правильная";
        }
        else {
            status = "Неправильная";
        }
        std::cout << name << ":\n" << status;
        std::cout << "\nКоличество сторон: " << sides;
        std::cout <<"\nCтороны: " << "a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
        std::cout << "Углы: " << "A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl << std::endl;
    }

};

//прямоугольный треугольник
class Triangle_C_90 : public Triangle {
protected:
    //проверяем доп условие для прямоугольного треугольника вместе с базовыми условиями треугольника
    //нижеследующие классы проводят проверку подобным образом
    bool check() override {        
        if (C == 90 && Triangle::check()) {
            return true;
        }
        else {
            return false;
        }

    }
public:
    Triangle_C_90(int a, int b, int c, int A, int B) :Triangle(a, b, c, A, B, 90) {
        name = "Прямоугольный треугольник";
        shape = check();
    };

};

//равнобедренный треугольник
class Triangle_bedra_ravny : public Triangle {
protected:
    bool check() override {
        if (a == c && A == C && Triangle::check()) {
            return true;
        }
        else {
            return false;
        }
    }
public:
    Triangle_bedra_ravny(int a, int b, int A, int B) : Triangle(a, b, a, A, B, A) {
        name = "Равнобедренный треугольник";
        shape = check();
    };
};

//равносторонний треугольник
class Triangle_all_sides_equal : public Triangle_bedra_ravny {
protected:
    bool check() override {
        //проверяем доп условие частично тут, частично оно уже проверено в классе родителе, поэтому не пишем целиком
        //в нижеизложенных классах делал так же(где было возможно)
        if (b == c && B == C && Triangle_bedra_ravny::check()) {
            return true;
        }
        else {
            return false;
        }
    }
public:
    Triangle_all_sides_equal(int a) : Triangle_bedra_ravny(a, a, 60, 60) {
        name = "Равносторонний треугольник";
        shape = check();
    };

};

//параллелограмм
class Parallelogramm : public Quadrangle {
protected:
    bool check() override {
        if (a == c && b == d && A == C && B == D && Quadrangle::check()) {
            return true;
        }
        else {
            return false;
        }
    }
public:
    Parallelogramm(int a, int b, int A, int B) : Quadrangle(a, b, a, b, A, B, A, B) {
        name = "Параллелограмм";
        shape = check();
    };
};

//прямоугольник
class Quadrangle_all_corners_90 : public Parallelogramm {
protected:
    bool check() override {
        if (A == 90 && B == 90 && Parallelogramm::check()) {
            return true;
        }
        else {
            return false;
        }
    }
public:
    Quadrangle_all_corners_90(int a, int b) : Parallelogramm(a, b, 90, 90) {
        name = "Прямоугольник";
        shape = check();
    };

};

//квадрат
class Square :public Quadrangle_all_corners_90 {
protected:
    bool check() override {
        if (a == b && Quadrangle_all_corners_90::check()) {
            return true;
        }
        else {
            return false;
        }
    }
public:
    Square(int a) :Quadrangle_all_corners_90(a, a) {
        name = "Квадрат";
        shape = check();
    };
};

//ромб
class Romb : public Parallelogramm {
protected:
    bool check() override {
        if (a == b && A == B && Parallelogramm::check()) {
            return true;
        }
        else {
            return false;
        }
    }
public:
    Romb(int a, int A, int B) :Parallelogramm(a, a, A, B) {
        name = "Ромб";
        shape = check();
    };
};

void print_info(Figure* adress) {
    adress->get_info();
}
int main()
{
    setlocale(LC_ALL, "rus");
    Figure figure;
    Triangle triangle_0(10, 20, 30, 50, 60, 70);
    Triangle_C_90 triangle_1(10, 20, 30, 50, 60);
    Triangle_bedra_ravny triangle_2(10, 20, 50, 60);
    Triangle_all_sides_equal triangle_3(30);
    Quadrangle quadrangle_0(10, 20, 30, 40, 50, 60, 70, 80);
    Quadrangle_all_corners_90 quadrangle_1(10, 20);
    Square quadrangle_2(20);
    Parallelogramm quadrangle_3(20, 30, 30, 40);
    Romb quadrangle_4(30, 30, 40);

    Figure** arr_ptr = new Figure * [10];
    arr_ptr[0] = &figure;
    arr_ptr[1] = &triangle_0;
    arr_ptr[2] = &triangle_1;
    arr_ptr[3] = &triangle_2;
    arr_ptr[4] = &triangle_3;
    arr_ptr[5] = &quadrangle_0;
    arr_ptr[6] = &quadrangle_1;
    arr_ptr[7] = &quadrangle_2;
    arr_ptr[8] = &quadrangle_3;
    arr_ptr[9] = &quadrangle_4;

    for (int i = 0; i < 10; i++) {
        print_info(arr_ptr[i]);
    }
    delete[]arr_ptr;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

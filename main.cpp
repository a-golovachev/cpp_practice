#include <iostream>
#include <cmath>

class dot {

public:

    dot() : x_(0), y_(0) {}

    dot(double x, double y) : x_(x), y_(y) {}

    ~dot() {}

    double x() {
        return x_;
    }

    double y() {
        return y_;
    }

protected:
    double x_;
    double y_;
};

double dist(dot a, dot b) {
    return sqrt(pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2));
}

class polygon {
public:

    polygon(int n) : size_(n), dots_(new dot[n]) {}

    polygon(const std::initializer_list<dot> &list):
            polygon(list.end() - list.begin())
    {
        int cnt = 0;
        for (auto &e : list) {
            dots_[cnt++] = e;
        }
    }

    virtual ~polygon() {
        delete []dots_;
    }

    virtual double area() {
        double sum = 0;
        for (int i = 0; i < (size_ - 1); ++i) {
            sum += dots_[i].x() * dots_[i + 1].y() - dots_[i + 1].x() * dots_[i].y();
        }
        sum += dots_[size_].x() * dots_[0].y() - dots_[0].x() * dots_[size_].y();
        return std::abs(sum / 2);
    }

    virtual double perimeter() {
        double sum = 0;
        for (int i = 0; i < (size_ - 1); ++i) {
            sum += dist(dots_[i], dots_[i + 1]);
        }
        sum += dist(dots_[size_ - 1], dots_[0]);
        return sum;
    }

protected:
    dot* dots_;
    int size_;
};

class rectangle : public polygon{
public:
    rectangle(double a, double b, dot start) : polygon(4), length_(a), height_(b), start_(start) {
        dots_[0] = start_;
        dots_[1] = dot(start_.x() + length_, start_.y());
        dots_[2] = dot(start_.x() + length_, start_.y() + height_);
        dots_[3] = dot(start_.x(), start_.y() + height_);
    }

    ~rectangle() override = default;

    double area() override {
        return length_ * height_;
    }

    double perimeter() override {
        return 2 * (length_ + height_);
    }


protected:
    double length_;
    double height_;
    dot start_;
};

class square final : public rectangle{
public:
    square(double a, dot start): rectangle(a, a, start) {}
    ~square() final = default;
};


class triangle : public polygon{
public:
    triangle(const std::initializer_list<dot> &list) : polygon(list) {}
    ~triangle() final = default;

    dot incenter() {
        double L01 = dist(dots_[0], dots_[1]);
        double L02 = dist(dots_[0], dots_[2]);
        double L12 = dist(dots_[1], dots_[2]);
        double x = (L12 * dots_[0].x() + L02 * dots_[1].x() + L01 * dots_[2].x()) / (L01 + L02 + L12);
        double y = (L12 * dots_[0].y() + L02 * dots_[1].y() + L01 * dots_[2].y()) / (L01 + L02 + L12);
        return dot(x, y);
    }

    dot outcenter() {
        double D = 2*(dots_[0].x()*(dots_[1].y() - dots_[2].y()) + dots_[1].x()*(dots_[2].y() - dots_[0].y()) +
                dots_[2].x()*(dots_[0].y() - dots_[1].y()));
        double A2 = dots_[0].x() * dots_[0].x() + dots_[0].y() * dots_[0].y();
        double B2 = dots_[1].x() * dots_[1].x() + dots_[1].y() * dots_[1].y();
        double C2 = dots_[2].x() * dots_[2].x() + dots_[2].y() * dots_[2].y();
        double x = (A2 * (dots_[1].y() - dots_[2].y()) + B2 * (dots_[2].y() - dots_[0].y()) +
                C2 * (dots_[0].y() - dots_[1].y()));
        double y = (A2 * (dots_[1].x() - dots_[2].x()) + B2 * (dots_[2].x() - dots_[0].x()) +
                    C2 * (dots_[0].x() - dots_[1].x()));
        return dot(x, y);
    }

    dot median_intersection() {
        double x = dots_[0].x() + dots_[1].x() + dots_[2].x();
        double y = dots_[0].y() + dots_[1].y() + dots_[2].y();
        return dot(x, y);
    }

    void print_medians() {
        dot med0 = {(dots_[1].x() + dots_[2].x()) / 2, (dots_[1].y() + dots_[2].y()) / 2};
        dot med1 = {(dots_[0].x() + dots_[2].x()) / 2, (dots_[0].y() + dots_[2].y()) / 2};
        dot med2 = {(dots_[1].x() + dots_[0].x()) / 2, (dots_[1].y() + dots_[0].y()) / 2};
        double k1 = (dots_[0].y() - med0.y()) / (dots_[0].x() - med0.x());
        double k2 = (dots_[1].y() - med1.y()) / (dots_[1].x() - med1.x());
        double k3 = (dots_[2].y() - med2.y()) / (dots_[2].x() - med2.x());
        double b1 = (dots_[0].x() * med0.y() - dots_[0].y() * med0.x()) / (dots_[0].x() - med0.x());
        double b2 = (dots_[1].x() * med1.y() - dots_[1].y() * med1.x()) / (dots_[1].x() - med1.x());
        double b3 = (dots_[2].x() * med2.y() - dots_[2].y() * med2.x()) / (dots_[2].x() - med2.x());
        std::cout << k1 << "x+" << b1 << std::endl;
        std::cout << k2 << "x+" << b2 << std::endl;
        std::cout << k3 << "x+" << b3 << std::endl;
    }

};

class ellipse {
public:
    ellipse(double a, double b) : init_(dot(0, 0)), a_(a), b_(b) {}
    virtual ~ellipse() = default;

    double area() {
        return 3.141592 * a_ * b_;
    }

    virtual double perimeter() {
        return 4 * (area() + (a_ - b_) * (a_ - b_)) / (a_ + b_);
    }

protected:
    dot init_;
    double a_;
    double b_;
};

class circle : public ellipse {
public:
    circle(double r) : ellipse(r, r) {}
    ~circle() override = default;

    double perimeter() override {
        return 2 * 3.141592 * a_;
    }
private:
};

int main() {
    triangle t = {{0, 2}, {2, 2}, {2, 0}};
    t.print_medians();
    return 0;
}

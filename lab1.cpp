#include <iostream>
#include <vector>
#include <cmath>
#include <random>

std::random_device rd;
std::mt19937 mersenne(rd());

class CPoint {
private:
    float x, y;
public:
    CPoint() = default;

    CPoint(float x_, float y_)
            : x(x_)
            , y(y_)
    {}

    CPoint(const CPoint& copy_value)
            : x(copy_value.x)
            , y(copy_value.y)
    {}

    CPoint& operator = (const CPoint& copy_value) {
        if (this != &copy_value) {
            x = copy_value.x;
            y = copy_value.y;
        }
        return *this;
    }

    void set(float x_, float y_){
        x = x_; y = y_;
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    void Print() const{
        std::cout << "Coordinates of Point are X = " << x << " " << "Y = " << y << "\n";
    }

    /*~CPoint(){
        std::cout << "Destructor of Point\n";
    }*/
};

class CFigure{
protected:
    static float getLength(const CPoint& a, const CPoint& b){
        return sqrt(pow(b.getX()-a.getX(), 2) + pow(b.getY() - a.getY(), 2));
    }

public:
    static bool isConvex(const std::vector<CPoint> &vertices){
        float direction = 0;
        for (int i = 1; i < vertices.size() - 1; i++) {
            CPoint x1{}, x2{};
            x1.set(vertices[i].getX() - vertices[i - 1].getX(), vertices[i].getY() - vertices[i - 1].getY());
            x2.set(vertices[i + 1].getX() - vertices[i].getX(), vertices[i + 1].getY() - vertices[i].getY());
            if (i == 1) {
                direction = x1.getX() * x2.getY() - x1.getY() * x2.getX();
                continue;
            }
            float extraDir = x1.getX() * x2.getY() - x1.getY() * x2.getX();
            if ((direction < 0 && extraDir > 0) || (direction > 0 && extraDir < 0)) {
                return false;
            }
        }
        return true;
    }

    void getData(){
        for (auto & vertex : vertices){
            std::cout << "(" << vertex.getX() << ", " << vertex.getY() << ")\n";
        }
    }

    virtual float getPerimeter() = 0;
    virtual float getSquare() = 0;
    virtual void  isFigure() = 0;

    std::vector <CPoint> vertices;
};

class CBroken : public CFigure {
private:
    int size; int perimeter{};

    void setPerimeter(){
        perimeter = 0;
        for (int i = 0; i < vertices.size() - 1; i++){
            perimeter += getLength(vertices[i], vertices[i + 1]);
        }
    }

    void isFigure() override{
        if (size < 3)
            throw std::runtime_error("Broken Line must have more than 2 points");
    }

public:
    CBroken(std::vector <CPoint>arr, int L){
        size = L;
        for (int i = 0; i < size; i++){
            vertices.push_back(arr[i]);
        }
        setPerimeter();
    };

    CBroken(const std::vector<CPoint>& arr){
        vertices = arr;
    }

    CBroken& operator = (const CBroken &p){
        return *this;
    }

    float getPerimeter() override{
        return perimeter;
    }

    float getSquare() override{
        return 0;
    }

    ~CBroken(){
        std::cout << "Destructor of the Broken\n";
    }
};

class CClosedBroken : public CBroken {
private:
    int perimeter;
    void setPerimeter(){
        perimeter = 0;
        for (int i = 0; i < vertices.size() - 1; i++){
            perimeter += getLength(vertices[0], vertices[vertices.size() - 1]);
        }
    }

public:
    CClosedBroken() = default;
    CClosedBroken(std::vector <CPoint> arr, int L) : CBroken(arr, L){}
};

class CPolygon : public CFigure{
private:
    float perimeter; float square; int size;
    void isFigure () override {
        if (size < 4) {
            throw std::runtime_error("It's not a Polygon\n");
        }
    }

    void setPerimeter(){
        perimeter = 0;
        for (int i = 0; i < vertices.size() - 1; i++){
            perimeter += getLength(vertices[i], vertices[i+1]);
        }
    }

    void setSquare(){
        square = 0;
        for (int i = 0; i < vertices.size() - 1; i++){
            square += vertices[i].getX() * vertices[i+1].getY();
        }
        square += vertices[vertices.size() - 1].getX() * vertices[0].getY();
        for (int i = 0; i < vertices.size() - 1; i++){
            square -= vertices[i + 1].getX() * vertices[i].getY();
        }
        square -= vertices[0].getX() * vertices[vertices.size() - 1].getY();
        square = (0.5) * abs(square);
    }
public:
    CPolygon(std::vector<CPoint> arr, int size_){
        if (isConvex(arr)){
            size = size_;
            isFigure();
            for (int i = 0; i < size_; i++){
                vertices.push_back(arr[i]);
            }
            setPerimeter();
            setSquare();
        } else {
            throw std::runtime_error("It's not a convex Polygon");
        }
    }

    float getSquare() override{
        return square;
    }

    float getPerimeter() override{
        return perimeter;
    }

    CPolygon (const std::vector <CPoint> &arr){
        vertices = arr;
    }

    CPolygon& operator = (const CPolygon &p){
        if (!isConvex(p.vertices)){
            throw std::runtime_error("It's not convex polygon\n");
        } else {
            return *this;
        }
    }

    ~CPolygon(){
        std::cout << "Destruction of the Polygon" << "\n";
    }

};

class CTriangle : public CFigure{
private:
    float perimeter; float square; int size;
    void isFigure() override{
        if (size != 3)
            throw std::runtime_error("It is not a triangle\n");
    }

    void setPerimeter(){
        perimeter = 0;
        for (int i = 0; i < 2; i++){
            perimeter += getLength(vertices[i], vertices[i + 1]);
        }
    }

    void setSquare(){
        square = 0;
        float p = perimeter / 2;
        float a = getLength(vertices[0], vertices[1]);
        float b = getLength(vertices [1], vertices[2]);
        float c = getLength(vertices[0], vertices[2]);
        
        square = sqrt(p * (p - a) * (p - b) * (p - c));
    }

public:
    CTriangle(std::vector<CPoint> arr, int size_){
        if (isConvex(arr)){
            size = size_;
            isFigure();
            for (int i = 0; i < 3; i ++){
                vertices.push_back(arr[i]);
            }
        } else {
            throw std::runtime_error("It's not convex triangle");
        }
    }

    float getSquare() override{
        setSquare();
        return square;
    }

    float getPerimeter() override{
        setPerimeter();
        return perimeter;
    }

    CTriangle(const std::vector <CPoint> &arr){
        vertices = arr;
    }

    CTriangle& operator = (const CTriangle &p){
        if (!isConvex(p.vertices)){
            throw std::runtime_error ("It's not convex triangle\n");
        } else {
            return *this;
        }
    }

    ~CTriangle(){
        std::cout << "Destructor of Triangle\n";
    }
};

class CTrapezoid : public CFigure{
private:
    float perimeter; float square; int size;

    void isFigure() override{
        float a = getLength(vertices[1], vertices[2]);
        float b = getLength(vertices[0], vertices[3]);

        float angle1 = getAngle(vertices[0], vertices[1], vertices[2]) * 180 / M_PI;
        float angle2 = getAngle(vertices[3], vertices[0], vertices[1]) * 180 / M_PI;

        if ((a != b) && (angle1 + angle2 == (float) 180))
            throw std::runtime_error("It's not trapezoid");
    }

    void setPerimeter(){
        perimeter = 0;
        for (int i = 0; i < vertices.size() - 1; i++){
            perimeter += getLength(vertices[i], vertices[i + 1]);
        }
    }

    void setSquare(){
        square = 0;
        float p = perimeter / 2;
        float a = getLength(vertices[0], vertices[1]);
        float b = getLength(vertices [1], vertices[2]);
        float c = getLength(vertices[2], vertices[3]);
        float d = getLength(vertices[3], vertices[0]);
        square = ((a + b) / abs(a - b)) * sqrt(p * (p - a) * (p - b) * (p - a - c) * (p - a -d));
    }

public:
    CTrapezoid(std::vector <CPoint> arr, int size_) {
        vertices = arr;
        if (isConvex(arr)){
            size = size_;
            isFigure();
        } else {
            throw std::runtime_error("It's not convex trapezoid");
        }
    }

    float getSquare() override{
        setSquare();
        return square;
    }

    float getPerimeter() override{
        setPerimeter();
        return perimeter;
    }

    float getAngle(const CPoint &a, const CPoint &b, const CPoint &c){
        float angle;
        angle = abs(atan2(a.getY() - b.getY(), a.getX() - b.getX()) - atan2(c.getY() - b.getY(), c.getX() - b.getX()));
        return angle;
    }

    CTrapezoid& operator = (const CTrapezoid &p){
        if (!isConvex(p.vertices)){
            throw std::runtime_error ("It's not a convex trapezoid\n");
        } else {
            return *this;
        }
    }

    ~CTrapezoid() {
        std::cout << "Destruction of trapezoid\n";
    }

};

class CRegularPolygon : public CFigure {
private:
    float perimeter; float square; int size;
    void setPerimeter(){
        perimeter = 0;
        for (int i = 0; i < vertices.size() - 1; i++){
            perimeter += getLength(vertices[i], vertices[i + 1]);
        }
    }

    void setSquare(){
        square = 0;
        int n = vertices.size();
        float a = getLength(vertices[0], vertices[1]);
        square = abs((n * (a * a)) / 4 * tan(360 / 2 * n));
    }

    void isFigure() override {
        bool result;
        float a = getLength(vertices[0], vertices[1]);
        float b = getLength(vertices [1], vertices[2]);
        float c = getLength(vertices[2], vertices[3]);

        if ((a == b) && (a == c)){
            result = true;
        } else {
            result = false;
        }

        if (size < 4 || !result)
            throw std::runtime_error("This is not a Regular Polygon\n");
    }

public:
    CRegularPolygon(std::vector <CPoint> arr, int size_) {
        vertices = arr;
        if (isConvex(arr)){
            size = size_;
            isFigure();
        } else {
            throw std::runtime_error("It's not convex regular Polygon");
        }
    };

    float getSquare() override{
        setSquare();
        return square;
    }

    float getPerimeter() override{
        setPerimeter();
        return perimeter;
    }
    explicit CRegularPolygon(const std::vector <CPoint> &m) {
        vertices = m;
    }

    CRegularPolygon& operator = (const CTrapezoid &p){
        if (!isConvex(p.vertices)){
            throw std::runtime_error ("It's not a convex regular polygon");
        } else {
            return *this;
        }
    }

    ~CRegularPolygon() {
        std::cout << "Destruction of trapezoid\n";
    }
};


int main(){
    //Point
    std::cout << "POINT\n";
    CPoint point{};
    point.set(5, 3);
    CPoint point1(point);

    point.Print();
    point1.Print();

    std::cout <<"\n";

    //Broken
    std::cout << "BROKEN\n";
    std::vector<CPoint> Points(4);
    for(auto &Point : Points){
        Point.set((mersenne() % 100) + 1, (mersenne() % 100) + 1);
    }
    CBroken broke(Points, 4);
    broke.getData();
    std::cout << "Perimeter = " <<broke.getPerimeter() << "\n";
    std::cout << "Square = " <<broke.getSquare() << "\n";
    CBroken broke1(broke);
    broke1.getData();
    std::cout << "\n";

    //Closed Broken
    std::cout << "CLOSED BROKEN\n";
    std::vector <CPoint> CrossedPoints(4);
    for (auto &CrossedPoint : CrossedPoints){
        CrossedPoint.set((mersenne() % 100) + 1, (mersenne() % 100) + 1);
    }
    CClosedBroken cl_broken(CrossedPoints, 3);
    CClosedBroken cl_broken2(cl_broken);
    cl_broken.getData();
    std::cout << "Perimeter = " << cl_broken.getPerimeter() << "\n";
    std::cout << "Square = " << cl_broken.getSquare() << "\n";
    std::cout << "\n";

    //Polygon
    std::cout << "POLYGON\n";
    std::vector <CPoint> polyPoints(4);
    polyPoints[0].set(5, 2);
    polyPoints[1].set(1,7);
    polyPoints[2].set(0,1);
    polyPoints[3].set(4,2);
    CPolygon poly(polyPoints, 4);
    CPolygon poly2(poly);
    poly.getData();
    std::cout << "Perimeter = " << poly.getPerimeter() << "\n";
    std::cout << "Square = " << poly.getSquare() << "\n";
    std::cout << "\n";

    //Triangle
    std::cout << "TRIANGLE\n";
    std::vector <CPoint> triVertices(3);
    triVertices[0].set(6, 4);
    triVertices[1].set(10, 3);
    triVertices[2].set(9,9);
    CTriangle tri(triVertices, 3);
    CTriangle tri2(tri);
    tri.getData();
    std::cout << "Perimeter = " << tri.getPerimeter() << "\n";
    std::cout << "Square = " << tri.getSquare() << "\n";
    std::cout << "\n";

    //Trapezoid
    std::cout << "TRAPEZOID\n";
    std::vector <CPoint> trapVertices (4);
    trapVertices[0].set(1,1);
    trapVertices[1].set(2,5);
    trapVertices[2].set(4, 5);
    trapVertices[3].set(6, 1);
    CTrapezoid trap(trapVertices, 4);
    CTrapezoid trap2(trap);
    trap.getData();
    std::cout << "Perimeter = " << trap.getPerimeter() << "\n";
    std::cout << "Square = " << trap.getSquare() << "\n";
    std::cout << "\n";

    //Regular Polygon
    std::cout << "REGULAR POLYGON\n";
    std::vector<CPoint> regularVertices(6);
    regularVertices[0].set(-2.5, -6);
    regularVertices[1].set(2.5, -6);
    regularVertices[2].set(5.5, -2);
    regularVertices[3].set(2.5, 2);
    regularVertices[4].set(-2.5, 2);
    regularVertices[5].set(-5.5, -2);
    regularVertices[6].set(-2.5, -6);
    CRegularPolygon reg_poly(regularVertices, 6);
    CRegularPolygon reg_poly2(reg_poly);
    reg_poly.getData();
    std::cout << "Perimeter = " << reg_poly.getPerimeter() << "\n";
    std::cout << "Square = " << reg_poly.getSquare() << "\n";
    std::cout << "\n";
}
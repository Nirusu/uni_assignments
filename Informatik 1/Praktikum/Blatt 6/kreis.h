class Kreis
{
private:
    double x, y, radius;
public:
    Kreis();
    Kreis(double ax, double ay, double aradius);
    void setzeX(double x);
    void setzeY(double y);
    void setzeRadius(double radius);
    double getX();
    double getY();
    double getRadius();
    double umfang();
    double flaeche();
    bool liegtInnerhalb(double ax, double ay);
};

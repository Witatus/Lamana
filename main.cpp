#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <sstream>
using namespace std;

struct Punkt{
    double x,y;
    Punkt(double x=0, double y=0) : x(x), y(y) {}
    string toXML(){
        ostringstream out;
        out << "<Punkt x=\"" << x << "\" y=\"" << y << "\"/>";
        out<< "AAAA";
        return out.str();
    }
};

class Lamana{
public:
//    Lamana(){}
    void wstawPunkt(const Punkt& punkt){
        punkty.push_back(punkt);
    }
    double dlugosc(){
        double d = 0;
        for(unsigned i=1;i<punkty.size();++i){
            double x = punkty[i-1].x - punkty[i].x;
            double y = punkty[i-1].y - punkty[i].y;
            d += sqrt(x*x+y*y);
        }
        return d;
    }
    bool czyZamknieta(){
        return punkty.size()>0 and
                punkty.front().x == punkty.back().x and
                punkty.front().y == punkty.back().y;
    }

    void przesun(const Punkt& punkt){
        for(Punkt& p : punkty){
            p.x += punkt.x;
            p.y += punkt.y;
        }
    }

    void pokaz(){
        cout << this->toString() << endl;
    }

    string toString(){
        ostringstream out;
        out << "[";
        for(Punkt& p : punkty)
            out << "(" << p.x << "," << p.y << ")";
        out << "]";
        return out.str();
    }
    string toXML(){
        ostringstream out;
        out << "<Lamana>\n";
        for(Punkt& p : punkty)
            out << p.toXML() << "\n";
        out << "</Lamana>";
        return out.str();
    }
    void obroc(const Punkt& sr, double a){
        double c = cos(a), s = sin(a);
        for(Punkt& p : punkty){
            p.x -= sr.x;
            p.y -= sr.y;
            double x = c*p.x - s*p.y;
            p.y = sr.y + s*p.x + c*p.y;
            p.x = x + sr.x;
        }
    }
private:
    std::vector<Punkt> punkty;
};

int main(){
    Lamana lamana;
    lamana.wstawPunkt(Punkt(1,1));
    lamana.wstawPunkt(Punkt(4,5));
    lamana.wstawPunkt(Punkt(1,1));
    lamana.pokaz();
    cout << lamana.dlugosc() << endl;
    cout << lamana.czyZamknieta() << endl;
    lamana.przesun(Punkt(2,3));
    lamana.pokaz();

    lamana.obroc(Punkt(1,1),M_PI/2);
    lamana.pokaz();

    Punkt punkt(3,4);
    cout << punkt.toXML() << endl;
    cout << lamana.toXML() << endl;
}
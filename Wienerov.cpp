#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>

class Trajektoria {
private:
    std::vector<double> x;
    std::vector<double> y;
public:
    Trajektoria() {};
    Trajektoria(std::vector<double> X, std::vector<double> Y) { x = X; y = Y; }
    std::vector<double> getX() {
        return x;
    }
    std::vector<double> getY() {
        return y;
    }
};

double rand_gen() {
    return ((double)(rand()) + 1.) / ((double)(RAND_MAX)+1.);
}
double normalRandom() {
    double v1 = rand_gen();
    double v2 = rand_gen();
    return cos(2 * M_PI * v2) * sqrt(-2. * log(v1));
}

Trajektoria generuj(std::vector<double> x, Trajektoria T) {
    std::vector<double> dS;
    double krok = x[1] - x[0];
    for (int i = 0; i <= x.size()-1; i++) {
        dS.push_back(sqrt(krok) * normalRandom());
    }
    double S0 = 0;
    std::vector<double> S;
    for (int i = 0; i <= x.size()-1; i++) {
        S.push_back(S0);
        S0 += dS[i];
    }
    Trajektoria P(x, S);
    T = P;
    return T;
}

void ulozenie(std::vector<Trajektoria> T, int d) {
    std::fstream out;
    out.open("Trajektorie.txt", std::ios::out);
    double vyhovuje = 0;
    if (out.is_open()) {
        out << "x,y,typ,color" << std::endl;
        for (int i = 0; i <= d; i++) {
            if (T.at(i).getY().at(1) > 0 && T.at(i).getY().at(2) < 0) {
                vyhovuje++;
            }
            for (int j = 0; j <= T.at(i).getX().size()-1; j++) {
                out << T.at(i).getX().at(j) << "," << T.at(i).getY().at(j) << "," << i << ",";
                if (T.at(i).getY().at(1) > 0 && T.at(i).getY().at(2) < 0) {
                   out << 25 << std::endl;
                }
                else {
                    out << 100 << std::endl;
                }
            }
        }
        out.close();
        std::cout << "Pravdepodobnost je " << vyhovuje / (double)(d + 1);
    }
    else {
        std::cout << "neotvorilo subor";
    }
}

int main()
{
   srand((unsigned)time(NULL));
   int  n = 1000;
   int d = 99;
   double T = 1.;
   double krok = T / (n);
   std::vector<double> casy;
   casy.push_back(0);
   for (int i = 1; i <= n-1; i++) {
       casy.push_back(casy[i - 1] + krok);
   }
   std::vector<Trajektoria> traj;
   for (int i = 0; i <= d; i++) {
       std::vector<double> B;
       Trajektoria TT;
       TT = generuj(casy, TT);
       traj.push_back(TT);
   }
   ulozenie(traj, d);    
}
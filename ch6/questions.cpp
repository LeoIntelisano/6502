#include <iostream>
#include <vector>
#include <cmath>

struct Thread {
    double exec_time;
    double exec_period;
};

struct Neuron {
    double output;
    double weight;
};

bool RMS(const std::vector<Thread>& threads) {
    bool sum = 0;
    for (size_t i = 0; i < threads.size(); i++){
        sum += (threads.at(i).exec_time/threads.at(i).exec_period) > (threads.size()*(pow(2, 1/(double)threads.size())) - 1);
    }
    return sum;
}

void DCT(const std::vector<double>& coefs, std::vector<double>& buffer) {
    double sum = 0;
    for (size_t k = 0; k < coefs.size(); k++){
        for (size_t n = 0; n < coefs.size(); n++){
            sum += coefs.at(n)*cos(3.14/(double)coefs.size()*(n + 0.5)*k);
        }
        buffer.emplace_back(sum);
        sum = 0;
    }
}

double activation(const std::vector<Neuron>& neurons){
    double sum = 0.0;
    for (size_t i = 0; i < neurons.size(); i++){
        sum+= neurons.at(i).output*neurons.at(i).weight;
    }
    return (exp(sum) - exp(-sum))/(exp(sum) + exp(-sum));
}


int main()
{
    std::vector<Thread> td {{50, 100}, {100, 500}, {120, 1000}};
    std::cout << RMS(td);
    
    std::vector<double> x {0.5, 0.2, 0.7, -0.6, 0.4, -0.2, 1.0, -0.3};
    std::vector<double> out;
    
    DCT(x, out);
    for (auto i : out){
        std::cout << i << ' ';
    }
    std::cout << "\n";

    std::vector<Neuron> neurons{{0.6, 0.4}, {-0.3, 0.8}, {0.5, -0.2}};
    std::cout << "Activation: " << activation(neurons);
}

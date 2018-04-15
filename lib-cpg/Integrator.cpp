#include "Integrator.h"

/**
 * Integrator constructor
 * @see Integrator(int count, std::vector<std::function<double (double, std::vector<double>)> > functions, std::vector<double> variables)
 */
Integrator::Integrator(): count(0), functions(), variables(), k(), l(), m(), lvariables(), mvariables(), nvariables()
{
    
}

/**
 * Integrator constructor
 * @param count number of equations
 * @param functions equations to be solved
 * @param variables variables vector
 * @see Integrator()
 */
Integrator::Integrator(int count, std::vector<std::function<double (double, std::vector<double>)> > functions, std::vector<double> variables) {
    this->count = count;
    this->functions = functions;
    this->variables = variables;

    k = std::vector<double>(count, 0.0);
    l = std::vector<double>(count, 0.0);
    m = std::vector<double>(count, 0.0);
    lvariables = std::vector<double>(count, 0.0);
    mvariables = std::vector<double>(count, 0.0);
    nvariables = std::vector<double>(count, 0.0);
}

Integrator::~Integrator() {
}

std::vector<double> Integrator::rk4(double t, double dt) {
    for (int i = 0; i < count; i++) {
        k[i] = dt * functions[i](t, variables);
        lvariables[i] = variables[i] + k[i] / 2.0;
    }
    for (int i = 0; i < count; i++) {
        l[i] = dt * functions[i](t + dt /2.0, lvariables);
        mvariables[i] = variables[i] + l[i] / 2.0;
    }
    for (int i = 0; i < count; i++) {
        m[i] = dt * functions[i](t + dt / 2.0, mvariables);
        nvariables[i] = variables[i] + m[i];
    }
    for (int i = 0; i < count; i++) {
        variables[i] = variables[i] + (k[i] + 2.0*l[i] + 2.0*m[i] + dt*functions[i](t, nvariables)) / 6.0;
    }

    return variables;
}

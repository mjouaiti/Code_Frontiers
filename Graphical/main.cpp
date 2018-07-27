//
//  main.cpp
//
//  Code_Frontiers
//  Copyright (C) 2018  Université de Lorraine - CNRS
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created by Melanie Jouaiti on 29/09/2017.
//

#include <iostream>
#include <math.h>

#ifdef __APPLE__
#   define _OSX
#elif defined(__linux__)
#   define _LINUX
#endif

#include "../../Grapher/src/Grapher.h"
#include "../Simulation/Simulation2.h"
#include "../common.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

std::vector<std::string> mico_names = {"Mico_joint1", "Mico_joint2", "Mico_joint3", "Mico_joint4", "Mico_joint5", "Mico_joint6"};

GLint WIDTH = 1024, HEIGHT = 768;

int main()
{
    Grapher* grapher;
    grapher = new Grapher(WIDTH, HEIGHT, TMAX, NB_VARIABLES);
    grapher->setDisplayedVariables(0, {_sigma_s2E, _sigma_s2F, _sigma_s3E, _sigma_s3F});
    grapher->setDisplayedVariables(1, {_F2, _s2});
    grapher->setDisplayedVariables(2, {_F3, _s3});
    grapher->setDisplayedVariables(3, {_Af_2E, _Af_2F, _Af_3E, _Af_3F});
    
    Simulation2 simulation(mico_names);
    simulation.init();

    float t = 0.0, dt = 0.01;
    
    while (t < 10 && !grapher->shouldClose())
    {
        grapher->step(simulation.step());
        t += dt;
    }
    
    return 0;
}

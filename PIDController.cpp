//
//  PIDController.cpp
//  Handshaking
//
//  Created by Melanie Jouaiti on 08/10/2017.
//  Copyright © 2017 Melanie Jouaiti. All rights reserved.
//

#include "PIDController.h"
#include <cmath>
#define PI acos(-1)

/**
 * PID Controller Constructor
 * @see PIDController(const double kp, const double ki, const double kd, const double dt)
 */
PIDController::PIDController(): m_kp(0), m_ki(0), m_kd(0), m_init(true),
                                m_pidCumulativeErrorForIntegralParam(0),
                                m_pidLastErrorForDerivativeParam(0),
                                m_targetPos(0)
{
    
}

/**
 * PID Controller Constructor
 * @param kp P gain (double)
 * @param ki I gain (double)
 * @param kd D gain (double)
 * @param dt timestep (double)
 * @see PIDController()
 */
PIDController::PIDController(const double kp, const double ki,
                             const double kd, const double dt): m_kp(kp), m_ki(ki),
                                                                m_kd(kd), m_dt(dt), m_init(true),
                                                                m_pidCumulativeErrorForIntegralParam(0),
                                                                m_pidLastErrorForDerivativeParam(0),
                                                                m_targetPos(0)
{
    
}

/**
 * PID Controller Destructor
 */
PIDController::~PIDController()
{
    
}

/**
 * updates the controller. Here we transform velocity control into position control to use the traditional PID formulaes.
 * @param currentPos current joint angular position (double)
 * @param targetVel target velocity (double)
 * @return velocity to be applied to the joint (double)
 */
double PIDController::update(const double currentPos, const double targetVel)
{
    if(m_init)
    {
        m_pidCumulativeErrorForIntegralParam = 0;
        m_targetPos = currentPos;
    }
    
    m_targetPos += targetVel * m_dt;
    float errorValue = m_targetPos - currentPos;
    float ctrl = errorValue * m_kp;
    if(m_ki!=0)
        m_pidCumulativeErrorForIntegralParam = m_pidCumulativeErrorForIntegralParam + errorValue * m_dt;
    else
        m_pidCumulativeErrorForIntegralParam = 0;
    
    ctrl = ctrl + m_pidCumulativeErrorForIntegralParam * m_ki;
    
    if(!m_init)
        ctrl = ctrl + (errorValue - m_pidLastErrorForDerivativeParam) * m_kd / m_dt;
    
    m_pidLastErrorForDerivativeParam = errorValue;
    
    if(m_init)
        m_init = false;
    
    float maxVelocity = ctrl / m_dt;
    float velUpperLimit = 90.0 / 180.0 * PI;
    if(maxVelocity > velUpperLimit)
        maxVelocity = velUpperLimit;
    if(maxVelocity < -velUpperLimit)
        maxVelocity = -velUpperLimit;
    return maxVelocity;
}

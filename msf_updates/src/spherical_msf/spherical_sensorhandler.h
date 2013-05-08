/*

Copyright (c) 2010, Stephan Weiss, ASL, ETH Zurich, Switzerland
You can contact the author at <stephan dot weiss at ieee dot org>
Copyright (c) 2012, Simon Lynen, ASL, ETH Zurich, Switzerland
You can contact the author at <slynen at ethz dot ch>
 Copyright (c) 2012, Markus Achtelik, ASL, ETH Zurich, Switzerland
 You can contact the author at <acmarkus at ethz dot ch>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
 * Neither the name of ETHZ-ASL nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ETHZ-ASL BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include <msf_core/msf_sensormanagerROS.h>
#include <geometry_msgs/PointStamped.h>

namespace msf_spherical_position{

template<typename MEASUREMENT_TYPE, typename MANAGER_TYPE>
class AngleSensorHandler : public msf_core::SensorHandler<typename msf_updates::EKFState>
{
private:

  msf_core::Vector2 z_a_; ///< angle measurement
  double n_za_; ///< position measurement noise
  double delay_;        ///< delay to be subtracted from the ros-timestamp of the measurement provided by this sensor

  ros::Subscriber subPointStamped_;
  bool use_fixed_covariance_;
  bool provides_absolute_measurements_; ///<does this sensor measure relative or absolute values

  void measurementCallback(const geometry_msgs::PointStampedConstPtr & msg);
public:
  typedef MEASUREMENT_TYPE measurement_t;
  AngleSensorHandler(MANAGER_TYPE& meas, std::string topic_namespace, std::string parameternamespace);
  //used for the init
  msf_core::Vector2 getAngleMeasurement(){
    return z_a_;
  }
  //setters for configure values
  void setNoises(double n_za);
  void setDelay(double delay);
};


template<typename MEASUREMENT_TYPE, typename MANAGER_TYPE>
class DistanceSensorHandler : public msf_core::SensorHandler<typename msf_updates::EKFState>
{
private:

  msf_core::Vector1 z_d_; ///< angle measurement
  double n_zd_; ///< position measurement noise
  double delay_;        ///< delay to be subtracted from the ros-timestamp of the measurement provided by this sensor

  ros::Subscriber subPointStamped_;

  bool use_fixed_covariance_;
  bool provides_absolute_measurements_; ///<does this sensor measure relative or absolute values

  void measurementCallback(const geometry_msgs::PointStampedConstPtr & msg);
public:
  typedef MEASUREMENT_TYPE measurement_t;
  DistanceSensorHandler(MANAGER_TYPE& meas, std::string topic_namespace, std::string parameternamespace);
  //used for the init
  msf_core::Vector1 getDistanceMeasurement(){
    return z_d_;
  }
  //setters for configure values
  void setNoises(double n_za);
  void setDelay(double delay);
};
}
#include "spherical_sensorhandler.hpp"

#endif /* POSITION_SENSOR_H */
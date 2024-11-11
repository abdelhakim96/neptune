/* ----------------------------------------------------------------------------
 * Nanyang Technological University
 * Authors: Cao Muqing, et al.
 * Acknowledgement: Jesus Tordesillas
 * See LICENSE file for the license information
 * -------------------------------------------------------------------------- */

#include "neptune_ros.hpp"
#include <ros/callback_queue.h>
#include <ros/rate.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "neptune");

  ros::NodeHandle nh1("~");
  ros::NodeHandle nh2("~");
  ros::NodeHandle nh3("~");

  // Concurrency and parallelism in ROS:
  // https://nicolovaligi.com/concurrency-and-parallelism-in-ros1-and-ros2-application-apis.html

  ros::CallbackQueue custom_queue1;
  ros::CallbackQueue custom_queue2;
  ros::CallbackQueue custom_queue3;

  nh1.setCallbackQueue(&custom_queue1);
  nh2.setCallbackQueue(&custom_queue2);
  nh3.setCallbackQueue(&custom_queue3);

  NeptuneRos NeptuneRos(nh1, nh2, nh3);

  ros::AsyncSpinner spinner1(1, &custom_queue1);  // 1 thread for the custom_queue1
  ros::AsyncSpinner spinner2(1, &custom_queue2);  // 1 thread for the custom_queue2
  ros::AsyncSpinner spinner3(1, &custom_queue3);  // 1 thread for the custom_queue3

  spinner1.start();  // start spinner of the custom queue 1
  spinner2.start();  // start spinner of the custom queue 2
  spinner3.start();  // start spinner of the custom queue 3

  // Set the loop rate to 5 Hz
  ros::Rate rate(5);

  while (ros::ok()) {
    rate.sleep();  // Sleep to maintain 5 Hz rate
  }

  ros::waitForShutdown();
  return 0;
}

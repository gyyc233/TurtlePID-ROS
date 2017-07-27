#include <ros/ros.h>
#include <std_msgs/Float64.h>

std_msgs::Float64 heading;

ros::Publisher setpoint_publisher;
ros::Timer heading_timer;
void headingTimerHandler(const ros::TimerEvent&);

int main(int argc, char **argv) {
  ros::init(argc, argv, "setpoint_node");
  ros::NodeHandle nh;

  heading.data = 0;

  setpoint_publisher = nh.advertise<std_msgs::Float64>("/setpoint", 1, true);
  heading_timer  = nh.createTimer(ros::Duration(5), &headingTimerHandler);

  ros::spin();
  return 0;
}

void headingTimerHandler(const ros::TimerEvent&) {
  heading.data += M_PI_2;

  if (heading.data >= 2 * M_PI) {
    heading.data = 0;
  }

  setpoint_publisher.publish(heading);
}

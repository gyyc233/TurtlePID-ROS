#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>

bool control_publish = false;
bool state_publish = false;

ros::Subscriber control_sub;
ros::Subscriber state_sub;

ros::Publisher control_pub;
ros::Publisher state_pub;

ros::Timer timer;

void controlHandler(const std_msgs::Float64 &msg);
void stateHandler(const turtlesim::Pose &msg);
void timerHandler(const ros::TimerEvent&);

int main(int argc, char **argv) {
  ros::init(argc, argv, "transformer");
  ros::NodeHandle nh;

  control_sub = nh.subscribe("/control_effort", 10, &controlHandler);
  state_sub = nh.subscribe("/turtle1/pose", 10, &stateHandler);

  control_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1, true);
  state_pub = nh.advertise<std_msgs::Float64>("/state", 1, true);

  timer = nh.createTimer(ros::Duration(0.5), &timerHandler);

  ros::spin();
  return 0;
}

void controlHandler(const std_msgs::Float64 &msg) {
  if (control_publish) {
    control_publish = false;
    geometry_msgs::Twist cmd;

    cmd.angular.z = msg.data;

    control_pub.publish(cmd);
  }
}
void stateHandler(const turtlesim::Pose &msg) {
  //if(state_publish) {
  state_publish = false;
  std_msgs::Float64 state;
  state.data = msg.theta;

  //while (abs(state.data) > 2 * M_PI) {
    //if (state.data < 0) {
      //state.data += 2 * M_PI;
    //} else {
      //state.data -= 2 * M_PI;
    //}
  //}

  state_pub.publish(state);
  //}
}

void timerHandler(const ros::TimerEvent&) {
  control_publish = true;
  state_publish = true;
}

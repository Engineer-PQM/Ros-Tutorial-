#include <iostream>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

using namespace std ; 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  double P_x , P_y ;
  char choice_to_continue = 'Y';
  bool run = true;
  while(run) {   
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  cout << "Hay nhap Toa do  \n "; 
  cout << "Nhap x = "; 
  cin >> P_x ;
  cout << "Nhap y = ";
  cin >> P_y ;
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = P_x;
  goal.target_pose.pose.position.y = P_y;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Da nhan thong tin ");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Done");
  else
    ROS_INFO("Done");
  do {
      cout << "\n You want to move on? (Y/N)" << endl;
      cin >> choice_to_continue;
      choice_to_continue = tolower(choice_to_continue); // Put your letter to its lower case
  } while (choice_to_continue != 'n' && choice_to_continue != 'y'); 
 
  if(choice_to_continue =='n') {
        run = false;
    }  
  }
  return 0;
}

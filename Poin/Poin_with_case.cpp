
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
 
using namespace std;
 
// Action specification for move_base
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 
int main(int argc, char** argv){
   
  // Connect to ROS
  ros::init(argc, argv, "simple_navigation_goals");
 
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
 
  // Wait for the action server to come up so that we can begin processing goals.
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
 
  int user_choice = 4;
  char choice_to_continue = 'Y';
  bool run = true;
     
  while(run) {
 
    // Ask the user where he wants the robot to go?
    cout << "\nWhere do you want the robot to go?" << endl;
    cout << "\n1 = position number 1" << endl;
    cout << "2 = position number 2" << endl;
    cout << "3 = position number 3" << endl;
    cout << "4 = position number 4" << endl;
    cout << "\nEnter a number: ";
    cin >> user_choice;
 
    // Create a new goal to send to move_base 
    move_base_msgs::MoveBaseGoal goal;
 
    // Send a goal to the robot
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
         
    bool valid_selection = true;
 
    // Use map_server to load the map of the environment on the /map topic. 
    // Launch RViz and click the Publish Point button in RViz to 
    // display the coordinates to the /clicked_point topic.
    switch (user_choice) {
      case 1:
        cout << "\nGoal Location: position number 1\n" << endl;
        goal.target_pose.pose.position.x = 1.5;
        goal.target_pose.pose.position.y = 0.8;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 2:
        cout << "\nGoal Location: position number 2\n" << endl;
        goal.target_pose.pose.position.x = 1.5;
        goal.target_pose.pose.position.y = -0.8;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 3:
        cout << "\nGoal Location: position number 3\n" << endl;
        goal.target_pose.pose.position.x = -0.1;
        goal.target_pose.pose.position.y = -1.95;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 4:
        cout << "\nGoal Location: position number 4\n" << endl;
        goal.target_pose.pose.position.x = -1.9;
        goal.target_pose.pose.position.y = -0.1;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      default:
        cout << "\nInvalid selection. Please try again.\n" << endl;
        valid_selection = false;
    }       
         
    // Go back to beginning if the selection is invalid.
    if(!valid_selection) {
      continue;
    }
 
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
 
    // Wait until the robot reaches the goal
    ac.waitForResult();
 
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("The robot has arrived at the goal location");
    else
      ROS_INFO("The robot failed to reach the goal location for some reason");
         
    // Ask the user if he wants to continue giving goals
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

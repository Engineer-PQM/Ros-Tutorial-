#!/usr/bin/env python
# license removed for brevity

import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal

def readfile():
    #filename = "demofile.txt"
    with open("/home/mm/catkin_ws/src/simple_navigation_goals/src/demofile.txt") as my_file:
        for line in my_file:
         sothu = line.split(",")
         x = sothu[1]
         y = sothu[2]
         #print(x)
         #print(y)
         return [x, y]


def movebase_client():

    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
    client.wait_for_server()

    run = readfile()
    print(run[0])
    print(run[1])
    print("Xet gia tri x , y ")


    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()  
    goal.target_pose.pose.position.x = run[0]
    goal.target_pose.pose.position.y = run[1]


    goal.target_pose.pose.orientation.w = 1.0

    client.send_goal(goal)
    wait = client.wait_for_result()
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
    else:
        return client.get_result()

if __name__ == '__main__':
    try:
        rospy.init_node('MinhTestMove')
        result = movebase_client()
        if result:
            rospy.loginfo("Goal execution done!")
    except rospy.ROSInterruptException:
        rospy.loginfo("Navigation test finished.")

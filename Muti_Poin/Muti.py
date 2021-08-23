#!/usr/bin/env python
# license removed for brevity

import roslib 
import rospy
import actionlib
import geometry_msgs
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import tf.transformations
import time

def movebase_client(x,y):
    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
    client.wait_for_server()

    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()
    goal.target_pose.pose.position.x = x
    goal.target_pose.pose.position.y = y
    goal.target_pose.pose.orientation.w = 1.0

    client.send_goal(goal)
    wait = client.wait_for_result()
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
        time.sleep(canceltime)
        print 'Cancelling current goal...'
        client.cancel_goal()
    else:
        client.wait_for_result()
        return client.get_result()

if __name__ == '__main__':
    try:
        rospy.init_node('movebase_client_py')
        print 'Testing goal (4.0, 0) with no (invalid) headig...'
        result = movebase_client(4.0549993515, 0.229999542236)
        print 'Testing goal (1.8, 2, 3.14159)...'
        result = movebase_client( 0.414999872446, -0.460000097752)
        print 'Testing goal (1.8, 1, 1.5707)...'
        result = movebase_client( 1.5649998188, 2.24999952316)

        if result:
            rospy.loginfo("Hoan Thanh di toi muc tieu ")
    except rospy.ROSInterruptException:
        rospy.loginfo("Navigation test finished.")

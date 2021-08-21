#!/usr/bin/python
# coding: UTF-8

import rospy
from move_base_msgs.msg import MoveBaseActionGoal

rospy.init_node('topic_publisher')
pub = rospy.Publisher('/move_base/goal', MoveBaseActionGoal, queue_size=5)
rate = rospy.Rate(0.1)

target_pos=MoveBaseActionGoal()
target_pos.goal.target_pose.header.frame_id = "map"
target_pos.goal.target_pose.pose.position.x = 0.5
target_pos.goal.target_pose.pose.position.y = 0.5
target_pos.goal.target_pose.pose.orientation.w = 0.999607289662

count = 0
while not rospy.is_shutdown():
    target_pos.header.stamp = rospy.Time.now()
    target_pos.goal.target_pose.header.stamp = rospy.Time.now()
    pub.publish(target_pos)
    rate.sleep()
    count += 1
    print count

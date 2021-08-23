---
Date : Aug 2021
Author : Phạm Quang Minh 
Gmail : Engineer.pqm@gmail.com
---

## Threads
    Move (Robot) to known coordinates X,Y and W =1.

## REQUIREMENTS
This Project requires the following :

 * [Ubuntu 18.04 or newer](https://ubuntu.com/download/desktop)
 * [Ros Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)
 * [Turtlebot3](https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/)
 
## Usage
    1. (Bringup) Connect PC to a WiFi device and find the assigned IP address 
       https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/
       
    2. (Simulation) Can use Gazebo or use Stage , In this project we use Stage (contact by gmail above)

       
Commonly used commands

- Map
Depending on the usage environment, we have different maps , If Bringup run `roslaunch turtlebot3_bringup turtlebot3_robot.launch` , If Simulation world run `roslaunch turtlebot3_gazebo turtlebot3_world.launch` ....


- Key
`roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch`

- Auto run
`roslaunch turtlebot3_gazebo turtlebot3_simulation.launch` initialization map

- Slam
`roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping`


- Save_map
`rosrun map_server map_saver -f ~/map` create 2 files named : map (map.pgm and map.yaml)

- Rviz 
` roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml` User map from Slam (map.yaml)


## Configuration


NOTE : There are detailed explanations in each piece of code

## Explain (Vietsub nhé )


Chúng ta có thể điều khiển robot đến một mục tiêu, sử dụng base_move và amcl tuy nhiên amcl chỉ thuật là giá trị mang tính chất điều khiển động cơ không thể đạt được 1 số giá trị mang tích chất về goal ... 

#### TOPIC : Move_base 

 Đơn giản mà nói Move_base là 1 trong phần tử chính của ROS Navigation stack Nó di chuyển robot từ vị trí hiện tại của nó đến vị trí mục tiêu được published trong topic move_base/goal .

Mục tiêu điều hướng 2D trong Rviz để chỉ định vị trí và hướng mục tiêu. Vị trí này (x, y, z) và hướng (x, y, z, w) tuy nhiên w = 1 để không xoay trục tọa độ 

Mục tiêu của bài này là sử dụng Node để điều hướng thay vì sử dụng Rviz 

![Move_base](http://library.isr.ist.utl.pt/docs/roswiki/attachments/move_base/overview_tf.png)

Nếu để ý hơn 1 tý chúng ta sẽ có move_base_msgs.msg/MoveBaseGoal và move_base_msgs.msg/MoveBaseAction

File : move_base_msgs/MoveBaseAction.msg gồm có 

- MoveBaseActionGoal action_goal
- MoveBaseActionResult action_result
- MoveBaseActionFeedback action_feedback


        Quả Thực cái này rất dài nên khi nào sử dụng sẽ giải thích sau 

   Ta xét riêng từng cái ra thì ta được cấu trúc của move_base_msgs.msg/MoveBaseGoal như sau 

      geometry_msgs/PoseStamped target_pose
      Header header
        uint32 seq
        time stamp
        string frame_id
      geometry_msgs/Pose pose
        geometry_msgs/Point position
            float64 x
            float64 y
            float64 z
        geometry_msgs/Quaternion orientation
            float64 x
            float64 y
            float64 z
            float64 w
    
  Ta có thể dễ dàng xét được vị trí Goal cho Robot bằng cách thêm giá trị x/y vào MoveBaseGoal nếu ta xét id = "map" và như đã nói ta sẽ để w = 1 để đảm bảo không xoay trục tọa độ các giá trị còn lại có thể có hoặc không 
       
        moveBaseGoal.target_pose.header.frame_id = "map"
        moveBaseGoal.target_pose.pose.position.x = x
        moveBaseGoal.target_pose.pose.position.y = y
        moveBaseGoal.target_pose.pose.orientation.w = 1.0

Directory Poin : Poin and Poin (Từng điểm một)

- Base_Move (Cái này dễ , đơn giản chỉ sử dụng 1 node pub giá trị x/y lên moveBaseGoal)
- Move gồm cả 2 file .py và .cpp cả 2 file có ý nghĩa và nhiệm vụ như nhau chỉ là ngôn ngữ sử dụng (về cơ bản mà nói nó khác file Base_move ở chỗ nó tạo ra 1 cái action client và gọi với action definition file "MoveBaseAction")

- Move_ip(x and y coordinates entered from the keyboard)
- Move_with_case (use case replace input )

parameter storage position 

- Move_with_txt(data is stored as text)
- Move_with_dictionary(data is stored as dictionary)


Processing Muti-Poin

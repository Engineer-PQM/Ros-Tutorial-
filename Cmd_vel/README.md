---
Date : Aug 2021
Author : Phạm Quang Minh 
Gmail : Engineer.pqm@gmail.com
---

<h3 align="center">-------------------------------------</h3>



## Topic /Cmd_vel

 Convert Giá trị động cơ sang Twist 
 
`Giá trị Đã biết `

       Rpm = 3000 Cho từng bánh 
       Dạng vận tốc Analog (0 - 255)
       WHEEL_SEPARATION = 0.42m (Khoảng cách giữa 2 bánh )
       WHEEL_RADIUS = 0.075m = r ( bán kính bánh xe )
       d = 2r = 2 WHEEL_RADIUS = 150mm = 0.15 m
       Hộp giảm số 1/30 

Ta biết dạng của Topic /cmd_vel như sau 

    geometry_msgs/Vector3 linear
      float64 linear.x
      float64 linear.y
      float64 linear.z
    geometry_msgs/Vector3 angular
      float64 angular.x
      float64 angular.y
      float64 angular.z

Trong này chúng ta chỉ quan tâm tới 

- Linear.x  `m/s`   ( Vận tốc tuyến tính )
- Angular.z `Rad/s` ( Vận tốc góc ) 

## Algorithm

Ta xét Refer của 
[Turtlebot](https://github.com/ROBOTIS-GIT/OpenCR/blob/master/arduino/opencr_arduino/opencr/libraries/turtlebot3_ros2/src/turtlebot3/turtlebot3_motor_driver.cpp) 
ta có : 

    wheel_velocity[LEFT]   = (lin_vel - (ang_vel * wheel_separation / 2))  (1)
    wheel_velocity[RIGHT]  = (lin_vel + (ang_vel * wheel_separation / 2))  (2)
    
###  ⭐️  Linear.x

Giá trị quay tối đa của động cơ sau hộp giảm số 
 
    Rpm * (1/30) = 3000/30 = 100 vòng/phút 
    
Vì giá trị vận tốc tính toán là m/s 

    f = 100/60(s) = 1.666666 v/s
    
Chu Vi (C) với Pi ( ~ 3.14)

    (C) = d x Pi = 0.15 * 3.14 = 0.471 

Vận tốc của từng bánh 

    V = f * C = 1.666666 * 0.471 = 0.78499 m/s 

Xét để giá trị trùng với Refer như trên 

    Vận tốc bánh trái = wheel_velocity[LEFT]
    Vận tốc bánh phải = wheel_velocity[RIGHT]
    
![240779389_617990985833400_1602310391635025706_n](https://user-images.githubusercontent.com/82381342/131255930-9c834d89-a18c-49f7-abeb-c03be1364e51.png)
    
Vận tốc tuyến tính khi động cơ di chuyển thằng theo chiều X sẽ là 

    linear.x = (wheel_velocity[LEFT] + wheel_velocity[RIGHT] ) / 2

Bằng cách cộng phương trình (1) và (2) theo Refer như trên ta cũng có kết quả tương tự như sau 

    wheel_velocity[LEFT] + wheel_velocity[RIGHT] = 2 linear.x
    linear.x = (wheel_velocity[LEFT] + wheel_velocity[RIGHT] ) / 2
    
Tuy nhiên giá trị ta có đang ở dạng Analog (Max = 255 ) nên giá trị tỉ lệ là 

    0.78499/255 = 0.003078


###  ⭐️  Angular.z

Vì vận tốc góc được tính bằng Rad/s nên ta phải quy đổi 1 số giá trị sang rad như bằng cách nhân với hệ số 0.10472 
[Turtlebot](https://github.com/ROBOTIS-GIT/OpenCR/blob/master/arduino/opencr_arduino/opencr/libraries/turtlebot3/include/turtlebot3/turtlebot3_motor_driver.h)

![240779389_617990985833400_1602310391635025706_n](https://user-images.githubusercontent.com/82381342/131256905-b5aab0f6-99e4-4e83-9a84-b14f72fbb7b0.png)

    w = 100 * 0.10472 = 10.472

Tuy nhiên đây là Tutorial nên mình sẽ giải thích vì sao 

    f = 1.666666 v/s (như trên)
    T = 1/f = 1/1.666666 = 0.600(s)
    w = 2Pi/T = 6.24/0.60 = 10.4 Rad/s 
    

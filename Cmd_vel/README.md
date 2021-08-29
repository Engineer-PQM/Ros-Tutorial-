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

###  ⭐️  Linear.x

Giá trị quay tối đa của động cơ sau hộp giảm số 
 
    Rpm * (1/30) = 3000/30 = 100 vòng/phút 
    
Vì giá trị vận tốc tính toán là m/s 

    f = 100/60(s) = 1.666666 v/s
    
Chu Vi (C) với Pi ( ~ 3.14)

    (C) = d x Pi = 0.15 * 3.14 = 0.471 

Vận tốc tuyến tính 

    f * C = 1.666666 * 0.471 = 0.78499 m/s 


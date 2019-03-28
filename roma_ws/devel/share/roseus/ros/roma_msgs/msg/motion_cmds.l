;; Auto-generated. Do not edit!


(when (boundp 'roma_msgs::motion_cmds)
  (if (not (find-package "ROMA_MSGS"))
    (make-package "ROMA_MSGS"))
  (shadow 'motion_cmds (find-package "ROMA_MSGS")))
(unless (find-package "ROMA_MSGS::MOTION_CMDS")
  (make-package "ROMA_MSGS::MOTION_CMDS"))

(in-package "ROS")
;;//! \htmlinclude motion_cmds.msg.html


(defclass roma_msgs::motion_cmds
  :super ros::object
  :slots (_power _steer_ang _near_cone _cone_visible _opencv_error ))

(defmethod roma_msgs::motion_cmds
  (:init
   (&key
    ((:power __power) 0.0)
    ((:steer_ang __steer_ang) 0.0)
    ((:near_cone __near_cone) nil)
    ((:cone_visible __cone_visible) nil)
    ((:opencv_error __opencv_error) 0.0)
    )
   (send-super :init)
   (setq _power (float __power))
   (setq _steer_ang (float __steer_ang))
   (setq _near_cone __near_cone)
   (setq _cone_visible __cone_visible)
   (setq _opencv_error (float __opencv_error))
   self)
  (:power
   (&optional __power)
   (if __power (setq _power __power)) _power)
  (:steer_ang
   (&optional __steer_ang)
   (if __steer_ang (setq _steer_ang __steer_ang)) _steer_ang)
  (:near_cone
   (&optional __near_cone)
   (if __near_cone (setq _near_cone __near_cone)) _near_cone)
  (:cone_visible
   (&optional __cone_visible)
   (if __cone_visible (setq _cone_visible __cone_visible)) _cone_visible)
  (:opencv_error
   (&optional __opencv_error)
   (if __opencv_error (setq _opencv_error __opencv_error)) _opencv_error)
  (:serialization-length
   ()
   (+
    ;; float32 _power
    4
    ;; float32 _steer_ang
    4
    ;; bool _near_cone
    1
    ;; bool _cone_visible
    1
    ;; float32 _opencv_error
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _power
       (sys::poke _power (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _steer_ang
       (sys::poke _steer_ang (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _near_cone
       (if _near_cone (write-byte -1 s) (write-byte 0 s))
     ;; bool _cone_visible
       (if _cone_visible (write-byte -1 s) (write-byte 0 s))
     ;; float32 _opencv_error
       (sys::poke _opencv_error (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _power
     (setq _power (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steer_ang
     (setq _steer_ang (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _near_cone
     (setq _near_cone (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _cone_visible
     (setq _cone_visible (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _opencv_error
     (setq _opencv_error (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get roma_msgs::motion_cmds :md5sum-) "b8d7592f04e59bfb9ef4b6b5b23f809d")
(setf (get roma_msgs::motion_cmds :datatype-) "roma_msgs/motion_cmds")
(setf (get roma_msgs::motion_cmds :definition-)
      "float32 power
float32 steer_ang
bool near_cone
bool cone_visible
float32 opencv_error
")



(provide :roma_msgs/motion_cmds "b8d7592f04e59bfb9ef4b6b5b23f809d")



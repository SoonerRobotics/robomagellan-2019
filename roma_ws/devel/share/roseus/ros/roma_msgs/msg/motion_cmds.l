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
  :slots (_power _steer_ang ))

(defmethod roma_msgs::motion_cmds
  (:init
   (&key
    ((:power __power) 0.0)
    ((:steer_ang __steer_ang) 0.0)
    )
   (send-super :init)
   (setq _power (float __power))
   (setq _steer_ang (float __steer_ang))
   self)
  (:power
   (&optional __power)
   (if __power (setq _power __power)) _power)
  (:steer_ang
   (&optional __steer_ang)
   (if __steer_ang (setq _steer_ang __steer_ang)) _steer_ang)
  (:serialization-length
   ()
   (+
    ;; float32 _power
    4
    ;; float32 _steer_ang
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
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _power
     (setq _power (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steer_ang
     (setq _steer_ang (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get roma_msgs::motion_cmds :md5sum-) "4f545a067a10b78db31f8ffc31ecfca8")
(setf (get roma_msgs::motion_cmds :datatype-) "roma_msgs/motion_cmds")
(setf (get roma_msgs::motion_cmds :definition-)
      "float32 power
float32 steer_ang
")



(provide :roma_msgs/motion_cmds "4f545a067a10b78db31f8ffc31ecfca8")



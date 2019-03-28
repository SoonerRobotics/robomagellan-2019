;; Auto-generated. Do not edit!


(when (boundp 'roma_msgs::motion_feedback)
  (if (not (find-package "ROMA_MSGS"))
    (make-package "ROMA_MSGS"))
  (shadow 'motion_feedback (find-package "ROMA_MSGS")))
(unless (find-package "ROMA_MSGS::MOTION_FEEDBACK")
  (make-package "ROMA_MSGS::MOTION_FEEDBACK"))

(in-package "ROS")
;;//! \htmlinclude motion_feedback.msg.html


(defclass roma_msgs::motion_feedback
  :super ros::object
  :slots (_steer_ang ))

(defmethod roma_msgs::motion_feedback
  (:init
   (&key
    ((:steer_ang __steer_ang) 0.0)
    )
   (send-super :init)
   (setq _steer_ang (float __steer_ang))
   self)
  (:steer_ang
   (&optional __steer_ang)
   (if __steer_ang (setq _steer_ang __steer_ang)) _steer_ang)
  (:serialization-length
   ()
   (+
    ;; float32 _steer_ang
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _steer_ang
       (sys::poke _steer_ang (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _steer_ang
     (setq _steer_ang (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get roma_msgs::motion_feedback :md5sum-) "f280d41ee1efe0c343af20f8e2f5d9fa")
(setf (get roma_msgs::motion_feedback :datatype-) "roma_msgs/motion_feedback")
(setf (get roma_msgs::motion_feedback :definition-)
      "float32 steer_ang
")



(provide :roma_msgs/motion_feedback "f280d41ee1efe0c343af20f8e2f5d9fa")



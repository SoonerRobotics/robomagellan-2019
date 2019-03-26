;; Auto-generated. Do not edit!


(when (boundp 'roma_vision::obstacles)
  (if (not (find-package "ROMA_VISION"))
    (make-package "ROMA_VISION"))
  (shadow 'obstacles (find-package "ROMA_VISION")))
(unless (find-package "ROMA_VISION::OBSTACLES")
  (make-package "ROMA_VISION::OBSTACLES"))

(in-package "ROS")
;;//! \htmlinclude obstacles.msg.html


(defclass roma_vision::obstacles
  :super ros::object
  :slots (_angles _distances ))

(defmethod roma_vision::obstacles
  (:init
   (&key
    ((:angles __angles) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:distances __distances) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _angles __angles)
   (setq _distances __distances)
   self)
  (:angles
   (&optional __angles)
   (if __angles (setq _angles __angles)) _angles)
  (:distances
   (&optional __distances)
   (if __distances (setq _distances __distances)) _distances)
  (:serialization-length
   ()
   (+
    ;; float32[] _angles
    (* 4    (length _angles)) 4
    ;; float32[] _distances
    (* 4    (length _distances)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[] _angles
     (write-long (length _angles) s)
     (dotimes (i (length _angles))
       (sys::poke (elt _angles i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _distances
     (write-long (length _distances) s)
     (dotimes (i (length _distances))
       (sys::poke (elt _distances i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[] _angles
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _angles (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _angles i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _distances
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _distances (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _distances i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get roma_vision::obstacles :md5sum-) "4079861bcc588d6429dc8dce9e7ca922")
(setf (get roma_vision::obstacles :datatype-) "roma_vision/obstacles")
(setf (get roma_vision::obstacles :definition-)
      "float32[] angles
float32[] distances
")



(provide :roma_vision/obstacles "4079861bcc588d6429dc8dce9e7ca922")



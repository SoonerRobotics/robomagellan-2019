; Auto-generated. Do not edit!


(cl:in-package roma_msgs-msg)


;//! \htmlinclude motion_feedback.msg.html

(cl:defclass <motion_feedback> (roslisp-msg-protocol:ros-message)
  ((steer_ang
    :reader steer_ang
    :initarg :steer_ang
    :type cl:float
    :initform 0.0))
)

(cl:defclass motion_feedback (<motion_feedback>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <motion_feedback>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'motion_feedback)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name roma_msgs-msg:<motion_feedback> is deprecated: use roma_msgs-msg:motion_feedback instead.")))

(cl:ensure-generic-function 'steer_ang-val :lambda-list '(m))
(cl:defmethod steer_ang-val ((m <motion_feedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:steer_ang-val is deprecated.  Use roma_msgs-msg:steer_ang instead.")
  (steer_ang m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <motion_feedback>) ostream)
  "Serializes a message object of type '<motion_feedback>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer_ang))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <motion_feedback>) istream)
  "Deserializes a message object of type '<motion_feedback>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer_ang) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<motion_feedback>)))
  "Returns string type for a message object of type '<motion_feedback>"
  "roma_msgs/motion_feedback")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'motion_feedback)))
  "Returns string type for a message object of type 'motion_feedback"
  "roma_msgs/motion_feedback")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<motion_feedback>)))
  "Returns md5sum for a message object of type '<motion_feedback>"
  "f280d41ee1efe0c343af20f8e2f5d9fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'motion_feedback)))
  "Returns md5sum for a message object of type 'motion_feedback"
  "f280d41ee1efe0c343af20f8e2f5d9fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<motion_feedback>)))
  "Returns full string definition for message of type '<motion_feedback>"
  (cl:format cl:nil "float32 steer_ang~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'motion_feedback)))
  "Returns full string definition for message of type 'motion_feedback"
  (cl:format cl:nil "float32 steer_ang~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <motion_feedback>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <motion_feedback>))
  "Converts a ROS message object to a list"
  (cl:list 'motion_feedback
    (cl:cons ':steer_ang (steer_ang msg))
))

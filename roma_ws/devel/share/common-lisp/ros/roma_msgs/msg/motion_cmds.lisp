; Auto-generated. Do not edit!


(cl:in-package roma_msgs-msg)


;//! \htmlinclude motion_cmds.msg.html

(cl:defclass <motion_cmds> (roslisp-msg-protocol:ros-message)
  ((power
    :reader power
    :initarg :power
    :type cl:float
    :initform 0.0)
   (steer_ang
    :reader steer_ang
    :initarg :steer_ang
    :type cl:float
    :initform 0.0))
)

(cl:defclass motion_cmds (<motion_cmds>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <motion_cmds>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'motion_cmds)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name roma_msgs-msg:<motion_cmds> is deprecated: use roma_msgs-msg:motion_cmds instead.")))

(cl:ensure-generic-function 'power-val :lambda-list '(m))
(cl:defmethod power-val ((m <motion_cmds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:power-val is deprecated.  Use roma_msgs-msg:power instead.")
  (power m))

(cl:ensure-generic-function 'steer_ang-val :lambda-list '(m))
(cl:defmethod steer_ang-val ((m <motion_cmds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:steer_ang-val is deprecated.  Use roma_msgs-msg:steer_ang instead.")
  (steer_ang m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <motion_cmds>) ostream)
  "Serializes a message object of type '<motion_cmds>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'power))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer_ang))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <motion_cmds>) istream)
  "Deserializes a message object of type '<motion_cmds>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'power) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer_ang) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<motion_cmds>)))
  "Returns string type for a message object of type '<motion_cmds>"
  "roma_msgs/motion_cmds")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'motion_cmds)))
  "Returns string type for a message object of type 'motion_cmds"
  "roma_msgs/motion_cmds")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<motion_cmds>)))
  "Returns md5sum for a message object of type '<motion_cmds>"
  "4f545a067a10b78db31f8ffc31ecfca8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'motion_cmds)))
  "Returns md5sum for a message object of type 'motion_cmds"
  "4f545a067a10b78db31f8ffc31ecfca8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<motion_cmds>)))
  "Returns full string definition for message of type '<motion_cmds>"
  (cl:format cl:nil "float32 power~%float32 steer_ang~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'motion_cmds)))
  "Returns full string definition for message of type 'motion_cmds"
  (cl:format cl:nil "float32 power~%float32 steer_ang~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <motion_cmds>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <motion_cmds>))
  "Converts a ROS message object to a list"
  (cl:list 'motion_cmds
    (cl:cons ':power (power msg))
    (cl:cons ':steer_ang (steer_ang msg))
))

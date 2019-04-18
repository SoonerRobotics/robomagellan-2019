// Auto-generated. Do not edit!

// (in-package roma_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class motion_cmds {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.power = null;
      this.steer_ang = null;
    }
    else {
      if (initObj.hasOwnProperty('power')) {
        this.power = initObj.power
      }
      else {
        this.power = 0.0;
      }
      if (initObj.hasOwnProperty('steer_ang')) {
        this.steer_ang = initObj.steer_ang
      }
      else {
        this.steer_ang = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type motion_cmds
    // Serialize message field [power]
    bufferOffset = _serializer.float32(obj.power, buffer, bufferOffset);
    // Serialize message field [steer_ang]
    bufferOffset = _serializer.float32(obj.steer_ang, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type motion_cmds
    let len;
    let data = new motion_cmds(null);
    // Deserialize message field [power]
    data.power = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [steer_ang]
    data.steer_ang = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'roma_msgs/motion_cmds';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4f545a067a10b78db31f8ffc31ecfca8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 power
    float32 steer_ang
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new motion_cmds(null);
    if (msg.power !== undefined) {
      resolved.power = msg.power;
    }
    else {
      resolved.power = 0.0
    }

    if (msg.steer_ang !== undefined) {
      resolved.steer_ang = msg.steer_ang;
    }
    else {
      resolved.steer_ang = 0.0
    }

    return resolved;
    }
};

module.exports = motion_cmds;

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

class obstacles {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.angles = null;
      this.distances = null;
    }
    else {
      if (initObj.hasOwnProperty('angles')) {
        this.angles = initObj.angles
      }
      else {
        this.angles = [];
      }
      if (initObj.hasOwnProperty('distances')) {
        this.distances = initObj.distances
      }
      else {
        this.distances = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type obstacles
    // Serialize message field [angles]
    bufferOffset = _arraySerializer.float32(obj.angles, buffer, bufferOffset, null);
    // Serialize message field [distances]
    bufferOffset = _arraySerializer.float32(obj.distances, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type obstacles
    let len;
    let data = new obstacles(null);
    // Deserialize message field [angles]
    data.angles = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [distances]
    data.distances = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.angles.length;
    length += 4 * object.distances.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'roma_msgs/obstacles';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4079861bcc588d6429dc8dce9e7ca922';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[] angles
    float32[] distances
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new obstacles(null);
    if (msg.angles !== undefined) {
      resolved.angles = msg.angles;
    }
    else {
      resolved.angles = []
    }

    if (msg.distances !== undefined) {
      resolved.distances = msg.distances;
    }
    else {
      resolved.distances = []
    }

    return resolved;
    }
};

module.exports = obstacles;

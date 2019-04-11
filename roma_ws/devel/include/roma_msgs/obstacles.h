// Generated by gencpp from file roma_msgs/obstacles.msg
// DO NOT EDIT!


#ifndef ROMA_MSGS_MESSAGE_OBSTACLES_H
#define ROMA_MSGS_MESSAGE_OBSTACLES_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace roma_msgs
{
template <class ContainerAllocator>
struct obstacles_
{
  typedef obstacles_<ContainerAllocator> Type;

  obstacles_()
    : angles()
    , distances()  {
    }
  obstacles_(const ContainerAllocator& _alloc)
    : angles(_alloc)
    , distances(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _angles_type;
  _angles_type angles;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _distances_type;
  _distances_type distances;





  typedef boost::shared_ptr< ::roma_msgs::obstacles_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::roma_msgs::obstacles_<ContainerAllocator> const> ConstPtr;

}; // struct obstacles_

typedef ::roma_msgs::obstacles_<std::allocator<void> > obstacles;

typedef boost::shared_ptr< ::roma_msgs::obstacles > obstaclesPtr;
typedef boost::shared_ptr< ::roma_msgs::obstacles const> obstaclesConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::roma_msgs::obstacles_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::roma_msgs::obstacles_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace roma_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'roma_msgs': ['/home/jkleiber/robomagellan-2019/roma_ws/src/roma_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::roma_msgs::obstacles_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::roma_msgs::obstacles_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roma_msgs::obstacles_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roma_msgs::obstacles_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roma_msgs::obstacles_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roma_msgs::obstacles_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::roma_msgs::obstacles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4079861bcc588d6429dc8dce9e7ca922";
  }

  static const char* value(const ::roma_msgs::obstacles_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4079861bcc588d64ULL;
  static const uint64_t static_value2 = 0x29dc8dce9e7ca922ULL;
};

template<class ContainerAllocator>
struct DataType< ::roma_msgs::obstacles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "roma_msgs/obstacles";
  }

  static const char* value(const ::roma_msgs::obstacles_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::roma_msgs::obstacles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32[] angles\n\
float32[] distances\n\
";
  }

  static const char* value(const ::roma_msgs::obstacles_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::roma_msgs::obstacles_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.angles);
      stream.next(m.distances);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct obstacles_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::roma_msgs::obstacles_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::roma_msgs::obstacles_<ContainerAllocator>& v)
  {
    s << indent << "angles[]" << std::endl;
    for (size_t i = 0; i < v.angles.size(); ++i)
    {
      s << indent << "  angles[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.angles[i]);
    }
    s << indent << "distances[]" << std::endl;
    for (size_t i = 0; i < v.distances.size(); ++i)
    {
      s << indent << "  distances[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.distances[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROMA_MSGS_MESSAGE_OBSTACLES_H
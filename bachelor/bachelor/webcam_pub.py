# Basic ROS 2 program to publish real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
# only minor changes made by Anders Schack
  
# Import the necessary libraries
import rclpy # Python Client Library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
import cv2 #OpenCV library
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy
 
class WebcamPublisher(Node):
  """
  Create an WebcamPublisher class, which is a subclass of the Node class.
  """
  def __init__(self):
    """
    Class constructor to set up the node
    """
    # Initiate the Node class's constructor and give it a name
    super().__init__('Webcam_Publisher')
      
    # Create the publisher. This publisher will publish an Image
    # to the webcam topic. The queue size is 10 messages.
    qos = QoSProfile(reliability=QoSReliabilityPolicy.RELIABLE, history=QoSHistoryPolicy.KEEP_LAST, depth=1)
    self.publisher_ = self.create_publisher(Image, 'image_raw', qos)
      
    # We will publish a message every 0.1 seconds
    timer_period = 0.2  # seconds
      
    # Create the timer
    self.timer = self.create_timer(timer_period, self.timer_callback)
         
    # Create a VideoCapture object
    # The argument '0' gets the default webcam.
    self.cap = cv2.VideoCapture(0)
    self.cap.set(cv2.CAP_PROP_FPS, 5)
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()
   
  def timer_callback(self):
    """
    Callback function.
    This function gets called every 0.1 seconds.
    """
    # Capture frame-by-frame
    # This method returns True/False as well
    # as the video frame.
    ret, frame = self.cap.read()
          
    if ret == True:
      # Publish the image.
      # The 'cv2_to_imgmsg' method converts an OpenCV
      # image to a ROS 2 image message
      frame = cv2.resize(frame, None, fx=0.2, fy=0.1, interpolation=cv2.INTER_AREA)
      #frame = cv2.resize(frame, None, fx=10, fy=5, interpolation=cv2.INTER_AREA)
      self.publisher_.publish(self.br.cv2_to_imgmsg(frame))
 
    # Display the message on the console
    # self.get_logger().info('Publishing video frame')
    self.get_logger().info(str(self.get_clock().now().to_msg()))

def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  webcam_publisher = WebcamPublisher()
  
  # Spin the node so the callback function is called.
  rclpy.spin(webcam_publisher)
  
  # Destroy the node explicitly
  # (optional - otherwise it will be done automatically
  # when the garbage collector destroys the node object)
  webcam_publisher.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()

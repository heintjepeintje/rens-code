#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <utility>

int main(int argc, char **argv) {
	rclcpp::init(argc, argv); 

	// Initialize the ros api
	rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("custom_publisher_node");

	rclcpp::QoSInitialization qos_options = rclcpp::QoSInitialization(rmw_qos_history_policy_t::RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT, 1000);

	rclcpp::QoS subscription_qos = rclcpp::QoS(qos_options);

	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription = node->create_subscription<std_msgs::msg::String>(std::string("custom_topic"), subscription_qos, [](const std_msgs::msg::String::SharedPtr msg) {
		RCLCPP_INFO(rclcpp::get_logger("subscriber"), "Received message: %s", msg->data.c_str());
	});

	rclcpp::spin(node);
}
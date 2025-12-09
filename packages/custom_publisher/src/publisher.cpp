#include <rclcpp/node.hpp>
#include <std_msgs/msg/string.hpp>
#include <utility>

int main(int argc, char **argv) {
	rclcpp::init(argc, argv); 

	// Initialize the ros api
	rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("custom_publisher_node");

	rclcpp::QoSInitialization qos_options = rclcpp::QoSInitialization(rmw_qos_history_policy_t::RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT, 1000);

	rclcpp::QoS publisher_qos = rclcpp::QoS(qos_options);

	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher = node->create_publisher<std_msgs::msg::String>(std::string("custom_topic"), publisher_qos);

	rclcpp::Rate limiter(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(100)));

	uint32_t count = 0;

	while (rclcpp::ok()) {
		std_msgs::msg::String message;

		std::stringstream stream;
		stream << "Hello World (" << count << ")";
		message.data = stream.str();

		RCLCPP_INFO(rclcpp::get_logger("custom_publisher"), "published: \"%s\"", message.data.c_str());

		publisher->publish(message);

		count++;

		limiter.sleep();
	}
}
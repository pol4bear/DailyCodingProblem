#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Node {
public:
	Node()
	{

	}

	Node(int value_in, Node* left_in = nullptr, Node* right_in = nullptr)
	{
		value = value_in;
		left = left_in;
		right = right_in;
	}

	static constexpr int NULL_NODE = -1;

	int value;
	Node *left;
	Node *right;
};

void serialize(Node* node, ofstream& file_out)
{
	file_out.write((char*)& node->value, sizeof(node->value));

	if (node->left != nullptr)
		serialize(node->left, file_out);
	else
		file_out.write((char*)& Node::NULL_NODE, sizeof(node->value));
	if (node->right != nullptr)
		serialize(node->right, file_out);
	else
		file_out.write((char*)& Node::NULL_NODE, sizeof(node->value));
}

void serialize(Node *node, string file_name)
{
	// Open file to save serialized data
	ofstream file_out(file_name, ios::out | ios::binary);
	if (!file_out.is_open())
		throw invalid_argument("Cannot create file " + file_name + ". Check your permission.");

	// Write serialized data to the file
	serialize(node, file_out);

	// Close file
	file_out.close();
}

Node* deserialize(uint8_t* data, int &index)
{
	Node* node = new Node();

	int* current_node = (int*)(data + index);
	index += sizeof(node->value);

	if (*current_node == -1) {
		delete node;

		return nullptr;
	}
		
	node->value = *current_node;
	
	int* left_node = (int*)(data + index);;
	if (*left_node == -1) {
		node->left = nullptr;
		index += sizeof(node->value);
	}
	else {
		node->left = deserialize(data, index);
	}

	int* right_node = (int*)(data + index);;
	if (*right_node == -1) {
		node->right = nullptr;
		index += sizeof(node->value);
	}
	else {
		node->right = deserialize(data, index);
	}

	return node;
}

Node* deserialize(string file_name)
{
	// Open file to read serialized data
	ifstream file_in(file_name, ios::in | ios::binary);
	if (!file_in.is_open())
		throw invalid_argument("Cannot open file " + file_name + ". Check your permission.");

	// Read data to end
	string data((istreambuf_iterator<char>(file_in)), (istreambuf_iterator<char>()));

	// Close file
	file_in.close();

	int index = 0;
	return deserialize((uint8_t*)data.c_str(), index);
}



void distroy(Node *node) {
	if (node->left != nullptr)
		distroy(node->left);
	if (node->right != nullptr)
		distroy(node->right);

	free(node);
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " [serialized file]\n";
		exit(1);
	}

	try {
		Node* node = new Node(0, new Node(1, new Node(3), nullptr), new Node(2, nullptr, new Node(4)));
		string file_name = string(argv[1]);

		serialize(node, file_name);

		// Distory node recursively
		distroy(node);

		// Read serialized data and deserialize
		node = deserialize(file_name);

		// Distroy node recursievely	
		distroy(node);
	}
	catch (invalid_argument e) {
		cerr << e.what() << "\n";
	}

	exit(0);
}
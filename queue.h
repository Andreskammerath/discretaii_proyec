struct Node {
	int data;
	struct Node *next;
};
 
typedef struct Queue {
	struct Node *front;
	struct Node *last;
	unsigned int size;
} Queue;
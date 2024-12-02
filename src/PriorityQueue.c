typedef struct ListNode {
	int val;
	int from;
	int to;
	struct ListNode* next;
} ListNode;

typedef struct PriorityQueue {
	int size;
	ListNode* items;
} PriorityQueue;

PriorityQueue* create_queue() {
	PriorityQueue* q = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	if (!q) {
		printf("Could not initialize Priority Queue!");
		return NULL;
	}
	q->size = 0;
	q->items = NULL;

	return q;
}

void enqueue(PriorityQueue* q, int val, int from, int to) {
	if (!q) {
		printf("No queue provided!\n");
		return;
	}

	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->val = val;
	newNode->from = from;
	newNode->to = to;
	newNode->next = NULL;

	q->size++;

	// If the queue is empty, insert as the first node
	if (q->items == NULL) {
		q->items = newNode;
		return;
	}

	ListNode* currNode = q->items;

	// If the new node has a higher priority (lower value) than the head
	if (val < currNode->val) {
		newNode->next = currNode;
		q->items = newNode; // Update the head of the list
		return;
	}

	// Traverse the list to find the correct position
	while (currNode->next != NULL && currNode->next->val <= val) {
		currNode = currNode->next;
	}

	// Insert the new node in the correct position
	newNode->next = currNode->next;
	currNode->next = newNode;
}


ListNode* dequeue(PriorityQueue* q) {
	if (!q) {
		printf("No queue provided!\n");
		return;
	}

	if (q->items == NULL) {
		printf("Queue is empty!\n");
		return NULL;
	}

	q->size--;
	ListNode* head = q->items;
	q->items = head->next;
	return head;
}

void printQueue(PriorityQueue* q) {
	ListNode* currNode = q->items;

	printf("Queue: ");
	while (currNode != NULL) {
		printf("(%4d, %4d, %4d)->", currNode->from, currNode->to, currNode->val);

		currNode = currNode->next;
	}
	printf("NULL\n");
}
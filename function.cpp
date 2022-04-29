#include "function.h"
#include <iostream>
#include <string>

using namespace std;

Node::Node(std::string id, u32 time) : id(id), time(time){}

std::string Node::get_id()
{
	return id;
}

u32 Node::get_time()
{
	return time;
}

void Node::set_time(u32 time)
{
    Node::time = time;
}

// [TODO]: Implement Operator Overloading for Node.
// Check if the time of node1 is equal to the time of node2.
bool operator== (Node& node1, Node& node2){return node1.get_time()==node2.get_time();};
// Check if the time of node1 is not equal to the parameter time.
bool operator== (Node& node1, u32 time){return node1.get_time()==time;};

// Check if the time of node1 is not equal to the time of node2.
bool operator!= (Node& node1, Node& node2){return node1.get_time()!=node2.get_time();};
// Check if the time of node1 is not equal to the parameter time.
bool operator!= (Node& node1, u32 time){return node1.get_time()!=time;};

/*
Check if the time of node1 is less than the time of node2.
If the time of node1 is equal to node2, check if the id of node1 is less than the id of node2.
*/
bool operator< (Node& node1, Node& node2){
	if(node1.get_time()==node2.get_time()){
	return node1.get_id() < node2.get_id();}
	else{return node1.get_time() < node2.get_time();}
	}
// Check if the time of node1 is less than the parameter time.
bool operator< (Node& node1, u32 time){return node1.get_time() < time;};
/*
Check if the time of node1 is greater than node2.
If the time of node1 is equal to node2, check if the id of node1 is greater than the id of node2.
*/
bool operator> (Node& node1, Node& node2){
	if(node1.get_time()==node2.get_time()){
	return node1.get_id() > node2.get_id();}
	else{return node1.get_time() > node2.get_time();}
	}
// Check if the time of node1 is greater than the parameter time.
bool operator> (Node& node1, u32 time){return node1.get_time() > time;};

// Check if the time of node1 is not greater than node2.
bool operator<= (Node& node1, Node& node2){
	return node1.get_time() <= node2.get_time();
	}
// Check if the time of node1 is not greater than the parameter time.
bool operator<= (Node& node1, u32 time){
	return node1.get_time() <= time;
	}

// Check if the time of node1 is not less than node2.
bool operator>= (Node& node1, Node& node2){
	return node1.get_time() >= node2.get_time();
	}
// Check if the time of node1 is not less than the parameter time.
bool operator>= (Node& node1, u32 time){
	return node1.get_time() >= time;
	}

// Add the parameter time to the time of node.
void operator+= (Node& node1,u32 time){
	node1.set_time(node1.get_time() + time);
};

template < class T >
u32 BinaryHeap<T>::parent_idx(u32 idx){
    if(idx != 1) return idx / 2;
    else return 1;
};

template < class T >
u32 BinaryHeap<T>::left_idx(u32 idx){
    //if(idx*2 <= heap.size())
    return idx * 2;
};

template < class T >
u32 BinaryHeap<T>::right_idx(u32 idx){
    //if(idx*2+1 <= heap.size())
    return idx * 2 + 1;
};

template < class T >
void BinaryHeap<T>::heapify_down(int idx){
    u32 left = left_idx(idx);
    u32 right = right_idx(idx);
    u32 smallest = idx;
    if(left < heap.size() and heap[left] < heap[idx]){
        smallest = left;
    }
    if(right < heap.size() and heap[right] < heap[smallest]){
        smallest = right;
    }
    if(smallest != idx){
        cout << "SWITCH" << endl;
        std::swap(heap[idx], heap[smallest]);
        heapify_down(smallest);
    }
};

template < class T >
u32 BinaryHeap<T>::size()
{
    return heap.size();
}

template < class T >
void BinaryHeap<T>::insert(T element){
    if(heap.size() == 0){
        heap.push_back(element);
    }
    heap.push_back(element);
    u32 idx1 = heap.size()-1;
    while(heap[idx1] < heap[parent_idx(idx1)]){
        std::swap(heap[idx1], heap[parent_idx(idx1)]);
        idx1 = parent_idx(idx1);
    }
};

template < class T >
void BinaryHeap<T>::del_min(){
    std::swap(heap[heap.size()-1], heap[1]);
    heap.pop_back();
    heapify_down(1);
};

template < class T >
T BinaryHeap<T>::get_min(){
    if(heap.size() > 1) return heap[1];
};


u32 currentTime = 0;


template < class T >
int Manager<T>::finish_in_time(u32 costTime,u32 deadLine)
{
    if(taQue.size() < 1){
        return 0;
    }
    else{
        return (costTime + taQue.get_min().get_time() < deadLine) and (taQue.get_min().get_time() < endTime - costTime);
    }
};


template < class T >
void Manager<T>::cmd_set_endTime(u32 endTime)
{
    if(endTime > currentTime){
        Manager::endTime = endTime;
        cout << "SET_ENDTIME SUCCESS" << endl;
    }
    else{
        cout << "SET_ENDTIME FAIL" << endl;
    }
};  // time complexity: O(n)

template < class T >
void Manager<T>::cmd_add_task(string taskName, u32 costTime)
{
    if(finish_in_time(costTime, endTime)){
        u32 tmp_time = taQue.get_min().get_time() + costTime;
        std::string tmp_id = taQue.get_min().get_id();
        if(tmp_time > currentTime){currentTime = tmp_time;}
        Node newNode(tmp_id, tmp_time);
        taQue.del_min();
        taQue.insert(newNode);
        cout << "ADD_TASK " << taskName << ": " << tmp_id << " AT " << tmp_time << endl;
    }
    else{
        cout << "ADD_TASK " << taskName << ": FAIL" << endl;
    }
};    // time complexity: O(log n)

template < class T >
void Manager<T>::cmd_add_ta(std::string id, u32 begin)
{
    if(begin < endTime){
        if(begin > currentTime){currentTime = begin;}
        Node newTA = Node(id, begin);
        taQue.insert(newTA);
        cout << "ADD_TA SUCCESS" << endl;
    }
    else{
        cout << "ADD_TA FAIL" << endl;
    }
};

template < class T >
void Manager<T>::cmd_check_schedule(u32 costTime,u32 deadLine)
{
    if(taQue.size() < 1){
        cout << "CHECK_SCHEDULE: NO TA WARNING!" << endl;
    }
    else if(finish_in_time(costTime, deadLine)){
        cout << "CHECK_SCHEDULE: CAN FINISH!" << endl;
    }
    else{
        cout << "CHECK_SCHEDULE: OVERTIME WARNING!" << endl;
    }
};

template < class T >
void Manager<T>::result()
{
    if(taQue.size() > 1){
        cout << "NUMBER_TA: " << taQue.size()-1 << endl;
        cout << "EARLIEST FINISH TA: " << taQue.get_min().get_id() << " AT " << taQue.get_min().get_time() << endl;
    }
    else{
        cout << "NUMBER_TA: 0" << endl;
    }
};

template < class T >
Manager<T>::Manager(){
	endTime = 4294967295;
};

template class Manager<Node>;

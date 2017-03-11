#include <iostream>
using namespace std;

class Heap {
private:
	int* arr;
	int lastIdx;
	bool(*compare)(int, int);
public:
	Heap(int*arr, int length, bool(*fptr)(int, int)) {
		this->arr = arr;
		lastIdx = length - 1;
		compare = fptr;
	}

	Heap(int size,bool (*fptr)(int,int)) {
		arr = new int[size + 1];
		lastIdx = 0;
		compare = fptr;
	}

	bool isEmpty() {
		if (lastIdx <= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool hasChild(int index) {
		if (index * 2 > lastIdx) {
			return false;
		}
		else {
			return true;
		}
	}

	int getNumOfChild(int index) {
		if (index * 2 > lastIdx) {
			return 0;
		}
		else if (index * 2 == lastIdx) {
			return 1;
		}
		else { // index*2 < lastIdx
			return 2;
		}
	}

	int getPriChildIdx(int index) {
		int childNum = getNumOfChild(index);

		switch (childNum) {
		case 0:
			return -1;
			break;
		case 1:
			return getLeftChildIdx(index);
			break;
		case 2:
			if (compare(arr[getLeftChildIdx(index)], arr[getRightChildIdx(index)])) {
				return getLeftChildIdx(index);
			}
			else {
				return getRightChildIdx(index);
			}
			break;
		}
	}

	int getParentIdx(int index) {
		return index / 2;
	}

	int getLeftChildIdx(int index) {
		return 2 * index;
	}

	int getRightChildIdx(int index) {
		return 2 * index + 1;
	}

	void add(int data) {
		if (isEmpty()) {
			arr[1] = data;
			lastIdx++;
			return;
		}

		lastIdx += 1;
		int curIdx = lastIdx;
		while (true) {
			int parentIdx = getParentIdx(curIdx);
			if (curIdx == 1 || !compare(data, arr[parentIdx])) {
				arr[curIdx] = data;
				break;
			}
			else {
				arr[curIdx] = arr[parentIdx];
				curIdx = parentIdx;
			}
		}
	}

	void heapify(int idx) {
		int value = arr[idx];
		while (true) {
			if (!hasChild(idx) || compare(value, arr[getPriChildIdx(idx)])) {
				arr[idx] = value;
				break;
			}
			else {
				arr[idx] = arr[getPriChildIdx(idx)];
				idx = getPriChildIdx(idx);
			}
		}
	}

	int pop() {
		const int returnValue = arr[1];
		int data = arr[lastIdx];
		lastIdx--;
		if (isEmpty()) {
			return returnValue;
		}
		int curIdx = 1;
		while (true) {
			if (!hasChild(curIdx) || compare(data, arr[getPriChildIdx(curIdx)])) {
				arr[curIdx] = data;
				break;
			}
			else {
				arr[curIdx] = arr[getPriChildIdx(curIdx)];
				curIdx = getPriChildIdx(curIdx);
			}
		}
		return returnValue;
	}

	void buildHeap() {
		int start = lastIdx / 2;
		for (int i = start; i >= 1; i--) {
			heapify(i);
		}
	}

	int extractHeap() {
		int returnValue = arr[1];
		arr[1] = arr[lastIdx];
		lastIdx--;
		heapify(1);
		return returnValue;
	}

	void heapSort() {
		int length = lastIdx + 1;
		for (int i = lastIdx; i >= 1; i--) {
			arr[i] = extractHeap();
		}
	}
};
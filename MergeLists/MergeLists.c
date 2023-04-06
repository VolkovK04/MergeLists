#include <stdlib.h>
#include <stdio.h>


struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct {
    int* data;
    int len;
    int cap;
} Heap;

void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("Out of memory!");
        exit(0);
    }
}

Heap* heapCreate() {
    int cap = 16;
    int len = 0;
    int* ptr = (int*)malloc(cap * sizeof(int));
    nullCheck(ptr);
    Heap* res = (Heap*)malloc(sizeof(Heap));
    *res = (Heap){
        .data = ptr,
        .len = len,
        .cap = cap
    };
    return res;
}

void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void heapPush(Heap* obj, int val) {
    obj->len++;
    if (obj->len > obj->cap) {
        obj->cap *= 2;
        obj->data = (int*)realloc(obj->data, obj->cap * sizeof(int));
        nullCheck(obj->data);
    }
    int index = obj->len - 1;
    obj->data[index] = val;
    while (1) {
        int parent = (index - 1) / 2;
        if (parent < 0) {
            return;
        }
        if (obj->data[parent] > obj->data[index]) {
            swap(obj->data + parent, obj->data + index);
        }
        else {
            return;
        }
        index = parent;
    }
}

int heapPop(Heap* obj) {
    int result = obj->data[0];
    obj->len--;
    int index = 0;
    obj->data[index] = obj->data[obj->len];
    while (1) {
        int minIndex = 2 * index + 1;
        if (minIndex >= obj->len) {
            return result;
        }
        if (minIndex + 1 < obj->len) {
            if (obj->data[minIndex] > obj->data[minIndex + 1]) {
                minIndex++;
            }
        }
        if (obj->data[index] > obj->data[minIndex]) {
            swap(obj->data + index, obj->data + minIndex);
        }
        else {
            return result;
        }
        index = minIndex;
    }
}


void heapFree(Heap* obj) {
    free(obj->data);
    free(obj);
}

void printArr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    Heap* heap = heapCreate();
    for (int i = 0; i < listsSize; i++) {
        struct ListNode* list = lists[i];
        while (list != NULL) {
            heapPush(heap, list->val);
            list = list->next;
        }
    }
    if (heap->len == 0) {
        return NULL;
    }
    //printArr(heap->data, heap->len);
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    nullCheck(node);
    struct ListNode* result = node;
    node->val = heapPop(heap);
    while (heap->len != 0) {
        node->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        node = node->next;
        nullCheck(node);
        node->val = heapPop(heap);
    }
    node->next = NULL;
    heapFree(heap);
    return result;
}

void scanList(struct ListNode* list) {
    int x;
    scanf_s("%d", &x);
    if (x == 0) {
        return;
    }
    list->val = x;
    while (1) {
        scanf_s("%d", &x);
        if (x == 0) {
            break;
        }
        list->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        list = list->next;
        nullCheck(list);
        list->val = x;
    }
    list->next = NULL;
}

void printList(struct ListNode* list) {
    while (list != NULL) {
        printf("%d\n", list->val);
        list = list->next;
    }
}

int main() {
    struct ListNode* list1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    printf("input list1:\n");
    scanList(list1);
    struct ListNode* list2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    printf("input list2:\n");
    scanList(list2);
    struct ListNode* list3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    printf("input list3:\n");
    scanList(list3);
    struct ListNode** arr = (struct ListNode**)malloc(3 * sizeof(struct ListNode*));
    nullCheck(arr);
    arr[0] = list1;
    arr[1] = list2;
    arr[2] = list3;

    struct ListNode* output = mergeKLists(arr, 3);
    printf("output list:\n");
    printList(output);

    return 0;
}
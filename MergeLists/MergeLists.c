typedef struct {
    int val;
    int listIndex;
} Pair;

typedef struct {
    Pair* data;
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
    Pair* ptr = (Pair*)malloc(cap * sizeof(Pair));
    nullCheck(ptr);
    Heap* res = (Heap*)malloc(sizeof(Heap));
    *res = (Heap){
        .data = ptr,
        .len = len,
        .cap = cap
    };
    return res;
}

void swap(Pair* a, Pair* b) {
    Pair c = *a;
    *a = *b;
    *b = c;
}

void heapPush(Heap* obj, Pair val) {
    obj->len++;
    if (obj->len > obj->cap) {
        obj->cap *= 2;
        obj->data = (Pair*)realloc(obj->data, obj->cap * sizeof(Pair));
        nullCheck(obj->data);
    }
    int index = obj->len - 1;
    obj->data[index] = val;
    while (1) {
        int parent = (index - 1) / 2;
        if (parent < 0) {
            return;
        }
        if (obj->data[parent].val > obj->data[index].val) {
            swap(obj->data + parent, obj->data + index);
        }
        else {
            return;
        }
        index = parent;
    }
}

Pair heapPop(Heap* obj) {
    Pair result = obj->data[0];
    obj->len--;
    int index = 0;
    obj->data[index] = obj->data[obj->len];
    while (1) {
        int minIndex = 2 * index + 1;
        if (minIndex >= obj->len) {
            return result;
        }
        if (minIndex + 1 < obj->len) {
            if (obj->data[minIndex].val > obj->data[minIndex + 1].val) {
                minIndex++;
            }
        }
        if (obj->data[index].val > obj->data[minIndex].val) {
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

void printArr(Pair* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("<%d %d>, ", arr[i].val, arr[i].listIndex);
    }
    printf("\n");
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    Heap* heap = heapCreate();
    for (int i = 0; i < listsSize; i++) {
        struct ListNode* list = lists[i];
        if (list != NULL)
        heapPush(heap, (Pair){
            .val = list->val,
            .listIndex = i
            });
    }
    if (heap->len == 0) {
        return NULL;
    }
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    nullCheck(node);
    struct ListNode* result = node;
    Pair pair = heapPop(heap);
    node->val = pair.val;
    int ind = pair.listIndex;
    lists[ind] = lists[ind]->next;
    if (lists[ind] != NULL) {
        struct ListNode* list = lists[ind];
        heapPush(heap, (Pair){
            .val = list->val,
            .listIndex = ind
        });
    }
    while (heap->len != 0) {
        node->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        node = node->next;
        nullCheck(node);
        pair = heapPop(heap);
        node->val = pair.val;
        ind = pair.listIndex;
        lists[ind] = lists[ind]->next;
        if (lists[ind] != NULL) {
            struct ListNode* list = lists[ind];
            heapPush(heap, (Pair){
                .val = list->val,
                .listIndex = ind
            });
        }
    }
    node->next = NULL;
    heapFree(heap);
    return result;
}
